#pragma once 

#include <GL/glew.h>
#include <string>

class Material
{
public:
	Material();
	~Material();

	bool loadFromFile(const std::string& name);
	bool create(uint32_t width, uint32_t height, uint32_t bits, GLint format, GLint internalFormat);
	GLint getID() const;

	void bind(uint8_t unit = 0);
	void unbind(uint8_t unit = 0);

private:
	GLint m_texID;
};