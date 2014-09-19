#ifndef CONNECTION_H
#define CONNECTION_H

#include <boost/enable_shared_from_this.hpp>
#include "asio_common.h"
#include "http/response/ResponseBuilder.h"
#include "http/response/Response.h"
#include "fs/FileSupplier.h"

class Connection : public boost::enable_shared_from_this<Connection>
{
public:
    Connection(asio::io_service &service, FileSupplier &fileSupplier, ResponseBuilder &responseBuilder);

    asio::ip::tcp::socket &getSocket();

    void start();

    void writeHandler(const boost::system::error_code& error,
                      size_t bytesTransferred);
    void readHandler(const boost::system::error_code& error,
                     size_t bytesTransferred);

    void sendResponse();

private:
    FileSupplier &fileSupplier;
    ResponseBuilder &responseBuilder;

    boost::shared_ptr<Response> response;

    asio::ip::tcp::socket socket;
    asio::streambuf readBuffer;
};

#endif // CONNECTION_H
