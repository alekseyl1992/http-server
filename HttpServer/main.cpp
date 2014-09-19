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
        config = ConfigParser::load();
    } catch (const ConfigOpenError &e) {
        std::cerr << "Unable to open config file. Falling back to default config.";
        std::cerr << std::endl;
    } catch (const ConfigParseError &e) {
        std::cerr << "Unable to parse config file. Exiting now.";
        std::cerr << std::endl;
        return -1;
    }

    std::cout << "Starting server..." << std::endl;

    Server server(config);
    server.start();

//    std::cout << "Press any enter to stop..." << std::endl;
//    std::cin.get();

//    std::cout << "Stopping server..." << std::endl;;
//    server.stop();
}
#endif
