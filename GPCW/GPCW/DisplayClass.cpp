#include "DisplayClass.h"
using namespace std;


DisplayClass::DisplayClass()
{
	_window = nullptr; //initilise the window and generate a null access violation for debugging 
	_displayHeight = 1024; //sets the screen height 
	_displayWidth = 768; //sets the screen width
}

DisplayClass::~DisplayClass()
{
}

void DisplayClass::returnError(std::string errorString)
{
	cout << errorString << endl;
	cout << "Press any key to quit..." << endl;
	int inp;
	cin >> inp;
	SDL_Quit();
}

void DisplayClass::exchangeBuffer()
{
	SDL_GL_SwapWindow(_window);
}

void DisplayClass::loadDisplay()
{
	SDL_Init(SDL_INIT_EVERYTHING); //initilise everything 
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8); //Min no of bits used to diplay colour
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1); // set up double buffer   



}
