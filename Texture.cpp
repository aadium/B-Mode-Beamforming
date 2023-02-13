#include"Texture.h"
#include<iostream>

// Texturev2::Texturev2(){} //Default Constructor?

// Texturev2::Texturev2(const float* image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType, const int width, const int height)
Texturev2::Texturev2()
{
	GLenum texType = GL_TEXTURE_2D;
	
	// Assigns the type of the texture ot the texture object
	type = texType;

	///////////////////////////////////////////////////////////
	// Generates an OpenGL texture object
	glGenTextures(1, &ID);
	// std::cout<<"ID = "<<ID<<std::endl;
	// Assigns the texture to a Texture Unit
	glActiveTexture(GL_TEXTURE0);
	// glBindTexture(texType, ID);

	// Configures the type of algorithm that is used to make the image smaller or bigger
	glTexParameteri(texType, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	glTexParameteri(texType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// Configures the way the texture repeats (if it does at all)
	glTexParameteri(texType, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(texType, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// Extra lines in case you choose to use GL_CLAMP_TO_BORDER
	// float flatColor[] = {1.0f, 1.0f, 1.0f, 1.0f};
	// glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, flatColor);

	// Assigns the image to the OpenGL Texture object
	// glTexImage2D(texType, 0, GL_RGBA, width, height, 0, format, GL_FLOAT, image);
	// Generates MipMaps
	// glGenerateMipmap(texType);

	// Unbinds the OpenGL Texture object so that it can't accidentally be modified
	// glBindTexture(texType, 0);
}

void Texturev2::update(const float* image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType, const int width, const int height){
    // glActiveTexture(slot);
	glActiveTexture(GL_TEXTURE0);
	// std::cout<<"Update 1: "<<ID<<std::endl;
	glBindTexture(texType, ID);

    // Assigns the image to the OpenGL Texture object
	glTexImage2D(texType, 0, GL_RGBA, width, height, 0, format, GL_FLOAT, image);
	// Generates MipMaps
	glGenerateMipmap(texType);

	// Unbinds the OpenGL Texture object so that it can't accidentally be modified
	// glBindTexture(texType, 0);
	// std::cout<<"Update 2: "<<ID<<std::endl;
}

void Texturev2::texUnit(Shader* shader, const char* uniform, GLuint unit)
{
	// Gets the location of the uniform
	// std::cout<<shader->ID<<std::endl;
	GLuint texUni = glGetUniformLocation(shader->ID, uniform);
	// Shader needs to be activated before changing the value of a uniform
	shader->Activate();
	// Sets the value of the uniform
	glUniform1i(texUni, unit);
}

void Texturev2::Bind()
{
	// std::cout<<"Binding ID = "<<ID<<std::endl;
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(type, ID);
	// glBindTexture(type, 1);
}

void Texturev2::Unbind()
{
	glBindTexture(type, 0);
}

void Texturev2::Delete()
{
	glDeleteTextures(1, &ID);
}