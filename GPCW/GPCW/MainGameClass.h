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

	void loadSystems();
	void checkInput();
	void mainGameLoop();
	void projectGame();

	DisplayClass _gameDisplay;
	GameState _gameState;

};
