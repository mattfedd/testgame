#ifndef TEXT_SPRITE_H
#define TEXT_SPRITE_H

#include "Sprite.h"

class TextSprite : public Sprite
{
private:
	int index;

public:
	TextSprite(int width, int height, SpriteSheet* ss);
	~TextSprite(void);

	void setLetter(char c);
	int getIndex();
	void calcLetter();
};

#endif