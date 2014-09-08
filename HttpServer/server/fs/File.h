#ifndef FILE_H
#define FILE_H

#include <string>

class File
{
public:
    explicit File(const std::string &path);

    char *getData() const;
    unsigned long getSize() const;

private:
    void open(const std::string &path);

    char *data = nullptr;
    unsigned long size = 0;
};

#endif // FILE_H
