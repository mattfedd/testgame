#include "Game.h"
//#include "Collision.h"
#include "MeleeWeapon.h"
#include "HUD.h"
#include "EntityManager.h"
#include "Components.h"

Game* Game::instance_;

Game::Game()
{
	//paused_ = false;

	bg = new BGSprite(3840, 2160, getSpriteSheet("res/bg.tga"));
	camera_ = Camera();

	tileData.startX = -100;
	tileData.startY = 100;
	tileData.tileHeight = 64;
	tileData.tileWidth = 64;
	tileData.arrayWidth = 16;

	int temptiles[256] = {
		1,0,0,0,0,0,0,0,2,2,2,2,1,0,0,1,
		1,0,0,0,0,0,0,0,2,2,2,2,0,0,0,1,
		2,0,0,0,0,0,0,1,0,0,2,0,0,0,0,1,
		1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,
		2,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,
		1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,
		2,2,2,2,1,0,0,0,0,0,0,0,1,0,0,1,
		1,2,1,2,1,2,1,1,1,1,1,1,1,1,1,1
	};

	for(int i=0; i<256; ++i)
	{
		tiles[i] = temptiles[i];
	}

	Tile* t = new Tile();
	t->setSprite(new TerrainGreenSprite(tileData.tileWidth, tileData.tileHeight,getSpriteSheet("res/terrain.tga")));
	
	tileIdTranslator[0] = NULL;
	tileIdTranslator[2] = t;

	t = new Tile();
	t->setSprite(new TerrainOrangeSprite(tileData.tileWidth, tileData.tileHeight, getSpriteSheet("res/terrain.tga")));
	tileIdTranslator[1] = t;

	em = new EntityManager();

	Object& o = em->createEntity();
	o.setId(4);
	o.addComponent(PositionComponent(0,0,0));
	o.addComponent(HealthComponent(10, 20));
	o.addComponent(SpriteComponent("Player", PlayerSprite(128, 128, getSpriteSheet("res/player.tga"))));
	o.addComponent(CollisionComponent(CollideBox(40,0,128-80,128), COLLISION_PLAYER, 0xffff));
	o.addComponent(PhysicsComponent());

	player_ = &em->getEntities().get(0);
	camera_.setReference(&em->getComponentVector<PositionComponent>()->get(player_->components[POSITION_ID])); //todo : give the camera a position element it can attach to aka the id of the player position element...

}

Game::~Game()
{

}

void Game::Setup()
{
	/*AddEntity(spawner_.createTerrain("green", 0,-20,3000,120));
	AddEntity(spawner_.createTerrain("green", -50,-20,50,120));
	AddEntity(spawner_.createTerrain("orange", 400,150,500,150));
	AddEntity(spawner_.createTerrain("orange", 1400, 200, 400, 100));
	AddEntity(spawner_.createEnemy("basic", 1000, 120));
	AddEntity(spawner_.createItem("smallHeart", 300, 150));*/
}

void Game::Run(bool paused)
{
	if(!paused)
	{
		Update();
		CheckCollisions();
	}
	Draw();
}

void Game::Update()
{
	playerinputsys.update(em);
	physicssys.update(em);
	collisionsys.update(em);
	camera_.update();
}

void Game::CheckCollisions()
{

}

void Game::Draw()
{
	//maybe do a check inside of draw to see if we need to push the matrix
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glBindTexture(GL_TEXTURE_2D, bg->getSpriteSheet()->getGLuintTexture()); //just one spritesheet for all tiles
	bg->calcNextFrame();
	glPushMatrix();
	glTranslatef(-0.5-camera_.getXNorm()*0.6, -1.5-camera_.getYNorm()*0.6, 0);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, bg->getVertexPoints());
	glTexCoordPointer(2, GL_FLOAT, 0, bg->getTexturePoints());
	glDrawArrays(GL_QUADS, 0, 4);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glPopMatrix();

	Sprite* s = tileIdTranslator[tiles[0]]->getSprite();
	glBindTexture(GL_TEXTURE_2D, s->getSpriteSheet()->getGLuintTexture()); //just one spritesheet for all tiles

	for(int i=0; i<256; ++i)
	{
		if(tiles[i] != 0)
		{
			s = tileIdTranslator[tiles[i]]->getSprite();
			s->calcNextFrame();
			glPushMatrix();
			glTranslatef((tileData.startX + i%tileData.arrayWidth*tileData.tileWidth*1.0)/SCREEN_WIDTH-camera_.getXNorm(),(tileData.startY + i/tileData.arrayWidth * -1.0*tileData.tileHeight)/SCREEN_HEIGHT-camera_.getYNorm(), 0);
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glEnableClientState(GL_VERTEX_ARRAY);
		
			glVertexPointer(3, GL_FLOAT, 0, s->getVertexPoints());
			glTexCoordPointer(2, GL_FLOAT, 0, s->getTexturePoints());
			glDrawArrays(GL_QUADS, 0, 4);
	
			glDisableClientState(GL_VERTEX_ARRAY);
			glDisableClientState(GL_TEXTURE_COORD_ARRAY);

			glPopMatrix();
		}
	}
	
	spritesys.update(em);

	glfwSwapBuffers();
}

void Game::Destroy()
{

}

void Game::PauseMenu()
{

}

void Game::AddEntity(Object* e)
{

}

SpriteSheet* Game::getSpriteSheet(std::string filename)
{
	//do we have a copy of the desired spritesheet?
	if(spriteSheets.count(filename) > 0)
	{
		//yes? let's get it
		return spriteSheets[filename];
	}
	else
	{
		//we don't have it, so we need to create it
		const char * c = filename.c_str();
		spriteSheets[filename] = new SpriteSheet(c);
		return spriteSheets[filename];		
	}
}

int Game::getTileIndexByPosition(float x, float y)
{
	int i=0;
	float dx = x-tileData.startX;
	float dy = tileData.startY+tileData.tileHeight-y;

	i = (int)(dx/tileData.tileWidth) + (int)(dy/tileData.tileHeight) * tileData.arrayWidth;

	return i;
}
