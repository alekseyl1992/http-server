#include "Response.h"

Response::Response(const std::string &headers, const char *body, size_t bodySize)
{
    size = headers.size() + bodySize;
    data = new char[size];

    ::memcpy(data, headers.c_str(), headers.size());
    ::memcpy(data + headers.size(), body, bodySize);
}

Response::~Response()
{
    delete[] data;
}

const char *Response::getData() const
{
    return data;
}

size_t Response::getSize() const
{
    return size;
}
