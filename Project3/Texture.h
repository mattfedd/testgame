#ifndef TEXTURE_H
#define TEXTURE_H

#include "Includes.h"

class Texture
{
private:
	GLuint texture_;
	int width_;
	int height_;

	GLuint LoadTexture(const char* filename);

public:
	Texture(void);
	Texture(const char* filename);
	~Texture(void);

	int getWidth();
	int getHeight();
	GLuint getGLuintTexture();
};


#endif