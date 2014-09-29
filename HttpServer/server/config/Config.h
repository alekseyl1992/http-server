#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include <sstream>

struct Config
{
    std::string ip = "127.0.0.1";
    short int port = 8088;

    std::string root = "./";
    std::string index = "index.html";

    size_t acceptorsPoolSize = 2;
    size_t executorsPoolSize = 2;
    size_t cacheSize = 1024*1024*1024;

    size_t cachedLifeTime = 60 * 10; // 10 minutes

    std::string toString() const
    {
        std::stringstream ss;
        ss << "ip: "    << ip   << std::endl
           << "port: "  << port << std::endl
           << "root: "  << root << std::endl
           << "index: " << index << std::endl
           << "acceptorsPoolSize: " << acceptorsPoolSize << std::endl
           << "executorsPoolSize: " << executorsPoolSize << std::endl
           << "cacheSize: " << cacheSize << std::endl
           << "cachedLifeTime: " << cachedLifeTime << std::endl;

        return ss.str();
    }
};

#endif // CONFIG_H
