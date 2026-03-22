#ifndef PRINTER_H
#define PRINTER_H

#include <unordered_map>

#include "ESCPOS/connection/Connection.h"
#include "ESCPOS/image/Image.h"
#include "ESCPOS/text/Text.h"

using namespace std::string_literals;

class Printer final {
public:
    enum class Justification;

    explicit Printer(Connection& connection);

    Printer(const Printer& printer) = delete;

    Printer& operator=(const Printer& printer) = delete;

    void initialize() const;

    void write(const std::string& data) const;
    void write(const unsigned char& ch) const;

    void print() const;

    void print(const std::string& data) const;
    void print(const unsigned char& ch) const;

    void set_text_feature(Text::TextFeature feature, bool v);
    void reset_text_features();
    void set_text_underline_thickness(Text::UnderlineThickness v);

    bool get_text_feature(Text::TextFeature feature) const;
    Text::UnderlineThickness get_text_underline_thickness() const;

    void set_text_width_scale(Text::Scale v);
    void set_text_height_scale(Text::Scale v);
    void set_text_scale(Text::Scale width, Text::Scale height);
    void reset_text_scale();

    Text::Scale get_text_width_scale() const;
    Text::Scale get_text_height_scale() const;

    void set_font(Text::Font v);

    void set_rotation(Text::Angle v);
    void reset_rotation();

    void print_image(Image& image) const;

    void set_absolute_print_position(uint16_t v);
    void set_relative_print_position(uint16_t v);
    void set_right_side_character_spacing(uint8_t v);
    void set_line_spacing(uint8_t v);
    void reset_line_spacing();

    void justify(Justification v);

    void set_left_margin(uint16_t v);

    void set_print_area_width(uint16_t v);

    enum class Justification {
        LEFT = 0,
        CENTER = 1,
        RIGHT = 2
    };

private:
    Connection& _connection;
    Text _text;

    std::unordered_map<Text::TextFeature, std::string> _font_feature_commands = {
        {Text::TextFeature::BOLD, "\x1B\x45"s},
        {Text::TextFeature::ITALIC, "\x1B\x34"s},
        {Text::TextFeature::INVERTED, "\x1D\x42"s},
        {Text::TextFeature::UNDERLINED, "\x1B\x2D"s},
    };

    void _scale_text();

    void _rotate_90(bool v);
    void _rotate_180(bool v);
};

#endif //PRINTER_H
