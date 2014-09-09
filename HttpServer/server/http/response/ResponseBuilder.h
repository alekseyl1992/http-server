#ifndef REQUESTPARSER_H
#define REQUESTPARSER_H

#include <string>
#include "Response.h"

class ResponseBuilder
{
public:
    ResponseBuilder() = delete;
    static Response build();
};

#endif // REQUESTPARSER_H
