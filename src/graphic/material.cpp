#include <graphic/material.h>

#include <iostream>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

Material::Material() : m_texID(-1) 
{
	glGenTextures(1, (GLuint*)&m_texID);
}

Material::~Material() 
{
	//std::cout << "destroying " << m_texID << std::endl;
	glDeleteTextures(1, (GLuint*)&m_texID);
}

bool Material::loadFromFile(const std::string& name)
{
	
	SDL_Surface *image = IMG_Load(name.c_str());
	if(!image) {
		std::cerr << "Unable to load texture \"" << name << "\"" << std::endl;
		return false;
	}

	//m_image.flipHorizontally();
	//m_image.flipVertically();
	glBindTexture(GL_TEXTURE_2D, m_texID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	GLenum format = GL_RGB;

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, image->w, image->h, 0, format, GL_UNSIGNED_BYTE, image->pixels);

	glBindTexture(GL_TEXTURE_2D, 0);
	SDL_FreeSurface(image);

	return true;
}

bool Material::create(uint32_t width, uint32_t height, uint32_t bits, GLint format, GLint internalFormat) {
	glBindTexture(GL_TEXTURE_2D, m_texID);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, GL_FLOAT, nullptr);
	glBindTexture(GL_TEXTURE_2D, 0);
	return true;
}

GLint Material::getID() const {
	return m_texID;
}

void Material::bind(uint8_t unit) {
	glActiveTexture(GL_TEXTURE0+unit);
	glBindTexture(GL_TEXTURE_2D, m_texID);
	glActiveTexture(GL_TEXTURE0);
}

void Material::unbind(uint8_t unit) {
	glActiveTexture(GL_TEXTURE0+unit);
	glBindTexture(GL_TEXTURE_2D, 0);
	glActiveTexture(GL_TEXTURE0);
}