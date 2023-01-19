#include "Converters.h"
#include "WAVParser.h"
#include "SoundProcessor.h"
#include <algorithm>
#include <iostream>

void Converters::MuteConverter::convert(SamplesProduct* input) {
    for(unsigned long long i = start * SAMPLES_IN_SECOND; i < std::min(input->size(), (unsigned long long)end * SAMPLES_IN_SECOND); i++) {
        (*input)[i] = 0;
    }
}

Converters::MuteConverter::MuteConverter(std::vector<std::string> args) {
    if (args.size() != 3) {
        throw std::runtime_error("Wrong number of arguments for mute converter");
    }
    start = std::stoi(args[1]);
    end = std::stoi(args[2]);
}

void Converters::MixConverter::convert(SamplesProduct* input) {
    WAVParser parser(fileName);
    std::vector<short int> toMixWith = parser.parse();
    int j = 0;
    for(unsigned long long i = time * SAMPLES_IN_SECOND; i < std::min(input->size(), time * SAMPLES_IN_SECOND + toMixWith.size()); i++) {
        (*input)[i] = (toMixWith[j++] + (*input)[i]) / 2;
    }
}

Converters::MixConverter::MixConverter(std::vector<std::string> args) {
    if (args.size() != 2 and args.size() != 3) {
        throw std::runtime_error("Wrong number of arguments for mix converter");
    } else if (args.size() == 2) {
        time = 0;
    } else {
        time = std::stoi(args[2]);
    }
    fileName = SoundProcessor::other_input_names[stoi(args[1].substr(1))];
}

void Converters::VolumeConverter::convert(SamplesProduct* input) {
    if(start == -1) {
        for(short int& sample : *input) {
            sample *= factor;
        }
    } else {
        for(unsigned long long i = start * SAMPLES_IN_SECOND; i < std::min(input->size(), (unsigned long long)end * SAMPLES_IN_SECOND); i++) {
            (*input)[i] = (*input)[i] * factor;
        }
    }
}

Converters::VolumeConverter::VolumeConverter(std::vector<std::string> args) {
    if (args.size() != 2 and args.size() != 4) {
        throw std::runtime_error("Wrong number of arguments for volume converter");
    } else if (args.size() == 2) {
        factor = std::stof(args[1]);
    } else {
        factor = std::stof(args[1]);
        start = std::stoi(args[2]);
        end = std::stoi(args[3]);
    }
}
