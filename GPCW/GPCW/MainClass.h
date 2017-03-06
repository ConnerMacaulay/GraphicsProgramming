#include <iostream>
#include "MainGameClass.h"

int main(int argc, char** argv) //arguments used to call SDL main
{
	MainGameClass mainGame; //create a new MainGameClass calling it mainGame
	mainGame.runGame(); //running the new main game class by calling the run function within it 

	return 0;
}
