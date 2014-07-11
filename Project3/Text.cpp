#include "Text.h"
#include "Game.h"
#include "Includes.h"

Text::Text()
{
	x = 50;
	y = 50;
	ss = new SpriteSheet("Inconsolata.tga");
	spriteArray = NULL;
	text = NULL;
	length = 0;
}

Text::Text(char* text, int length)
{
	x = 50;
	y = 50;
	ss = new SpriteSheet("Inconsolata.tga");
	spriteArray = NULL;
	this->text = NULL;
	this->length = 0;
	setText(text, length);
}

Text::~Text()
{
	if(text != NULL)
	{
		delete[] text;
	}

	if(this->spriteArray != NULL)
	{
		for(int i=0; i<this->length; ++i)
		{
			if(spriteArray[i] != NULL)
			{
				delete spriteArray[i];
				spriteArray[i] = NULL;
			}
		}
		delete[] spriteArray;
		spriteArray = NULL;
	}
}

void Text::setText(char* text, int length)
{
	if(this->length > 0 && this->length == length)
	{
		//determine differences between our text and the arg
		for(int i=0; i<length; ++i)
		{
			if(this->text[i] != text[i])
			{
				changeLetter(i, text[i]);
			}
		}
		return;
	}	

	if(this->text != NULL)
	{
		delete[] this->text;
		this->text = NULL;
	}

	if(this->spriteArray != NULL)
	{
		for(int i=0; i<this->length; ++i)
		{
			if(spriteArray[i] != NULL)
			{
				delete spriteArray[i];
				spriteArray[i] = NULL;
			}
		}
		delete[] spriteArray;
		spriteArray = NULL;
	}
	
	spriteArray = new TextSprite*[length];

	for(int i=0; i<length; ++i)
	{
		spriteArray[i] = new TextSprite(20,36,ss);
		spriteArray[i]->setLetter(text[i]);
	}

	this->text = new char[length];
	this->length = length;
}

void Text::changeLetter(int index, char c)
{
	text[index] = c;
	spriteArray[index]->setLetter(c);
}

int Text::getLength()
{
	return length;
}

void Text::setTextSize(float size)
{
	if(size > 0);
	textSize = size;
}

void Text::setX(float val)
{
	x = val;
}

void Text::setY(float val)
{
	y = val;
}

float Text::getX()
{
	return x;
}

float Text::getY()
{
	return y;
}

float Text::getTextSize()
{
	return textSize;
}

void Text::draw()
{
	if(spriteArray == NULL)
		return;

	for(int i=0; i<length; ++i)
	{
		spriteArray[i]->calcLetter();
		glBindTexture(GL_TEXTURE_2D, spriteArray[i]->getSpriteSheet()->getGLuintTexture());

		glPushMatrix();
		glTranslatef((1.0f*(x + 20*i)/SCREEN_WIDTH) - GAME->getCamera()->getXNorm(), (1.0f*y/SCREEN_HEIGHT) - GAME->getCamera()->getYNorm(), 0);
		//glTranslatef(getXNorm(), getYNorm(), 0);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glEnableClientState(GL_VERTEX_ARRAY);	
		
		glVertexPointer(3, GL_FLOAT, 0, spriteArray[i]->getVertexPoints());
		glTexCoordPointer(2, GL_FLOAT, 0, spriteArray[i]->getTexturePoints());
		glDrawArrays(GL_QUADS, 0, 4);
	
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);

		glPopMatrix();
	}	
}
