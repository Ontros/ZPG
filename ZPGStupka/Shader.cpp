#include "App.h"
#include "Shader.h"

Shader::Shader(const char* path, GLenum shaderType)
{
	m_shader = glCreateShader(shaderType);
	std::string shaderSource = readShaderFromPath(path);
	const char* sourcePtr = shaderSource.c_str();
	glShaderSource(m_shader, 1, &sourcePtr, NULL);
	glCompileShader(m_shader);
}

Shader::~Shader()
{
	if (m_shader) glDeleteShader(m_shader);
}

GLuint Shader::GetShader() const
{
	return m_shader;
}

std::string Shader::readShaderFromPath(const char* path)
{
	std::fstream file(path);
	if (!file.is_open()) {
		App::s_throwRuntimeError("Failed to open shader file");
	}
	std::stringstream ss;
	ss << file.rdbuf();
	return ss.str();
}
