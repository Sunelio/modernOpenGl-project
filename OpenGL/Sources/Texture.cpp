#define STB_IMAGE_IMPLEMENTATION
#include<Texture.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <STB_Image/stb_image.h>

using namespace Resources;
using namespace std;

//--------------Texture------------\\

void Texture::Load(const std::string& name)
{
	int width, height, nrChannels;

	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(name.c_str(), &width, &height, &nrChannels, 0);
	
	glGenTextures(1, &textKey);
	glBindTexture(GL_TEXTURE_2D, textKey);
	if(nrChannels == 3)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	else
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(data);
}

void Texture::UnLoad()
{

}

Texture::Texture()
{

}

Texture::~Texture()
{

}