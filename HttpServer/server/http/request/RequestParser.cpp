#include "RequestParser.h"

#include <sstream>
#include <algorithm>
#include <iterator>
#include <iostream>

#include "RequestParseError.h"

Request RequestParser::parse(const std::string &reqString)
{
    std::cout << "Request: " << std::endl << reqString << std::endl;

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

    std::string decodedUri;
    if (!urlDecode(reqUriToken, decodedUri))
        throw RequestParseError("Bad request");

    request.uri = decodedUri;

    return request;
}

bool RequestParser::urlDecode(const std::string& in, std::string& out)
{
    out.clear();
    out.reserve(in.size());

    for (std::size_t i = 0; i < in.size(); ++i) {
        if (in[i] == '%') {
            if (i + 3 <= in.size()) {
                int value = 0;
                std::istringstream is(in.substr(i + 1, 2));
                if (is >> std::hex >> value) {
                    out += static_cast<char>(value);
                    i += 2;
                } else {
                    return false;
                }
            } else {
                return false;
            }
        } else if (in[i] == '+') {
            out += ' ';
        } else {
            out += in[i];
        }
    }

    return true;
}
