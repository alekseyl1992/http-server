#ifndef ACCEPTORSPOOL_H
#define ACCEPTORSPOOL_H

#include <functional>
#include <boost/thread.hpp>
#include <deque>

#include "asio_common.h"

class AcceptorsPool
{
    typedef boost::shared_ptr<boost::thread> thread_ptr;
public:
    AcceptorsPool(size_t threadsCount);
    ~AcceptorsPool();

    void startAll();
    void stopAll();

    void join();

    asio::io_service &getService();

private:
    size_t threadsCount = 0;
    io_service_ptr service;
    asio::io_service::work serviceWork;
    std::vector<thread_ptr> threads;
};
#endif // ACCEPTORSPOOL_H
