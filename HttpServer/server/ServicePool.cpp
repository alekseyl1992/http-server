#include "ServicePool.h"

#include <memory>
#include <functional>
#include <boost/make_shared.hpp>

ServicePool::ServicePool(size_t servicesCount)
    : servicesCount(servicesCount)
{
    for (size_t i = 0; i < servicesCount; ++i) {
        services.push_back(io_service_ptr(new asio::io_service()));
        serviceWorks.push_back(asio::io_service::work(*services.back()));
    }
}

ServicePool::~ServicePool()
{
    stopAll();
}

void ServicePool::startAll()
{
    for (size_t i = 0; i < servicesCount; ++i) {
        threads.push_back(boost::make_shared<boost::thread>(
                              boost::bind(&boost::asio::io_service::run, services[i])));
    }

    for (auto thread: threads)
        if (thread->joinable())
            thread->join();
}

void ServicePool::stopAll()
{
    serviceWorks.clear();

    for (auto service: services)
        service->stop();
}

asio::io_service &ServicePool::getService()
{
    if (currentService >= servicesCount)
        currentService = 0;

    return *services[currentService++];
}
