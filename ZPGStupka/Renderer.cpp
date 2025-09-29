#include "Renderer.h"
#include "models/suzi_flat.h"

Renderer::Renderer()
{
	m_timer = new Timer();
	m_camera = new Camera();
}

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

	m_camera->PrepareWindow(m_window);
}

void Renderer::loadShaders()
{
	const char* vertex_shader_su =
	"#version 410\n"
	"layout(location=0) in vec3 vp;"
	"layout(location=1) in vec3 vn;"
	"layout(location=0) out vec3 normal;"
	"out vec3 position;"
	"uniform mat4 mat;"
	"void main () {"
	"     gl_Position = mat*vec4(vp, 1.0);"
	"     position = vp;"
	"     normal = vn;"	
	"}";
	const char* fragment_shader_su =
	"#version 410\n"
	"layout(location=0) in vec3 normal;"
	"in vec3 position;"
	"out vec4 frag_colour;"
	"void main () {"
	"     frag_colour = vec4(normal, 1.0f);"
	"}";

	m_shaderModuleSu = new ShaderProgram(vertex_shader_su, fragment_shader_su);
}

void Renderer::loadModels()
{
	m_modelSu = new Model(suziFlat, 17424, 2);
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
