#include "Server.h"

#include <iostream>
#include <boost/bind.hpp>
#include <boost/make_shared.hpp>

Server::Server(const Config &config)
    : config(config)
    , fileSupplier(config.root, config.index, config.cachedLifeTime)
    , executorsPool(config.executorsPoolSize)
    , acceptorsPool(config.acceptorsPoolSize)
{
}

Server::~Server()
{
    stop();
}

void Server::start()
{
    acceptor = boost::make_shared<asio::ip::tcp::acceptor>(
                acceptorsPool.getService(),
                asio::ip::tcp::endpoint(
                    asio::ip::tcp::v4(),
                    config.port));

    //initSignals();

    std::cout << "Server started with configuration:"
              << std::endl
              << config.toString()
              << std::endl;

    acceptorsPool.startAll();
    executorsPool.startAll();

    for (int i = 0; i < config.acceptorsPoolSize; ++i)
        acceptNextClient();

    acceptorsPool.join();
    executorsPool.join();
}

/*void Server::initSignals()
{
    signals = boost::make_shared<boost::asio::signal_set>(executorsPool.getService());
    signals->add(SIGINT);
    signals->add(SIGTERM);
#ifdef SIGQUIT
    signals->add(SIGQUIT);
#endif

    signals->async_wait(
                [this](boost::system::error_code ec, int signo) {
                stop();
            });
}*/

void Server::stop()
{
    std::cout << "Stopping server..." << std::endl;

    acceptorsPool.stopAll();
    executorsPool.stopAll();
}

void Server::acceptHandler(boost::shared_ptr<Connection> connection,
                   const boost::system::error_code& error)
{
    if (!error) {
        //std::cout << "Client accepted!" << std::endl;

        executorsPool.getService().post(boost::bind(&Connection::start, connection));
        acceptNextClient();
    }
}

void Server::acceptNextClient() {
    auto connection = boost::make_shared<Connection>(
                executorsPool.getService(),
                fileSupplier,
                responseBuilder);

    acceptor->async_accept(connection->getSocket(),
                          boost::bind(&Server::acceptHandler,
                                      this,
                                      connection,
                                      asio::placeholders::error));
}
