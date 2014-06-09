#ifndef SPRITE_H
#define SPRITE_H

#include "Includes.h"
#include "Texture.h"

class Sprite
{
private:
	GLfloat vertexPoints_[12];
	GLfloat texturePoints[12];
	int animState_;
	Texture texture_;
	//Animation* anim_;

	void setVertexPoints(GLfloat* source);
	void setTexturePoints(GLfloat* source);

public:
	Sprite(void);
	~Sprite(void);

	void draw();

	GLfloat* getVertexPoints();
	GLfloat* getTexturePoints();

	void setAnimState(int new_state);

	Texture* getTexture();
};





#endif
