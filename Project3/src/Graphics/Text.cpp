#include "Text.h"
#include "Game.h"
#include "Includes.h"

Text::Text()
{
	init();
}

Text::Text(std::string text)
{
	init();
	setText(text);
}

Text::~Text()
{
	if(this->spriteArray != NULL)
	{
		for(int i=0; i<text.length(); ++i)
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

void Text::init()
{
	x = 0;
	y = 0;
	ss = new SpriteSheet("res/Inconsolata.tga");
	spriteArray = NULL;
	text = "";
	attachable = NULL;
	textSize = 20;
}

void Text::setText(std::string val)
{
	if(text.length() > 0 && text.length() == val.length())
	{
		//determine differences between our text and the arg
		for(int i=0; i<text.length(); ++i)
		{
			if(this->text[i] != val[i])
			{
				changeLetter(i, val[i]);
			}
		}
		return;
	}	


	if(spriteArray != NULL)
	{
		for(int i=0; i<text.length(); ++i)
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
	
	text = val;
	
	spriteArray = new TextSprite*[text.length()];

	for(int i=0; i<text.length(); ++i)
	{
		spriteArray[i] = new TextSprite(textSize,textSize*1.8,ss);
		spriteArray[i]->setLetter(text[i]);
	}
}

void Text::changeLetter(int index, char c)
{
	text[index] = c;
	spriteArray[index]->setLetter(c);
}

int Text::getLength()
{
	return text.length();
}

void Text::setTextSize(float size)
{
	if(size > 0)
		textSize = size;

	else return;

	int width = size;
	int height = 1.8 * size;

	for(int i=0; i<text.length(); ++i)
	{
		if(spriteArray[i] != NULL) 
		{
			spriteArray[i]->setWidth(width);
			spriteArray[i]->setHeight(height);
		}
	}
}

float Text::getTextSize()
{
	return textSize;
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

void Text::attachToEntity(Entity* e)
{
	attachable = e;
}

void Text::draw()
{
	if(spriteArray == NULL)
		return;

	for(int i=0; i<text.length(); ++i)
	{
		spriteArray[i]->calcLetter();
		glBindTexture(GL_TEXTURE_2D, spriteArray[i]->getSpriteSheet()->getGLuintTexture());

		glPushMatrix();
		if(attachable != NULL) glTranslatef((1.0f*(x + textSize*i)/SCREEN_WIDTH) - attachable->getXNorm()-GAME->getCamera()->getXNorm(), (1.0f*y/SCREEN_HEIGHT) - attachable->getYNorm() - GAME->getCamera()->getYNorm(), 0);
		else glTranslatef(1.0f*(x + textSize*i)/SCREEN_WIDTH, 1.0f*y/SCREEN_HEIGHT, 0);
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
