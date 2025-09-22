#pragma once

// Include GLEW
#include <GL/glew.h>

//Include GLFW  
#include <GLFW/glfw3.h>  

//Include GLM  
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

//Include the standard C++ headers  
#include <stdlib.h>
#include <stdio.h>

// Include Assimp
//#include <assimp/Importer.hpp>
//#include <assimp/scene.h>
//#include <assimp/postprocess.h>

// Include OpenCV
//#include <opencv2/opencv.hpp>

// Include AntTweakBar
//#include <AntTweakBar/AntTweakBar.h>

//static bool rightRotation = true;
//
//static double mouseX = 0;
//static double mouseY = 0;

#include "Timer.h"
#include "ShaderModule.h"
#include "Model.h"

static void error_callback(int error, const char* description) { fputs(description, stderr); }

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	//if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
	//	rightRotation = !rightRotation;

	printf("key_callback [%d,%d,%d,%d] \n", key, scancode, action, mods);
}

static void window_focus_callback(GLFWwindow* window, int focused) { printf("window_focus_callback \n"); }

static void window_iconify_callback(GLFWwindow* window, int iconified) { printf("window_iconify_callback \n"); }

static void window_size_callback(GLFWwindow* window, int width, int height) {
	printf("resize %d, %d \n", width, height);
	glViewport(0, 0, width, height);
}

static void cursor_callback(GLFWwindow* window, double x, double y) { printf("cursor_callback %f %f\n",x,y); }

static void button_callback(GLFWwindow* window, int button, int action, int mode) {
	if (action == GLFW_PRESS) printf("button_callback [%d,%d,%d]\n", button, action, mode);
}



class Renderer {
public:
	Renderer();
	void init();
	void loadShaders();
	void loadModels();
	void run();
private:
	GLFWwindow* m_window = nullptr;
	GLuint m_VAO = 0;
	ShaderModule* m_shaderModuleTri = nullptr;
	Model* m_modelTri = nullptr;
	ShaderModule* m_shaderModuleSq = nullptr;
	Model* m_modelSq = nullptr;
	Timer* m_timer = nullptr;
};
