#ifndef FILENOTFOUNDERROR_H
#define FILENOTFOUNDERROR_H

#include <string>
#include <stdexcept>

class FileNotFoundError : public std::runtime_error
{
public:
    FileNotFoundError(const std::string &reason)
        : std::runtime_error(reason)
    { }
};

#endif // FILENOTFOUNDERROR_H
