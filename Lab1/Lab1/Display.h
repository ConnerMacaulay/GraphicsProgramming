#pragma once
#include <SDL/SDL.h>
#include <GL\glew.h>
#include <iostream>
#include <string>
using namespace std;


class Display
{
public:
	Display();
	~Display();
	void initDisplay();
	void swapBuffer();
	void clear();
	SDL_GLContext glContext();

private:

	void returnError(std::string errorString);

	SDL_Window* _window; //holds pointer to out window
	int _screenWidth;
	int _screenHeight;
};

