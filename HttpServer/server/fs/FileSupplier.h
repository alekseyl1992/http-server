#ifndef FILESUPPLIER_H
#define FILESUPPLIER_H

#include <map>
#include <string>
#include <boost/filesystem.hpp>

#include "File.h"

class FileSupplier
{
public:
    FileSupplier(const std::string &rootPath);
    File getFile(const std::string &fileName, bool justGetSize);

private:
    boost::filesystem::path root;

    //TODO: unused stuff
    std::map<std::string, File> cache;
    unsigned long currentCacheSize = 0;
    unsigned long maxCacheSize = 0;
};

#endif // FILESUPPLIER_H
