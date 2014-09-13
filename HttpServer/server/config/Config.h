#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include <sstream>

struct Config
{
    std::string ip = "127.0.0.1";
    short int port = 8088;

    std::string root = "./";

    size_t threadPoolSize = 8;
    size_t cacheSize = 1024*1024*1024;

    std::string toString() const
    {
        std::stringstream ss;
        ss << "ip: "    << ip   << std::endl
           << "port: "  << port << std::endl
           << "root: "  << root << std::endl
           << "threadPoolSize: "  << threadPoolSize << std::endl
           << "cacheSize: "  << cacheSize << std::endl;

        return ss.str();
    }
};

#endif // CONFIG_H
