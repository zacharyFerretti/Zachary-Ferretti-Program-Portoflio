#include <CImg.h>
#include <iostream>
using cimg_library::CImg;
CImg<unsigned char> FilterImage(const CImg<unsigned char>& image, 
								const CImg<unsigned char>& filter);