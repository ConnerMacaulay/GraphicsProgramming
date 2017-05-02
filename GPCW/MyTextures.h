#pragma once
#include <string>
#include <GL\glew.h>

class MyTextures
{
public:
	MyTextures(const std::string& fileName); //texture path stored

	void Bind(unsigned int unit); // bind upto 32 textures

	~MyTextures();

protected:
private:

	GLuint textureHandler;
};

