#ifndef SERVER_H
#define SERVER_H

#include <boost/noncopyable.hpp>
#include "config/Config.h"
#include "fs/FileSupplier.h"
#include "ServicePool.h"

class Server
        : public boost::noncopyable
{
public:
    explicit Server(const Config &config);
    ~Server();

    void start();
    void stop();

private:
    Config config;
    FileSupplier fileSupplier;
    ServicePool servicePool;
};

#endif // SERVER_H
