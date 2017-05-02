#include "View.h"
using namespace std;

View::View()
{
	mySDLWindow = nullptr; //initialise to generate null access violation for debugging. 
	displayWidth = 1024.0f;	//sets the windows width
	displayHeight = 768.0f; //sets the windows height
}

View::~View()
{
	SDL_GL_DeleteContext(glContext); // delete context
	SDL_DestroyWindow(mySDLWindow); // detete window (make sure to delete the context and the window in the opposite order of creation in loadDisplay())
	SDL_Quit();
}

float View::getWidth() { return displayWidth; } //getters
float View::getHeight() { return displayHeight; }

void View::returnError(string errorString)
{
	//displays the errors called 
	cout << errorString << endl;
	cout << "press any  key to quit...";
	int in;
	cin >> in;
	SDL_Quit();
}

void View::SwapBuffers()
{
	SDL_GL_SwapWindow(mySDLWindow); //swap buffers
}

void View::cleanView(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear colour and depth buffer - set colour to colour defined in glClearColor
}

void View::loadDisplay()
{
	SDL_Init(SDL_INIT_EVERYTHING); //initalise everything

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8); //Min no of bits used to diplay colour
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);// set up z-buffer
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1); // set up double buffer   

	mySDLWindow = SDL_CreateWindow("Game Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, (int)displayWidth, (int)displayHeight, SDL_WINDOW_OPENGL); // create window
	
	//sends out an error if the window was not created
	if (mySDLWindow == nullptr)
	{
		returnError("window failed to create");
	}

	glContext = SDL_GL_CreateContext(mySDLWindow);

	//sends out an error if the context was not created 
	if (glContext == nullptr)
	{
		returnError("SDL_GL context failed to create");
	}

	//Sends out an error if glew was not initilaised 
	GLenum error = glewInit();
	if (error != GLEW_OK)
	{
		returnError("GLEW failed to initialise");
	}

	glEnable(GL_DEPTH_TEST); //enable z-buffering 
	glEnable(GL_CULL_FACE); //dont draw faces that are not pointing at the camera

	glClearColor(0.0f, 1.0f, 1.0f, 1.0f); //sets the background colour
}