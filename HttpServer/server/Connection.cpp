#include "Connection.h"

#include <boost/regex.hpp>
#include <boost/bind.hpp>
#include <string>
#include <iostream>

#include "http/request/RequestParser.h"
#include "http/response/ResponseBuilder.h"
#include "http/response/Response.h"
#include "http/request/RequestParseError.h"
#include "fs/FileSupplier.h"
#include "fs/FileNotFoundError.h"
#include "fs/FileNotInRootError.h"

Connection::Connection(asio::io_service &service, FileSupplier &fileSupplier)
    : fileSupplier(fileSupplier), socket(service)
{
}

asio::ip::tcp::socket &Connection::getSocket()
{
    return socket;
}

boost::shared_ptr<Connection> Connection::create(asio::io_service &service, FileSupplier &fileSupplier)
{
    return boost::shared_ptr<Connection>(new Connection(service, fileSupplier));
}

void Connection::start()
{
    asio::async_read_until(socket, readBuffer, boost::regex("\r\n\r\n"),
        boost::bind(&Connection::readHandler, shared_from_this(),
                    asio::placeholders::error,
                    asio::placeholders::bytes_transferred));
}

void Connection::writeHandler(const boost::system::error_code &error, size_t bytesTransferred)
{
}

void Connection::readHandler(const boost::system::error_code &error, size_t bytesTransferred)
{
    if (error && bytesTransferred == 0) {
        std::cout << "readHandler error: " << error.message() << std::endl;
        return;
    }

    auto data = readBuffer.data();

    std::string dataStr(
                asio::buffers_begin(data),
                asio::buffers_begin(data) + bytesTransferred);

    Request request;
    try {
        request = RequestParser::parse(dataStr);
    }
    catch (const RequestParseError &e) {
        std::cout << "RequestParseError: " << e.what() << std::endl;

        const Response &response = ResponseBuilder::getInstance()
                .buildDefaultPage(ResponseBuilder::BAD_REQUEST);
        sendResponse(response);

        return;
    }

    try {
        const File &file = fileSupplier.getFile(request.uri, request.method == Request::HEAD);

        const Response &response = ResponseBuilder::getInstance()
                .build(ResponseBuilder::OK, file.getExtension(),
                       file.getData(), file.getSize(),
                       request.method == Request::HEAD ? 0 : file.getSize());

        sendResponse(response);
    }
    catch (const FileNotInRootError &e) {
        const Response &response = ResponseBuilder::getInstance()
                .buildDefaultPage(ResponseBuilder::FORBIDDEN);
        sendResponse(response);
    }
    catch (const FileNotFoundError &e) {
        const Response &response = ResponseBuilder::getInstance()
                .buildDefaultPage(ResponseBuilder::NOT_FOUND);
        sendResponse(response);
    }

    socket.shutdown(asio::ip::tcp::socket::shutdown_both); //not sure, if needed
}

void Connection::sendResponse(const Response &response)
{
    asio::async_write(socket,
                      asio::buffer(response.getData(), response.getSize()),
                      boost::bind(&Connection::writeHandler,
                                  this,
                                  asio::placeholders::error,
                                  asio::placeholders::bytes_transferred));
}
