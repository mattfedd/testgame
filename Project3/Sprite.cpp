#include "Sprite.h"

Sprite::Sprite(int width, int height, SpriteSheet* ss)
{
	GLfloat temp_vert[12] = 
	{
		0.0f*width/SCREEN_WIDTH,1.0f*height/SCREEN_HEIGHT, 0.0f,
		1.0f*width/SCREEN_WIDTH,1.0f*height/SCREEN_HEIGHT, 0.0f,
		1.0f*width/SCREEN_WIDTH,0.0f*height/SCREEN_HEIGHT, 0.0f,
		0.0f*width/SCREEN_WIDTH,0.0f*height/SCREEN_HEIGHT, 0.0f
	};
	
	setVertexPoints(temp_vert);

	GLfloat temp_tex[12] = 
	{
		0.0f,1.0f,
		0.25f,1.0f,
		0.25f,0.75f,
		0.0f,0.75f
	};

	setTexturePoints(temp_tex);

	sheet_ = ss;
}

Sprite::~Sprite(void)
{

}

void Sprite::setVertexPoints(GLfloat* source)
{
	for(int i=0; i<12; ++i)
	{
		vertexPoints_[i] = source[i];
	}
}

void Sprite::setTexturePoints(GLfloat* source)
{
	for(int i=0; i<12; ++i)
	{
		texturePoints_[i] = source[i];
	}
}

GLfloat* Sprite::getVertexPoints()
{
	return vertexPoints_;
}

GLfloat* Sprite::getTexturePoints()
{
	return texturePoints_;
}

void Sprite::setAnimState(int new_state)
{

}

void Sprite::setSpriteSheet(SpriteSheet* tex)
{
	sheet_ = tex;
}

SpriteSheet* Sprite::getSpriteSheet()
{
	return sheet_;
}
