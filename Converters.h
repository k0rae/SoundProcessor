#include <vector>
#include <string>

#define CVT_MUTE 0
#define CVT_MIX 1
#define CVT_REVERSE 2
#define CVT_VOLUME 3

typedef std::vector<short int> SamplesProduct;

namespace Converters {

    class BaseConverter {
    public:
        virtual void convert() = 0;
    };

    class MuteConverter: public BaseConverter {
    public:
        MuteConverter(SamplesProduct* input, int start, int end);
        void convert() override;
    private:
        SamplesProduct* input;
        int start, end;
    };

    class MixConverter: public BaseConverter {
    public:
        MixConverter(SamplesProduct* input, std::string fileName, int time);
        MixConverter(SamplesProduct* input, std::string fileName);
        void convert() override;
    private:
        SamplesProduct* input;
        std::string fileName;
        int time;
    };

    class VolumeConverter: public BaseConverter {
    public:
        VolumeConverter(SamplesProduct* input, float factor, int start, int end);
        VolumeConverter(SamplesProduct* input, float factor);
        void convert() override;
    private:
        SamplesProduct* input;
        float factor;
        int start, end;
    };

    class ReverseConverter: public BaseConverter {
    public:
        ReverseConverter(SamplesProduct* input, int start, int end);
        ReverseConverter(SamplesProduct* input);
        void convert() override;
    private:
        SamplesProduct* input;
        int start, end;
    };
}
