#include "Server.h"

#include <iostream>
#include <boost/bind.hpp>
#include <boost/make_shared.hpp>

Server::Server(const Config &config)
    : config(config)
    , fileSupplier(config.root, config.index)
    , servicePool(config.threadPoolSize)
{
}

Server::~Server()
{
    stop();
}

void Server::start()
{
    acceptor = boost::make_shared<asio::ip::tcp::acceptor>(
                servicePool.getService(),
                asio::ip::tcp::endpoint(
                    asio::ip::tcp::v4(),
                    config.port));

    _signals = boost::make_shared<boost::asio::signal_set>(servicePool.getService());
    _signals->add(SIGINT);
    _signals->add(SIGTERM);
#ifdef SIGQUIT
    _signals->add(SIGQUIT);
#endif
    init_signal_handlers();

    acceptNextClient();

    std::cout << "Server started with configuration:"
              << std::endl
              << config.toString()
              << std::endl;

    servicePool.startAll();
}

void Server::init_signal_handlers()
{
    _signals->async_wait(
    [this](boost::system::error_code /*ec*/, int /*signo*/) {
        stop();
    });
}

void Server::stop()
{
    std::cout << "Server stopped" << std::endl;
    servicePool.stopAll();
}

void Server::acceptHandler(boost::shared_ptr<Connection> connection,
                   const boost::system::error_code& error)
{
    if (!error) {
        //std::cout << "Client accepted!" << std::endl;

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
