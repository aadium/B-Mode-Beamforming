#include <iostream>
#include <fstream>
#include <cmath>
#include <algorithm>

#include "dataBuffer.h"
#include "imageParam.h"

#ifndef IMAGE_BUFFER_HEADER
#define IMAGE_BUFFER_HEADER

class BmodeClass
{
    public:
        // Public data component
        imageParam *imparams;
        dataBuffer *RFData;
        BmodeClass *next;
        int line;

        // Constructor
        BmodeClass();
        BmodeClass(imageParam *params,dataBuffer *data,int numline);
        
        // Destructor
        ~BmodeClass();
        
        // Public methods
        void beamform();
        void getScanline(float *data); // a new array containing a copy of the scanline is returned
        void deleteScanline();

    private:
        // private data component
        float* scanline;
        // private methods
        float *createScanline(int numPixel);
};

#endif