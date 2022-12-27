#include <string>
#include <iostream>
#include <vector>
#include <tuple>
#include <map>
#include "SoundProcessor.h"
#include "ConfigParser.h"
#include "Converters.h"
#include "WAVWriter.h"

SoundProcessor::SoundProcessor(int argc, char **argv): argc(argc), argv(argv) {
//    this->argc = argc;
//    this->argv = argv;
}

void PrintHelp() {
    std::cout << "help" << std::endl;
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

    std::string config_file_name = argv[2];
    std::string output_file_name = argv[3];
    std::string input_file_name = argv[4];

    std::vector<std::string> other_input_names;

    for(int i = 5; i < argc; i++) {
        other_input_names.emplace_back(argv[i]);
    }

    ConfigParser configParser(config_file_name);
    std::vector<ConfigTuple> parsed = configParser.Parse();

    WAVParser wavParser(input_file_name);
    std::vector<short int> currentProduct = wavParser.parse();
    std::map<std::string, int> mapping;
    mapping["mute"] = CVT_MUTE;
    mapping["mix"] = CVT_MIX;
    mapping["reverse"] = CVT_REVERSE;
    for(const ConfigTuple& tuple : parsed) {
        std::string cvtName;
        std::vector<std::string> args;
        std::tie(cvtName, args) = tuple;
        switch (mapping[cvtName]) {
            case CVT_MUTE:
                if(args.size() != 3) {
                    throw std::runtime_error("Wrong number of arguments for mute converter");
                }
                int start, end;
                start = std::stoi(args[1]);
                end = std::stoi(args[2]);
                Converters::MuteConverter cvt(&currentProduct, start, end);
                cvt.convert();
                break;
        }
    }
    WAVWriter wavWriter(output_file_name);
    wavWriter.write(currentProduct, *wavParser.header);
}
