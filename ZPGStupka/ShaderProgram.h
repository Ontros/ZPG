#pragma once

#include "Libraries.h"
#include "Shader.h"

class ShaderProgram {
public:
	ShaderProgram(const char* vertexShaderPath, const char* fragmentShaderPath);
	~ShaderProgram();
	void setShader() const;
	void setUniform(float a, const char* uniformName);
	void setUniform(glm::mat4 mat, const char* uniformName);

private:
	GLuint m_id;
	Shader m_vertShader;
	Shader m_fragShader;

	GLint findUniformLocation(const char* uniformName) const;
};
