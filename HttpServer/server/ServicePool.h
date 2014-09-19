#ifndef SERVICEPOOL_H
#define SERVICEPOOL_H

#include <functional>
#include <boost/thread.hpp>
#include <deque>

#include "asio_common.h"

class ServicePool
{
    typedef boost::shared_ptr<boost::thread> thread_ptr;
public:
    ServicePool(size_t servicesCount);
    ~ServicePool();

    void startAll();
    void stopAll();

    asio::io_service &getService();

private:
    size_t servicesCount = 0;
    std::deque<io_service_ptr> services;
    size_t currentService = 0;

    std::deque<asio::io_service::work> serviceWorks;
    std::vector<thread_ptr> threads;
};

#endif // SERVICEPOOL_H
