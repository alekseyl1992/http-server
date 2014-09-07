#ifndef CONFIGOPENERROR_H
#define CONFIGOPENERROR_H

#include <string>
#include <stdexcept>

class ConfigOpenError : public std::runtime_error
{
public:
    ConfigOpenError(const std::string &reason)
        : std::runtime_error(reason)
    { }
};

#endif // CONFIGOPENERROR_H
