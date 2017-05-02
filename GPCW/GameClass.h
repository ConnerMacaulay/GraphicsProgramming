#pragma once
#include <SDL\SDL.h>
#include <GL/glew.h>
#include "View.h" 
#include "ShaderClass.h"
#include "MyMesh.h"
#include "MyTextures.h"
#include "MyTransforms.h"

enum class GState{PLAY, EXIT};

class GameClass
{
public:
	GameClass();
	~GameClass();

	void Initialize();

private:

	void loadSystems();
	void ProcessInputs();
	void mainLoop();
	void ProduceGame();

	View m_gDisplay;
	GState m_gState;
	MyMesh mesh1;
	MyMesh mesh2;
	MyMesh mesh3;
	MyCamera myCamera;

	float counter;


};

