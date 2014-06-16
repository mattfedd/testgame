#include "SpriteSheet.h"

SpriteSheet::SpriteSheet(const char* filename)
{
	texture_ = LoadTexture(filename);
}

SpriteSheet::~SpriteSheet(void)
{

}

GLuint SpriteSheet::LoadTexture(const char* filename)
{
	GLuint Texture;  //variable for texture
	glGenTextures(1,&Texture); //allocate the memory for texture
	glBindTexture(GL_TEXTURE_2D,Texture); //Binding the texture

	if(glfwLoadTexture2D(filename, GLFW_BUILD_MIPMAPS_BIT | GLFW_ORIGIN_UL_BIT))
	{	
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
		return Texture;
	}
	else return -1;
}

GLuint SpriteSheet::getGLuintTexture()
{
	return texture_;
}