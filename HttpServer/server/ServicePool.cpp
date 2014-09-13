#include "ServicePool.h"

#include <memory>
#include <functional>

ServicePool::ServicePool(size_t servicesCount)
{
}

ServicePool::~ServicePool()
{

}

void ServicePool::startAll()
{
    for (size_t i = 0; i < servicesCount; ++i) {
        services.push_back(io_service_ptr(new asio::io_service()));
        serviceWorks.emplace_back(asio::io_service::work(*services.back()));

        std::thread th([service = services.back()]() {
            service->run();
        });

        th.detach();
    }
}

void ServicePool::stopAll()
{
    serviceWorks.clear();
}

asio::io_service &ServicePool::getService()
{
    io_service_ptr service = services.front();

    services.push_back(services.front());
    services.pop_front();

    return *service;
}
