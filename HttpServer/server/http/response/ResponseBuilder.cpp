#include "ResponseBuilder.h"

#include <sstream>
#include <ctime>
#include <iostream>
#include "../../common.h"

ResponseBuilder *ResponseBuilder::instance = nullptr;

ResponseBuilder &ResponseBuilder::getInstance()
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
    defaultPages.insert({400, "Bad request. Very bad request!"});
    defaultPages.insert({403, "Go away!"});
    defaultPages.insert({404, "Such page. So not found. Wow!"});
    defaultPages.insert({405, "Method not allowed"});
    defaultPages.insert({500, "Internal Server Error"});

    //status names setup
    statusNames.insert({200, "OK"});
    statusNames.insert({400, "Bad request"});
    statusNames.insert({403, "Go away!"});
    statusNames.insert({404, "Such page. So not found. Wow!"});
    statusNames.insert({405, "Method not allowed"});
    statusNames.insert({500, "Internal Server Error"});
}

std::string ResponseBuilder::getDefaultPage(ushort status, std::string info) const
{
    auto page = defaultPages.find(status);
    if (page == defaultPages.end())
        return "No such page for such error: " + std::to_string(status);

    return page->second;
}

std::string ResponseBuilder::getStatusName(ushort status) const
{
    auto statusName = statusNames.find(status);
    if (statusName == statusNames.end())
        return "UNKNOWN";

    return statusName->second;
}

std::string ResponseBuilder::getMimeType(std::string extension) const
{
    auto mime = extToMime.find(extension);
    if (mime == extToMime.end())
        return "text/plain";

    return mime->second;
}

Response ResponseBuilder::build(ushort status, std::string bodyExtension, const char *body, size_t bodySize)
{
    std::stringstream headers;
    const char *delimiter = "\r\n";

    headers << "HTTP/1.1 " << status << " " << getStatusName(status) << delimiter;

    headers << "Date: "              << getDate()           << delimiter;
    headers << "Server: "            << "HttpServer/1.1"    << delimiter;
    headers << "Content-Length: "    << bodySize            << delimiter;
    headers << "Content-Type: "      << getMimeType(bodyExtension) << delimiter;
    headers << "Connection: "        << "close"             << delimiter;

    headers << delimiter;

    std::cout << "Response headers:" << std::endl << headers.str();

    return Response(headers.str(), body, bodySize);
}

Response ResponseBuilder::buildDefaultPage(ushort status, std::string info)
{
    std::string page = getDefaultPage(status, info);
    return build(status, "", page.c_str(), page.size());
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
