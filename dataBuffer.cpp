#include "dataBuffer.h"
using namespace std;

dataBuffer::dataBuffer()
{
    // declaring variables
    numElement = 0;
    numSample = 0;
    scanline = 0;
    dataMatrix = NULL;
    next = NULL;
}

dataBuffer::dataBuffer(std::ifstream *imagFile, std::ifstream *realFile, int inputNumElement, int inputNumSample, int inputScanline)
{
    // Assigning variables to the corresponding counterpart of the class component variables
    numElement = inputNumElement;
    numSample = inputNumSample;
    scanline = inputScanline;
    dataMatrix = createDataMatrix();
    loadRFData(dataMatrix, imagFile, realFile); // populating the dataMatrix, imagFile and realFile are two ifstream pointers that point to the file object for data reading

} 

dataBuffer::~dataBuffer()
{
    deleteDataMatrix(); // releasing the 2D array dynamically allocated for dataMatrix
}

complex **dataBuffer::createDataMatrix()
{
    complex **RFData = new complex *[numElement];

    // allocates a complex array of length numElement to each of the RFData pointer
    for (int i = 0; i < numElement; i++)
    {
        RFData[i] = new complex[numSample];
    }

    return RFData;
}

int dataBuffer::loadRFData(complex **RFData, std::ifstream *imagFile, std::ifstream *realFile) 
{ 
    // create a 'real' and 'imag' character array with a maximum length of 50 characters to store the imput file data
    char real[50];
    char imag[50];

    // Getline() command is used to extract the data lines from the txt files
    for (int i = 0; i < numElement; i++)
    {
        for (int j = 0; j < numSample; j++)
        {
            imagFile->getline(imag, 50);
            realFile->getline(real, 50);

            RFData[i][j].imag = atof(imag);
            RFData[i][j].real = atof(real);
        }
    }

    return 0;
}

float dataBuffer::getRealRFData(int element,int sample)
{
    return dataMatrix[element][sample].real; // Returns the real component of the complex data stored in dataMatrix
}
float dataBuffer::getImagRFData(int element,int sample)
{
    return dataMatrix[element][sample].imag; // Returns the imaginary component of the complex data stored in dataMatrix
}

void dataBuffer::deleteDataMatrix()
// releasing the 2D dataMatrix array
{
    for (int i = 0; i < numElement; i++)
    {
        delete dataMatrix[i];
    }
    delete dataMatrix;
}




