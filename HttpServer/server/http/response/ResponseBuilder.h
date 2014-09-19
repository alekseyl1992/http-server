#ifndef RESPONSEBUILDER_H
#define RESPONSEBUILDER_H

#include <string>
#include <map>
#include <memory>
#include <boost/shared_ptr.hpp>
#include <boost/noncopyable.hpp>
#include "Response.h"
#include "../../common.h"

class ResponseBuilder
        : public boost::noncopyable
{
public:
    ResponseBuilder();

    boost::shared_ptr<Response> build(ushort status, std::string bodyExtension, const char *body, size_t bodySize, size_t fileSize);
    boost::shared_ptr<Response> buildDefaultPage(ushort status, std::string info = "");

    enum Status : ushort {
        OK = 200,
        BAD_REQUEST = 400,
        FORBIDDEN = 403,
        NOT_FOUND = 404,
        METHOD_NOT_ALLOWED = 405,
        INTERNAL_SERVER_ERROR = 500
    };
private:
    std::string getDefaultPage(ushort, std::string info="") const;
    std::string getMimeType(std::string extension) const;

    std::string getDate() const;

    std::string getStatusName(ushort code) const;

    std::map<std::string, std::string> extToMime;
    std::map<ushort, std::string> defaultPages;
    std::map<ushort, std::string> statusNames;
};

#endif // RESPONSEBUILDER_H
