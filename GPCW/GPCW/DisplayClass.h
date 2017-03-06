#pragma once
#include <SDL/SDL.h>
#include <GL\glew.h>
#include <iostream>
#include <string>
using namespace std;


class DisplayClass
{
public:
	DisplayClass();
	~DisplayClass();
	void loadDisplay();
	void exchangeBuffer();

private:

	void returnError(std::string errorString);

	SDL_Window* _window; //holds pointer to out window
	int _displayWidth; //used to hold the screen width
	int _displayHeight; //used to hold the screen height
};

