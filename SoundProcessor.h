#include "vector"
#include "string"

class SoundProcessor {
public:
    SoundProcessor(int argc, char** argv);
    void run();
private:
    int argc;
    char** argv;
};
