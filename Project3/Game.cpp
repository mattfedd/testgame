#include "Includes.h"
#include "game.h"
//#include "Collision.h"

#include "Player.h"
#include "Text.h"

Game* Game::instance_;
Text* debugText;
Text* text;
Player* player;
Entity* entity;

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
	player = new Player();
	player->setY(200);
	
	entity = new Entity();
	entity->setWidth(2000);

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

			player->updateInput(); 
			entity->updateInput();
			GAME->getCamera()->update();

			checkCollisions();

			//draw
			draw();

			//framerate stuff
			framerate = 1/(glfwGetTime() - last_time);
			//printf("%f\n", 1/(glfwGetTime() - last_time));
			//_itoa_s((int)(1/(glfwGetTime() - last_time)), buffer, 10);
			//debugText->setText(buffer);
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
	//since there's no rotation, just do a two axis test on the rectangles

	//hard coding with player and entity to begin with

	int x1 = player->getX();
	int y1 = player->getY();
	int w1 = player->getWidth();
	int h1 = player->getHeight();

	int x2 = entity->getX();
	int y2 = entity->getY();
	int w2 = entity->getWidth();
	int h2 = entity->getHeight();

	if(x1 > x2 && x1-x2 > w2) //left
		return;
	else if(x2 > x1 && x2-x1 > w1)
		return;

	if(y1 > y2 && y1-y2 > h2)
		return;
	else if(y2 > y1 && y2-y1 > h1)
		return;

	else 
	{
		//printf("colliding!!\n");
		player->colliding = true;
		//we want player to be affected, and the entity to not move
		
		//if(x1 + w1/2 <= x2 + w2 / 2) //if player center x is left of entity center x
		//{
		//	//move left enough
		//	player->setX(x2-w1);
		//}
		//else if(x1 + w1/2 > x2 + w2 / 2) //if player center x is right of entity center x
		//{
		//	//move right
		//	player->setX(x2+w2);
		//}

		if(y1 + h1/2 <= y2 + h2 / 2) //if player center y is below entity center y
		{
			//move down
			//printf("moving down\n");
			player->setY(y2-h1-1);
			player->setDY(0);
		}
		else if(y1 + h1/2 > y2 + h2 / 2) //if player center y above entity center y
		{
			//move up
			//printf("moving up\n");
			player->setY(y2+h2);
			player->setDY(0);
		}
	}
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
