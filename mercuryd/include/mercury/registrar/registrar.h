#ifndef __MERCURY_REGISTRAR_REGISTRAR_H__
#define __MERCURY_REGISTRAR_REGISTRAR_H__

#include <thread>

#include "mercury/config.h"
#include "mercury/log/log.h"

#include <string>

namespace mercury { namespace registrar {

//! registrar --------------------------------------------------------------------------------------

struct registrar {
public:
    registrar(const std::string& path);
   ~registrar();

    int start();
    int stop();

    static void admin_loop(registrar* self);

    void handle(const char* command);
private:
    const std::string&     path_;
    log::log_t             log_;


    std::thread            client_;
    std::thread            servier_;
    std::thread            admin_;
    std::thread            gc_;
};

}}

#endif //__MERCURY_REGISTRAR_REGISTRAR_H__
