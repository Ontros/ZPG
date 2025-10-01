#pragma once

#include "Libraries.h"

class Shader
{
public:
	Shader(const char* path, GLenum shaderType);
	~Shader();
	GLuint GetShader() const;

private:
	std::string readShaderFromPath(const char* path);
	GLuint m_shader;
};
