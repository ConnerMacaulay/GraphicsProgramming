#pragma once

#include <SDL\SDL.h>
#include <GL/glew.h>
#include "DisplayClass.h" 

enum class GameState{ PLAY, EXIT };

class MainGameClass
{
public:
	MainGameClass();
	~MainGameClass();

	void runGame();

private:

	void loadSystems(); //initilise the system
	void checkInput(); //check for any inputs ie keypress, controller buttons
	void mainGameLoop(); //run through the main loop of the game 
	void projectGame(); //Display the proccess onto the screen

	DisplayClass _gameDisplay;
	GameState _gameState;

};
