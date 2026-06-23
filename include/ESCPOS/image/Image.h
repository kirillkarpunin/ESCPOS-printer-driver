#ifndef ESCPOS_IMAGE_H
#define ESCPOS_IMAGE_H

#include <cstdint>
#include <string>
#include <vector>

class Printer;

namespace ImageUtils
{

// COLOR
constexpr double DEFAULT_GAMMA = 1.0;

}

class Image final {
    friend Printer;

public:
    explicit Image(const std::string& path, int target_width = 0, int target_height = 0, double gamma = ImageUtils::DEFAULT_GAMMA);

    Image(const Image& image) = delete;

    Image& operator=(const Image& image) = delete;

    enum class Scale {
        x1 = 0,
        x2 = 1
    };

    void set_width_scale(Scale v);
    void set_height_scale(Scale v);
    void set_scale(Scale width, Scale height);
    void reset_scale();

    Scale get_width_scale() const;
    Scale get_height_scale() const;

private:
    std::string _data_str() const;

    Scale _width_scale{Scale::x1};
    Scale _height_scale{Scale::x1};

    void _scale();

    int _meta_length{5};

    std::vector<uint8_t> _bitmap;
};

namespace ImageUtils
{

// COLOR
uint8_t color_to_gray(uint8_t r, uint8_t g, uint8_t b, double gamma);

// DITHERING
constexpr uint8_t BAYER4_MTX[4][4] = {
    {  0,  8,  2, 10 },
    { 12,  4, 14,  6 },
    {  3, 11,  1,  9 },
    { 15,  7, 13,  5 }
};
bool dither_bayer4(int x, int y, uint8_t gray);

}

#endif //ESCPOS_IMAGE_H
