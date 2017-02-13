#include "Texture.h"
#include "stb_image.h"
#include <cassert>
#include <iostream>


Texture::Texture(const std::string& fileName)
{
	int height;
	int width;
	int noComp;

	unsigned char* imageData = stbi_load((fileName).c_str(), &width, &height, &noComp, 4); //4 is the required components (no important for us) 

	if (imageData == NULL)
	{
		std::cerr << "texture load failed" << fileName << std::endl;
		glGenTextures(1, &textureHandler); //number of and address of textures
		glBindTexture(GL_TEXTURE_2D, textureHandler);//bind texture-define type & specify texture we are working with 

		//Set the parameters to control texture wrapping and linear filtering 
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); //wrap texture otside width
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); //wrap texture otside Height
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //linear filtering for minification (texture is smaller than the area) 
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);//linear filtering for magnification(texture is larger than the area)

		//send texture to the GPU 
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);//Target, Mipmapping level, Pixel Format, width,height,Border SIze, Input Format, Data Type of Texture, Our Images Data

		//Delete the data from CPU 
		stbi_image_free(imageData);
	}
}


Texture::~Texture()
{
	glDeleteTextures(1, &textureHandler);//number of and address of textures
}

void Texture::Bind(unsigned int unit)
{
	assert(unit >= 0 && unit <= 31); /// check we are working with one of the 32 textures

	glActiveTexture(GL_TEXTURE0 + unit);//set active texture unit
	glBindTexture(GL_TEXTURE_2D, textureHandler);//type of and texture to bind to unit
}
