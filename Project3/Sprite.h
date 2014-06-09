#ifndef SPRITE_H
#define SPRITE_H

#include "Includes.h"

class Sprite
{
private:
	GLfloat vertexPoints_[12];
	GLfloat texturePoints[12];
	int animState_;
	//Animation* anim_;

	void setVertexPoints(GLfloat* source);
	void setTexturePoints(GLfloat* source);

public:
	Sprite(void);
	~Sprite(void);

	void draw();

	GLfloat* getVertPoints();
	GLfloat* getTexturePoints();





};





#endif
