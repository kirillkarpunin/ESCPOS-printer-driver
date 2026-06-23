#include "TextFontTest.h"

INSTANTIATE_TEST_SUITE_P(
    HW,
    ESCPOSTextFontTest,
    connections
);

TEST_P(ESCPOSTextFontTest, TextFont) {
    printer->print("Standard font");

    printer->set_font(Text::Font::B);
    printer->print("Alternative font");

    printer->set_font(Text::Font::A);
    printer->print("Standard font");
}