#ifndef RESPONSE_H
#define RESPONSE_H

#include <string>

class Response
{
public:
    Response(const std::string &headers, const char *body, size_t bodySize);
    ~Response();

    const char *getData() const;
    size_t getSize() const;

private:
    char *data = nullptr;
    unsigned long size = 0;
};

#endif // RESPONSE_H
