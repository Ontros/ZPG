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
	Model(const float* points, int size, int vec3s);
	~Model();
	void drawModel() const;

private:
	GLuint m_VBO = 0;
	GLuint m_VAO = 0;
	int m_triangles = 0;
};
