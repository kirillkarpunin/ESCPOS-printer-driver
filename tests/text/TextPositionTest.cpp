#include "TextPositionTest.h"

INSTANTIATE_TEST_SUITE_P(
    HW,
    ESCPOSTextPositionTest,
    connections
);

TEST_P(ESCPOSTextPositionTest, TextJustification) {
    printer->print("Standard justification");

    printer->justify(Printer::Justification::CENTER);
    printer->print("Centered text");

    printer->justify(Printer::Justification::RIGHT);
    printer->print("Right-justified text");

    printer->justify(Printer::Justification::LEFT);
    printer->print("Left-justified text");
}

TEST_P(ESCPOSTextPositionTest, LineSpacing) {
    printer->print("--- [30 dots (std.)] Start ---");
    printer->print("--- [30 dots (std.)] End   ---");
    printer->reset_line_spacing();

    printer->write('\n');

    printer->set_line_spacing(45);
    printer->print("--- [45 dots] Start ---");
    printer->print("--- [45 dots] End   ---");
    printer->reset_line_spacing();

    printer->write('\n');

    printer->set_line_spacing(60);
    printer->print("--- [60 dots] Start ---");
    printer->print("--- [60 dots] End   ---");
    printer->reset_line_spacing();

    printer->write('\n');

    printer->set_line_spacing(90);
    printer->print("--- [90 dots] Start ---");
    printer->print("--- [90 dots] End   ---");
    printer->reset_line_spacing();
}

TEST_P(ESCPOSTextPositionTest, RightSideCharacterSpacing) {
    printer->print("Standard spacing");

    printer->set_right_side_character_spacing(5);
    printer->print("5 dots");

    printer->set_right_side_character_spacing(10);
    printer->print("10 dots");

    printer->set_right_side_character_spacing(20);
    printer->print("20 dots");
}

TEST_P(ESCPOSTextPositionTest, AbsolutePosition) {
    printer->print("Standard position");

    printer->set_absolute_print_position(5);
    printer->print("5 dots");

    printer->set_absolute_print_position(10);
    printer->print("10 dots");

    printer->set_absolute_print_position(20);
    printer->print("20 dots");
}

TEST_P(ESCPOSTextPositionTest, LeftMargin) {
    printer->print("Standard margin");

    printer->set_left_margin(25);
    printer->print("25 dots margin" + std::string(40, '.'));

    printer->set_left_margin(50);
    printer->print("50 dots margin" + std::string(40, '.'));

    printer->set_left_margin(75);
    printer->print("75 dots margin" + std::string(40, '.'));
}

TEST_P(ESCPOSTextPositionTest, PrintAreaWidth) {
    printer->print("Standard width" + std::string(40, '.'));

    printer->set_print_area_width(300);
    printer->print("300 dots width" + std::string(40, '.'));

    printer->set_print_area_width(200);
    printer->print("200 dots width" + std::string(40, '.'));

    printer->set_print_area_width(100);
    printer->print("100 dots width" + std::string(40, '.'));
}