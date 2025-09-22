#include "Renderer.h"

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
}

void Renderer::loadShaders()
{
	const char* vertex_shader =
	"#version 330\n"
	"layout(location=0) in vec3 vp;"
	"void main () {"
	"     gl_Position = vec4 (vp.x, vp.y, vp.z, 1.0);"
	"}";
	const char* fragment_shader =
	"#version 330\n"
	"out vec4 frag_colour;"
	"void main () {"
	"     frag_colour = vec4 (0.5, 0.0, 0.5, 1.0);"
	"}";

	m_shaderModuleTri = new ShaderModule(vertex_shader, fragment_shader);

	const char* vertex_shader_sq =
	"#version 330\n"
	"layout(location=0) in vec3 vp;"
	"out vec3 position;"
	"uniform float movX;"
	"void main () {"
	"     gl_Position = vec4 (vp.x + movX, vp.y - movX, vp.z, 1.0);"
	"     position = vp;"
	"}";
	const char* fragment_shader_sq =
	"#version 330\n"
	"in vec3 position;"
	"out vec4 frag_colour;"
	"void main () {"
	"     frag_colour = vec4 (position.r, position.g, position.b + 0.5, 1.0);"
	"}";

	m_shaderModuleSq = new ShaderModule(vertex_shader_sq, fragment_shader_sq);
}

void Renderer::loadModels()
{
	float points[] = {
		0.0f, 0.0f, 0.0f,
		0.0f, -0.5f, 0.0f,
	   -0.5f, -0.0f, 0.0f
	};
	m_modelTri = new Model(points, 9);
	float pointsSq[] = {
		0.0f, 0.0f, 0.0f,
		0.0f, 0.75f, 0.0f,
	    0.75f, 0.75f, 0.0f,
		0.0f, 0.0f, 0.0f,
	    0.75f, 0.75f, 0.0f,
	    0.75f, 0.0f, 0.0f,
	};
	m_modelSq = new Model(pointsSq, 18);
}

void Renderer::run()
{
	while (!glfwWindowShouldClose(m_window)) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		m_shaderModuleTri->setShader();
		m_modelTri->drawModel();
		m_shaderModuleSq->setShader();
		m_shaderModuleSq->setUniform(m_timer->getTimeSinceStartOfSecond());
		float f = m_timer->getTimeSinceStartOfSecond();
		m_modelSq->drawModel();
		glDrawArrays(GL_TRIANGLES, 0, 6); 
		glfwPollEvents();
		glfwSwapBuffers(m_window);
		m_timer->timeFrame();
	}

	glfwDestroyWindow(m_window);

	glfwTerminate();
	exit(EXIT_SUCCESS);
}
