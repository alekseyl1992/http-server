#ifndef REQUEST_H
#define REQUEST_H

#include <string>

struct Request
{
    enum Method {GET, HEAD, OTHER};

    Method method = OTHER;
    std::string uri;
};

#endif // REQUEST_H
