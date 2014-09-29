#include "AcceptorsPool.h"

#include <memory>
#include <functional>
#include <boost/make_shared.hpp>

AcceptorsPool::AcceptorsPool(size_t servicesCount)
    : threadsCount(servicesCount),
      service(new asio::io_service()),
      serviceWork(*service)
{

}

AcceptorsPool::~AcceptorsPool()
{
    stopAll();
}

void AcceptorsPool::startAll()
{
    for (size_t i = 0; i < threadsCount; ++i) {
        threads.push_back(boost::make_shared<boost::thread>(
                              boost::bind(&boost::asio::io_service::run, service)));
    }
}

void AcceptorsPool::stopAll()
{
    //should stop work maybe?
    service->stop();
}

void AcceptorsPool::join()
{
    for (auto thread: threads)
        if (thread->joinable())
            thread->join();
}

asio::io_service &AcceptorsPool::getService()
{
    return *service;
}
