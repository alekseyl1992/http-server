#include "FileSupplier.h"
#include <boost/make_shared.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/thread/lock_guard.hpp>

#include "FileNotInRootError.h"
#include "FileNotFoundError.h"

FileSupplier::FileSupplier(const std::string &rootPath, const std::string &index)
    : root(rootPath),
      index(index)
{
    using namespace boost::filesystem;
    root = canonical(absolute(rootPath));
}

FileSupplier::file_ptr FileSupplier::getFile(const std::string &fileName, bool justGetSize)
{
    boost::lock_guard<boost::mutex> lock(m);

    auto cachedFile = cache.find(fileName);
    if (cachedFile != cache.end())
        return cachedFile->second;

    using namespace boost::filesystem;

    //check path in root
    boost::system::error_code e;
    path fullPath = canonical("." + fileName, root, e); //solve symlinks, ".." and "." things

    if (e)
        throw FileNotFoundError(fullPath.string().c_str());

    if (boost::filesystem::is_directory(fullPath)) {
        fullPath = canonical(index, fullPath, e); // "/" -> "/index.html"

        if (e)
            throw FileNotInRootError(fullPath.string().c_str());
    }

    if (boost::starts_with(
                fullPath.generic_string(),
                root.generic_string())) {
        std::string extension = fullPath.extension().string();

        if (!extension.empty())
            extension = extension.substr(1, extension.size()); //remove dot


        auto file = boost::make_shared<File>(fullPath.string(), extension, justGetSize);
        cache[fileName] = file;

        return file;
    } else {
        throw FileNotInRootError(fullPath.string().c_str());
    }
}
