#ifndef CONFIGPARSER_H
#define CONFIGPARSER_H
#include "Config.h"

class ConfigParser
{
public:
    static Config load(const std::string &configFile = "config.json");
};

#endif // CONFIGPARSER_H
