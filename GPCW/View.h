#pragma once
#include <SDL/SDL.h>
#include <GL\glew.h>
#include <iostream>
#include <string>
using namespace std;


class View
{
public:
	View();
	~View();
	void loadDisplay();
	void SwapBuffers();
	void cleanView(float r, float g, float b, float a);

	float getWidth();
	float getHeight();

private:

	void returnError(string errorString);
	
	SDL_GLContext glContext; //global variable to hold the context
	SDL_Window* mySDLWindow; //holds pointer to out window
	float displayWidth;
	float displayHeight;
};

