//
// Created by amazi on 27.12.2022.
//

#ifndef SOUNDPROCESSOR_CONFIGPARSER_H
#define SOUNDPROCESSOR_CONFIGPARSER_H


#include <string>
#include <vector>

typedef std::tuple<std::string, std::vector<std::string>> ConfigTuple;

class ConfigParser {
public:
    ConfigParser(std::string configName);
    std::vector<ConfigTuple> Parse();
private:
    std::string configName;
};


#endif //SOUNDPROCESSOR_CONFIGPARSER_H
