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

    path fullPath = canonical("." + fileName, root); //solve symlinks, ".." and "." things

    if (boost::filesystem::is_directory(fullPath)) {
        fullPath = canonical(index, fullPath); // "/" -> "/index.html"
    }

    if (boost::starts_with(
                fullPath.generic_string(),
                root.generic_string())) {
        if (boost::filesystem::exists(fullPath)) {
            std::string extension = fullPath.extension().string();

            if (!extension.empty())
                extension = extension.substr(1, extension.size()); //remove dot

            return File(fullPath.string(),
                        extension,
                        justGetSize);
        } else {
            throw FileNotFoundError(fullPath.string().c_str());
        }
    } else {
        throw FileNotInRootError(fullPath.string().c_str());
    }
}
