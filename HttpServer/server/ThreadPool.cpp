#include "ThreadPool.h"

#include <memory>
#include <functional>
#include <boost/make_shared.hpp>

ThreadPool::ThreadPool(size_t threadsCountCount)
    : threadsCount(threadsCountCount),
      service(),
      serviceWork(service)
{

}

ThreadPool::~ThreadPool()
{
    stopAll();
}

void ThreadPool::startAll()
{
    for (size_t i = 0; i < threadsCount; ++i) {
        threads.emplace_back(boost::bind(&boost::asio::io_service::run,
                                         &service));
    }
}

void ThreadPool::stopAll()
{
    service.stop();
}

void ThreadPool::join()
{
    for (auto &thread: threads)
        if (thread.joinable())
            thread.join();
}

asio::io_service &ThreadPool::getService()
{
    return service;
}
