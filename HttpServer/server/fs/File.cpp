#include "File.h"

#include <iostream>
#include <fstream>

#include "FileNotFoundError.h"

File::File(const std::string &path, const std::string &extension, const boost::posix_time::ptime &getTimeToClose, bool justGetSize)
    : extension(extension), timeToClose(getTimeToClose)
{
    open(path, justGetSize);
}

File::~File()
{
    delete[] data;
    data = nullptr;
    size = 0;
}

void File::open(const std::string &path, bool justGetSize)
{
    std::ifstream fs(path, std::ios::in | std::ios::binary | std::ios::ate);

    if (fs.is_open())
    {
        size = fs.tellg();
        if (justGetSize) {
            fs.close();
            return;
        }

        data = new char[size];
        fs.seekg(0, std::ios::beg);
        fs.read(data, size);
        fs.close();
    }
    else
        throw FileNotFoundError(path.c_str());
}

char *File::getData() const
{
    return data;
}

unsigned long File::getSize() const
{
    return size;
}

std::string File::getExtension() const
{
    return extension;
}

const boost::posix_time::ptime &File::getTimeToClose() const
{
    return timeToClose;
}


