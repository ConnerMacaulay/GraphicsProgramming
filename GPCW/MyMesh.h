#pragma once
#include <glm\glm.hpp>
#include <GL\glew.h>
#include <string>
#include "obj_loader.h"
using namespace std;
struct MyVertex
{
public:
	MyVertex(const vec3& pos, const vec2& texCoord)
	{
		this->pos = pos;
		this->texCoord = texCoord;
		this->normal = normal;
	}

	vec3* FindPos() { return &pos; }
	vec2* FindTexCoord() { return &texCoord; }
	vec3* FindNormal() { return &normal; }

private:
	vec3 pos;
	vec2 texCoord;
	vec3 normal;
};

class MyMesh
{
public:
	MyMesh();
	~MyMesh();

	void draw();
	void init(MyVertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices);
	void loadModel(const std::string& filename);
	void initModel(const IndexedModel& model);

private:



	enum
	{
		POSITION_VERTEXBUFFER,
		TEXCOORD_VB,
		NORMAL_VB,
		INDEX_VB,
		NUM_BUFFERS
	};

	GLuint VAO;
	GLuint VBO[NUM_BUFFERS]; // create our array of buffers
	unsigned int drawCount; //how much of the vertexArrayObject do we want to draw
};

