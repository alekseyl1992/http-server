#ifndef FILE_H
#define FILE_H

#include <string>
#include <boost/date_time/posix_time/posix_time_types.hpp>

class File
{
public:
    explicit File(const std::string &path,
                  const std::string &extension,
                  const boost::posix_time::ptime &timeToClose,
                  bool justGetSize);
    ~File();

    char *getData() const;
    unsigned long getSize() const;
    std::string getExtension() const;
    const boost::posix_time::ptime &getTimeToClose() const;

private:
    void open(const std::string &path, bool justGetSize);

    char *data = nullptr;
    unsigned long size = 0;

    std::string extension;
    boost::posix_time::ptime timeToClose;
};

#endif // FILE_H
