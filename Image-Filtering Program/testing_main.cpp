#include <gtest/gtest.h>
#include <CImg.h>
#include "assignment3.h"

using cimg_library::CImg;

TEST(ImageFiltering, Identity) {
  CImg<unsigned char> filter(3, 3, 1, 1, 128);
  CImg<unsigned char> image(5, 5, 1, 1, 128);

  // Only the center value is 1, rest are 0.
  filter(1, 1, 0, 0) = 128 + 1;
  // Fill up the image.
  image(0, 0, 0, 0) = 0;
  image(1, 0, 0, 0) = 1;
  image(2, 0, 0, 0) = 2;
  image(3, 0, 0, 0) = 3;
  image(4, 0, 0, 0) = 4;

  image(0, 1, 0, 0) = 5;
  image(1, 1, 0, 0) = 6;
  image(2, 1, 0, 0) = 7;
  image(3, 1, 0, 0) = 8;
  image(4, 1, 0, 0) = 9;

  image(0, 2, 0, 0) = 10;
  image(1, 2, 0, 0) = 11;
  image(2, 2, 0, 0) = 12;
  image(3, 2, 0, 0) = 13;
  image(4, 2, 0, 0) = 14;

  image(0, 3, 0, 0) = 15;
  image(1, 3, 0, 0) = 16;
  image(2, 3, 0, 0) = 17;
  image(3, 3, 0, 0) = 18;
  image(4, 3, 0, 0) = 19;

  image(0, 4, 0, 0) = 20;
  image(1, 4, 0, 0) = 21;
  image(2, 4, 0, 0) = 22;
  image(3, 4, 0, 0) = 23;
  image(4, 4, 0, 0) = 24;
  
  const CImg<unsigned char> filtered_image = FilterImage(image, filter);

  ASSERT_EQ(0, filtered_image(0, 0, 0, 0));
  ASSERT_EQ(1, filtered_image(1, 0, 0, 0));
  ASSERT_EQ(2, filtered_image(2, 0, 0, 0));
  ASSERT_EQ(3, filtered_image(3, 0, 0, 0));
  ASSERT_EQ(4, filtered_image(4, 0, 0, 0));

  ASSERT_EQ(5, filtered_image(0, 1, 0, 0));
  ASSERT_EQ(6, filtered_image(1, 1, 0, 0));
  ASSERT_EQ(7, filtered_image(2, 1, 0, 0));
  ASSERT_EQ(8, filtered_image(3, 1, 0, 0));
  ASSERT_EQ(9, filtered_image(4, 1, 0, 0));

  ASSERT_EQ(10, filtered_image(0, 2, 0, 0));
  ASSERT_EQ(11, filtered_image(1, 2, 0, 0));
  ASSERT_EQ(12, filtered_image(2, 2, 0, 0));
  ASSERT_EQ(13, filtered_image(3, 2, 0, 0));
  ASSERT_EQ(14, filtered_image(4, 2, 0, 0));

  ASSERT_EQ(15, filtered_image(0, 3, 0, 0));
  ASSERT_EQ(16, filtered_image(1, 3, 0, 0));
  ASSERT_EQ(17, filtered_image(2, 3, 0, 0));
  ASSERT_EQ(18, filtered_image(3, 3, 0, 0));
  ASSERT_EQ(19, filtered_image(4, 3, 0, 0));

  ASSERT_EQ(20, filtered_image(0, 4, 0, 0));
  ASSERT_EQ(21, filtered_image(1, 4, 0, 0));
  ASSERT_EQ(22, filtered_image(2, 4, 0, 0));
  ASSERT_EQ(23, filtered_image(3, 4, 0, 0));
  ASSERT_EQ(24, filtered_image(4, 4, 0, 0));
}

TEST(ImageFiltering, ShiftImage) {
  CImg<unsigned char> filter(3, 3, 1, 1, 128);
  CImg<unsigned char> image(5, 5, 1, 1, 128);
  
  // The right-most, middle value is 2.
  filter(2, 1, 0, 0) = 128 + 2;

  // Fill up the image.
  image(0, 0, 0, 0) = 0;
  image(1, 0, 0, 0) = 1;
  image(2, 0, 0, 0) = 2;
  image(3, 0, 0, 0) = 3;
  image(4, 0, 0, 0) = 4;

  image(0, 1, 0, 0) = 5;
  image(1, 1, 0, 0) = 6;
  image(2, 1, 0, 0) = 7;
  image(3, 1, 0, 0) = 8;
  image(4, 1, 0, 0) = 9;

  image(0, 2, 0, 0) = 10;
  image(1, 2, 0, 0) = 11;
  image(2, 2, 0, 0) = 12;
  image(3, 2, 0, 0) = 13;
  image(4, 2, 0, 0) = 14;

  image(0, 3, 0, 0) = 15;
  image(1, 3, 0, 0) = 16;
  image(2, 3, 0, 0) = 17;
  image(3, 3, 0, 0) = 18;
  image(4, 3, 0, 0) = 19;

  image(0, 4, 0, 0) = 20;
  image(1, 4, 0, 0) = 21;
  image(2, 4, 0, 0) = 22;
  image(3, 4, 0, 0) = 23;
  image(4, 4, 0, 0) = 24;

  const CImg<unsigned char> filtered_image = FilterImage(image, filter);

  ASSERT_EQ(1, filtered_image(0, 0, 0, 0));
  ASSERT_EQ(2, filtered_image(1, 0, 0, 0));
  ASSERT_EQ(3, filtered_image(2, 0, 0, 0));
  ASSERT_EQ(4, filtered_image(3, 0, 0, 0));
  ASSERT_EQ(0, filtered_image(4, 0, 0, 0));

  ASSERT_EQ(6, filtered_image(0, 1, 0, 0));
  ASSERT_EQ(7, filtered_image(1, 1, 0, 0));
  ASSERT_EQ(8, filtered_image(2, 1, 0, 0));
  ASSERT_EQ(9, filtered_image(3, 1, 0, 0));
  ASSERT_EQ(0, filtered_image(4, 1, 0, 0));

  ASSERT_EQ(11, filtered_image(0, 2, 0, 0));
  ASSERT_EQ(12, filtered_image(1, 2, 0, 0));
  ASSERT_EQ(13, filtered_image(2, 2, 0, 0));
  ASSERT_EQ(14, filtered_image(3, 2, 0, 0));
  ASSERT_EQ(0, filtered_image(4, 2, 0, 0));

  ASSERT_EQ(16, filtered_image(0, 3, 0, 0));
  ASSERT_EQ(17, filtered_image(1, 3, 0, 0));
  ASSERT_EQ(18, filtered_image(2, 3, 0, 0));
  ASSERT_EQ(19, filtered_image(3, 3, 0, 0));
  ASSERT_EQ(0, filtered_image(4, 3, 0, 0));

  ASSERT_EQ(21, filtered_image(0, 4, 0, 0));
  ASSERT_EQ(22, filtered_image(1, 4, 0, 0));
  ASSERT_EQ(23, filtered_image(2, 4, 0, 0));
  ASSERT_EQ(24, filtered_image(3, 4, 0, 0));
  ASSERT_EQ(0, filtered_image(4, 4, 0, 0));
}

TEST(ImageFiltering, Sharp) {
  CImg<unsigned char> filter(5, 5, 1, 1, 128);
  CImg<unsigned char> image(5, 2, 1, 1, 128);
  
  // The right-most, middle value is 2.
  filter(2, 2, 0, 0) = 128 + 5;
  filter(1, 2, 0, 0) = 128 -1;
  filter(3, 2, 0, 0) = 128 -1;
  filter(2, 1, 0, 0) = 128 -1;
  filter(2, 3, 0, 0) = 128 -1;
  

  // Fill up the image.
  image(0, 0, 0, 0) = 0;
  image(1, 0, 0, 0) = 1;
  image(2, 0, 0, 0) = 2;
  image(3, 0, 0, 0) = 3;
  image(4, 0, 0, 0) = 4;

  image(0, 1, 0, 0) = 5;
  image(1, 1, 0, 0) = 6;
  image(2, 1, 0, 0) = 7;
  image(3, 1, 0, 0) = 8;
  image(4, 1, 0, 0) = 9;
  /*
  image(0, 2, 0, 0) = 10;
  image(1, 2, 0, 0) = 11;
  image(2, 2, 0, 0) = 12;
  image(3, 2, 0, 0) = 13;
  image(4, 2, 0, 0) = 14;

  image(0, 3, 0, 0) = 15;
  image(1, 3, 0, 0) = 16;
  image(2, 3, 0, 0) = 17;
  image(3, 3, 0, 0) = 18;
  image(4, 3, 0, 0) = 19;

  image(0, 4, 0, 0) = 20;
  image(1, 4, 0, 0) = 21;
  image(2, 4, 0, 0) = 22;
  image(3, 4, 0, 0) = 23;
  image(4, 4, 0, 0) = 24;*/
  
  const CImg<unsigned char> filtered_image = FilterImage(image, filter);

  ASSERT_EQ(0, filtered_image(0, 0, 0, 0));
  ASSERT_EQ(0, filtered_image(1, 0, 0, 0));
  ASSERT_EQ(0, filtered_image(2, 0, 0, 0));
  ASSERT_EQ(0, filtered_image(3, 0, 0, 0));
  ASSERT_EQ(2, filtered_image(4, 0, 0, 0));

  ASSERT_EQ(6, filtered_image(0, 1, 0, 0));
  ASSERT_EQ(8, filtered_image(1, 1, 0, 0));
  ASSERT_EQ(9, filtered_image(2, 1, 0, 0));
  ASSERT_EQ(10, filtered_image(3, 1, 0, 0));
  ASSERT_EQ(11, filtered_image(4, 1, 0, 0));
  /*
  ASSERT_EQ(11, filtered_image(0, 2, 0, 0));
  ASSERT_EQ(12, filtered_image(1, 2, 0, 0));
  ASSERT_EQ(13, filtered_image(2, 2, 0, 0));
  ASSERT_EQ(14, filtered_image(3, 2, 0, 0));
  ASSERT_EQ(0, filtered_image(4, 2, 0, 0));

  ASSERT_EQ(16, filtered_image(0, 3, 0, 0));
  ASSERT_EQ(17, filtered_image(1, 3, 0, 0));
  ASSERT_EQ(18, filtered_image(2, 3, 0, 0));
  ASSERT_EQ(19, filtered_image(3, 3, 0, 0));
  ASSERT_EQ(0, filtered_image(4, 3, 0, 0));

  ASSERT_EQ(21, filtered_image(0, 4, 0, 0));
  ASSERT_EQ(22, filtered_image(1, 4, 0, 0));
  ASSERT_EQ(23, filtered_image(2, 4, 0, 0));
  ASSERT_EQ(24, filtered_image(3, 4, 0, 0));
  ASSERT_EQ(0, filtered_image(4, 4, 0, 0));*/
}

TEST(ImageFiltering, SharpLarger) {
  CImg<unsigned char> filter(5, 5, 1, 1, 128);
  CImg<unsigned char> image(5, 3, 1, 1, 128);
  
  // The right-most, middle value is 2.
  filter(2, 2, 0, 0) = 128 + 5;
  filter(1, 2, 0, 0) = 128 -1;
  filter(3, 2, 0, 0) = 128 -1;
  filter(2, 1, 0, 0) = 128 -1;
  filter(2, 3, 0, 0) = 128 -1;
  

  // Fill up the image.
  image(0, 0, 0, 0) = 0;
  image(1, 0, 0, 0) = 1;
  image(2, 0, 0, 0) = 2;
  image(3, 0, 0, 0) = 3;
  image(4, 0, 0, 0) = 4;

  image(0, 1, 0, 0) = 5;
  image(1, 1, 0, 0) = 6;
  image(2, 1, 0, 0) = 7;
  image(3, 1, 0, 0) = 8;
  image(4, 1, 0, 0) = 9;
  
  image(0, 2, 0, 0) = 10;
  image(1, 2, 0, 0) = 11;
  image(2, 2, 0, 0) = 12;
  image(3, 2, 0, 0) = 13;
  image(4, 2, 0, 0) = 14;
  /*
  image(0, 3, 0, 0) = 15;
  image(1, 3, 0, 0) = 16;
  image(2, 3, 0, 0) = 17;
  image(3, 3, 0, 0) = 18;
  image(4, 3, 0, 0) = 19;

  image(0, 4, 0, 0) = 20;
  image(1, 4, 0, 0) = 21;
  image(2, 4, 0, 0) = 22;
  image(3, 4, 0, 0) = 23;
  image(4, 4, 0, 0) = 24;*/
  
  const CImg<unsigned char> filtered_image = FilterImage(image, filter);

  ASSERT_EQ(0, filtered_image(0, 0, 0, 0));
  ASSERT_EQ(0, filtered_image(1, 0, 0, 0));
  ASSERT_EQ(0, filtered_image(2, 0, 0, 0));
  ASSERT_EQ(0, filtered_image(3, 0, 0, 0));
  ASSERT_EQ(2, filtered_image(4, 0, 0, 0));

  ASSERT_EQ(4, filtered_image(0, 1, 0, 0));
  ASSERT_EQ(6, filtered_image(1, 1, 0, 0));
  ASSERT_EQ(7, filtered_image(2, 1, 0, 0));
  ASSERT_EQ(8, filtered_image(3, 1, 0, 0));
  ASSERT_EQ(9, filtered_image(4, 1, 0, 0));

  ASSERT_EQ(11, filtered_image(0, 2, 0, 0));
  ASSERT_EQ(13, filtered_image(1, 2, 0, 0));
  ASSERT_EQ(14, filtered_image(2, 2, 0, 0));
  ASSERT_EQ(15, filtered_image(3, 2, 0, 0));
  ASSERT_EQ(16, filtered_image(4, 2, 0, 0));
  /*
  ASSERT_EQ(16, filtered_image(0, 3, 0, 0));
  ASSERT_EQ(17, filtered_image(1, 3, 0, 0));
  ASSERT_EQ(18, filtered_image(2, 3, 0, 0));
  ASSERT_EQ(19, filtered_image(3, 3, 0, 0));
  ASSERT_EQ(0, filtered_image(4, 3, 0, 0));

  ASSERT_EQ(21, filtered_image(0, 4, 0, 0));
  ASSERT_EQ(22, filtered_image(1, 4, 0, 0));
  ASSERT_EQ(23, filtered_image(2, 4, 0, 0));
  ASSERT_EQ(24, filtered_image(3, 4, 0, 0));
  ASSERT_EQ(0, filtered_image(4, 4, 0, 0));*/
}

int main(int argc, char * argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
