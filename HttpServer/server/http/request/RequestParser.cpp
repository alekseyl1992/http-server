#include "RequestParser.h"

#include <sstream>
#include <algorithm>
#include <iterator>

#include "RequestParseError.h"

Request RequestParser::parse(const std::string &reqString)
{
    auto reqLineEndPos = reqString.find('\r');

    std::istringstream ss(reqString.substr(0, reqLineEndPos));
    std::vector<std::string> tokens;

    std::copy(std::istream_iterator<std::string>(ss),
         std::istream_iterator<std::string>(),
         std::back_inserter(tokens));

    if (tokens.size() != 3)
        throw RequestParseError("Wrong token count on request line: "
                                + std::to_string(tokens.size()));

    auto methodToken = tokens[0];
    auto reqUriToken = tokens[1];
    auto httpVerisonToken = tokens[2];

    Request request;

    if (methodToken == "GET")
        request.method = Request::GET;
    else if (methodToken == "HEAD")
        request.method = Request::HEAD;
    else
        request.method = Request::OTHER;

    request.uri = reqUriToken;

    return request;
}
