#ifndef SERVICEPOOL_H
#define SERVICEPOOL_H

#include <functional>
#include <thread>
#include <deque>
#include <boost/asio.hpp>

namespace asio = boost::asio;
typedef std::shared_ptr<asio::ip::tcp::socket> socket_ptr;
typedef std::shared_ptr<asio::io_service> io_service_ptr;

class ServicePool
{
public:
    ServicePool(size_t servicesCount);
    ~ServicePool();

    void startAll();
    void stopAll();

    io_service_ptr getService();

private:
    size_t servicesCount;
    std::deque<io_service_ptr> services;
    std::deque<asio::io_service::work> serviceWorks;
};

#endif // SERVICEPOOL_H
