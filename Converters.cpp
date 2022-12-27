#include "Converters.h"
#include "WAVParser.h"

Converters::MuteConverter::MuteConverter(SamplesProduct *input, int start, int end): input(input), start(start), end(end) {}

void Converters::MuteConverter::convert() {
    for(unsigned long long i = start * SAMPLES_IN_SECOND; i < std::min(input->size(), (unsigned long long)end * SAMPLES_IN_SECOND); i++) {
        (*input)[i] = 0;
    }
}
