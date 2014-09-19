#include <iostream>

#include "server/config/ConfigParser.h"
#include "server/config/ConfigOpenError.h"
#include "server/config/ConfigParseError.h"

#include "server/Server.h"

#ifndef TESTS_RUN
int main(int argc, char* argv[])
{
    std::cout << "Configuring..." << std::endl;

    Config config;
    try {
        if (argc > 1)
            config = ConfigParser::load(argv[1]);
        else
            config = ConfigParser::load();
    }
    catch (const ConfigOpenError &e) {
        std::cerr << "Unable to open config file. Falling back to default config.";
        std::cerr << std::endl;
    }
    catch (const ConfigParseError &e) {
        std::cerr << "Unable to parse config file. Exiting now.";
        std::cerr << std::endl;
        return -1;
    }

    std::cout << "Starting server..." << std::endl;

    Server server(config);
    server.start();

    std::cout << "Server stopped!" << std::endl;
}
#endif
