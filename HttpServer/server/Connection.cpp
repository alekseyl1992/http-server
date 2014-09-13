#include "Connection.h"

#include <boost/regex.hpp>
#include <boost/bind.hpp>
#include <string>
#include <iostream>

#include "http/request/RequestParser.h"
#include "http/response/ResponseBuilder.h"
#include "http/response/Response.h"
#include "http/request/RequestParseError.h"

Connection::Connection(asio::io_service &service)
    : socket(service)
{
}

asio::ip::tcp::socket &Connection::getSocket()
{
    return socket;
}

boost::shared_ptr<Connection> Connection::create(asio::io_service &service)
{
    return boost::shared_ptr<Connection>(new Connection(service));
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
        return;
    }

    const Response &response = ResponseBuilder::getInstance().buildDefaultPage(200, request.uri);



    asio::async_write(socket,
                      asio::buffer(response.getData(), response.getSize()),
                      boost::bind(&Connection::writeHandler,
                                  this,
                                  asio::placeholders::error,
                                  asio::placeholders::bytes_transferred));
}
