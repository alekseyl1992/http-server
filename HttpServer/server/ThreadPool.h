#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <functional>
#include <boost/thread.hpp>
#include <deque>

#include "asio_common.h"

class ThreadPool
{
public:
    ThreadPool(size_t threadsCountCount);
    ~ThreadPool();

    void startAll();
    void stopAll();

    void join();

    asio::io_service &getService();

private:
    size_t threadsCount = 0;
    asio::io_service service;
    asio::io_service::work serviceWork;
    std::vector<boost::thread> threads;
};
#endif // THREADPOOL_H
