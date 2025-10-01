#include "App.h"
#include "TriangleScene.h"
#include "ComplexScene.h"

GLFWwindow* App::m_window = nullptr;

App::App()
{
	m_timer = new Timer();
	m_camera = new Camera();

	createWindow();
	m_camera->UseCamera(m_window);
	loadScenes();
}

App::~App()
{
	for (Scene* scene : m_scenes) {
		if (scene) delete scene;
	}
}

static void error_callback(int error, const char* description) { fputs(description, stderr); }

void App::createWindow()
{
	glfwSetErrorCallback(error_callback);
	if (!glfwInit()) {
		fprintf(stderr, "ERROR: could not start GLFW3\n");
		exit(EXIT_FAILURE);
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  

	m_window = glfwCreateWindow(800, 600, "ZPG - Stupka", NULL, NULL);
	if (!m_window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(m_window);
	glfwSwapInterval(1);

	glewExperimental = GL_TRUE;
	glewInit();

	printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
	printf("Using GLEW %s\n", glewGetString(GLEW_VERSION));
	printf("Vendor %s\n", glGetString(GL_VENDOR));
	printf("Renderer %s\n", glGetString(GL_RENDERER));
	printf("GLSL %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
	int major, minor, revision;
	glfwGetVersion(&major, &minor, &revision);
	printf("Using GLFW %i.%i.%i\n", major, minor, revision);

	int width, height;
	glfwGetFramebufferSize(m_window, &width, &height);
	float ratio = width / (float)height;
	glViewport(0, 0, width, height);
	glEnable(GL_DEPTH_TEST);
	glfwSwapInterval(0);
}

void App::loadScenes()
{
	m_scenes[0] = new TriangleScene();
	//m_scenes[1] = new CircleScene();
	m_scenes[2] = new ComplexScene();
	for (Scene* scene : m_scenes) {
		if (scene) scene->load();
	}
	m_currentScene = m_scenes[1];
}

void App::handleInputs()
{
    glfwPollEvents();
    if (glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(m_window, 1); 
	if (glfwGetKey(m_window, GLFW_KEY_1) == GLFW_PRESS) {
		m_currentScene = m_scenes[0];
	}
	if (glfwGetKey(m_window, GLFW_KEY_2) == GLFW_PRESS) {
		//m_currentScene = m_scenes[1];
	}
	if (glfwGetKey(m_window, GLFW_KEY_3) == GLFW_PRESS) {
		m_currentScene = m_scenes[2];
	}
	m_camera->HandleInputs(m_timer->getDeltaTime(), m_window);
}

void App::s_throwRuntimeError(const char* error)
{
	printf("Runtime error: %s\n", error);
	glfwSetWindowShouldClose(m_window, 1);
}

//TODO: Transformation classes
//TODO: move camera to Scene?
void App::run()
{
	while (!glfwWindowShouldClose(m_window)) {
		handleInputs();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		if (m_currentScene->UseCamera()) {
			glm::mat4 proj = glm::perspective(glm::radians(60.f), 800.f / 600.f, 0.1f, 1000.0f);
			glm::mat4 view = glm::lookAt(m_camera->GetPosition(), m_camera->GetPosition() + m_camera->GetForwardVector(), glm::vec3(0, 1, 0));
			glm::mat4 model = glm::rotate(glm::mat4(1), m_timer->getTimeSinceStart(), glm::vec3(0, 1, 0));
			for (DrawableObject dO : m_currentScene->GetDrawableObjects()) {
				dO.draw(proj * view * model, "mat");
			}
		}
		else {
			glm::mat4 rotate = glm::rotate(glm::mat4(1), m_timer->getTimeSinceStart(), glm::vec3(0, 0, 1));
			for (DrawableObject dO : m_currentScene->GetDrawableObjects()) {
				dO.draw(rotate, "mat");
			}
		}
		glfwSwapBuffers(m_window);
		m_timer->timeFrame();
	}

	glfwDestroyWindow(m_window);

	glfwTerminate();
	exit(EXIT_SUCCESS);
}
