#include "Renderer.h"
#include "models/suzi_flat.h"

Renderer::Renderer()
{
	m_timer = new Timer();
}

void Renderer::init()
{
	glfwSetErrorCallback(error_callback);
	if (!glfwInit()) {
		fprintf(stderr, "ERROR: could not start GLFW3\n");
		exit(EXIT_FAILURE);
	}

	//inicializace konkretni verze
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  

	m_window = glfwCreateWindow(800, 600, "ZPG - Stupka", NULL, NULL);
	if (!m_window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(m_window);
	glfwSwapInterval(1);

	// start GLEW extension handler
	glewExperimental = GL_TRUE;
	glewInit();


	// get version info
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
}

void Renderer::loadShaders()
{
	const char* vertex_shader =
	"#version 410\n"
	"layout(location=0) in vec3 vp;"
	"void main () {"
	"     gl_Position = vec4 (vp.x, vp.y, vp.z, 1.0);"
	"}";
	const char* fragment_shader =
	"#version 410\n"
	"out vec4 frag_colour;"
	"void main () {"
	"     frag_colour = vec4 (0.5, 0.0, 0.5, 1.0);"
	"}";

	m_shaderModuleTri = new ShaderProgram(vertex_shader, fragment_shader);

	const char* vertex_shader_sq =
	"#version 410\n"
	"layout(location=0) in vec3 vp;"
	"out vec3 position;"
	"uniform mat4 mat;"
	"void main () {"
	"     gl_Position = mat * vec4(vp, 1.0f);"
	"     position = vp;"
	"}";
	const char* fragment_shader_sq =
	"#version 410\n"
	"in vec3 position;"
	"out vec4 frag_colour;"
	"void main () {"
	"     frag_colour = vec4 (position.r, position.g, position.b + 0.5, 1.0);"
	"}";

	m_shaderModuleSq = new ShaderProgram(vertex_shader_sq, fragment_shader_sq);
	const char* vertex_shader_sp =
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
	const char* fragment_shader_sp =
	"#version 410\n"
	"layout(location=0) in vec3 normal;"
	"in vec3 position;"
	"out vec4 frag_colour;"
	"void main () {"
	"     frag_colour = vec4(normal, 1.0f);"
	"}";

	m_shaderModuleSu = new ShaderProgram(vertex_shader_sp, fragment_shader_sp);
}

void Renderer::loadModels()
{
	float points[] = {
		0.0f, 0.0f, 0.0f,
		0.0f, -0.5f, 0.0f,
	   -0.5f, -0.0f, 0.0f
	};
	m_modelTri = new Model(points, 9, 1);
	float pointsSq[] = {
		-0.75f, -0.75f, 0.0f,
		-0.75f, 0.75f, 0.0f,
	    0.75f, 0.75f, 0.0f,
		-0.75f, -0.75f, 0.0f,
	    0.75f, 0.75f, 0.0f,
	    0.75f, -0.75f, 0.0f,
	};
	m_modelSq = new Model(pointsSq, 18, 1);
	m_modelSu = new Model(suziFlat, 17424, 2);
}

void Renderer::run()
{
	while (!glfwWindowShouldClose(m_window)) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//m_shaderModuleTri->setShader();
		//m_modelTri->drawModel();
		//m_shaderModuleSq->setShader();
		//glm::vec3 translation = glm::vec3(0.75, 0.75, 0.0);
		//glm::mat4 translated = glm::translate(glm::mat4(1), 0.5f*translation);
		//glm::mat4 rotated = glm::rotate(translated, m_timer->getTimeSinceStartOfSecond() * 2.0f * 3.14f, glm::vec3(0, 0, 1));
		//glm::mat4 scaled = glm::scale(rotated, glm::vec3(.5f));
		//m_shaderModuleSq->setUniform(scaled, "mat");
		//float f = m_timer->getTimeSinceStartOfSecond();
		//m_modelSq->drawModel();
		m_shaderModuleSu->setShader();
		//glm::mat4 view = glm::lookAt(glm::vec3(3, 0, 0), glm::vec3(2, 0, 0), glm::vec3(3, 1, 0));
		//glm::mat4 proj = glm::perspective(60.f, 800.f / 600.f, 0.1f, 1000.0f);
		glm::mat4 rotated = glm::rotate(glm::mat4(1), m_timer->getTimeSinceStartOfSecond() * 2.0f * 3.14f, glm::vec3(0, 1, 0));
		m_shaderModuleSu->setUniform(glm::mat4(1), "mat");
		m_modelSu->drawModel();
		glfwPollEvents();
		glfwSwapBuffers(m_window);
		m_timer->timeFrame();
	}

	glfwDestroyWindow(m_window);

	glfwTerminate();
	exit(EXIT_SUCCESS);
}
