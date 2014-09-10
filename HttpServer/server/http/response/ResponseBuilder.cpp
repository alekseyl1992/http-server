#include "ResponseBuilder.h"

#include <sstream>
#include <ctime>

const ResponseBuilder &ResponseBuilder::getInstance()
{
    if (instance == nullptr)
        instance = new ResponseBuilder();

    return *instance;
}


ResponseBuilder::ResponseBuilder()
{
    //MIME setup
    extToMime["htm"] = "text/html";
    extToMime["html"] = "text/html";
    extToMime["css"] = "text/css";
    extToMime["js"] = "application/javascript";
    extToMime["jpg"] = "image/jpeg";
    extToMime["jpeg"] = "image/jpeg";
    extToMime["png"] = "image/png";
    extToMime["gif"] = "image/gif";
    extToMime["swf"] = "application/x-shockwave-flash";

    //error pages setup
    defaultPages.insert({200, "OK, but no body in response"});
    defaultPages.insert({403, "Go away!"});
    defaultPages.insert({404, "Such page. So not found. Wow!"});
    defaultPages.insert({405, "Method not allowed"});
    defaultPages.insert({500, "Internal Server Error"});
}

std::string ResponseBuilder::getDefaultPage(unsigned int code, std::string info) const
{
    auto page = defaultPages.find(code);
    if (page == defaultPages.end())
        return "No such page for such error: " + std::to_string(code);

    return page->second;
}

std::string ResponseBuilder::getMimeType(std::string extension) const
{
    auto mime = extToMime.find(extension);
    if (mime == extToMime.end())
        return "text/plain";

    return mime->second;
}

Response ResponseBuilder::build(unsigned int code, std::string bodyExtension, const char *body, size_t bodySize)
{
    std::stringstream headers;
    headers << "Date: "              << getDate();
    headers << "Server: "            << "HttpServer/1.0";
    headers << "Content-Length: "    << bodySize;
    headers << "Content-Type: "      << getMimeType(bodyExtension);
    headers << "Connection: "        << "close";

    return Response(headers.str(), body, bodySize);
}

Response ResponseBuilder::buildDefaultPage(unsigned int code, std::string info)
{
    std::string page = getDefaultPage(code, info);
    return build(code, "", page.c_str(), page.size());
}

std::string ResponseBuilder::getDate() const
{
    time_t rawtime;
    time(&rawtime);
    struct tm *ptm = gmtime(&rawtime);

    char buffer[30]; //29-chars fixed-length format date + \0
    //ex: Sun, 06 Nov 1994 08:49:37 GMT

    strftime(buffer, 80, "%a, %d %b %Y %X GMT", ptm);

    return std::string(buffer);
}
