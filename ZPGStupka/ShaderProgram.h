#pragma once

#include "Libraries.h"

class ShaderProgram {
public:
	ShaderProgram(const char* vertexShaderCode, const char* fragmentShaderCode);
	void setShader();
	void setUniform(float a, const char* uniformName);
	void setUniform(glm::mat4 mat, const char* uniformName);

private:
	GLuint m_id;
};
