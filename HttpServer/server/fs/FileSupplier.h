#ifndef FILESUPPLIER_H
#define FILESUPPLIER_H

#include <map>
#include <string>
#include <boost/filesystem.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/thread/mutex.hpp>

#include "File.h"

class FileSupplier
{
public:
    typedef boost::shared_ptr<File> file_ptr;

    FileSupplier(const std::string &rootPath, const std::string &index, size_t cachedLifeTime);

    file_ptr getFile(const std::string &fileName, bool justGetSize);

private:
    boost::filesystem::path root;
    std::string index;

    boost::mutex m;

    //TODO: unused stuff
    std::map<std::string, file_ptr> cache;
    unsigned long currentCacheSize = 0;
    unsigned long maxCacheSize = 0;

    size_t cachedLifeTime = 0;
};

#endif // FILESUPPLIER_H
