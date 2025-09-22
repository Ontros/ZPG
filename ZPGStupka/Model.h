#pragma once

// Include GLEW
#include <GL/glew.h>

//Include GLFW  
#include <GLFW/glfw3.h>  


//Include the standard C++ headers  
#include <stdlib.h>
#include <stdio.h>

class Model {
public:
	Model(float* points, int size);
	void drawModel();

private:
	GLuint m_VBO = 0;
	GLuint m_VAO = 0;
	int m_triangles = 0;
};
