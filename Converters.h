#include <vector>
#include <string>

#define CVT_MUTE 0
#define CVT_MIX 1
#define CVT_REVERSE 2


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
        int time;
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
