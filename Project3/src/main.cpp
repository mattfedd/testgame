#include "Includes.h"

#include "Core.h"

int initWindow();
void checkAssets();
void startCore();
void GLFWCALL handle_resize(int width,int height);
void GLFWCALL handle_keypress(int key, int press);

int main(void)
{
	initWindow();
	checkAssets();
	startCore();
}

int initWindow()
{
	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	if (!glfwOpenWindow(SCREEN_WIDTH*2, SCREEN_HEIGHT*2, 8, 8, 8, 8, 24, 0, GLFW_WINDOW)) {
		fprintf(stderr, "problem with glfwOpenWindow");
		return -1;
	}

	glfwOpenWindowHint(GLFW_FSAA_SAMPLES, 4); // 4x antialiasing
	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3); // We want OpenGL 3.3
	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 3);
	glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //We don't want the old OpenGL

	glfwSetWindowTitle(GAME_TITLE);

	// Initialize GLEW
	GLenum err = glewInit();
	glewExperimental=true; // Needed in core profile

	if (GLEW_OK != err) {
		fprintf(stderr, "problem with GLEW %d", err);
		return -1;
	}

	glEnable(GL_TEXTURE_2D);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 
	glEnable(GL_BLEND); 
	//glEnable(GL_DEPTH_TEST);
	glClearColor(0.5,0.5,0.5,0.0);
	glColor4f(1.0,1.0,1.0,1.0);

	glfwSetWindowSizeCallback(handle_resize); //callback function of GLFW to handle window resize
	glfwSetKeyCallback(handle_keypress); //callback function to handle keypress
	LOGVS("MAIN", "Initialized GLFW.");
	return 0;
}

void checkAssets()
{
	//do nothing for now
}

void startCore()
{
	LOGVS("MAIN", "Initializing Core and setting up Game.");
	Core core = Core();
	LOGVS("MAIN", "Running...");
	core.Run();
}

void GLFWCALL handle_resize(int width,int height)
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

void GLFWCALL handle_keypress(int key, int press)
{
	//nothing for now
}