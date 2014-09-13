#ifndef ASIO_COMMON_H
#define ASIO_COMMON_H

#include <boost/asio.hpp>
#include <memory>
#include "common.h"

namespace asio = boost::asio;
typedef std::shared_ptr<asio::ip::tcp::socket> socket_ptr;
typedef std::shared_ptr<asio::io_service> io_service_ptr;

#endif // ASIO_COMMON_H
