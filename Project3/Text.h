#ifndef TEXT_H
#define TEXT_H

#include "TextSprite.h"
#include <string>

class Entity;

class Text 
{
private:
	std::string text;
	int x;
	int y;
	float textSize;
	TextSprite** spriteArray;
	SpriteSheet* ss;
	bool tiedToCamera;
	Entity* attachable;

	void changeLetter(int index, char c);
	void init();

public:
	Text(void);
	Text(std::string s);
	~Text(void);

	void setText(std::string s);
	int getLength();
	void setTextSize(float size);
	void setX(float val);
	void setY(float val);
	float getX();
	float getY();
	float getTextSize();
	void setTiedToCamera(bool val);
	void attachToEntity(Entity* e);

	void draw();

};

#endif