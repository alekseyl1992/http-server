#include "Server.h"

#include <iostream>

Server::Server(const Config &config)
    : config(config)
    , fileSupplier(config.root)
    , servicePool(config.threadPoolSize)
{
}

Server::~Server()
{
    servicePool.stopAll();
}

void Server::start()
{
    servicePool.startAll();

    std::cout << "Server started with configuration:"
              << std::endl
              << config.toString()
              << std::endl;
}

void Server::stop()
{
    std::cout << "Server stopped" << std::endl;;
}
