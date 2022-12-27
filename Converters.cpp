#include "Converters.h"
#include "WAVParser.h"
#include <algorithm>
#include <climits>
#include <iostream>
#include <utility>

template <typename T>
T swap_endian(T u)
{
    static_assert (CHAR_BIT == 8, "CHAR_BIT != 8");

    union
    {
        T u;
        unsigned char u8[sizeof(T)];
    } source, dest;

    source.u = u;

    for (size_t k = 0; k < sizeof(T); k++)
        dest.u8[k] = source.u8[sizeof(T) - k - 1];

    return dest.u;
}

Converters::MuteConverter::MuteConverter(SamplesProduct *input, int start, int end): input(input), start(start), end(end) {}

void Converters::MuteConverter::convert() {
    for(unsigned long long i = start * SAMPLES_IN_SECOND; i < std::min(input->size(), (unsigned long long)end * SAMPLES_IN_SECOND); i++) {
        (*input)[i] = 0;
    }
}

Converters::MixConverter::MixConverter(SamplesProduct *input, std::string fileName, int time): input(input), fileName(std::move(fileName)), time(0) {}

Converters::MixConverter::MixConverter(SamplesProduct *input, std::string fileName): input(input), fileName(std::move(fileName)), time(0) {}

void Converters::MixConverter::convert() {
    WAVParser parser(fileName);
    std::vector<short int> toMixWith = parser.parse();
    int j = 0;
    for(unsigned long long i = time * SAMPLES_IN_SECOND; i < std::min(input->size(), time * SAMPLES_IN_SECOND + toMixWith.size()); i++) {
        (*input)[i] = (toMixWith[j++] + (*input)[i]) / 2;
    }
}

Converters::ReverseConverter::ReverseConverter(SamplesProduct *input, int start, int end): input(input), start(start), end(end){}

Converters::ReverseConverter::ReverseConverter(SamplesProduct *input): input(input), start(-1), end(-1) {}

void Converters::ReverseConverter::convert() {      // ?????????????????
    if(start == -1) {
        std::reverse(input->begin(), input->end());
    }
}

Converters::VolumeConverter::VolumeConverter(SamplesProduct *input, float factor, int start, int end): input(input), factor(factor), start(start), end(end){}

Converters::VolumeConverter::VolumeConverter(SamplesProduct *input, float factor): input(input), factor(factor), start(-1), end(-1) {}

void Converters::VolumeConverter::convert() {
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
