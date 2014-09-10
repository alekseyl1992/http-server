#ifndef REQUESTPARSER_H
#define REQUESTPARSER_H

#include <string>
#include <map>
#include "Response.h"

class ResponseBuilder
{
public:
    const ResponseBuilder &getInstance();

    Response build(unsigned int code, std::string dataExtension, const char *data, unsigned long size);
    Response buildDefaultPage(unsigned int code, std::string info = "");

private:
    ResponseBuilder();
    ResponseBuilder(const &ResponseBuilder) = delete;

    ResponseBuilder *instance = nullptr;

    std::map<std::string, std::string> extToMime;
    std::map<std::string, std::string> defaultPageData;
};

#endif // REQUESTPARSER_H
