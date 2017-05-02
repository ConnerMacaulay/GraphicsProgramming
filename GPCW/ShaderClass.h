#pragma once
#include <string>
#include <GL\glew.h>
#include "MyTransforms.h"
#include "MyCamera.h"
using namespace std;

class ShaderClass
{
public:
	ShaderClass(const string& filename);

	void Bind(); //Set gpu to use our shaders
	void Update(const MyTransforms& transform, const MyCamera& camera);

	string ShaderClass::LoadShader(const string& fileName);
	void ShaderClass::CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const string& errorMessage);
	GLuint ShaderClass::CreateShader(const string& text, unsigned int type);

    ~ShaderClass();


protected:
private:
	static const unsigned int NUM_SHADERS = 2; // number of shaders

	enum
	{
		TRANSFORM_U,

		NUM_UNIFORMS
	};

	GLuint shadyProg; // Track the shader program
	GLuint shaders[NUM_SHADERS]; //array of shaders
	GLuint uniforms[NUM_UNIFORMS]; //no of uniform variables
};
