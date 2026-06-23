#include "TextScaleTest.h"

INSTANTIATE_TEST_SUITE_P(
    HW,
    ESCPOSTextScaleTest,
    connections
);

TEST_P(ESCPOSTextScaleTest, TextScaleX2) {
    printer->set_text_width_scale(Text::Scale::x2);
    ASSERT_EQ(printer->get_text_width_scale(), Text::Scale::x2);

    printer->print("Width x2");

    printer->set_text_width_scale(Text::Scale::x1);
    ASSERT_EQ(printer->get_text_width_scale(), Text::Scale::x1);

    printer->set_text_height_scale(Text::Scale::x2);
    ASSERT_EQ(printer->get_text_height_scale(), Text::Scale::x2);

    printer->print("Height x2");

    printer->set_text_height_scale(Text::Scale::x1);
    ASSERT_EQ(printer->get_text_height_scale(), Text::Scale::x1);

    printer->set_text_scale(Text::Scale::x2, Text::Scale::x2);
    ASSERT_EQ(printer->get_text_width_scale(), Text::Scale::x2);
    ASSERT_EQ(printer->get_text_height_scale(), Text::Scale::x2);

    printer->print("Width & height x2");

    printer->reset_text_scale();
    ASSERT_EQ(printer->get_text_width_scale(), Text::Scale::x1);
    ASSERT_EQ(printer->get_text_height_scale(), Text::Scale::x1);

    printer->print("Normal text");
}

TEST_P(ESCPOSTextScaleTest, TextScaleX3) {
    printer->set_text_width_scale(Text::Scale::x3);
    ASSERT_EQ(printer->get_text_width_scale(), Text::Scale::x3);

    printer->print("Width x3");

    printer->set_text_width_scale(Text::Scale::x1);
    ASSERT_EQ(printer->get_text_width_scale(), Text::Scale::x1);

    printer->set_text_height_scale(Text::Scale::x3);
    ASSERT_EQ(printer->get_text_height_scale(), Text::Scale::x3);

    printer->print("Height x3");

    printer->set_text_height_scale(Text::Scale::x1);
    ASSERT_EQ(printer->get_text_height_scale(), Text::Scale::x1);

    printer->set_text_scale(Text::Scale::x3, Text::Scale::x3);
    ASSERT_EQ(printer->get_text_width_scale(), Text::Scale::x3);
    ASSERT_EQ(printer->get_text_height_scale(), Text::Scale::x3);

    printer->print("Width & height x3");

    printer->reset_text_scale();
    ASSERT_EQ(printer->get_text_width_scale(), Text::Scale::x1);
    ASSERT_EQ(printer->get_text_height_scale(), Text::Scale::x1);

    printer->print("Normal text");
}

TEST_P(ESCPOSTextScaleTest, TextScaleX4) {
    printer->set_text_width_scale(Text::Scale::x4);
    ASSERT_EQ(printer->get_text_width_scale(), Text::Scale::x4);

    printer->print("Width x4");

    printer->set_text_width_scale(Text::Scale::x1);
    ASSERT_EQ(printer->get_text_width_scale(), Text::Scale::x1);

    printer->set_text_height_scale(Text::Scale::x4);
    ASSERT_EQ(printer->get_text_height_scale(), Text::Scale::x4);

    printer->print("Height x4");

    printer->set_text_height_scale(Text::Scale::x1);
    ASSERT_EQ(printer->get_text_height_scale(), Text::Scale::x1);

    printer->set_text_scale(Text::Scale::x4, Text::Scale::x4);
    ASSERT_EQ(printer->get_text_width_scale(), Text::Scale::x4);
    ASSERT_EQ(printer->get_text_height_scale(), Text::Scale::x4);

    printer->print("Width & height x4");

    printer->reset_text_scale();
    ASSERT_EQ(printer->get_text_width_scale(), Text::Scale::x1);
    ASSERT_EQ(printer->get_text_height_scale(), Text::Scale::x1);

    printer->print("Normal text");
}
