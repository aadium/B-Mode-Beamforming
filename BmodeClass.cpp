#include "BmodeClass.h"
using namespace std;

BmodeClass::BmodeClass()
{
    // declaring variables
    imparams = NULL;
    RFData = NULL;
    next = NULL;
    line = 0;
}

BmodeClass::BmodeClass(imageParam *params,dataBuffer *data,int numline)
{
    // declaring variables
    imparams = params;
    RFData = data;
    line = numline;
    scanline = createScanline(imparams->getNumPixel()); // We invoke createScanline to allocate memory for scanline
    beamform(); // We invoke beamform to beamform the scanline
}

BmodeClass::~BmodeClass()
{
    deleteScanline(); // releases the arrays dynamically allocated for scanline
}

float *BmodeClass::createScanline(int numPixel)
{
    // creating a float pointer array 'mem' and assign a float array to it.
    float *mem = new float [numPixel];
    return mem;
}

void BmodeClass::beamform()
{
    // declaring variables
    float tforward = 0;
    float tbackward = 0;
    float ttotal = 0;
    float sample = 0;

    for (int i = 0; i < imparams->getNumPixel(); i++)
    {
        // declaring the variables PReal and PImag
        float PReal = 0;
        float Pimag = 0;    
        // mathematical operations are used to get the values of the variables declared in this class
        for (int j = 0; j < imparams->getNumElement(); j++)
        {
            tforward = (imparams->getYPosition(line,i))/(imparams->SOS);

            tbackward = (sqrt(pow(imparams->getYPosition(line,i), 2) + (pow(imparams->getXPosition(line,i) - imparams->getElementPosition(j), 2))))/(imparams->SOS);

            ttotal = tforward + tbackward;

            sample = floor(ttotal * (imparams->FS));

// the following code breaks the loop if the value of the sample variable is more than the value of numSample (3338)
            if (sample > imparams->getNumSample())
            {
                cerr << "Invalid sample number" << endl;
                break;
            }

// PReal is incremented everytime the condition is met            
            if (sample < imparams->getNumSample())
            {
            PReal += (RFData->getRealRFData(j, sample));
            
            Pimag += (RFData->getImagRFData(j, sample));
            }
        }

        scanline[i] = sqrt(pow(PReal, 2) + pow(Pimag, 2));
    }
    
}

void BmodeClass::getScanline(float *data)
// Copies the content inside 'scanline' to 'data' element-by-element
{
    for (int i = 0; i < imparams->getNumPixel(); i++)
    {
        data[i] = scanline[i];
    }
    
}

void BmodeClass::deleteScanline()
// releases the memory allocated for 'scanline'
{
    delete scanline;
}