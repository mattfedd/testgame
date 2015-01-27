#ifndef PLAYER_SPRITE_H
#define PLAYER_SPRITE_H

#include "Sprite.h"

class PlayerSprite : public Sprite
{
public:
	PlayerSprite(int width, int height, SpriteSheet* ss);
	~PlayerSprite(void);
};

#endif
