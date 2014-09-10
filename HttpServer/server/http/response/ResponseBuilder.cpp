#include "ResponseBuilder.h"

const ResponseBuilder &ResponseBuilder::getInstance()
{
    if (instance == nullptr)
        instance = new ResponseBuilder();

    return *instance;
}


ResponseBuilder::ResponseBuilder()
{
    //fill the maps
}

Response ResponseBuilder::build(unsigned int code, std::string dataExtension, const char *data, unsigned long size)
{
    //TODO:
    //build headers

    //build data

    return Response();
}


Response ResponseBuilder::buildDefaultPage(unsigned int code, std::string info)
{
    switch (code) {
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
