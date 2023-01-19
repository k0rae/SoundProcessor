#include <string>
#include "Factory.h"
#include <iostream>
#include <vector>
#include <tuple>
#include "SoundProcessor.h"
#include "ConfigParser.h"
#include "WAVWriter.h"

SoundProcessor::SoundProcessor(int argc, char **argv): argc(argc), argv(argv) {}

void PrintHelp() {
    std::cout << "help" << std::endl;
}


void SoundProcessor::RegisterConverters() {
    Factory::RegisterConverter<Converters::MixConverter>("mix");
    Factory::RegisterConverter<Converters::VolumeConverter>("volume");
    Factory::RegisterConverter<Converters::MuteConverter>("mute");
}

void SoundProcessor::run() {
    if(argc < 2) {
        throw std::invalid_argument("Wrong number of arguments, usage: sound_processor -h");
    }
    std::string mode(argv[1]);
    if(mode == "-h") {
        PrintHelp();
        return;
    }
    if(mode != "-c") {
        throw std::invalid_argument("Wrong arguments, usage: sound_processor -h");
    }
    if(argc < 5) {
        throw std::invalid_argument("Wrong number of arguments, usage: sound_processor -h");
    }

    RegisterConverters();

    std::string config_file_name = argv[2];
    std::string output_file_name = argv[3];
    input_file_name = argv[4];

    for(int i = 5; i < argc; i++) {
        other_input_names.emplace_back(argv[i]);
    }

    ConfigParser configParser(config_file_name);
    std::vector<ConfigTuple> parsed = configParser.Parse();

    WAVParser wavParser(input_file_name);

    std::vector<short int> currentProduct = wavParser.parse();

    for(const ConfigTuple& tuple : parsed) {
        std::string cvtName;
        std::vector<std::string> args;
        std::tie(cvtName, args) = tuple;
        auto converter = Factory::CreateConverter(cvtName, args);
        converter->convert(&currentProduct);
    }
    WAVWriter wavWriter(output_file_name);
    wavWriter.write(currentProduct, *wavParser.header);
}
