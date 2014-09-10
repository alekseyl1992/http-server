#include "Response.h"

Response::Response(const std::string &headers, const char *body, size_t bodySize)
{
    std::string delimiter = "\r\n\r\n";
    data = new char[headers.size() + delimiter.size() + bodySize];

    ::memcpy(data, headers.c_str(), headers.size());
    ::memcpy(data + headers.size(), delimiter.c_str(), delimiter.size());
    ::memcpy(data + headers.size() + delimiter.size(), body, bodySize);
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
