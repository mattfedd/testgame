#include "Editor.h"

Editor::Editor(const char* title, int width, int height)
{
	size_ = 100.0f/SCREEN_WIDTH;
	counter_ = 0;
	running_ = GL_TRUE;

	initialized_ = Init(title, width, height);

	if(initialized_ != 0)
	{
		printf("Error in Initialization, looping endlessly.\n");
		while(true);
	}
}

Editor::~Editor()
{
	if(initialized_ != -1)
	{
		glfwTerminate();
	}
}

int Editor::Init(const char* title, int width, int height)
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
	//glfwSetKeyCallback(this->input_->handle_keypress); //callback function to handle keypress
	return 0;
}