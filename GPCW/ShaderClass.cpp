#include "ShaderClass.h"
#include <iostream>
#include <fstream>
using namespace std;

ShaderClass::ShaderClass(const string& filename)
{
	shadyProg = glCreateProgram(); // create shader program (openGL saves as ref number)
	shaders[0] = CreateShader(LoadShader("C:\\Users\\Conner\\Desktop\\GPCW\\res\\shader.vert"), GL_VERTEX_SHADER); // create vertex shader
	shaders[1] = CreateShader(LoadShader("C:\\Users\\Conner\\Desktop\\GPCW\\res\\shader.frag"), GL_FRAGMENT_SHADER); // create fragment shader

	for (unsigned int i = 0; i < NUM_SHADERS; i++)
	{
		glAttachShader(shadyProg, shaders[i]); //add all our shaders to the shader program "shaders" 
	}

	glBindAttribLocation(shadyProg, 0, "position"); // associate attribute variable with our shader program attribute (in this case attribute vec3 position;)
	glBindAttribLocation(shadyProg, 1, "texCoord"); 

	glLinkProgram(shadyProg); //create executables that will run on the GPU shaders
	CheckShaderError(shadyProg, GL_LINK_STATUS, true, "Error: Shader program linking failed"); // cheack for error

	glValidateProgram(shadyProg); //check the entire program is valid
	CheckShaderError(shadyProg, GL_VALIDATE_STATUS, true, "Error: Shader program not valid");

	uniforms[TRANSFORM_U] = glGetUniformLocation(shadyProg, "transform"); // associate with the location of uniform variable within a program
}


ShaderClass::~ShaderClass()
{
	for (unsigned int i = 0; i < NUM_SHADERS; i++)
	{
		glDetachShader(shadyProg, shaders[i]); //detach shader from program
		glDeleteShader(shaders[i]); //delete the sahders
	}
	glDeleteProgram(shadyProg); // delete the program
}

void ShaderClass::Bind()
{
	glUseProgram(shadyProg); //installs the program object specified by program as part of rendering state
}

void ShaderClass::Update(const MyTransforms& transform, const MyCamera& camera)
{
	glm::mat4 mvp = camera.GetViewProjection() * transform.GetModel();
	glUniformMatrix4fv(uniforms[TRANSFORM_U], 1, GLU_FALSE, &mvp[0][0]);
}


GLuint ShaderClass::CreateShader(const string& text, unsigned int type)
{
	GLuint shader = glCreateShader(type); //create shader based on specified type

	if (shader == 0) //if == 0 shader no created
		cerr << "Error type creation failed " << type << endl;

	const GLchar* stringSource[1]; //convert strings into list of c-strings
	stringSource[0] = text.c_str();
	GLint lengths[1];
	lengths[0] = text.length();

	glShaderSource(shader, 1, stringSource, lengths); //send source code to opengl
	glCompileShader(shader); //get open gl to compile shader code

	CheckShaderError(shader, GL_COMPILE_STATUS, false, "Error compiling shader!"); //check for compile error

	return shader;
}

string ShaderClass::LoadShader(const string& fileName)
{
	ifstream file;
	file.open((fileName).c_str());

	string output;
	string line;

	if (file.is_open())
	{
		while (file.good())
		{
			getline(file, line);
			output.append(line + "\n");
		}
	}
	else
	{
		cerr << "Unable to load shader: " << fileName << endl;
	}

	return output;
}

void ShaderClass::CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const string& errorMessage)
{
	GLint success = 0;
	GLchar error[1024] = { 0 };

	if (isProgram)
		glGetProgramiv(shader, flag, &success);
	else
		glGetShaderiv(shader, flag, &success);

	if (success == GL_FALSE)
	{
		if (isProgram)
			glGetProgramInfoLog(shader, sizeof(error), NULL, error);
		else
			glGetShaderInfoLog(shader, sizeof(error), NULL, error);

		cerr << errorMessage << ": '" << error << "'" << endl;
	}
}

