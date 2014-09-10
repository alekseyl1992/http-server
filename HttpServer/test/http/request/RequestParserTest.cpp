#ifdef TESTS_RUN

#include <boost/test/unit_test.hpp>

#include <string>

#include "server/http/request/RequestParser.h"
#include "server/http/request/RequestParseError.h"

BOOST_AUTO_TEST_SUITE(RequestParserSuite)

BOOST_AUTO_TEST_CASE(httpGetRequestTest)
{
    std::string requestStr = "GET /index.html HTTP/1.1\r\nHost: www.host1.com:80\r\n\r\n";

    Request req = RequestParser::parse(requestStr);

    BOOST_CHECK(req.method == Request::GET);
    BOOST_CHECK(req.uri == "/index.html");
}

BOOST_AUTO_TEST_CASE(httpHeadRequestTest)
{
    std::string requestStr = "HEAD /index.html HTTP/1.1\r\n\r\n";

    Request req = RequestParser::parse(requestStr);

    BOOST_CHECK(req.method == Request::HEAD);
    BOOST_CHECK(req.uri == "/index.html");
}

BOOST_AUTO_TEST_CASE(httpOtherRequestTest)
{
    std::string requestStr = "PUT /index.html HTTP/1.1\r\n\r\n";

    Request req = RequestParser::parse(requestStr);

    BOOST_CHECK(req.method == Request::OTHER);
    BOOST_CHECK(req.uri == "/index.html");
}

BOOST_AUTO_TEST_CASE(httpWrongRequestTest)
{
    std::string requestStr = "LOLNOSPACEHERE/index.html HTTP/1.1\r\n\r\n";

    BOOST_CHECK_THROW(RequestParser::parse(requestStr), RequestParseError);
}

BOOST_AUTO_TEST_CASE(httpUrlDecodeTest)
{
    std::string requestStr = "GET /index.html?q=20%2B10-3%3A20%26 HTTP/1.1\r\n\r\n";
    std::string decodedUri = RequestParser::parse(requestStr).uri;

    BOOST_CHECK(decodedUri == "/index.html?q=20+10-3:20&");
}

BOOST_AUTO_TEST_CASE(httpUrlDecodeSpacesTest)
{
    std::string requestStr = "GET /one%20plus%20one.test HTTP/1.1\r\n\r\n";
    std::string decodedUri = RequestParser::parse(requestStr).uri;

    BOOST_CHECK(decodedUri == "/one plus one.test");
}

BOOST_AUTO_TEST_SUITE_END()

#endif
