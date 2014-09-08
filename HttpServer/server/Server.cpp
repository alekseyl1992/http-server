#include "Server.h"

#include <iostream>

Server::Server(const Config &config)
    : config(config), supplier(config.root)
{
}

Server::~Server()
{

}

void Server::start()
{


    std::cout << "Server started with configuration:"
              << std::endl
              << config.toString()
              << std::endl;
}

void Server::stop()
{
    std::cout << "Server stopped" << std::endl;;
}
