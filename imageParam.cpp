#include "imageParam.h"
using namespace std;

imageParam::imageParam()
{
// declaring variables
    numElement = 128;
    numSample = 3338;
    numScanline = 127;
    elementPosition = genElementPosition();
    scanlinePosition = genScanlinePosition(numScanline, PITCH, elementPosition);
}

imageParam::~imageParam()
// releases the arrays dynamically allocated for elementPosition and scanlinePosition
{
    deletePositionArray();
}

float *imageParam::genElementPosition()
{
    // we create a pointer 'elementPosition' and assign a float array to it
    float *elementPosition;
    elementPosition = new float [numElement];

    // we assign the value of the nth element of the array by the below for loop
    for (int n = 0; n < numElement; n++)
    {
        elementPosition[n] = ((n - (((float)numElement - 1) / 2)) * PITCH);
    }
    return elementPosition;
}

float2 **imageParam::genScanlinePosition(int numScanline, const float PITCH, float* elementLocation)
{
    //taking the inputs of desiredDepth and numPixel from the user
    cout << "Depth" << endl;
    cin >> desiredDepth;

    cout << "Number of pixels" << endl;
    cin >> numPixel;

    // declaring a variable increment
    float increment = desiredDepth / (numPixel - 1);
    
    // creating a double pointer scanlinePosition that holds a float2 pointer array of length numScanline
    float2 **scanlinePosition = new float2 *[numScanline];

    // we derive the lateral position of the mth scanline by the below for loop
    for (int m = 0; m < numScanline; m++)
    {
        scanlinePosition[m] = new float2[numPixel];
        for (int i = 0; i <= numPixel; i++)
        {
            scanlinePosition[m][i].x = (m - ((numScanline - 1) / 2)) * PITCH;
            scanlinePosition[m][i].y = i * increment;
        }
    }
    
    return scanlinePosition;

}

float imageParam::getXPosition(int scanline, int pixel)
// This interface function is designed to return the x-coordinate of a pixel (scanlinePosition) specified by scanline and pixel
{
    return scanlinePosition[scanline][pixel].x; 
}

float imageParam::getYPosition(int scanline, int pixel)
// This interface function is designed to return the y-coordinate of a pixel (scanlinePosition) specified by scanline and pixel
{
    return scanlinePosition[scanline][pixel].y;
}

float imageParam::getElementPosition(int element)
// This interface function is designed to return the position of an element (elementPosition) specified by element
{
    return elementPosition[element];
}

// In the below functions, we return the respective private data components of the class
int imageParam::getNumElement()
{
    return numElement;
}

int imageParam::getNumSample()
{
    return numSample;
}

int imageParam::getNumScanline() 
{
    return numScanline;
}

int imageParam::getNumPixel() 
{
    return numPixel;
}

// We release the memory allocated for scanlinePosition and elementPosition by the below function
void imageParam::deletePositionArray()
{
    delete elementPosition;

    for (int i = 0; i < numScanline; i++)
    {
        delete scanlinePosition[i];
    }

    delete scanlinePosition;

}









