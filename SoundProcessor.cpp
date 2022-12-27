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
    mapping["volume"] = CVT_VOLUME;
    for(const ConfigTuple& tuple : parsed) {
        std::string cvtName;
        std::vector<std::string> args;
        std::tie(cvtName, args) = tuple;
        switch (mapping[cvtName]) {
            case CVT_MUTE: {
                if (args.size() != 3) {
                    throw std::runtime_error("Wrong number of arguments for mute converter");
                }
                int start, end;
                start = std::stoi(args[1]);
                end = std::stoi(args[2]);
                Converters::MuteConverter cvt(&currentProduct, start, end);
                cvt.convert();
                break;
            }
            case CVT_REVERSE: {
                if (args.size() != 1 and args.size() != 3) {
                    throw std::runtime_error("Wrong number of arguments for reverse converter");
                } else if (args.size() == 1) {
                    Converters::ReverseConverter cvt(&currentProduct);
                    cvt.convert();
                } else {
                    int start, end;
                    start = std::stoi(args[1]);
                    end = std::stoi(args[2]);
                    Converters::ReverseConverter cvt(&currentProduct, start, end);
                    cvt.convert();
                }
                break;
            }
            case CVT_VOLUME: {
                if (args.size() != 2 and args.size() != 4) {
                    throw std::runtime_error("Wrong number of arguments for volume converter");
                } else if (args.size() == 2) {
                    float factor = std::stof(args[1]);
                    Converters::VolumeConverter cvt(&currentProduct, factor);
                    cvt.convert();
                } else {
                    int start, end;
                    float factor = std::stof(args[1]);
                    start = std::stoi(args[2]);
                    end = std::stoi(args[3]);
                    Converters::VolumeConverter cvt(&currentProduct, factor, start, end);
                    cvt.convert();
                }
                break;
            }
            case CVT_MIX: {
                if (args.size() != 2 and args.size() != 3) {
                    throw std::runtime_error("Wrong number of arguments for mix converter");
                } else if (args.size() == 2) {
                    int toMixWith = stoi(args[1].substr(1));
                    std::string fileName = input_file_name;
                    if(toMixWith >= 2) fileName = other_input_names[toMixWith-2];
                    Converters::MixConverter cvt(&currentProduct, fileName);
                    cvt.convert();
                } else {
                    int toMixWith = stoi(args[1].substr(1));
                    std::string fileName = input_file_name;
                    if(toMixWith >= 2) fileName = other_input_names[toMixWith-2];
                    int time = std::stoi(args[2]);
                    Converters::MixConverter cvt(&currentProduct, fileName, time);
                    cvt.convert();
                }
            }
        }
    }
    WAVWriter wavWriter(output_file_name);
    wavWriter.write(currentProduct, *wavParser.header);
}
