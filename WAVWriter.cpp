#include "WAVWriter.h"

WAVWriter::WAVWriter(std::string fileName): filename(fileName) {}

void WAVWriter::write(std::vector<short> data, wav_header header) {
    header.subchunk2_id[0] = 'd'; header.subchunk2_id[1] = 'a'; header.subchunk2_id[2] = 't'; header.subchunk2_id[3] = 'a';
    header.subchunk2_size = data.size() * 2;
    std::ofstream file(filename, std::ios::binary);
    file.write((char *)&header, sizeof(header));
    file.write((char *)data.data(), data.size());

}
