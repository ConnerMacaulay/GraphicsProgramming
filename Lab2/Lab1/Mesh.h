#pragma once
#include <glm\glm.hpp>
#include <GL\glew.h>
#include "vector"

class Vertex
{
public:
	glm::vec2 texCoord;
	glm::vec2 pos;
	Vertex(const glm::vec3& pos, const glm::vec2& texCoord)
	{
		this->pos = pos;
		this->texCoord = texCoord;

	}
protected:
private:
	
};

class Mesh
{
public:
	Mesh(Vertex* vertices, unsigned int numVertices);
	~Mesh();

	void Draw();
private:
	
	enum
	{
		POSITION_VERTEXBUFFER,
		TEXCOORD_VB,
		NUM_BUFFERS
	};

	GLuint vertexArrayObject;
	GLuint vertexArrayBuffers[NUM_BUFFERS]; // create our array of buffers
	unsigned int drawCount; //how much of the vertexArrayObject do we want to draw
};

