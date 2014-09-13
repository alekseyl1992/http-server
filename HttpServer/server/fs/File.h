#ifndef FILE_H
#define FILE_H

#include <string>

class File
{
public:
    explicit File(const std::string &path, const std::string &extension, bool justGetSize);

    char *getData() const;
    unsigned long getSize() const;
    std::string getExtension() const;

private:
    void open(const std::string &path, bool justGetSize);

    char *data = nullptr;
    unsigned long size = 0;

    std::string extension;
};

#endif // FILE_H
