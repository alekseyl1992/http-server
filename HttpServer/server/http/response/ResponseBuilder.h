#ifndef REQUESTPARSER_H
#define REQUESTPARSER_H

#include <string>
#include <map>
#include "Response.h"

class ResponseBuilder
{
public:
    const ResponseBuilder &getInstance();

    Response build(unsigned int code, std::string bodyExtension, const char *body, size_t bodySize);
    Response buildDefaultPage(unsigned int code, std::string info = "");

private:
    ResponseBuilder();
    ResponseBuilder(const &ResponseBuilder) = delete;

    ResponseBuilder *instance = nullptr;

    std::string getDefaultPage(unsigned int code, std::string info="") const;
    std::string getMimeType(std::string extension) const;

    std::string getDate() const;

    std::map<std::string, std::string> extToMime;
    std::map<unsigned int, std::string> defaultPages;
};

#endif // REQUESTPARSER_H
