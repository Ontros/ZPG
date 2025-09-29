#pragma once

#include "Libraries.h"

#include "Timer.h"
#include "ShaderProgram.h"
#include "Model.h"
#include "Camera.h"

class Renderer {
public:
	Renderer();
	void init();
	void loadShaders();
	void loadModels();
	static void s_throwRuntimeError(const char* error);
	void run();
private:
	static GLFWwindow* m_window;
	GLuint m_VAO = 0;
	ShaderProgram* m_shaderModuleSu = nullptr;
	Model* m_modelSu = nullptr;
	Timer* m_timer = nullptr;
	Camera* m_camera = nullptr;
};
