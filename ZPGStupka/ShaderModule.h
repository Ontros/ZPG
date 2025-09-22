#pragma once

// Include GLEW
#include <GL/glew.h>

//Include GLFW  
#include <GLFW/glfw3.h>  


//Include the standard C++ headers  
#include <stdlib.h>
#include <stdio.h>

class ShaderModule {
public:
	ShaderModule(const char* vertexShaderCode, const char* fragmentShaderCode);
	void setShader();
	void setUniform(float a);

private:
	GLuint m_id;
};
