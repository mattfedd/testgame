#ifndef TILE_H
#define TILE_H

class Sprite;

class Tile
{
private:
	int x;
	int y;
	int direction;
	Sprite* sprite;
public:
	Tile(void);
	~Tile(void);

	void setSprite(Sprite* s) { sprite = s;}
	Sprite* getSprite() {return sprite;}
};

#endif
