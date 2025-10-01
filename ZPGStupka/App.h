#pragma once

#include "Libraries.h"

#include "Timer.h"
#include "Scene.h"

class App {
public:
	App();
	~App();

	static void s_throwRuntimeError(const char* error);
	void run();
private:
	static GLFWwindow* m_window;
	GLuint m_VAO = 0;
	Timer* m_timer = nullptr;
	Camera* m_camera = nullptr;
	Scene* m_scenes[3] = { nullptr, };
	Scene* m_currentScene = nullptr;

	void createWindow();
	void loadScenes();
	void handleInputs();
};
