#include <iostream>
#include <string>

#include "mercury/options/options.h"

#include <boost/program_options.hpp>

namespace opts = boost::program_options;
namespace mercury {

//! Extract command-line options
void parse_options(const opts::variables_map& vm, options& options)
{
}

int start(const options& options)
{
    return EXIT_SUCCESS;
}

} // namespace mercury

int main(int argc, char* argv[])
{
    opts::options_description desc("Usage: mercuryd [OPTION(S)]");
    desc.add_options()
            ("help",                             "display this help message")
            ("path", opts::value<std::string>(), "path via which clients will connect");
    opts::variables_map vm;
    opts::store(opts::parse_command_line(argc, argv, desc), vm);
    opts::notify(vm);

    if (vm.count("help") || argc == 1) {
        std::cout << desc << std::endl;
        return 0;
    }

    mercury::options options;
    mercury::parse_options(vm, options);

    return mercury::start(options);
}
