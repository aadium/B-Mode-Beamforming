#include <iostream>
#include <fstream>
#include <cmath>

#ifndef DATA_BUFFER_HEADER
#define DATA_BUFFER_HEADER

struct complex{
    float imag;
    float real;
};

class dataBuffer
{
    public:
        // Public Attributes
        dataBuffer *next;

        // Constructor
        dataBuffer(); //Default Constuctor
        dataBuffer(std::ifstream *imagFile, std::ifstream *realFile, int numElement, int numSample, int scanline);
        
        // Destructor
        ~dataBuffer();
        
        // Public Methods
        int loadRFData(complex **RFData, std::ifstream *imagFile, std::ifstream *realFile);
        float getRealRFData(int element,int sample);
        float getImagRFData(int element,int sample);
        void deleteDataMatrix();
    private:
        int numElement;
        int numSample;
        int scanline;
        complex **dataMatrix;
        // Private Methods
        complex **createDataMatrix(); //float **createDataMatrix(int numElement, int numSample, int numScan);
};

#endif