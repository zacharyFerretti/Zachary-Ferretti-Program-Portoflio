#include <iostream>
#include <CImg.h>
#include "assignment3.h"

using cimg_library::CImg;
using cimg_library::CImgDisplay;
using std::cerr;
using std::cout;

void PrintImage(const CImg<unsigned char>& image) {
  for (int y = 0; y < image.height(); ++y) {
  }
}

int main (int num_args, char* args[]) {
  if (num_args < 3) {
    std::cerr << "Usage: ./filter filter_file image_file\n";
    return 1;
  }
  CImg<unsigned char> filter(args[1]);
  CImg<unsigned char> image(args[2]);
  CImg<unsigned char> filtered_image = FilterImage(image, filter);
  CImgDisplay display(filtered_image, "Filtered Image");
  while (!display.is_closed()) {
    display.wait();
  }
  return 0;
}
