#ifndef COMON_H
#define COMON_H

#include <boost/asio.hpp>
#include <memory>

namespace asio = boost::asio;
typedef std::shared_ptr<asio::ip::tcp::socket> socket_ptr;
typedef std::shared_ptr<asio::io_service> io_service_ptr;


#endif // COMON_H
