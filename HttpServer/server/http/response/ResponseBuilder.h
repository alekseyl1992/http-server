#ifndef REQUESTPARSER_H
#define REQUESTPARSER_H

#include <string>
#include <map>
#include "Response.h"

class ResponseBuilder
{
public:
    const ResponseBuilder &getInstance();

    Response build(unsigned int code, std::string bodyExtension, const char *body, usize_t bodySize);
    Response buildDefaultPage(unsigned int code, std::string info = "");

private:
    ResponseBuilder();
    ResponseBuilder(const &ResponseBuilder) = delete;

    ResponseBuilder *instance = nullptr;

    std::string getDefaultPage(int code, std::string info);
    std::string getMimeType(std::string extension);

    std::map<std::string, std::string> extToMime;
    std::map<std::string, std::string> defaultPages;
};

#endif // REQUESTPARSER_H
