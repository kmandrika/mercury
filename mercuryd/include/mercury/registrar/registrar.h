#ifndef __MERCURY_REGISTRAR_REGISTRAR_H__
#define __MERCURY_REGISTRAR_REGISTRAR_H__

#include "mercury/config.h"
#include "mercury/log/log.h"

#include <string>

namespace mercury { namespace registrar {

struct registrar {
public:
    registrar(const std::string& path);
   ~registrar();

    int start();

private:
    const std::string&     path_;
    log::log_t             log_;
};

}}

#endif //__MERCURY_REGISTRAR_REGISTRAR_H__
