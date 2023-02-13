#ifndef TEXTURE_CLASS_H
#define TEXTURE_CLASS_H

#include<GL/glew.h>

#include"shaderClass.h"

class Texturev2
{
public:
	GLuint ID;
	GLenum type;
	Texturev2(); // Default Constructor?
	// Texturev2(const float* image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType, const int width, const int height);

	// Assigns a texture unit to a texture
	// void texUnit(Shader& shader, const char* uniform, GLuint unit);
	void texUnit(Shader* shader, const char* uniform, GLuint unit);
	// Binds a texture
	void Bind();
	// Unbinds a texture
	void Unbind();
	// Deletes a texture
	void Delete();
    // Updates Display Texture
    void update(const float* image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType, const int width, const int height);
};
#endif