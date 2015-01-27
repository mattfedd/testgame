#include "Includes.h"
#include "game.h"
//#include "Collision.h"

#include "Player.h"
#include "Terrain.h"
#include "Text.h"
#include "Collision.h"

Game* Game::instance_;
Text* debugText;
Text* text;
Player* player;
Terrain* entity;
Terrain* platform;
bool paused;

Game::Game(const char* title, int width, int height)
{
	size_ = 100.0f/SCREEN_WIDTH;
	counter_ = 0;
	running_ = GL_TRUE;

	camera_ = new Camera();
	input_ = new Input();

	initialized_ = Init(title, width, height);

	if(initialized_ != 0)
	{
		printf("Error in Initialization, looping endlessly.\n");
		while(true);
	}
}

Game::~Game()
{
	if(initialized_ != -1)
	{
		glfwTerminate();
	}
}

int Game::Init(const char* title, int width, int height)
{
	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	if (!glfwOpenWindow(width, height, 8, 8, 8, 8, 24, 0, GLFW_WINDOW)) {
		fprintf(stderr, "problem with glfwOpenWindow");
		while(running_==GL_TRUE);
		return -1;
	}

	glfwOpenWindowHint(GLFW_FSAA_SAMPLES, 4); // 4x antialiasing
	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3); // We want OpenGL 3.3
	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 3);
	glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //We don't want the old OpenGL

	glfwSetWindowTitle(title);

	// Initialize GLEW
	GLenum err = glewInit();
	glewExperimental=true; // Needed in core profile

	if ( GLEW_OK != err) {
		fprintf(stderr, "problem with GLEW %d", err);
		while(running_==GL_TRUE);
		return -1;
	}

	glEnable(GL_TEXTURE_2D);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 
	glEnable( GL_BLEND ); 
	glClearColor(0.5,0.5,0.5,0.0);
	glColor4f(1.0,1.0,1.0,1.0);

	glfwSetWindowSizeCallback(this->handle_resize); //callback function of GLFW to handle window resize
	glfwSetKeyCallback(this->input_->handle_keypress); //callback function to handle keypress
	return 0;
}

void Game::Run()
{
	paused = false;

	//entityManager.addPlayer(x,y);
	//entityManager.addEnemy(type1,x,y);
	//entityManager.addTerrain(type1, x,y,width,height);
	//entityManager.addTerrain(type1, x,y,width,height);
	//entityManager.addTextBox(type2, x,y,text, flags);

	player = new Player();
	player->setY(200);
	
	entity = new Terrain();
	entity->setWidth(2000);

	platform = new Terrain();
	platform->setX(300);
	platform->setY(80);
	platform->setHeight(220);
	platform->setWidth(500);

	text = new Text("Arrow keys to move, Space to jump, R to reset");
	text->setX(50);
	text->setY(50);
	text->attachToEntity(entity);

	debugText = new Text("debug stuff");
	debugText->setX(-640);
	debugText->setY(450);
	debugText->setTextSize(15);

	//char buffer[14];

	GAME->getCamera()->setAttachable(player);

	double saved_time = 0;
	double update_timer = 0;
	const double update_interval = 1.0/FRAME_RATE;
	double last_time = 0;
	glfwSetTime(0);

	int counter = 0;
	//std::vector<Drawable*> drawables = GAME->getLevel()->getScreenPtr()->getForegroundVector();
	
	std::ostringstream ss;
	int framerate=0;
	bool awaitingPauseRelease = false;
	/* Loop until the user closes the window */
	while (getRunning())
	{
		//framerate stuff
		double current_time =  glfwGetTime();
		double elapse_time = current_time - saved_time;
		saved_time = current_time;
		update_timer += elapse_time;

		if(update_timer >= update_interval)
		{
			//update
			if(glfwGetKey('R'))
			{
				player->setX(0);
				player->setY(200);
			}

			if(glfwGetKey('P') == GLFW_PRESS && !awaitingPauseRelease)
			{
				paused = !paused;
				awaitingPauseRelease = true;
			}
			else if(glfwGetKey('P') == GLFW_RELEASE)
			{
				awaitingPauseRelease = false;
			}

			

			if(!paused)
			{
				player->updateInput(); 
				entity->updateInput();
				GAME->getCamera()->update();

				checkCollisions();
			}
			
			//draw
			draw();
			

			//framerate stuff
			framerate = 1/(glfwGetTime() - last_time);
			ss.str("");
			ss.clear();
			ss << framerate;
			debugText->setText(ss.str());
			update_timer = 0;
			last_time = glfwGetTime();
		}

		// Check if ESC key was pressed or window was closed
		//GAME->setRunning(!glfwGetKey( GLFW_KEY_ESC ) && glfwGetWindowParam( GLFW_OPENED ));
		running_ = !glfwGetKey( GLFW_KEY_ESC ) && glfwGetWindowParam( GLFW_OPENED );

	}
}

void Game::checkCollisions()
{
	Collision::checkCollision(player, entity);
	Collision::checkCollision(player, platform);
}

void Game::draw()
{
	//iterate through Drawables, call draw()
	//maybe do a check inside of draw to see if we need to push the matrix
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	//player->calcNextFrame();
	text->draw();
	player->draw();
	entity->draw();
	platform->draw();
	debugText->draw();

	glfwSwapBuffers();
}

void GLFWCALL Game::handle_resize(int width,int height)
{
	//Tell OpenGL how to convert from coordinates to pixel values
	glViewport( 0, 0, width, height );
	glMatrixMode( GL_PROJECTION ); //Switch to setting the camera perspective

	//Set the camera perspective
	glLoadIdentity(); //reset the camera
	/* gluPerspective( 
	45.0f,                      //camera angle
	(GLfloat)width/(GLfloat)height, //The width to height ratio
	1.0f,                          //The near z clipping coordinate
	100.0f );   */ 
}

//Level* Game::createLevel(std::string filename)
//{
//	level_ = new Level(filename);
//	return level_;
//}

int Game::getRunning(){ return running_; }
void Game::setRunning(int val){ running_ = val; }
Camera* Game::getCamera(){ return camera_; }
Input* Game::getInput(){ return input_; }
//Level* Game::getLevel(){ return level_; }

bool Game::isPaused() {return paused; }
