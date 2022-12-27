#include <iostream>
#include "WAVParser.h"

WAVParser::WAVParser(std::string fileName): fileName(fileName) {}

std::vector<short int> WAVParser::parse() {
    std::ifstream file(fileName, std::ios::binary); // читаем файл
    if(!file.is_open()) {
        throw std::runtime_error("Unable to open and parse WAV file " + fileName);
    }

    header =(wav_header* ) malloc(sizeof(wav_header));

    file.read((char* )header, sizeof(wav_header));

    char* junk =(char *)malloc(sizeof(char) * (header->subchunk2_size + 4));
    file.read(junk, sizeof(char) * (header->subchunk2_size + 4));

    int dataSize;

    file.read(reinterpret_cast<char *>(&dataSize), sizeof(dataSize));
    std::vector<short int> data;
    data.resize(dataSize);
    file.read((char *)data.data(), dataSize);

    free(junk);
    return data;
}

WAVParser::~WAVParser() {
    free(header);
}
