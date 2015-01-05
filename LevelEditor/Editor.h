#ifndef EDITOR_H
#define EDITOR_H

#include "Includes.h"

class Editor
{
public:

	static Editor* instance()
	{
		if(instance_ == NULL) instance_ = new Editor(GAME_TITLE, SCREEN_WIDTH, SCREEN_HEIGHT);
		return instance_;
	}
	~Editor();

	void Run();

	int getRunning();
	void setRunning(int val);

	int initialized_;

	GLuint vertexbuffer;

private:
	Editor(const char* title, int width, int height);
	int Init(const char* title, int width, int height);
	
	//Run()
	void softReset();
	void checkInputs(); 
	void draw();

	static void GLFWCALL handle_resize(int width,int height);

	float size_;
	int running_;
	int counter_;

	static Editor *instance_;
};


#endif