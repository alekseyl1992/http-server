#include "Response.h"
#include <memory.h>

Response::Response(const std::string &headers, const char *body, size_t bodySize)
{
    if (!body)
        bodySize = 0;

    size = headers.size() + bodySize;
    data = new char[size];

    ::memcpy(data, headers.c_str(), headers.size());

    if (body)
        ::memcpy(data + headers.size(), body, bodySize);
}

Response::~Response()
{
    delete[] data;
    data = nullptr;
    size = 0;
}


const char *Response::getData() const
{
    return data;
}

size_t Response::getSize() const
{
    return size;
}
