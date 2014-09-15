#ifndef CONNECTION_H
#define CONNECTION_H

#include <boost/enable_shared_from_this.hpp>
#include "asio_common.h"
#include "http/response/Response.h"
#include "fs/FileSupplier.h"

class Connection : public boost::enable_shared_from_this<Connection>
{
public:
    static boost::shared_ptr<Connection> create(asio::io_service &service, FileSupplier &fileSupplier);

    asio::ip::tcp::socket &getSocket();

    void start();

    void writeHandler(const boost::system::error_code& error,
                      size_t bytesTransferred);
    void readHandler(const boost::system::error_code& error,
                     size_t bytesTransferred);

    void sendResponse();

private:
    Connection(asio::io_service &service, FileSupplier &fileSupplier);

    FileSupplier &fileSupplier;

    std::shared_ptr<Response> response;

    asio::ip::tcp::socket socket;
    asio::streambuf readBuffer;
};

#endif // CONNECTION_H
