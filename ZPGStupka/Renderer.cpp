#include "Renderer.h"
#include "models/suzi_flat.h"

GLFWwindow* Renderer::m_window = nullptr;

Renderer::Renderer()
{
	m_timer = new Timer();
	m_camera = new Camera();
}

static void error_callback(int error, const char* description) { fputs(description, stderr); }

void Renderer::init()
{
	glfwSetErrorCallback(error_callback);
	if (!glfwInit()) {
		fprintf(stderr, "ERROR: could not start GLFW3\n");
		exit(EXIT_FAILURE);
	}

	//TODO: remove
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
	//glfwSwapInterval(0);

	m_camera->PrepareWindow(m_window);
}

void Renderer::loadShaders()
{
	m_shaderModuleSu = new ShaderProgram("Shaders/vert.glsl", "Shaders/frag.glsl");
}

void Renderer::loadModels()
{
	m_modelSu = new Model(suziFlat, 17424, 2);
}

void Renderer::s_throwRuntimeError(const char* error)
{
	printf("Runtime error: %s\n", error);
	glfwSetWindowShouldClose(m_window, 1);
}

void Renderer::run()
{
	while (!glfwWindowShouldClose(m_window)) {
		m_camera->HandleInputs(m_timer->getDeltaTime(), m_window);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		m_shaderModuleSu->setShader();
		glm::mat4 view = glm::lookAt(m_camera->GetPosition(), m_camera->GetPosition() + m_camera->GetForwardVector(), glm::vec3(0, 1, 0));
		glm::mat4 proj = glm::perspective(glm::radians(60.f), 800.f / 600.f, 0.1f, 1000.0f);
		glm::mat4 model = glm::rotate(glm::mat4(1), m_timer->getTimeSinceStart(), glm::vec3(0, 1, 0));
		m_shaderModuleSu->setUniform(proj * view * model, "mat");
		m_modelSu->drawModel();
		glfwSwapBuffers(m_window);
		m_timer->timeFrame();
	}

	glfwDestroyWindow(m_window);

	glfwTerminate();
	exit(EXIT_SUCCESS);
}
