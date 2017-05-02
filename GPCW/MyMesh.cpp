#include "MyMesh.h"
#include <vector>


void MyMesh::init(MyVertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices)
{
	IndexedModel model;

	//get the position and texcoords for each model vert
	for (unsigned int i = 0; i < numVertices; i++)
	{
		model.positions.push_back(*vertices[i].FindPos());
		model.texCoords.push_back(*vertices[i].FindTexCoord());
	}

	for (unsigned int i = 0; i < numIndices; i++)
		model.indices.push_back(indices[i]);

	initModel(model);
}

void MyMesh::initModel(const IndexedModel& model)
{
	
	drawCount = model.indices.size();

	glGenVertexArrays(1, &VAO); //generate a vertex array and store it in the VAO
	glBindVertexArray(VAO); //bind the VAO (any operation that works on a VAO will work on our bound VAO - binding)

	glGenBuffers(NUM_BUFFERS, VBO); //generate our buffers based of our array of data/buffers - GLuint vertexArrayBuffers[NUM_BUFFERS];
	
	glBindBuffer(GL_ARRAY_BUFFER, VBO[POSITION_VERTEXBUFFER]); //tell opengl what type of data the buffer is (GL_ARRAY_BUFFER), and pass the data
	glBufferData(GL_ARRAY_BUFFER, model.positions.size() * sizeof(model.positions[0]), &model.positions[0], GL_STATIC_DRAW); //move the data to the GPU - type of data, size of data, starting address (pointer) of data, where do we store the data on the GPU (determined by type)
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[TEXCOORD_VB]); //tell opengl what type of data the buffer is (GL_ARRAY_BUFFER), and pass the data
	glBufferData(GL_ARRAY_BUFFER, model.positions.size() * sizeof(model.texCoords[0]), &model.texCoords[0], GL_STATIC_DRAW); //move the data to the GPU - type of data, size of data, starting address (pointer) of data, where do we store the data on the GPU
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[NORMAL_VB]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(model.normals[0]) * model.normals.size(), &model.normals[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBO[INDEX_VB]); //tell opengl what type of data the buffer is (GL_ARRAY_BUFFER), and pass the data
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, model.indices.size() * sizeof(model.indices[0]), &model.indices[0], GL_STATIC_DRAW); //move the data to the GPU - type of data, size of data, starting address (pointer) of data, where do we store the data on the GPU

	glBindVertexArray(0); // unbind our VAO
}

MyMesh::MyMesh()
{
	drawCount = NULL;
}

void MyMesh::loadModel(const std::string& filename)
{
	IndexedModel model = OBJModel(filename).ToIndexedModel();
	initModel(model);
}

MyMesh::~MyMesh()
{
	glDeleteVertexArrays(1, &VAO); // delete arrays
}

void MyMesh::draw()
{
	glBindVertexArray(VAO);
	
	glDrawElements(GL_TRIANGLES, drawCount, GL_UNSIGNED_INT, 0);
	
	glBindVertexArray(0);
}

