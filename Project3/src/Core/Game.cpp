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
	
	double time1 = glfwGetTime();
	loadTiles(1,1);
	double time2 = glfwGetTime();
	LOGV("GAME", "Tile Loading took %f seconds", time2-time1);

	bg = new BGSprite(3840, 2160, getSpriteSheet("res/bg.tga"));
	camera_ = Camera();

	score = 0;

	tileData.startX = -200;
	tileData.startY = 300;
	tileData.tileHeight = 64;
	tileData.tileWidth = 64;
	tileData.arrayWidth = 128;

	tileReference = new TerrainSprite(tileData.tileWidth, tileData.tileHeight,getSpriteSheet("res/terrain.tga"));

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

	Entity& scoreText = em->createEntity();
	scoreText.addComponent(PositionComponent(0.7*SCREEN_WIDTH, 0.8*SCREEN_HEIGHT+30));
	scoreText.addComponent(TextComponent("Score", new TextSprite(10,18, getSpriteSheet("res/Inconsolata.tga")), 0,0,10));
	debugTexts.push_back(&em->getComponentVector<TextComponent>()->get(2));
	
	Entity& helpText = em->createEntity();
	helpText.addComponent(PositionComponent(-0.5*SCREEN_WIDTH, -0.8*SCREEN_HEIGHT-30));
	helpText.addComponent(TextComponent("Arrow keys to move, Jump to beep, Esc to exit", new TextSprite(10,18, getSpriteSheet("res/Inconsolata.tga")), 0,0,10));
	debugTexts.push_back(&em->getComponentVector<TextComponent>()->get(3));

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
	debugTexts[2]->text = "Score: " + std::to_string(score);
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
	glTranslatef(-1-camera_.getXNorm()*0.6, -1.75-camera_.getYNorm()*0.6, 0);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, bg->getVertexPoints());
	glTexCoordPointer(2, GL_FLOAT, 0, bg->getTexturePoints());
	glDrawArrays(GL_QUADS, 0, 4);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glPopMatrix();

	glBindTexture(GL_TEXTURE_2D, tileReference->getSpriteSheet()->getGLuintTexture()); //just one spritesheet for all tiles

	for(int i=0; i<backgroundTiles.size(); ++i)
	{
		int BG = backgroundTiles[i];
		int FG = foregroundTiles[i];

		if(!(BG == -1 && FG == -1))
		{
			int x = tileData.startX + i%tileData.arrayWidth*tileData.tileWidth;
			int y = tileData.startY + i/tileData.arrayWidth * -1.0*tileData.tileHeight;
			if(camera_.isInBounds(x,y,tileData.tileHeight))
			{
				glPushMatrix();
				
				glEnableClientState(GL_TEXTURE_COORD_ARRAY);
				glEnableClientState(GL_VERTEX_ARRAY);

				glTranslatef((x*1.0)/SCREEN_WIDTH-camera_.getXNorm(),(y*1.0)/SCREEN_HEIGHT-camera_.getYNorm(), 0);
						
				if(BG !=-1)
				{
					tileReference->setFrame(backgroundTiles[i]);
					tileReference->calcNextFrame();
					glVertexPointer(3, GL_FLOAT, 0, tileReference->getVertexPoints());
					glTexCoordPointer(2, GL_FLOAT, 0, tileReference->getTexturePoints());
					glDrawArrays(GL_QUADS, 0, 4);
				}

				if(FG !=-1)
				{
					tileReference->setFrame(foregroundTiles[i]);
					tileReference->calcNextFrame();								
					glVertexPointer(3, GL_FLOAT, 0, tileReference->getVertexPoints());
					glTexCoordPointer(2, GL_FLOAT, 0, tileReference->getTexturePoints());
					glDrawArrays(GL_QUADS, 0, 4);
				}

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

void Game::loadTiles(unsigned int level, unsigned int sublevel)
{
	std::string fileName = "res/"+std::to_string(level) + "_" + std::to_string(sublevel) + ".lvl";

	std::string line;
	std::ifstream file(fileName);
	
	int parseState = 0;
	int lineCounter = 0;
	int height = 0;

	if(file.is_open())
	{
		while(std::getline(file, line))
		{
			if(parseState == 0) //beginning
			{
				if(line.compare("Tile Data " + std::to_string(level) + "_" + std::to_string(sublevel)) != 0)
				{
					LOGES("FILE", "Error reading tile data file: header error");
					return;
				}
				else
				{
					parseState++;
				}
			}

			else if(parseState == 1) //width
			{
				std::istringstream ss(line);
				std::string word;
				ss >> word;
				if(word.compare("width") != 0)
				{
					LOGES("FILE", "Error reading tile data file: width parameter not found in second line");
					return;
				}
				else
				{
					ss>>word;
					tileData.arrayWidth = std::stoi(word);
					parseState++;
				}
			}

			else if(parseState == 2) //height
			{
				std::istringstream ss(line);
				std::string word;
				ss >> word;
				if(word.compare("height") != 0)
				{
					LOGES("FILE", "Error reading tile data file: height parameter not found in third line");
					return;
				}
				else
				{
					ss>>word;
					height = std::stoi(word);
					parseState++;
				}
			}

			else if(parseState == 3) //Background
			{
				if(line.compare("Background") != 0)
				{
					LOGES("FILE", "Error reading tile data file: 'Background' header error");
					return;
				}
				else
				{
					parseState++;
				}
			}

			else if(parseState == 4) //background data
			{
				if(line.compare("Foreground") == 0)
				{
					LOGES("FILE", "Error reading tile data file: 'Foreground' data appeared earlier than expected");
					return;
				}
				else
				{
					int value = 0;
					unsigned int pos = 0;
					std::string token;
					while ((pos = line.find(',')) != std::string::npos) 
					{
						token = line.substr(0, pos);
						value = std::stoi(token);
						backgroundTiles.push_back(value);
						line.erase(0, pos + 1);
					}
					value = std::stoi(line);
					backgroundTiles.push_back(value);

					lineCounter++;

					if(lineCounter == height)
					{
						parseState++;
						lineCounter = 0;
					}
				}
			}

			else if(parseState == 5) //Background
			{
				if(line.compare("Foreground") != 0)
				{
					LOGES("FILE", "Error reading tile data file: 'Foreground' header error");
					return;
				}
				else
				{
					parseState++;
				}
			}

			else if(parseState == 6) //foreground data
			{
				int value = 0;
				unsigned int pos = 0;
				std::string token;
				while ((pos = line.find(',')) != std::string::npos) 
				{
					token = line.substr(0, pos);
					value = std::stoi(token);
					foregroundTiles.push_back(value);
					line.erase(0, pos + 1);
				}
				value = std::stoi(line);
				foregroundTiles.push_back(value);

				lineCounter++;

				if(lineCounter == height)
				{
					parseState++;
				}
			}

		}

		file.close();
	}
}
