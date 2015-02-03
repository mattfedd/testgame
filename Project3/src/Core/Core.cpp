#include "core.h"
#include "Game.h"

//Game* Game::instance_;

//add GameState, PlayerProgress, and SaveState structs to h

Core::Core()
{
	//set gamestate
	//get playerstate
	//get savestate
	
	GAME->Setup();
}

Core::~Core()
{
	
}


void Core::Run()
{
	paused_ = false;

	// scene = new EntityManager();

	// scene->addPlayer(10,200);
	// scene->getPlayer()->setWeapon(new MeleeWeapon());
	
	// scene->addTerrain(0,0, 2000, 50);
	// scene->addTerrain(300,150,500,70);

	// text = new Text("Arrow keys to move, Space to jump, X to attack, R to reset");
	// text->setX(-1*SCREEN_WIDTH + 30);
	// text->setY(-1*SCREEN_HEIGHT +30);

	// debugText = new Text("debug stuff");
	// debugText->setX(-1*SCREEN_WIDTH + 30);
	// debugText->setY(SCREEN_HEIGHT-30);
	// debugText->setTextSize(15);

	double saved_time = 0;
	double update_timer = 0;
	const double update_interval = 1.0/FRAME_RATE;
	double last_time = 0;
	glfwSetTime(0);

	int counter = 0;
	
	std::ostringstream ss;
	int framerate=0;
	bool awaitingPauseRelease = false;
	/* Loop until the user closes the window */
	while (running_)
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
				GAME->getPlayer()->setX(0);
				GAME->getPlayer()->setY(200);
			}

			if(glfwGetKey('P') == GLFW_PRESS && !awaitingPauseRelease)
			{
				paused_ = !paused_;
				awaitingPauseRelease = true;
			}
			else if(glfwGetKey('P') == GLFW_RELEASE)
			{
				awaitingPauseRelease = false;
			}

			if(!paused_)
			{
				//switch states here
				GAME->Run();
			}
			
			//draw
			//DrawDebug();


			framerate = 1/(glfwGetTime() - last_time);
			LOGV("CORE", "%d fps", framerate);
			ss.str("");
			ss.clear();
			ss << framerate;
			//debugText->setText(ss.str());
			
			update_timer = 0;
			last_time = glfwGetTime();
		}

		// Check if ESC key was pressed or window was closed
		//Core->setRunning(!glfwGetKey( GLFW_KEY_ESC ) && glfwGetWindowParam( GLFW_OPENED ));
		running_ = !glfwGetKey( GLFW_KEY_ESC ) && glfwGetWindowParam( GLFW_OPENED );
	}
}

void Core::DrawDebug()
{
	//maybe do a check inside of draw to see if we need to push the matrix
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	//draw debug text or something

	glfwSwapBuffers();
}

bool Core::isPaused() {return paused_; }
