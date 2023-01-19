#include <string>
#include <memory>
#include <map>
#include "Converters.h"

typedef std::map<std::string, std::unique_ptr<Converters::BaseConverter>(*)(std::vector<std::string>)> map_type;

template<typename T>
std::unique_ptr<Converters::BaseConverter> create(std::vector<std::string> args) { return std::make_unique<T>(args); }

class Factory {
public:
    Factory() = default;
    template<typename T>
    static bool RegisterConverter(std::string name);
    static std::unique_ptr<Converters::BaseConverter> CreateConverter(std::string name, std::vector<std::string> args);

private:
    static map_type converterMap;
};

template<typename T>
bool Factory::RegisterConverter(std::string name) {
    auto cvt = converterMap.find(name);
    if(cvt != converterMap.end()) {
        return false;
    }
    converterMap.insert(std::make_pair(name, &create<T>));
    return true;
}
