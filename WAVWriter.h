#include <string>
#include <vector>
#include "WAVParser.h"

class WAVWriter {
public:
    WAVWriter(std::string fileName);
    void write(std::vector<short int> data, wav_header header);
private:
    std::string filename;
};
