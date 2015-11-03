#include "mercury/config.h"

#include <cstdlib>
#include <iostream>

#include "mercury/registrar/registrar.h"

mercury::registrar::registrar::registrar(const std::string& path)
    : path_(path)
{
    log_.start();
}

mercury::registrar::registrar::~registrar()
{
}

int mercury::registrar::registrar::start()
{
    log_(INFO("Starting registrar..."));
    log_(INFO("Listening for clients on %s", path_.c_str()));

    return EXIT_SUCCESS;
}
