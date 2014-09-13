#ifndef SERVICEPOOL_H
#define SERVICEPOOL_H

#include <functional>
#include <thread>
#include <deque>

#include "common.h"

class ServicePool
{
public:
    ServicePool(size_t servicesCount);
    ~ServicePool();

    void startAll();
    void stopAll();

    asio::io_service &getService();

private:
    size_t servicesCount;
    std::deque<io_service_ptr> services;
    std::deque<asio::io_service::work> serviceWorks;
};

#endif // SERVICEPOOL_H
