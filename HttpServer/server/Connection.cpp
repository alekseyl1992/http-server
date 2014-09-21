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

Connection::Connection(asio::io_service &service, FileSupplier &fileSupplier, ResponseBuilder &responseBuilder)
    : fileSupplier(fileSupplier), responseBuilder(responseBuilder), socket(service)
{
}

asio::ip::tcp::socket &Connection::getSocket()
{
    return socket;
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
    if (error) {
        std::cout << "writeHandler error: " << error.message() << std::endl;
    }
    else {
        socket.shutdown(asio::ip::tcp::socket::shutdown_both);
    }
}

void Connection::readHandler(const boost::system::error_code &error, size_t bytesTransferred)
{
    if (error && bytesTransferred == 0) {
        std::cout << "readHandler error: " << error.message() << std::endl;
        socket.shutdown(asio::ip::tcp::socket::shutdown_both);
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

        response = responseBuilder.buildDefaultPage(ResponseBuilder::BAD_REQUEST);

        return sendResponse();
    }

    if (request.method == Request::OTHER) {
        response = responseBuilder.buildDefaultPage(ResponseBuilder::METHOD_NOT_ALLOWED);

        return sendResponse();
    }

    try {
        bool justSize = request.method == Request::HEAD;

        auto file = fileSupplier.getFile(request.uri, justSize);

        //everything is fine, try to contruct result page
        response = responseBuilder.build(
                    ResponseBuilder::OK,
                    file->getExtension(),
                    justSize ? nullptr : file->getData(),
                    file->getSize());

        return sendResponse();
    }
    catch (const FileNotInRootError &e) {
        response = responseBuilder.buildDefaultPage(ResponseBuilder::FORBIDDEN);

        return sendResponse();
    }
    catch (const FileNotFoundError &e) {
        response = responseBuilder.buildDefaultPage(ResponseBuilder::NOT_FOUND);

        return sendResponse();
    }
}

void Connection::sendResponse()
{
    asio::async_write(socket,
                      asio::buffer(response->getData(), response->getSize()),
                      boost::bind(&Connection::writeHandler,
                                  shared_from_this(),
                                  asio::placeholders::error,
                                  asio::placeholders::bytes_transferred));
}
