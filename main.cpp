#include <iostream>
#include "SoundProcessor.h"

int main(int argc, char* argv[]) {
    SoundProcessor soundProcessor(argc, argv);
    soundProcessor.run();
    return 0;
}
