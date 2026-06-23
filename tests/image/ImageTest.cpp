#include "ImageTest.h"

INSTANTIATE_TEST_SUITE_P(
    HW,
    ESCPOSImageTest,
    connections
);

TEST_P(ESCPOSImageTest, ImageScale) {
    Image img{"resources/img.png", 128, 128, 1.75};

    printer->print("Standard image");
    printer->print_image(img);

    img.set_width_scale(Image::Scale::x2);
    ASSERT_EQ(img.get_width_scale(), Image::Scale::x2);

    printer->print("Width x2");
    printer->print_image(img);

    img.set_width_scale(Image::Scale::x1);
    ASSERT_EQ(img.get_width_scale(), Image::Scale::x1);

    img.set_height_scale(Image::Scale::x2);
    ASSERT_EQ(img.get_height_scale(), Image::Scale::x2);

    printer->print("Height x2");
    printer->print_image(img);

    img.set_height_scale(Image::Scale::x1);
    ASSERT_EQ(img.get_height_scale(), Image::Scale::x1);

    img.set_scale(Image::Scale::x2, Image::Scale::x2);
    ASSERT_EQ(img.get_width_scale(), Image::Scale::x2);
    ASSERT_EQ(img.get_height_scale(), Image::Scale::x2);

    printer->print("Width & height x2");
    printer->print_image(img);

    img.reset_scale();
    ASSERT_EQ(img.get_width_scale(), Image::Scale::x1);
    ASSERT_EQ(img.get_height_scale(), Image::Scale::x1);
}