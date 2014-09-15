#include "FileSupplier.h"
#include <boost/algorithm/string/predicate.hpp>

#include "FileNotInRootError.h"
#include "FileNotFoundError.h"

FileSupplier::FileSupplier(const std::string &rootPath, const std::string &index)
    : root(boost::filesystem::path(rootPath)), index(index)
{
    using namespace boost::filesystem;
    root = canonical(root);
}

File FileSupplier::getFile(const std::string &fileName, bool justGetSize)
{
    //check path in root
    using namespace boost::filesystem;

    boost::system::error_code e;
    path fullPath = canonical("." + fileName, root, e); //solve symlinks, ".." and "." things

    if (e)
        throw FileNotFoundError(fullPath.string().c_str());

    if (boost::filesystem::is_directory(fullPath)) {
        fullPath = canonical(index, fullPath, e); // "/" -> "/index.html"

        if (e)
            throw FileNotFoundError(fullPath.string().c_str());
    }

    if (boost::starts_with(
                fullPath.generic_string(),
                root.generic_string())) {
        std::string extension = fullPath.extension().string();

        if (!extension.empty())
            extension = extension.substr(1, extension.size()); //remove dot

        return File(fullPath.string(),
                    extension,
                    justGetSize);
    } else {
        throw FileNotInRootError(fullPath.string().c_str());
    }
}
