#ifndef REQUESTPARSEERROR_H
#define REQUESTPARSEERROR_H

#include <string>
#include <stdexcept>

class RequestParseError : public std::runtime_error
{
public:
    RequestParseError(const std::string &reason)
        : std::runtime_error(reason)
    { }
};

#endif // REQUESTPARSEERROR_H
