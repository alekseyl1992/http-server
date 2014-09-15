#include "Server.h"

#include <iostream>
#include <boost/bind.hpp>

Server::Server(const Config &config)
    : config(config)
    , fileSupplier(config.root, config.index)
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

    acceptor = std::make_shared<asio::ip::tcp::acceptor>(
                servicePool.getService(),
                asio::ip::tcp::endpoint(
                    asio::ip::tcp::v4(),
                    config.port));

    acceptNextClient();

    std::cout << "Server started with configuration:"
              << std::endl
              << config.toString()
              << std::endl;
}

void Server::stop()
{
    std::cout << "Server stopped" << std::endl;
}

void Server::acceptHandler(boost::shared_ptr<Connection> connection,
                   const boost::system::error_code& error)
{
    if (!error) {
        std::cout << "Client accepted!" << std::endl;

        connection->start();
        acceptNextClient();
    }
}

void Server::acceptNextClient() {
    auto connection = Connection::create(servicePool.getService(), fileSupplier);
    acceptor->async_accept(connection->getSocket(),
                          boost::bind(&Server::acceptHandler,
                                      this,
                                      connection,
                                      asio::placeholders::error));
}
