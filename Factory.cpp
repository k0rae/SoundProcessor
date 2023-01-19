#include "Factory.h"

#include <utility>
map_type Factory::converterMap;

std::unique_ptr<Converters::BaseConverter> Factory::CreateConverter(std::string name, std::vector<std::string> args) {
    auto cvt = converterMap.find(name);
    if(cvt == converterMap.end()) {
        return nullptr;
    }
    return cvt->second(std::move(args));
}
