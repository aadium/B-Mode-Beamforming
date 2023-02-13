#include <iostream>
#include "ImageDisplay.h"
#include "dataBuffer.h"
#include "BmodeClass.h"
#include "imageParam.h"

using namespace std;

int main(){
    
    //// 1. Initialize imaging parameters
    int numFrames = 2;
    imageParam *parameters = new imageParam();
    cout<<"Params Created"<<endl;
    
    //// 2. Import data into linked list
    // Create ifstream objects to keep track of line position 
    ifstream *imagFile = new ifstream;
    ifstream *realFile = new ifstream;
    imagFile->open("A4ImagRFData.txt");     // Replace the file name to A4ImagRFData_Mystery for last part
    realFile->open("A4RealRFData.txt");     // Replace the file name to A4RealRFData_Mystery for last part
    if (imagFile->fail() || realFile->fail())
    {
        cerr<<"Cannot load from file, exiting program" << std::endl;
        return -1;
    }

    // Read data from files into dataBuffer objects
    dataBuffer* dataHead = new dataBuffer(imagFile,realFile,parameters->getNumElement(),parameters->getNumSample(),0); // Create head node
    dataHead->next = NULL; // Initialize head node "next" attibute
    dataBuffer *currentData = dataHead; //Initialize current data pointer
    for(int i = 1; i < parameters->getNumScanline(); i++){
        currentData->next = new dataBuffer(imagFile,realFile,parameters->getNumElement(),parameters->getNumSample(),i); // Create new node and assign address to current node "next" attribute
        currentData = currentData->next; // Point current node to newly created node
        currentData->next = NULL; // Set new node "next" attribute to NULL
    }
    // Close and delete ifstream objects
    imagFile->close();
    realFile->close();
    delete imagFile;
    delete realFile;
    cout<<"Data Buffer Created"<<endl;

    
    //// 3. Beamform data into linked list
    BmodeClass *scanlineHead = new BmodeClass(parameters, dataHead, 0);
    scanlineHead->next = NULL;

    // ASSIGNMENT 4 PART 5 BEGIN: TO BE COMPLETED BY STUDENTS
    
    BmodeClass *currentScanline = scanlineHead;
    currentData = dataHead;

    for (int i = 1; i < parameters->getNumScanline(); i++)
    {
        currentData = currentData->next;
        currentScanline->next = new BmodeClass(parameters, currentData, i); //creates an object at the next position in the list
        currentScanline = currentScanline->next; //advances the current position of the list to the next position
        currentScanline->next = NULL; //Advances the list tail until 'numScanline' is reached
    }

    // END OF ASSIGNMENT 4 PART 5

    cout<<"Scanline Buffer Created"<<endl;

    //// 4. Aggregate all scanlines into bmode image
    float **image2D = new float*[parameters->getNumScanline()]; // Create array of pointers
    currentScanline = scanlineHead; // Point current scanline to scanline node head
    for (int i=0; i<parameters->getNumScanline(); i++){
        image2D[i] = new float[parameters->getNumPixel()];
        currentScanline->getScanline(image2D[i]); // Point each array element to scanline contained in node
        currentScanline = currentScanline->next; // Point current scanline to next node
    }
    cout<<"Scanlines Aggregated"<<endl;

    //// 5. Display Linked list
    ImageDisplay imaging;
    cout<<"ImageDisplay Created"<<endl;

    // Visualization loop
    imaging.display(image2D, parameters->getNumScanline(), parameters->getNumPixel());
    while(imaging.displayFlag){
        imaging.checkInput(); // Check for keyboard presses
    }

    // Stop imaging and destroy imaging objects
    imaging.exit();

    //// 6. Destroy all objects
    //Destroy Images
    dataBuffer *nextData;
    currentData = dataHead;
    for(int f = 0; f<parameters->getNumScanline(); f++){
        // Store next object
        nextData = currentData->next;
        // Destroy Current
        delete currentData;
        // Move on to the next object
        currentData = nextData;

        // Delete image data
        delete [] image2D[f]; // use delete [] to deallocate an array
    }
    delete [] image2D; // use delete [] to deallocate an array

    //Destroy Data
    BmodeClass *nextScanline;
    currentScanline = scanlineHead;
    for(int f = 0; f<parameters->getNumScanline(); f++){
        // currentData = currentData->next;
        // Store next object
        // Destroy Current
        nextScanline = currentScanline->next;
        delete currentScanline;
        currentScanline = nextScanline;
    }
    
    //Destroy Params
    delete parameters;

    return 0;
}