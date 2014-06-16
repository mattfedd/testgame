#ifndef SPRITE_SHEET_H
#define SPRITE_SHEET_H

#include "Includes.h"

/*
 A glorified texture wrapper.
 Basically this is supposed to be a shared piece of data 
 for all entities that reference a single spritesheet, so 
 we don't repeat ourselves unnecessarily.
*/

class SpriteSheet
{
private:
	GLuint texture_;
	int width_;
	int height_;

	GLuint LoadTexture(const char* filename);

public:
	SpriteSheet(const char* filename);
	~SpriteSheet(void);
	GLuint getGLuintTexture();
};


#endif