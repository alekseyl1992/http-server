#include "FileSupplier.h"
#include <boost/algorithm/string/predicate.hpp>

#include "FileNotInRootError.h"

FileSupplier::FileSupplier(const std::string &rootPath)
    : root(boost::filesystem::path(rootPath))
{
    root = root.normalize();
}

File FileSupplier::getFile(const std::string &fileName)
{
    //check path in root
    using namespace boost::filesystem;
    path fullPath = absolute(fileName, root);
    fullPath = fullPath.normalize(); //solve ".." things

    if (boost::starts_with(
                fullPath.generic_string(),
                root.generic_string()))
        return File(fullPath.string());
    else
        throw FileNotInRootError(fileName);
}
