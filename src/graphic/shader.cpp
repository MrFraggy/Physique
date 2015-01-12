#include <graphic/shader.h>
#include <exception>
#include <iostream>
#include <fstream>

Shader::Shader() :
	m_vertex(0), m_fragment(0), m_program(0),
	m_vertexLoaded(false), m_fragmentLoaded(false), m_programLoaded(false)
{}

Shader::~Shader()
{

}

bool Shader::loadFromFile(const std::string& src, ShaderType t)
{
	
	try {
		std::ifstream file(src);
		if(!file.is_open())
			return false;
		
		std::string data;
		char c;
		while(!file.eof()) {
			c = file.get();
			data += c;
		}
		data.resize(data.size()-1);
		const char* s = data.c_str();
		if(t == ShaderType_Vertex) {
			m_vertex = glCreateShader(GL_VERTEX_SHADER);
			m_vertFile = src;
			glShaderSource(m_vertex, 1, &s, 0);
		} else if(t == ShaderType_Fragment) {
			m_fragment = glCreateShader(GL_FRAGMENT_SHADER);
			m_fragFile = src;
			glShaderSource(m_fragment, 1, &s, 0);
		} else {
			std::cerr << "Unknown ShaderType" << std::endl;
			return false;
		}
	return true;
	} catch(const std::exception& e) {
		std::cerr << e.what() << std::endl;
		return false;
	}
}

bool Shader::loadFromMemory(const std::string& vert, const std::string& frag) {
	const char* v = vert.c_str();
	const char* f = frag.c_str();
	m_vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(m_vertex, 1, &v, 0);
	m_fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(m_fragment, 1, &f, 0);

	return true;
}

bool Shader::compile()
{
	m_program = glCreateProgram();
	glCompileShader(m_vertex);
	GLint status;
	glGetShaderiv(m_vertex, GL_COMPILE_STATUS, &status);
	if(status != GL_TRUE)
	{
		GLint length;
		glGetShaderiv(m_vertex, GL_INFO_LOG_LENGTH, &length);
		char* log = new char[length];
		glGetShaderInfoLog(m_vertex, length, 0, log);
		std::string logString(log);
		delete [] log;
		std::cerr << "Error while compiling vertex shader " << m_vertFile << ": " << logString << std::endl;
		return false;
	} else
		m_vertexLoaded = true;

	glCompileShader(m_fragment);
	glGetShaderiv(m_fragment, GL_COMPILE_STATUS, &status);
	if(status != GL_TRUE)
	{
		GLint length;
		glGetShaderiv(m_fragment, GL_INFO_LOG_LENGTH, &length);
		char* log = new char[length];
		glGetShaderInfoLog(m_fragment, length, 0, log);
		std::string logString(log);
		delete [] log;
		std::cerr << "Error while compiling fragment shader "<< m_fragFile << ": "<<logString<< std::endl;
		return false;
	} else
		m_fragmentLoaded = true;
	glAttachShader(m_program, m_vertex);
	glAttachShader(m_program, m_fragment);
	glLinkProgram(m_program);

	glGetProgramiv(m_program, GL_LINK_STATUS, &status);
	if(status != GL_TRUE)
	{
		GLint length;
		glGetProgramiv(m_program, GL_INFO_LOG_LENGTH, &length);
		char* log = new char[length];
		glGetProgramInfoLog(m_program, length, 0, log);
		std::string logString(log);
		delete [] log;
		std::cerr << "Error while linking shader " << logString << std::endl; 
		return false;
	} else
		m_programLoaded = true;

	return true;
}

GLuint Shader::getProgram() const
{
	return m_program;
}

void Shader::bind()
{
	glUseProgram(m_program);
}
void Shader::unbind()
{
	glUseProgram(0);
}