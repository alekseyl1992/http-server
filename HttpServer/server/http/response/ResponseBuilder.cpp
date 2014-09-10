#include "ResponseBuilder.h"

#include <sstream>

const ResponseBuilder &ResponseBuilder::getInstance()
{
    if (instance == nullptr)
        instance = new ResponseBuilder();

    return *instance;
}


ResponseBuilder::ResponseBuilder()
{
    //MIME setup
    extToMime.insert("htm", "text/html"),
    extToMime.insert("html", "text/html");
    extToMime.insert("css", "text/css");
    extToMime.insert("js", "application/javascript");
    extToMime.insert("jpg", "image/jpeg");
    extToMime.insert("jpeg", "image/jpeg");
    extToMime.insert("png", "image/png");
    extToMime.insert("gif", "image/gif");
    extToMime.insert("swf", "application/x-shockwave-flash");

    //error pages setup
    defaultPages.insert(200, "OK, but no body in response");
    defaultPages.insert(403, "Go away!");
    defaultPages.insert(404, "Such page. So not found. Wow!");
    defaultPages.insert(405, "Method not allowed");
    defaultPages.insert(500, "Internal Server Error");
}

std::string ResponseBuilder::getDefaultPage(int code, std::string info)
{
    auto page = defaultPages.find(code);
    if (page == defaultPages.end())
        return "No such page for such error: " + std::to_string(code);

    return *page;
}

std::string ResponseBuilder::getMimeType(std::string extension)
{
    auto mime = extToMime.find(extension);
    if (mime == extToMime.end())
        return "text/plain";

    return *mime;
}

Response ResponseBuilder::build(unsigned int code, std::string bodyExtension, const char *body, usize_t bodySize)
{
    std::stringstream headers;
    headers << "Date: "              << ""; //TODO:
    headers << "Server: "            << "";
    headers << "Content-Length: "    << "";
    headers << "Content-Type: "      << "";
    headers << "Connection: "        << "";

    return Response(headers.str(), body, bodySize);
}


Response ResponseBuilder::buildDefaultPage(unsigned int code, std::string info)
{
    switch (code) { //TODO:
    case 200:
        return build(200, "", info.c_str(), info.size());
        break;
    case 403:
        return build(403, "", info.c_str(), info.size());
        break;
    case 404:
        return build(404, "", info.c_str(), info.size());
        break;
    case 500:
        return build(500, "", info.c_str(), info.size());
        break;

    default:
        return build(500, "", info.c_str(), info.size());
        break;
    }
}
