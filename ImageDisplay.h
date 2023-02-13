#include<iostream>
#include<string>
#include<cmath>
#include<fstream>
#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<windows.h>

#include"Texture.h"
#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"

class ImageDisplay{
public:
    GLFWwindow* window;
    VAO* pVAO1; // use pointer to object? HOW TO CREATE OBJECT INSIDE OBJECT THAT IS VISIBLE TO METHODS???????
    VBO* pVBO1;
    EBO* pEBO1;
    // Texture* ptexture;
    Texturev2* ptexture;
    Shader* pshaderProgram;

    bool displayFlag;

    ImageDisplay(); // Initialize GLEW,GLFW, and window instance. Create and bind VAO,VBO,EBO instances

    void display(float **Image,const int width, const int height); // Display frame
    
    void checkInput(); // Check for keyboard presses to exit program
    void exit(); // Destroy VAO,VBO,EBO,window instances
private:
    float* format(float **Result, const int numPixel, const int numScanline);
    void output(float* data,std::string file, const int size); // Debugging: Output to csv
};