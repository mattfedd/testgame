#ifndef GAME_H
#define GAME_H

#include "Includes.h"
//#include "Camera.h"
//#include "Level.h"
#include "Input.h"
//#include "Drawable.h"

class Level;
class Drawable;

class Game
{
public:
	static Game* instance()
	{
		if(instance_ == NULL) instance_ = new Game(GAME_TITLE, SCREEN_WIDTH, SCREEN_HEIGHT);
		return instance_;
	}
	~Game();

	void Run();
	//void Quit(); //necessary yet?

	int getRunning();
	void setRunning(int val);
	Level* createLevel(std::string filename);

	//Camera* getCamera();
	Input* getInput();
	Level* getLevel();

	int initialized_;

	GLuint vertexbuffer;

private:
	Game(const char* title, int width, int height);
	int Init(const char* title, int width, int height);
	
	//Run()
	void softReset();
	void checkInputs(); 
	void checkCollisions();
	void calcAndApplyResults();
	void draw();

	static void GLFWCALL handle_resize(int width,int height);

	//Camera* camera_;
	Input* input_;
	Level* level_;

	float size_;
	int running_;
	int counter_;

	static Game *instance_;

};

#endif