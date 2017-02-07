#pragma once
#include <glm\glm\glm.hpp>
#include <GL\glew.h>

class vertex
{
public:
	vertex(const glm::vec3&pos)
	{
		this->pos = pos;
	}
protected:
private:
	glm::vec3 pos;
};

class Mesh 
{
public:
	Mesh(vertex* vertices, unsigned int numVertecies);
	~Mesh();

	void Draw();
private: 

	enum 
	{
		POSITION_VERTEXBUFFER,
		NUM_BUFFERS
	};

	GLuint vertexArrayObject;
	GLuint vertexArrayBuffers[NUM_BUFFERS];//create our array of buffers
	unsigned int drawCount; //how much of the vertexArrayObject do we want to draw
};


