#include <format>
#include <stdexcept>
#include <vector>

#include "ESCPOS/image/Image.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include "stb_image_resize2.h"

Image::Image(const std::string& path, int target_width, int target_height, double gamma) {
    int raw_width, raw_height;

    unsigned char* raw_img = stbi_load(
        path.c_str(),
        &raw_width,
        &raw_height,
        nullptr,
        3
    );

    if (!raw_img) {
        throw std::runtime_error(
            std::format("Failed to load image: {}", stbi_failure_reason())
        );
    }

    bool need_resize = false;
    int final_width = raw_width, final_height = raw_height;

    if (target_width != raw_width || target_height != raw_height) {
        if (target_width > 0) {
            final_width = target_width;
            need_resize = true;
        }

        if (target_height > 0) {
            final_height = target_height;
            need_resize = true;
        }
    }

    unsigned char* final_img;
    if (need_resize) {
        final_img = static_cast<unsigned char*>(malloc(final_width * final_height * 3));

        stbir_resize_uint8_linear(raw_img, raw_width, raw_height, 0, final_img, final_width, final_height, 0, STBIR_RGB);

        stbi_image_free(raw_img);
    } else {
        final_img = raw_img;
    }

    int padded_width = (final_width + 7) & ~7;
    int width_bytes  = padded_width / 8;

    _bitmap = std::vector<uint8_t>(width_bytes * final_height + _meta_length, 0x00);

    for (int y = 0; y < final_height; ++y) {
        for (int x = 0; x < padded_width; ++x) {
            if (x >= final_width) {
                break;
            }

            int idx = (y * final_width + x) * 3;
            uint8_t gray = ImageUtils::color_to_gray(
                final_img[idx],
                final_img[idx + 1],
                final_img[idx + 2],
                gamma
            );

            bool white = ImageUtils::dither_bayer4(x, y, gray);

            if (!white) {
                int byte_index = y * width_bytes + (x / 8) + _meta_length;
                _bitmap[byte_index] |= (1 << (7 - (x & 7)));
            }
        }
    }

    stbi_image_free(final_img);

    uint16_t width_bytes_16 = width_bytes;
    uint16_t height_16 = final_height;

    // meta
    _scale();

    _bitmap[1] = width_bytes_16 & 0xFF;          // xL
    _bitmap[2] = (width_bytes_16 >> 8) & 0xFF;   // xH
    _bitmap[3] = height_16 & 0xFF;               // yL
    _bitmap[4] = (height_16 >> 8) & 0xFF;        // yH
}

std::string Image::data_str() const {
    std::string str;
    str.append(
        reinterpret_cast<const char*>(_bitmap.data()),
        _bitmap.size()
    );

    return str;
}

void Image::set_width_scale(Image::Scale v) {
    _width_scale = v;
    _scale();
}

void Image::set_height_scale(Image::Scale v) {
    _height_scale = v;
    _scale();
}

void Image::set_scale(Image::Scale width, Image::Scale height) {
    set_width_scale(width);
    set_height_scale(height);
}

void Image::reset_scale() {
    set_scale(Image::Scale::x1, Image::Scale::x1);
}

void Image::_scale() {
    if (_width_scale == Image::Scale::x2 && _height_scale == Image::Scale::x2) {
        _bitmap[0] = 3;
    } else if (_height_scale == Image::Scale::x2) {
        _bitmap[0] = 2;
    } else if (_width_scale == Image::Scale::x2) {
        _bitmap[0] = 1;
    } else {
        _bitmap[0] = 0;
    }
}

Image::Scale Image::get_width_scale() const {
    return _width_scale;
}

Image::Scale Image::get_height_scale() const {
    return _height_scale;
}

uint8_t ImageUtils::color_to_gray(uint8_t r, uint8_t g, uint8_t b, double gamma) {
    return static_cast<uint8_t>(255 * std::pow((0.299 * r + 0.587 * g + 0.114 * b) / 255, 1 / gamma));
}

bool ImageUtils::dither_bayer4(int x, int y, uint8_t gray) {
    uint8_t threshold = BAYER4_MTX[y % 4][x % 4] * (255 / 16);

    return gray > threshold; // true = white, false = black
}
