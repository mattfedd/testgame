#ifndef CORE_H
#define CORE_H

#include "Includes.h"

class Core
{
public:
	Core();
	~Core();

	void Run();

	bool isPaused();

	GLuint vertexbuffer;

private:
	void DrawDebug();

	int running_;
	int counter_;
	bool paused_;
};

#endif