#include "Connection.h"

#include <boost/regex.hpp>
#include <boost/bind.hpp>
#include <string>

#include "http/request/RequestParser.h"
#include "http/response/ResponseBuilder.h"

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
    /*std::string dataStr(
                asio::buffers_begin(data),
                asio::buffers_begin(data) + bytesTransferred);

    Request request = RequestParser::parse(dataStr);

    Response response = ResponseBuilder::getInstance().buildDefaultPage(200);
    */
    std::string message = "HTTP/1.0 200 OK\r\nContent-Type: text/html\r\n\r\n"
        "<html><head><title>test</title>"
        "</head><body><h1>Test</h1><p>This is a test!</p></body></html>";


    asio::async_write(socket,
                      asio::buffer(message),
                      boost::bind(&Connection::writeHandler,
                                  this,
                                  asio::placeholders::error,
                                  asio::placeholders::bytes_transferred));
}
