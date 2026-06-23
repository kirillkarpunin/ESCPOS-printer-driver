#include "TextRotationTest.h"

INSTANTIATE_TEST_SUITE_P(
    HW,
    ESCPOSTextRotationTest,
    connections
);

TEST_P(ESCPOSTextRotationTest, TextRotation90) {
    printer->print("Not rotated");

    printer->set_rotation(Text::Angle::o90);
    printer->print("Rotated 90");

    printer->reset_rotation();
    printer->print("Rotation reset");
}

TEST_P(ESCPOSTextRotationTest, TextRotation180) {
    printer->print("Not rotated");

    printer->set_rotation(Text::Angle::o180);
    printer->print("Rotated 180");

    printer->reset_rotation();
    printer->print("Rotation reset");
}

TEST_P(ESCPOSTextRotationTest, TextRotation270) {
    printer->print("Not rotated");

    printer->set_rotation(Text::Angle::o270);
    printer->print("Rotated 270");

    printer->reset_rotation();
    printer->print("Rotation reset");
}