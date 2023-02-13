#include <iostream>
#include "imageParam.h"
using namespace std;

int main(){
    int numPixel = 256;
    int numScanlines = 127;
    int numElements = 128;
    imageParam* parameters = new imageParam();
    
    // Case 1 - Objective: Check Variable initialization
    cout<<"Testing Case 1: Correct Variable Initialization"<<endl;
    cout<<"numElement: Correct Value = 128, Your Value = "<<parameters->getNumElement()<<endl;
    if(parameters->getNumElement() == 128){
        cout<<"Success"<<endl;
    } else {
        cout<<"Failed"<<endl;
        return -1;
    }
    cout<<"numSample: Correct Value = 3338, Your Value = "<<parameters->getNumSample()<<endl;
    if(parameters->getNumSample() == 3338){
        cout<<"Success"<<endl;
    } else {
        cout<<"Failed"<<endl;
        return -1;
    }
    cout<<"numScanline: Correct Value = 127, Your Value = "<<parameters->getNumScanline()<<endl;
    if(parameters->getNumScanline() == 127){
        cout<<"Success"<<endl;
    } else {
        cout<<"Failed"<<endl;
        return -1;
    }

    // Case 2 - Objective: Check Element positions
    cout<<"Testing Case 2: Correct Element positions"<<endl;
    cout<<"getElementPosition(60) = -0.0010668, Your Value = "<<parameters->getElementPosition(60)<<endl;
    if(parameters->getElementPosition(60) > -0.0011 && parameters->getElementPosition(60) < -0.001){
        cout<<"Success"<<endl;
    } else {
        cout<<"Failed"<<endl;
        return -1;
    }
    cout<<"getElementPosition(110) = 0.0141732, Your Value = "<<parameters->getElementPosition(110)<<endl;
    if(parameters->getElementPosition(110) > 0.013 && parameters->getElementPosition(110) < 0.015){
        cout<<"Success"<<endl;
    } else {
        cout<<"Failed"<<endl;
        return -1;
    }

    // Case 3 - Objective: Check scanline positions
    cout<<"Testing Case 3: Correct Scanline positions"<<endl;
    cout<<"getXPosition(30,30) = -0.0100584, Your Value = "<<parameters->getXPosition(30,30)<<endl;
    if(parameters->getXPosition(30,30) > -0.0103632 && parameters->getXPosition(30,30) < -0.0097536){
        cout<<"Success"<<endl;
    } else {
        cout<<"Failed"<<endl;
        return -1;
    }
    cout<<"parameters->getYPosition(30,30) = 0.00588235, Your Value = "<<parameters->getYPosition(30,30)<<endl;
    if(parameters->getYPosition(30,30) > 0.00568627 && parameters->getYPosition(30,30) < 0.00607843){
        cout<<"Success"<<endl;
    } else {
        cout<<"Failed"<<endl;
        return -1;
    }
    cout<<"Testing Case 3: Correct Scanline positions"<<endl;
    cout<<"getXPosition(63,60) = 0, Your Value = "<<parameters->getXPosition(63,60)<<endl;
    if(parameters->getXPosition(63,60) > -0.001 && parameters->getXPosition(63,60) < 0.001){
        cout<<"Success"<<endl;
    } else {
        cout<<"Failed"<<endl;
        return -1;
    }
    cout<<"parameters->getYPosition(63,60) = 0.0117647, Your Value = "<<parameters->getYPosition(63,60)<<endl;
    if(parameters->getYPosition(63,60) > 0.0117 && parameters->getYPosition(63,60) < 0.0118){
        cout<<"Success"<<endl;
    } else {
        cout<<"Failed"<<endl;
        return -1;
    }

}