#pragma once

// Include GLEW
#include <GL/glew.h>

//Include GLFW  
#include <GLFW/glfw3.h>  


//Include the standard C++ headers  
#include <stdlib.h>
#include <stdio.h>
#include <glm/ext/matrix_float4x4.hpp>

class ShaderProgram {
public:
	ShaderProgram(const char* vertexShaderCode, const char* fragmentShaderCode);
	void setShader();
	void setUniform(float a, const char* uniformName);
	void setUniform(glm::mat4 mat, const char* uniformName);

private:
	GLuint m_id;
};
