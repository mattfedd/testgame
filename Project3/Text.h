#ifndef TEXT_H
#define TEXT_H

#include "TextSprite.h"

class Text 
{
private:
	char* text;
	int length;
	int x;
	int y;
	float textSize;
	TextSprite** spriteArray;
	SpriteSheet* ss;

	void changeLetter(int index, char c);

public:
	Text(void);
	Text(char* text, int length);
	~Text(void);

	void setText(char* text, int length);
	int getLength();
	void setTextSize(float size);
	void setX(float val);
	void setY(float val);
	float getX();
	float getY();
	float getTextSize();

	void draw();

};

#endif