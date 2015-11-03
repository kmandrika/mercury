#include <cstdlib>
#include <iostream>
#include "mercury/registrar/registrar.h"

mercury::registrar::registrar::registrar(const std::string& path)
    : path_(path)
{
}

mercury::registrar::registrar::~registrar()
{
}

int mercury::registrar::registrar::start()
{
    std::cout << "Starting mercuryd, listening to \"" << path_ << "\"" << std::endl;

    return EXIT_SUCCESS;
}
