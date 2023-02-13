#include "dataBuffer.h"
#include <iostream>
#include <fstream>

using namespace std;

int main(){

    int numElements = 128;
    int numSample = 3338;
    int numScanline = 127;
    ifstream* imagData = new ifstream;
    ifstream* realData = new ifstream;
    imagData->open("A4ImagRFData.txt");     // Replace the file name to A4ImagRFData_Mystery for last part
    realData->open("A4RealRFData.txt");     // Replace the file name to A4RealRFData_Mystery for last part
    
    // Objective: Check next = NULL
    // Case 1
    dataBuffer* testBuffer_default = new dataBuffer();
    cout<<"Testing Case 1: next = NULL"<<endl;
    if(testBuffer_default->next == NULL){
        cout<<"Success"<<endl;
    } else {
        cout<<"Failed"<<endl;
        return -1;
    }
    delete testBuffer_default;

    // Objective: Check getXData functionality
    // Case 2: 
    dataBuffer* testBuffer = new dataBuffer(imagData,realData, numElements, numSample, numScanline);
    cout<<"Testing Case 2: getRealRFData(element = 3, sample = 0)"<<endl;
    cout<<"Test Value: -648.096"<<" , "<<"Your Value: "<<testBuffer->getRealRFData(3,0)<< endl;
    if((testBuffer->getRealRFData(3,0) < -648) && (testBuffer->getRealRFData(3,0) > -649)){
        cout<<"Success"<<endl;
    } else {
        cout<<"Failed"<<endl;
        return -1;
    }
    
    // Case 3
    cout<<"Testing Case 3: getImagRFData(element = 64, sample = 1500)"<<endl;
    cout<<"Test Value: 10.3761"<<" , "<<"Your Value: "<<testBuffer->getImagRFData(64,1500)<< endl;
    if((testBuffer->getImagRFData(64,1500) > 10) && (testBuffer->getImagRFData(64,1500) < 11)){
        cout<<"Success"<<endl;
    } else {
        cout<<"Failed"<<endl;
        return -1;
    }

}