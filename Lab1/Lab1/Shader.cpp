#include "Shader.h"
#include <iostream>
#include <fstream>

std::string Shader::LoadShader(const std::string&fileName)
{
	std::ifstream file;
	file.open((fileName).c_str());

	std::string output;
	std::string line;

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
		std::cerr << "Unable to load shader:" << fileName << std::endl;
	}

	return output;
}

void Shader::CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string&errorMessage)
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
			glGetShaderInfoLog(shader, sizeof(error),NULL, error);

		std::cerr << errorMessage << ":" << error << "" << std::endl;

	}
}

GLuint Shader::CreateShader(const std::string& text, unsigned int type)
{
	GLuint shader = glCreateShader(type); //create shader based on specified type

	if (shader == 0) //if == 0 shader no created
		std::cerr << "Error type creation failed " << type << std::endl;

	const GLchar* stringSource[1]; //convert strings into list of c-strings
	stringSource[0] = text.c_str();
	GLint lengths[1];
	lengths[0] = text.length();

	glShaderSource(shader, 1, stringSource, lengths); //send source code to opengl
	glCompileShader(shader); //get open gl to compile shader code

	CheckShaderError(shader, GL_COMPILE_STATUS, false, "Error compiling shader!"); //check for compile error

	return shader;
}

Shader::Shader(const std::string&filename)
{
	program = glCreateProgram();
	shaders[0] = CreateShader(LoadShader("C:\\Users\\cmacau200\\Desktop\\GitHub\\GraphicsProgramming\\Lab1\\res\\shader.vert"), GL_VERTEX_SHADER);
	shaders[1] = CreateShader(LoadShader("C:\\Users\\cmacau200\\Desktop\\GitHub\\GraphicsProgramming\\Lab1\\res\\shader.frag"), GL_FRAGMENT_SHADER);

	for (unsigned int i; i < NUM_SHADERS; i++)
	{
		glAttachShader(program, shaders[i]);
	}

	glBindAttribLocation(program, 0, "position");
	glLinkProgram(program);//create executables that will run on the GPU shaders
	CheckShaderError(program, GL_VALIDATE_STATUS, true, "Error:Shader program not valid");
}

Shader:: ~Shader()
{
	for (unsigned int i; i < NUM_SHADERS; i++)
	{
		glDetachShader(program, shaders[i]);//detach shader from program
		glDetachShader(shaders[i]);//detach the shaders
	}
	glDeleteProgram(program);
}
