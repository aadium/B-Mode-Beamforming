#include <iostream>


#ifndef IMAGE_PARAM_HEADER
#define IMAGE_PARAM_HEADER

struct float2{ // Use a function called scanlinePosition which returns 2d array of float 2
    float x;
    float y;
};

class imageParam
{
    public:
        ////Public data components 
        // These are constant parameters and are pre-defined for you
        const float PITCH = 0.3048/1000;    // This is the transducer pitch
        const float SOS = 1540;             // Speed of sound variable
        const float FS = 40e6;              // Sampling frequency variable
        const float TS = 1.f/FS;              // Sampling time variable        
        
        // Public methods
        imageParam();
        ~imageParam();
        
        // Interface functions to return a value of the private variables
        float getXPosition(int scanline, int pixel); 
        float getYPosition(int scanline, int pixel); 
        float getElementPosition(int element);
        int getNumElement();
        int getNumSample();
        int getNumScanline();
        int getNumPixel();

    private:
        // Private data components
        int numElement;                     // Number of channels
        int numSample;                      // Number of Samples
        int numScanline;                    // Number of scanlines
        int numPixel;                       // Number of pixels per scanline
        float desiredDepth;                 // Imaging depth [in meter]
        float2 **scanlinePosition;         // 2D array storing the physical location of each scanline [x-,z-directions, in meter]
        float *elementPosition;             // 1D array storing element physical locations [x-direction, in meter]
        
        

        // Private methods
        // Create a 2D array and derive the physical location of all pixels and scanlines
        float2 **genScanlinePosition(int numScanline, float PITCH, float* elementLocation);
        // Create a 1D array and derive the physical location of each transducer element
        float *genElementPosition();
        void deletePositionArray();
};

#endif