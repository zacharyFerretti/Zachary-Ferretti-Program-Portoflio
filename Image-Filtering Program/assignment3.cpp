#include <CImg.h>
#include <iostream>
using cimg_library::CImg;
float performConvulotion(int rowLocation, int columnLocation, CImg<unsigned char>& image, CImg<unsigned char>& filter, int spectrum);

CImg<unsigned char> FilterImage(const CImg<unsigned char>& image, const CImg<unsigned char>& filter){
        CImg<unsigned char> dupeImage=image;
        CImg<unsigned char> returningImage= image;
        CImg<unsigned char> dupeFilter=filter;
        for(int currentSpectrum=0; currentSpectrum<image.spectrum();currentSpectrum++){
            for(int row=0; row<image.height();row++){
                for(int column=0; column<image.width(); column++){             
                    float newPixelValue = performConvulotion(row,column, dupeImage, dupeFilter, currentSpectrum);
                    returningImage(column,row,0,currentSpectrum) = (unsigned char) newPixelValue;
                }
            }
        }
        return returningImage;      
}
float performConvulotion(int rowLocation, int columnLocation, CImg<unsigned char>& image, CImg<unsigned char>& filter, int spectrum){
    int filterRowLocation=0;
    int filterColumnLocation=0;
    float pixelValueSumNum=0, filterSumDenom=0;
    for(int row= rowLocation-(filter.height()/2); row<=rowLocation+(filter.height()/2); row++){
        for(int column= columnLocation-(filter.width()/2); column<=columnLocation+(filter.width()/2); column++){
            if( (row<0 || row>image.height()-1) || (column<0 || column>image.width()-1)){
                filterColumnLocation++;
                if(filterColumnLocation>=filter.width()){filterColumnLocation=0; filterRowLocation++;}      
            }
            else{
                float pixelValue = image(column,row,0,spectrum)-128;
                float filterValue= filter(filterColumnLocation,filterRowLocation,0,0)-128;
                pixelValueSumNum=pixelValueSumNum+(pixelValue*filterValue);
                filterSumDenom=filterSumDenom+(filterValue);
                filterColumnLocation++;
                if(filterColumnLocation>=filter.width()){filterColumnLocation=0; filterRowLocation++;}
            }
        }
    }
    if (filterSumDenom==0){ filterSumDenom=0;}
    float average=(pixelValueSumNum/filterSumDenom)+128;
    if(average<0){average=0;}
    else if(average>255){average=255;}
    return average;
}