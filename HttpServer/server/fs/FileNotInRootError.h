#ifndef FILENOTINROOTERROR_H
#define FILENOTINROOTERROR_H

#include <string>
#include <stdexcept>

class FileNotInRootError : public std::runtime_error
{
public:
    FileNotInRootError(const std::string &reason)
        : std::runtime_error(reason)
    { }
};

#endif // FILENOTINROOTERROR_H
