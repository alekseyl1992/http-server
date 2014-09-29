#include "ConfigParser.h"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/exceptions.hpp>

#include "ConfigOpenError.h"
#include "ConfigParseError.h"

Config ConfigParser::load(const std::string &configFile)
{
    Config config;

    try {
        std::ifstream ifs(configFile);

        if (!ifs.is_open())
            throw ConfigOpenError(std::string("Unable to open: ")
                                  + configFile);

        boost::property_tree::ptree pt;
        boost::property_tree::read_json(ifs, pt);

        config.ip = pt.get<std::string>("ip", config.ip);
        config.port = pt.get<unsigned short>("port", config.port);
        config.root = pt.get<std::string>("root", config.root);
        config.index = pt.get<std::string>("index", config.index);
        config.threadPoolSize = pt.get<size_t>("threadPoolSize", config.threadPoolSize);
        config.acceptorsPoolSize = pt.get<size_t>("acceptorsPoolSize", config.acceptorsPoolSize);
        config.cacheSize = pt.get<size_t>("cacheSize", config.cacheSize);
        config.cachedLifeTime = pt.get<size_t>("cachedLifeTime", config.cachedLifeTime);
    } catch(const boost::property_tree::ptree_error &e) {
        throw ConfigParseError(e.what());
    }

    return config;
}

