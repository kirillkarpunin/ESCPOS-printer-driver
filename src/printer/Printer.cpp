#include <vector>

#include "ESCPOS/printer/Printer.h"

Printer::Printer(Connection& connection): _connection(connection) {
    for (auto& item: _font_feature_commands) {
        _text.features[item.first] = false;
    }
}

void Printer::initialize() const {
    write("\x1B\x40"s);
}

void Printer::write(const std::string& data) const {
    _connection._write(data);
}

void Printer::write(const unsigned char& ch) const {
    _connection._write(ch);
}

void Printer::print() const {
    write('\x0A');
}

void Printer::print(const std::string& data) const {
    write(data);
    print();
}

void Printer::print(const unsigned char& ch) const {
    write(ch);
    print();
}

void Printer::set_text_feature(Text::TextFeature feature, bool v) {
    write(_font_feature_commands[feature]);

    if (!v) {
        write(static_cast<unsigned char>(0));
        _text.features[feature] = false;
        return;
    }

    _text.features[feature] = true;

    if (feature == Text::TextFeature::UNDERLINED) {
        write(static_cast<unsigned char>(_text.underline_thickness));
        return;
    }

    write(static_cast<unsigned char>(1));
}

void Printer::reset_text_features() {
    for (auto& item: _font_feature_commands) {
        write(item.second);
        write(static_cast<unsigned char>(0));
    }
}

bool Printer::get_text_feature(Text::TextFeature feature) const {
    return _text.features.at(feature);
}

void Printer::set_text_underline_thickness(Text::UnderlineThickness v) {
    _text.underline_thickness = v;

    if (_text.features[Text::TextFeature::UNDERLINED]) {
        // apply thickness changes
        set_text_feature(Text::TextFeature::UNDERLINED, true);
    }
}

Text::UnderlineThickness Printer::get_text_underline_thickness() const {
    return _text.underline_thickness;
}

void Printer::set_text_width_scale(Text::Scale v) {
    _text.width_scale = v;
    _scale_text();
}

void Printer::set_text_height_scale(Text::Scale v) {
    _text.height_scale = v;
    _scale_text();
}

void Printer::set_text_scale(Text::Scale width, Text::Scale height) {
    set_text_width_scale(width);
    set_text_height_scale(height);
}

void Printer::reset_text_scale() {
    set_text_scale(Text::Scale::x1, Text::Scale::x1);
}

void Printer::_scale_text() {
    write("\x1D\x21"s);
    write(
        static_cast<unsigned char>(
            (static_cast<int>(_text.width_scale) << 4) | static_cast<int>(_text.height_scale)
        )
    );
}

Text::Scale Printer::get_text_width_scale() const {
    return _text.width_scale;
}

Text::Scale Printer::get_text_height_scale() const {
    return _text.height_scale;
}

void Printer::set_font(Text::Font v) {
    write("\x1B\x4D"s);
    write(static_cast<unsigned char>(v));
}

void Printer::set_rotation(Text::Angle v) {
    reset_rotation();

    int angle = static_cast<int>(v);

    if (angle >= 180) {
        _rotate_180(true);
        angle -= 180;
    }

    if (angle >= 90) {
        _rotate_90(true);
    }
}

void Printer::reset_rotation() {
    _rotate_90(false);
    _rotate_180(false);
}

void Printer::_rotate_90(bool v) {
    write("\x1B\x56"s);
    write(static_cast<unsigned char>(v));
}

void Printer::_rotate_180(bool v) {
    write("\x1B\x7B"s);
    write(static_cast<unsigned char>(v));
}

void Printer::print_image(Image& image) const {
    write("\x1D\x76\x30"s);
    print(image._data_str());
}

void Printer::set_absolute_print_position(uint16_t v) {
    write("\x1B\x24"s);
    write(
        static_cast<unsigned char>(v & 0xFF)
    );
    write(
        static_cast<unsigned char>((v >> 8) & 0xFF)
    );
}

void Printer::set_relative_print_position(uint16_t v) {
    write("\x1B\x5C"s);
    write(
        static_cast<unsigned char>(v & 0xFF)
    );
    write(
        static_cast<unsigned char>((v >> 8) & 0xFF)
    );
}

void Printer::set_right_side_character_spacing(uint8_t v) {
    write("\x1B\x20"s);
    write(static_cast<unsigned char>(v));
}

void Printer::set_line_spacing(uint8_t v) {
    write("\x1B\x33"s);
    write(static_cast<unsigned char>(v));
}

void Printer::reset_line_spacing() {
    write("\x1B\x32"s);
}

void Printer::justify(Justification v) {
    write("\x1B\x61"s);
    write(static_cast<unsigned char>(v));
}

void Printer::set_left_margin(uint16_t v) {
    write("\x1D\x4C"s);
    write(
        static_cast<unsigned char>(v & 0xFF)
    );
    write(
        static_cast<unsigned char>((v >> 8) & 0xFF)
    );
}

void Printer::set_print_area_width(uint16_t v) {
    write("\x1D\x57"s);
    write(
        static_cast<unsigned char>(v & 0xFF)
    );
    write(
        static_cast<unsigned char>((v >> 8) & 0xFF)
    );
}
