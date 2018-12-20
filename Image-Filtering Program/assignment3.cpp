#include <iostream>
#include "CImg.h"


using namespace cimg_library;
using cimg_library::CImg;


//float performConvulotion(int Row_Location, int columnLocation, CImg<unsigned char>& image, CImg<unsigned char>& filter, int spectrum);


float performConvulotion(int  Row_Location, int columnLocation, CImg<unsigned char>& image, CImg<unsigned char>& filter, int spectrum){

	int filterRowLocation=0;
	int filterColumnLocation=0;
	float Pixel_Value_Sum_Numerator=0, Filter_Sum_Denominator=0;

	for(int Row =  Row_Location-(filter.height()/2); Row <= Row_Location+(filter.height()/2); Row ++){
		
		for(int Column = columnLocation-(filter.width()/2); Column <=columnLocation+(filter.width()/2); Column ++){
			
			if( (Row <0 || Row >image.height()-1) || (Column <0 || Column >image.width()-1)){
				filterColumnLocation++;

				if(filterColumnLocation>=filter.width()){	filterColumnLocation=0; filterRowLocation++;	}      
			}

			else{
				float Pixel_Value = image(Column ,Row ,0,spectrum)-128;
				float Filter_Value= filter(filterColumnLocation,filterRowLocation,0,0)-128;
				Pixel_Value_Sum_Numerator=Pixel_Value_Sum_Numerator+(Pixel_Value*Filter_Value);
				Filter_Sum_Denominator=Filter_Sum_Denominator+(Filter_Value);
				filterColumnLocation++;

				if(filterColumnLocation>=filter.width()){	filterColumnLocation=0; filterRowLocation++;	}
			}

		}
	}

	if (Filter_Sum_Denominator==0){	Filter_Sum_Denominator=1;	}//Changing this to one as opposed to zero for sake of not dividing by zero?

	float average=(Pixel_Value_Sum_Numerator/Filter_Sum_Denominator)+128;

	if(average<0){	average=0;	}

	else if(average>255){	average=255;	}

	return average;
}

CImg<unsigned char> FilterImage(const CImg<unsigned char>& image, const CImg<unsigned char>& filter){

	CImg<unsigned char> Copy_Image=image;
	CImg<unsigned char> Returning_Image= image;
	CImg<unsigned char> Copy_Filter=filter;
        /***
		 Goes through each channel in the image, by getting the spectrum of the image. Then goes through every
		 pixel in the array with dimensions height * width. 
         ***/

	for(int Current_Spectrum=0; Current_Spectrum<image.spectrum();Current_Spectrum++){

		for(int Row=0; Row<image.height();Row++){

			for(int Column=0; Column<image.width(); Column++){             

				float newPixelValue = performConvulotion(Row,Column, Copy_Image, Copy_Filter, Current_Spectrum);
				Returning_Image(Column,Row,0,Current_Spectrum) = (unsigned char) newPixelValue;

			}

		}

	}
	return Returning_Image;      
}