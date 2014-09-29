#ifndef SERVER_H
#define SERVER_H

#include <boost/noncopyable.hpp>
#include <vector>
#include "config/Config.h"
#include "fs/FileSupplier.h"
#include "ThreadPool.h"
#include "Connection.h"
#include "asio_common.h"

class Server
        : public boost::noncopyable
{
public:
    explicit Server(const Config &config);
    ~Server();

    void start();
    void stop();

private:
    void acceptNextClient();
    void acceptHandler(boost::shared_ptr<Connection> connection,
                       const boost::system::error_code& error);
    void initSignals();

    Config config;
    FileSupplier fileSupplier;
    ResponseBuilder responseBuilder;
    ThreadPool executorsPool;
    ThreadPool acceptorsPool;

    boost::shared_ptr<asio::ip::tcp::acceptor> acceptor;
    //boost::shared_ptr<boost::asio::signal_set> signals;
};

#endif // SERVER_H
