#ifndef CONNECTION_H
#define CONNECTION_H

#include <boost/enable_shared_from_this.hpp>
#include "common.h"

class Connection : public boost::enable_shared_from_this<Connection>
{
public:
    static std::shared_ptr<Connection> create(asio::io_service &service);

    asio::ip::tcp::socket &getSocket();

    void start();

    void writeHandler(const boost::system::error_code& error,
                      size_t bytesTransferred);
    void readHandler(const boost::system::error_code& error,
                     size_t bytesTransferred);

private:
    Connection(asio::io_service &service);

    asio::ip::tcp::socket socket;
    asio::streambuf readBuffer;
};

#endif // CONNECTION_H
