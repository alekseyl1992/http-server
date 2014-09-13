#ifndef RESPONSEBUILDER_H
#define RESPONSEBUILDER_H

#include <string>
#include <map>
#include "Response.h"
#include "../../common.h"

class ResponseBuilder
{
public:
    static ResponseBuilder &getInstance();

    Response build(ushort status, std::string bodyExtension, const char *body, size_t bodySize);
    Response buildDefaultPage(ushort status, std::string info = "");

private:
    ResponseBuilder();
    ResponseBuilder(const &ResponseBuilder) = delete;

    static ResponseBuilder *instance;

    std::string getDefaultPage(ushort, std::string info="") const;
    std::string getMimeType(std::string extension) const;

    std::string getDate() const;

    std::string getStatusName(ushort code) const;

    std::map<std::string, std::string> extToMime;
    std::map<ushort, std::string> defaultPages;
    std::map<ushort, std::string> statusNames;
};

#endif // RESPONSEBUILDER_H
