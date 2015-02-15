#include "Game.h"
//#include "Collision.h"
#include "MeleeWeapon.h"
#include "HUD.h"
#include "EntityManager.h"
#include "Components.h"


Game* Game::instance_;

Game::Game()
{
	////basically the new EntityManager 
	//paused_ = false;
	bg = new BGSprite(3840, 2160, getSpriteSheet("res/bg.tga"));
	camera_ = Camera();
	camera_.setX(256);
	camera_.setY(-400);
	////player_ = Player();
	//player_.setSprite(new PlayerSprite(player_.getWidth(), player_.getHeight(), getSpriteSheet("res/player.tga")));
	//player_.setWeapon(new MeleeWeapon());
	//player_.setX(0);
	//player_.setY(200);
	//hud_ = new HUD();

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
	t->setSprite(new TerrainGreenSprite(64,64,getSpriteSheet("res/terrain.tga")));
	
	tileIdTranslator[0] = NULL;
	tileIdTranslator[2] = t;

	t = new Tile();
	t->setSprite(new TerrainOrangeSprite(64, 64, getSpriteSheet("res/terrain.tga")));
	tileIdTranslator[1] = t;

	em = new EntityManager();

	Object& o = em->createEntity();
	o.setId(4);
	o.addComponent(PositionComponent(0,0,0));
	o.addComponent(HealthComponent(10, 20));
	o.addComponent(SpriteComponent("Player", PlayerSprite(128, 128, getSpriteSheet("res/player.tga"))));

	//camera_.setAttachable(&player_); //todo : give the camera a position element it can attach to aka the id of the player position element...

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
	//player_.updateInput();
	//camera_.update();
	//hud_->updateInput();



	/*for(int i=0; i<enemyContainer.size(); ++i)
	{
		enemyContainer[i]->updateInput();
		if(enemyContainer[i]->getAnimState() == ANIM_STATE::DEATH)
		{
			Entity* e = enemyContainer[i];
			e->onDeath();
			enemyContainer.erase(enemyContainer.begin()+i);
			i--;
			delete e;
		}
	}

	for(int i=0; i<itemContainer.size(); ++i)
	{
		itemContainer[i]->updateInput();
		if(itemContainer[i]->getAnimState() == ANIM_STATE::DEATH)
		{
			Entity* e = itemContainer[i];
			itemContainer.erase(itemContainer.begin()+i);
			i--;
			delete e;
		}
	}*/

	if(glfwGetKey(GLFW_KEY_LEFT))
	{
		camera_.setX(camera_.getX()-2);
	}
	if(glfwGetKey(GLFW_KEY_RIGHT))
	{
		camera_.setX(camera_.getX()+2);
	}

	if(glfwGetKey(GLFW_KEY_UP))
	{
		camera_.setY(camera_.getY()+2);
	}
	if(glfwGetKey(GLFW_KEY_DOWN))
	{
		camera_.setY(camera_.getY()-2);
	}
}

void Game::CheckCollisions()
{
	/*for(int i=0; i<terrainContainer.size(); ++i)
	{
		Collision::checkCollision(&player_, terrainContainer[i]);
		
		for(int j=0; j<enemyContainer.size(); ++j)
		{
			Collision::checkCollision(enemyContainer[j], terrainContainer[i]);
		}
	}

	for(int i=0; i<enemyContainer.size(); ++i)
	{
		Collision::checkCollision(enemyContainer[i], &player_);
	}

	for(int i=0; i<itemContainer.size(); ++i)
	{
		Collision::checkCollision(itemContainer[i], &player_);
	}*/
}

void Game::Draw()
{
	//maybe do a check inside of draw to see if we need to push the matrix
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	Sprite* s = tileIdTranslator[tiles[0]]->getSprite();
	glBindTexture(GL_TEXTURE_2D, s->getSpriteSheet()->getGLuintTexture()); //just one spritesheet for all tiles

	for(int i=0; i<256; ++i)
	{
		if(tiles[i] != 0)
		{
			s = tileIdTranslator[tiles[i]]->getSprite();
			s->calcNextFrame();
			glPushMatrix();
			glTranslatef(i%16*64.0/SCREEN_WIDTH-camera_.getXNorm(),i/16 * -1*64.0/SCREEN_HEIGHT-camera_.getYNorm(), 0);
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
	
	glBindTexture(GL_TEXTURE_2D, bg->getSpriteSheet()->getGLuintTexture()); //just one spritesheet for all tiles
	bg->calcNextFrame();
	glPushMatrix();
	glTranslatef(0-camera_.getXNorm(), 0-camera_.getYNorm(), 0);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);
	
	glVertexPointer(3, GL_FLOAT, 0, bg->getVertexPoints());
	glTexCoordPointer(2, GL_FLOAT, 0, bg->getTexturePoints());
	glDrawArrays(GL_QUADS, 0, 4);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	glPopMatrix();
	
	
	spritesys.update(em);
	
	//glTranslatef(getXNorm(), getYNorm(), 0);
	

	//draw stuff
	/*player_.draw();

	for(int i=0; i<terrainContainer.size(); ++i)
	{
		terrainContainer[i]->draw();
	}

	for(int i=0; i<enemyContainer.size(); ++i)
	{
		enemyContainer[i]->draw();
	}

	for(int i=0; i<itemContainer.size(); ++i)
	{
		itemContainer[i]->draw();
	}

	hud_->draw();*/

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
	//switch(e->getEntityType())
	//{
	//case ENTITY_TYPE::TERRAIN:
	//	terrainContainer.push_back(e);
	//	break;
	//case ENTITY_TYPE::ENEMY:
	//	enemyContainer.push_back(e);
	//	break;
	//case ENTITY_TYPE::ITEM:
	//	itemContainer.push_back(e);
	//	break;
	//default:
	//	LOGES("GAME", "Just tried to add an un-logged entity type");
	//	break;
	//}
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

