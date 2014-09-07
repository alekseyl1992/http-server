#ifndef CONFIGPARSEERROR_H
#define CONFIGPARSEERROR_H

#include <string>
#include <stdexcept>

class ConfigParseError : public std::runtime_error
{
public:
    ConfigParseError(const std::string &reason)
        : std::runtime_error(reason)
    { }
};

#endif // CONFIGPARSEERROR_H
