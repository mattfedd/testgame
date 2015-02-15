#ifndef HUD_H
#define HUD_H

//#include "Entity.h"
#include "Sprite.h"

class HeartSprite : public Sprite
{
private:

public:
	HeartSprite(int width, int height, SpriteSheet* ss);
	~HeartSprite();
};

class HUD 
{
private:
	struct Heart {
		HeartSprite* sprite;
		int x;
		int y;
	};

	int heartSize_;
	int heartStartX_;
	int heartStartY_;
	int heartHealthAmt_;

	std::vector<Heart> hearts;

public:
	HUD();
	~HUD();

	virtual void updateInput();

	virtual void draw();
	virtual void debugDraw();

};



//
//class ManabarSprite : public Sprite
//{
//private:
//
//public:
//	ManabarSprite(int width, int height, SpriteSheet* ss);
//	~ManabarSprite();
//};

#endif
