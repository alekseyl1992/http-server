#include "File.h"

#include <iostream>
#include <fstream>

#include "FileNotFoundError.h"

File::File(const std::string &path)
{
    open(path);
}

void File::open(const std::string &path)
{
    std::ifstream fs(path, std::ios::in | std::ios::binary | std::ios::ate);

    if (fs.is_open())
    {
        size = fs.tellg();
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


