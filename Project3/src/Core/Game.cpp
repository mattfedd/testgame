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
	tileData.arrayWidth = 32;

	int temptiles[NUM_TILES] = {
		1,1,1,1,1,1,1,1,2,2,2,2,1,1,1,1,1,1,1,1,1,1,1,1,2,2,2,2,1,1,1,1,
		1,0,0,0,0,0,0,0,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		2,0,0,0,0,0,0,1,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		2,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,1,
		1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,
		1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,
		2,2,2,2,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,1,
		1,2,1,2,1,2,1,1,1,1,1,1,1,1,1,1,1,2,1,2,1,2,1,1,1,1,1,1,1,1,1,1

	};

	for(int i=0; i<NUM_TILES; ++i)
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

	Entity& o = em->createEntity();
	o.setId(4);
	o.addComponent(PositionComponent(0,-50,0));
	o.addComponent(HealthComponent(10, 20));
	o.addComponent(SpriteComponent("Player", PlayerSprite(128, 128, getSpriteSheet("res/player.tga"))));
	o.addComponent(CollisionComponent(Rect(40,0,128-80,128), COLLISION_PLAYER, 0xffff));
	o.addComponent(PhysicsComponent());

	player_ = &em->getEntities().get(0);
	camera_.setReference(&em->getComponentVector<PositionComponent>()->get(player_->components[POSITION_ID])); //todo : give the camera a position element it can attach to aka the id of the player position element...

	//debug text stuff
	for(int i=0; i<2; ++i)
	{
		Entity& text = em->createEntity();
		text.addComponent(PositionComponent(-0.8*SCREEN_WIDTH-80,30+0.8*SCREEN_HEIGHT - i*22,0));
		text.addComponent(TextComponent("Basic Text", new TextSprite(10,18, getSpriteSheet("res/Inconsolata.tga")), 0,0,10));
		debugTexts.push_back(&em->getComponentVector<TextComponent>()->get(i));
	}

	//stress test
	//for(int i=5; i<25; i++)
	//{
	//	Entity& e = em->createEntity();
	//	e.setId(i+5);
	//	e.addComponent(PositionComponent(100+i*4,-200,0));
	//	e.addComponent(HealthComponent(10, 20));
	//	e.addComponent(SpriteComponent("Player", PlayerSprite(128, 128, getSpriteSheet("res/player.tga"))));
	//	e.addComponent(CollisionComponent(Rect(40,0,128-80,128), COLLISION_PLAYER, 0xffff));
	//	e.addComponent(PhysicsComponent());
	//}
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
	profiler.startMeasure("Update");
	
	playerinputsys.update(em);
	physicssys.update(em);
	collisionsys.update(em);
	camera_.update();

	profiler.stopMeasure("Update");

	debugTexts[0]->text = "Update: " + std::to_string((int)profiler.getPercentage("Update")) + "%";
	debugTexts[1]->text = "Draw: " + std::to_string((int)profiler.getPercentage("Drawing")) + "%";
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

	for(int i=0; i<NUM_TILES; ++i)
	{
		if(tiles[i] != 0)
		{
			int x = tileData.startX + i%tileData.arrayWidth*tileData.tileWidth;
			int y = tileData.startY + i/tileData.arrayWidth * -1.0*tileData.tileHeight;
			if(camera_.isInBounds(x,y,tileData.tileHeight))
			{
				s = tileIdTranslator[tiles[i]]->getSprite();
				s->calcNextFrame();
				glPushMatrix();
				glTranslatef((x*1.0)/SCREEN_WIDTH-camera_.getXNorm(),(y*1.0)/SCREEN_HEIGHT-camera_.getYNorm(), 0);
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
	}
	
	profiler.startMeasure("Drawing");
	spritesys.update(em);
	debugdrawsys.update(em);
	profiler.stopMeasure("Drawing");

	glfwSwapBuffers();
}

void Game::Destroy()
{

}

void Game::PauseMenu()
{

}

void Game::AddEntity(Entity* e)
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

//gives the lower left corner of the tile position
//This is just like the other position components, which are lower left corner reference
Vector2d Game::getTilePositionByIndex(int index)
{
	int x = (index%tileData.arrayWidth)*tileData.tileWidth + tileData.startX;
	int y = -1*(index/tileData.arrayWidth)*tileData.tileHeight + tileData.startY;
	Vector2d v = {x,y};
	return v;
}
