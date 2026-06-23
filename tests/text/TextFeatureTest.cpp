#include "TextFeatureTest.h"

INSTANTIATE_TEST_SUITE_P(
    HW,
    ESCPOSTextFeatureTest,
    connections
);

TEST_P(ESCPOSTextFeatureTest, TextFeatureBold) {
    printer->set_text_feature(Text::TextFeature::BOLD, true);
    ASSERT_TRUE(printer->get_text_feature(Text::TextFeature::BOLD));

    printer->print("Bold text");

    printer->set_text_feature(Text::TextFeature::BOLD, false);
    ASSERT_FALSE(printer->get_text_feature(Text::TextFeature::BOLD));

    printer->print("Normal text");
}

TEST_P(ESCPOSTextFeatureTest, TextFeatureItalic) {
    printer->set_text_feature(Text::TextFeature::ITALIC, true);
    ASSERT_TRUE(printer->get_text_feature(Text::TextFeature::ITALIC));

    printer->print("Italic text");

    printer->set_text_feature(Text::TextFeature::ITALIC, false);
    ASSERT_FALSE(printer->get_text_feature(Text::TextFeature::ITALIC));

    printer->print("Normal text");
}

TEST_P(ESCPOSTextFeatureTest, TextFeatureInverted) {
    printer->set_text_feature(Text::TextFeature::INVERTED, true);
    ASSERT_TRUE(printer->get_text_feature(Text::TextFeature::INVERTED));

    printer->print("Inverted text");

    printer->set_text_feature(Text::TextFeature::INVERTED, false);
    ASSERT_FALSE(printer->get_text_feature(Text::TextFeature::INVERTED));

    printer->print("Normal text");
}

TEST_P(ESCPOSTextFeatureTest, TextFeatureUnderlined) {
    printer->set_text_feature(Text::TextFeature::UNDERLINED, true);
    ASSERT_TRUE(printer->get_text_feature(Text::TextFeature::UNDERLINED));

    printer->print("Underlined text");

    printer->set_text_feature(Text::TextFeature::UNDERLINED, false);
    ASSERT_FALSE(printer->get_text_feature(Text::TextFeature::UNDERLINED));

    printer->print("Normal text");
}

TEST_P(ESCPOSTextFeatureTest, TextFeatureUnderlineThickness) {
    printer->set_text_feature(Text::TextFeature::UNDERLINED, true);
    ASSERT_TRUE(printer->get_text_feature(Text::TextFeature::UNDERLINED));
    ASSERT_EQ(printer->get_text_underline_thickness(), Text::UnderlineThickness::x1);

    printer->print("Underlined text");

    printer->set_text_underline_thickness(Text::UnderlineThickness::x2);
    ASSERT_EQ(printer->get_text_underline_thickness(), Text::UnderlineThickness::x2);

    printer->print("Double underlined text");

    printer->set_text_underline_thickness(Text::UnderlineThickness::x1);
    ASSERT_EQ(printer->get_text_underline_thickness(), Text::UnderlineThickness::x1);

    printer->print("Underlined text");
}

