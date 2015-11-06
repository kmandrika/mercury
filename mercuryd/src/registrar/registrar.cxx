#include "mercury/config.h"

#include <cerrno>
#include <cstdlib>
#include <iostream>
#include <cstring>

#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>

#include <unistd.h>

#include "mercury/registrar/registrar.h"

mercury::registrar::registrar::registrar(const std::string& path)
    : path_(path)
{
    log_.start();
}

mercury::registrar::registrar::~registrar()
{
}

namespace mercury { namespace detail {


}}

int mercury::registrar::registrar::start()
{
    log_(__I("Starting registrar..."));
    log_(__I("Listening for clients on %s", path_.c_str()));

    admin_ = std::thread(std::bind(admin_loop, this));
    admin_.join();

    return EXIT_SUCCESS;
}

int mercury::registrar::registrar::stop()
{
    return EXIT_SUCCESS;
}

void mercury::registrar::registrar::handle(const char* command)
{
}

namespace mercury { namespace detail {

//! managed_descriptor -----------------------------------------------------------------------------

struct managed_descriptor {
    managed_descriptor(int fd);
   ~managed_descriptor();

    int get() const;
private:
    int fd_;
};

//! implementation ---------------------------------------------------------------------------------

managed_descriptor::managed_descriptor(int fd) : fd_(fd)
{
}

managed_descriptor::~managed_descriptor()
{
    if (fd_ != -1) { close(fd_); }
}

int managed_descriptor::get() const
{
    return fd_;
}

managed_descriptor make_socket_channel(log::log_t& log, const std::string& path)
{
    struct sockaddr_un address;
    int fd;

    if ((fd = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
        log(__E("socket() failed with %s", strerror(errno)));
        return -1;
    }

    address.sun_family = AF_UNIX;
    strcpy(address.sun_path, path.c_str());
    unlink(address.sun_path);

    auto length = strlen(address.sun_path) + sizeof (address.sun_family);

    log(__I("Attempting to bind to %s", path.c_str()));

    if (::bind(fd, (struct sockaddr *)&address, length) == -1) {
        log(__E("bind() failed; %s", strerror(errno)));
        return managed_descriptor(-1);
    }

    if (::listen(fd, 5) == -1) {
        log(__E("listen() failed; %s", strerror(errno)));
        return managed_descriptor(-1);
    }

    return managed_descriptor(fd);
}

struct buffer { char value[256]; };

template<size_t N>
inline int read(log::log_t& log, const managed_descriptor& from, char (&buffer)[N])
{
    managed_descriptor connection = accept(from.get(), NULL, NULL);

    if (connection.get() == -1) {
        log(__W("Couldn't accept connection; %s", strerror(errno)));
        return -1;
    }

    std::memset(buffer, 0, N);
    int read;
    while ((read = ::read(connection.get(), buffer, sizeof (buffer))) >= 0) {
        log(__E("Couldn't read from accepted connection; %s", strerror(errno)));
        return -1;
    }

    return read;
}

}} // namespace detail/mercury

void mercury::registrar::registrar::admin_loop(registrar* self)
{
    detail::managed_descriptor descriptor = detail::make_socket_channel(self->log_, self->path_);
    detail::buffer buffer;

    if (descriptor.get() == -1) {
        self->log_(__E("Couldn't establish an admin channel, quitting..."));
        self->stop();
        return;
    }

    for (;;) {
        if (detail::read(self->log_, descriptor, buffer.value) != -1) {
            self->handle(buffer.value);
            continue;
        }

        break;
    }

    self->stop();
}
