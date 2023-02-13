#include "ImageDisplay.h"

#include<string>

GLfloat vertices[] =
{ //     COORDINATES     /        COLORS      /   TexCoord  //
	-1.0f, -1.0f, 0.0f,     1.0f, 0.0f, 0.0f,	0.0f, 0.0f, // Lower left corner
	-1.0f,  1.0f, 0.0f,     0.0f, 1.0f, 0.0f,	0.0f, 1.0f, // Upper left corner
	 1.0f,  1.0f, 0.0f,     0.0f, 0.0f, 1.0f,	1.0f, 1.0f, // Upper right corner
	 1.0f, -1.0f, 0.0f,     1.0f, 1.0f, 1.0f,	1.0f, 0.0f  // Lower right corner
};


// Indices for vertices order
GLuint indices[] =
{
	0, 2, 1, // Upper triangle
	0, 3, 2 // Lower triangle
};

// ImageDisplay::ImageDisplay(float *Image[],const int width, const int height){
ImageDisplay::ImageDisplay(){
    // std::cout<<"Here1"<<'\n';
    // float* bytes = format(Image,width,height);
    
	displayFlag = true;

    ///////// VISUALIZATION /////////////
	// Initialize GLFW
	glfwInit();

	// Tell GLFW what version of OpenGL we are using 
	// In this case we are using OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Tell GLFW we are using the CORE profile
	// So that means we only have the modern functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	/////// DONT FORGET FORWARD COMPAT FOR MAC VERSION //////////


	// Create a GLFWwindow object of 800 by 800 pixels, naming it "YoutubeOpenGL"
	// GLFWwindow* window = glfwCreateWindow(800, 800, "MyWindow", NULL, NULL);
	window = glfwCreateWindow(800, 800, "BME 121 Assignment 4 B-mode imaging", NULL, NULL);
	// Error check if the window fails to create
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return;
	}
	// Introduce the window into the current context
	glfwMakeContextCurrent(window);

	// Initialize GLEW
	glewInit();
	// Specify the viewport of OpenGL in the Window
	// In this case the viewport goes from x = 0, y = 0, to x = 800, y = 800
	glViewport(0, 0, 800, 800);

	// Generates Shader object using shaders default.vert and default.frag
	pshaderProgram = new Shader("default.vert", "default.frag");

	// Generates Vertex Array Object and binds it
	pVAO1 = new VAO();
    pVAO1->Bind();

	// Generates Vertex Buffer Object and links it to vertices
    pVBO1 = new VBO(vertices, sizeof(vertices));

	// Generates Element Buffer Object and links it to indices
    pEBO1 = new EBO(indices, sizeof(indices));

	// Links VBO attributes such as coordinates and colors to VAO
	pVAO1->LinkAttrib(pVBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	pVAO1->LinkAttrib(pVBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	pVAO1->LinkAttrib(pVBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	// Unbind all to prevent accidentally modifying them
	pVAO1->Unbind();
	pVBO1->Unbind();
	pEBO1->Unbind();

	// Texture
	ptexture = new Texturev2();
	ptexture->texUnit(pshaderProgram, "tex0", 0);

}

void ImageDisplay::display(float **Image,const int width, const int height){
	// Image data conversion
	float* bytes = format(Image,width,height);
	// output(bytes,"debug.txt",12);
	
	// Create Texture from Image
	ptexture->update(bytes, GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE, width, height);

	// Set Window Properties
	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	// Tell OpenGL which Shader Program we want to use
	pshaderProgram->Activate();
	// Binds texture so that is appears in rendering
	ptexture->Bind();
	// Bind the VAO so OpenGL knows to use it
	pVAO1->Bind();
	// Draw primitives, number of indices, datatype of indices, index of indices
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	// Swap the back buffer with the front buffer
	glfwSwapBuffers(window);
}

void ImageDisplay::exit(){
    std::cout<<"Exiting"<<"\n";
    // Delete all the objects we've created
	pVAO1->Delete();
	pVBO1->Delete();
	pEBO1->Delete();
	ptexture->Delete();
	pshaderProgram->Delete();
	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
}


void ImageDisplay::checkInput(){
	glfwPollEvents();

	if(glfwGetKey(window,GLFW_KEY_ESCAPE)==GLFW_PRESS){
        glfwSetWindowShouldClose(window,true);
		displayFlag = false;
    }
}

void ImageDisplay::output(float* data,std::string file, const int size){
	
    std::ofstream myfile;
    myfile.open (file);
    int count=0;
	for (int l=0; l<size; l++)
    {
		myfile<<data[l]<<',';
		if(count==4){
			myfile << "\n";
			count=0;
		}
    }
    myfile.close();
}

float* ImageDisplay::format(float** Result, const int numScanline, const int numPixel){

	/// NOTE: Result[numScanline][numPixel] 
	/// Find maximum value for normalization
	float max_num = 0;
	// for (int l=0; l<height; l++)
	for (int l=0; l<numPixel; l++)
	{
		// for (int k=0; k<width; k++){
		for (int k=0; k<numScanline ; k++){
				// std::cout<<Result[k][l]<<std::endl;
                if(Result[k][l]>max_num){
					max_num = Result[k][l];
				}
				// if(Result[l][k]>max_num){
				// 	max_num = Result[l][k];
				// }
		}
	}
	max_num = 20 * log10(std::max(float(0.001), max_num));
	// std::cout<<"Max: "<<max_num<<std::endl;

	//// Create float array of pixel values
	// Format: [R1,G1,B1,A1,R2,G2,B2,A2,...]
	//          (-Pixel 1-),(-Pixel 2-),...
	float* bytes = new float[numPixel*numScanline*4];
	float temp;
	for (int l=0; l<numPixel; l++)
	{
		for (int k=0; k<numScanline; k++){
				// std::cout<<"l = "<<l<<" k = "<<k<<std::endl;
				// std::cout<<(height-1)-l<<" "<<k<<std::endl;
				temp = 20 * log10(std::max(float(0.001), Result[k][(numPixel-1)-l]));
				bytes[(4*((numScanline*l)+k))+0] = temp/max_num; //Result[(numPixel-1)-k][l]/max; //Normalize pixel values before storing
				bytes[(4*((numScanline*l)+k))+1] = temp/max_num;
				bytes[(4*((numScanline*l)+k))+2] = temp/max_num;
				bytes[(4*((numScanline*l)+k))+3] = 1;
		}
	}
    // std::cout<<"Formatting Done"<<'\n';
	return bytes;
}