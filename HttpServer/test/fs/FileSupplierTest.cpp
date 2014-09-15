#ifdef TESTS_RUN

#include <boost/test/unit_test.hpp>

#include <string>
#include <iostream>

#include "server/fs/FileSupplier.h"
#include "server/fs/FileNotFoundError.h"
#include "server/fs/FileNotInRootError.h"

BOOST_AUTO_TEST_SUITE(FileSupplierSuite)

void test(std::string root, std::string index, std::string fileName, std::string extension)
{
    FileSupplier fs(root, index);

    try {
        File file = fs.getFile(fileName, true);
        BOOST_CHECK(file.getExtension() == extension);
    } catch (const FileNotFoundError &e) {
        std::cout << "FileNotFoundError:" << std::endl
                  << e.what() << std::endl;

        BOOST_CHECK(false);
    } catch (const FileNotInRootError &e) {
        std::cout << "FileNotInRootError:" << std::endl
                  << e.what() << std::endl;

        BOOST_CHECK(false);
    }
}

BOOST_AUTO_TEST_CASE(indexFSTest)
{
    test(".\\", "index.html", "/test/index.html", "html");
}

BOOST_AUTO_TEST_CASE(slashIndexFSTest)
{
    test(".\\", "index.html", "/test/", "html");
}

BOOST_AUTO_TEST_SUITE_END()

#endif
