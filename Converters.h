#include <vector>
#include <string>

typedef std::vector<short int> SamplesProduct;

namespace Converters {

    class BaseConverter {
    public:
        virtual void convert(SamplesProduct* input) = 0;
    };

    class MuteConverter: public BaseConverter {
    public:
        explicit MuteConverter(std::vector<std::string> args);
        void convert(SamplesProduct* input) override;
    private:
        int start, end;
    };

    class MixConverter: public BaseConverter {
    public:
        explicit MixConverter(std::vector<std::string> args);
        void convert(SamplesProduct* input) override;
    private:
        std::string fileName;
        int time;
    };

    class VolumeConverter: public BaseConverter {
    public:
        explicit VolumeConverter(std::vector<std::string> args);
        void convert(SamplesProduct* input) override;
    private:
        float factor;
        int start, end;
    };
}
