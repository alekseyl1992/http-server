#ifndef SERVER_H
#define SERVER_H

#include "config/Config.h"

class Server
{
public:
    explicit Server(const Config &config);
    ~Server();

    void start();
    void stop();

private:
    Config config;
};

#endif // SERVER_H
