#ifndef TEXT_H
#define TEXT_H

#include <unordered_map>

struct Text final {
    enum class TextFeature {
        BOLD,
        ITALIC,
        INVERTED,
        UNDERLINED
    };

    enum class Scale {
        x1 = 0,
        x2 = 1,
        x3 = 2,
        x4 = 3
    };

    enum class Font {
        A = 0,
        B = 1
    };

    enum class Angle {
        o0 = 0,
        o90 = 90,
        o180 = 180,
        o270 = 270
    };

    enum class UnderlineThickness {
        x1 = 1,
        x2 = 2
    };

    Scale width_scale{Scale::x1};
    Scale height_scale{Scale::x1};

    UnderlineThickness underline_thickness{UnderlineThickness::x1};

    std::unordered_map<TextFeature, bool> features;
};

#endif //TEXT_H
