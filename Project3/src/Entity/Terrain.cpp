#include "Terrain.h"


Terrain::Terrain(void)
{
	collideBoxes.push_back(new CollideBox(0,0,10,10));
}


Terrain::~Terrain(void)
{
}

void Terrain::draw()
{
	if(sprite_ == NULL)
		return;

	sprite_->calcNextFrame();

	glBindTexture(GL_TEXTURE_2D, sprite_->getSpriteSheet()->getGLuintTexture());

	glPushMatrix();
	glTranslatef(getXNorm() - GAME->getCamera()->getXNorm(), getYNorm() - GAME->getCamera()->getYNorm(), 0);
	//glTranslatef(getXNorm(), getYNorm(), 0);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);

	/*
	START TILE CODE HERE
	*/

	GLfloat* temp = sprite_->getVertexPoints();
	GLfloat vertexPoints[12] = 
	{
		temp[0], temp[1], temp[2], temp[3], temp[4], temp[5], temp[6],
		temp[7], temp[8], temp[9], temp[10], temp[11]
	};

	temp = sprite_->getTexturePoints();
	GLfloat texturePoints[12] = 
	{
		temp[0], temp[1], temp[2], temp[3], temp[4], temp[5], temp[6],
		temp[7], temp[8], temp[9], temp[10], temp[11]
	};

	GLfloat startX = vertexPoints[9];
	GLfloat startY = vertexPoints[10];

	int frameW = sprite_->getFrameWidth()*2;
	int frameH = sprite_->getFrameHeight()*2;

	GLfloat dx = frameW * 1.0 / SCREEN_WIDTH;
	GLfloat dy = frameH * 1.0 / SCREEN_HEIGHT;
	
	GLfloat truncateX = (frameW-(width_%frameW))*1.0/SCREEN_WIDTH;
	GLfloat truncateY = (frameH-(height_%frameH))*1.0/SCREEN_HEIGHT;
	
	vertexPoints[1] = vertexPoints[10]+dy;
	vertexPoints[3] = vertexPoints[9]+dx;
	vertexPoints[4] = vertexPoints[1];
	vertexPoints[6] = vertexPoints[3];
	
	glTexCoordPointer(2, GL_FLOAT, 0, texturePoints);
	for (int j=0; j<height_; j+=frameH)
	{
		if(j+frameH > height_ && height_%frameH >0)
		{
			vertexPoints[1] -= truncateY;
			vertexPoints[4] -= truncateY;
			texturePoints[1] += truncateY;
			texturePoints[3] += truncateY;
		}

		for(int i=0; i<width_; i+=frameW)
		{
			if(i+frameW > width_ && width_%frameW >0)
			{
				//truncate the texture by modifying both the vertex and texture points
				vertexPoints[3] -= truncateX;
				vertexPoints[6] -= truncateX;
				texturePoints[2] -= truncateX;
				texturePoints[4] -= truncateX;
			}

			glVertexPointer(3, GL_FLOAT, 0, vertexPoints);
			glDrawArrays(GL_QUADS, 0, 4);
		
			if(i+frameW > width_ && width_%frameW >0)
			{
				//reset the texture points
				texturePoints[2]+=truncateX;
				texturePoints[4]+=truncateX;
			}

			vertexPoints[0] += dx;
			vertexPoints[3] += dx;
			vertexPoints[6] += dx;
			vertexPoints[9] += dx;
		}	

		vertexPoints[9] = startX;
		vertexPoints[0] = startX;
		vertexPoints[10] = startY + dy*(1+j/frameH);
		vertexPoints[7] = vertexPoints[10];
		vertexPoints[1] = vertexPoints[10]+dy;
		vertexPoints[3] = vertexPoints[9]+dx;
		vertexPoints[4] = vertexPoints[1];
		vertexPoints[6] = vertexPoints[3];
	}
	//end tile code

	//draw the borders around the box
	for(int i=0; i<collideBoxes.size(); ++i)
	{
		if(collideBoxes[i]->isActive())
		{
			GLfloat tempVerts[4] = 
			{
				0.0f*(collideBoxes[i]->getWidth()+collideBoxes[i]->getX()-getX())/SCREEN_WIDTH,0.0f*(collideBoxes[i]->getHeight()+collideBoxes[i]->getY()-getY())/SCREEN_HEIGHT,
				1.0f*(collideBoxes[i]->getWidth()+collideBoxes[i]->getX()-getX())/SCREEN_WIDTH,1.0f*(collideBoxes[i]->getHeight()+collideBoxes[i]->getY()-getY())/SCREEN_HEIGHT
			};

			glLineWidth(2.5); 
			glColor3f(1.0, 0.0, 0.0);
		
			glBegin(GL_LINES);
			glVertex3f(tempVerts[0], tempVerts[3], -1.0);
			glVertex3f(tempVerts[2], tempVerts[3], -1.0);
			glEnd();

			glBegin(GL_LINES);
			glVertex3f(tempVerts[2], tempVerts[1], -1.0);
			glVertex3f(tempVerts[0], tempVerts[1], -1.0);
			glEnd();

			glBegin(GL_LINES);
			glVertex3f(tempVerts[2], tempVerts[3], -1.0);
			glVertex3f(tempVerts[2], tempVerts[1], -1.0);
			glEnd();

			glBegin(GL_LINES);
			glVertex3f(tempVerts[0], tempVerts[1], -1.0);
			glVertex3f(tempVerts[0], tempVerts[3], -1.0);
			glEnd();

			glColor3f(1.0,1.0,1.0);
		}
	}


	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	glPopMatrix();
}