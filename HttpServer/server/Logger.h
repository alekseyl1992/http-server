#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <queue>
#include <boost/thread/mutex.hpp>

class Logger
{
public:
    Logger(const std::string &fileName);

    void log(const std::string &str);

private:
    std::queue<std::string> q;

    boost::mutex m;
};

#endif // LOGGER_H
