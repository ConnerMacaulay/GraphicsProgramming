#include "GameClass.h"
#include "MyCamera.h"
#include <iostream>
#include <string>
using namespace glm;


MyVertex vertices[] = {MyVertex(vec3(-0.5, -0.5, 0), vec2(0.0, 0.0)),
					MyVertex(vec3(0, 0.5, 0), vec2(0.5, 1.0)),
					MyVertex(vec3(0.5, -0.5, 0), vec2(1.0, 0.0)) };

unsigned int indices[] = { 0, 1, 2 };

MyTransforms transform;

GameClass::GameClass()
{
	m_gState = GState::PLAY; //states the game is playing
	View* m_gDisplay = new View(); //new display
    MyMesh* mesh1();//stores the model meshes
	MyMesh* mesh2();
	MyMesh* mesh3();
}

GameClass::~GameClass()
{
}

void GameClass::Initialize()
{
	//called once on program start up 
	loadSystems(); 
	mainLoop();
}

void GameClass::loadSystems()
{
	m_gDisplay.loadDisplay(); 
	mesh1.loadModel("C:\\Users\\Conner\\Desktop\\GPCW\\res\\almondkernel.obj"); 
	mesh2.loadModel("C:\\Users\\Conner\\Desktop\\GPCW\\res\\monkey3.obj");	// all three links to three diffrent objects
	mesh3.loadModel("C:\\Users\\Conner\\Desktop\\GPCW\\res\\Evaporating-dish-obj.obj");
	myCamera.loadCamera(vec3(0, 0, -5), 70.0f, (float)m_gDisplay.getWidth()/m_gDisplay.getHeight(), 0.01f, 1000.0f); //sets the cameras position 
	counter = 0.0f;
}

void GameClass::mainLoop()
{
	while (m_gState != GState::EXIT) //main game loop will only exit when the state changes
	{
		ProcessInputs();
		ProduceGame();
	}
}

void GameClass::ProcessInputs()
{
	SDL_Event evnt;

	while(SDL_PollEvent(&evnt)) //get and process events
	{
		switch (evnt.type)
		{
			//proccesses the quit event
			case SDL_QUIT:
				m_gState = GState::EXIT;
				break;
		}
	}
	
}


void GameClass::ProduceGame()
{
	m_gDisplay.cleanView(0.0f, 0.0f, 0.0f, 1.0f);
	
	ShaderClass gameShader("C:\\Users\\Conner\\Desktop\\GPCW\\res\\shader"); //new shader
	MyTextures seedTxt("C:\\Users\\Conner\\Desktop\\GPCW\\res\\seed.jpg"); //load texture
	MyTextures statueTxt("C:\\Users\\Conner\\Desktop\\GPCW\\res\\Marble.jpg"); //load texture
	MyTextures bowlTxt("C:\\Users\\Conner\\Desktop\\GPCW\\res\\itemamacotm3.jpg");//load texture
	
	//set the position, rotation and scale of each object
	transform.SetPos(vec3(sinf(counter), 0.0, 0.0));
	transform.SetRot(vec3(0.0, 0.0, counter * 5));
	transform.SetScale(vec3(sinf(counter), sinf(counter), sinf(counter)));

	//Binds the textures to the objects
	gameShader.Bind();
	gameShader.Update(transform, myCamera);
	seedTxt.Bind(0);
	mesh1.draw();
	statueTxt.Bind(0);
	mesh2.draw();
	bowlTxt.Bind(0);
	mesh3.draw();
	counter = counter + 0.01f;
				
	glEnableClientState(GL_COLOR_ARRAY); 
	glEnd();

	m_gDisplay.SwapBuffers();
} 