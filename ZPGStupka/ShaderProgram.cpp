#include "App.h"
#include "ShaderProgram.h"

ShaderProgram::ShaderProgram(const char* vertexShaderPath, const char* fragmentShaderPath) : m_vertShader (vertexShaderPath, GL_VERTEX_SHADER), m_fragShader(fragmentShaderPath, GL_FRAGMENT_SHADER)
{
	m_id = glCreateProgram();
	glAttachShader(m_id, m_vertShader.GetShader());
	glAttachShader(m_id, m_fragShader.GetShader());
	glLinkProgram(m_id);

	GLint status;
	glGetProgramiv(m_id, GL_LINK_STATUS, &status);
	if (status == GL_FALSE)
	{
		GLint infoLogLength;
		glGetProgramiv(m_id, GL_INFO_LOG_LENGTH, &infoLogLength);
		GLchar* strInfoLog = new GLchar[infoLogLength + 1];
		glGetProgramInfoLog(m_id, infoLogLength, NULL, strInfoLog);
		fprintf(stderr, "Linker failure: %s\n", strInfoLog);
		delete[] strInfoLog;
		App::s_throwRuntimeError("Shader failed to compile");
	}
}

ShaderProgram::~ShaderProgram()
{
	if (m_id) glDeleteProgram(m_id);
}

void ShaderProgram::setShader() const
{
	glUseProgram(m_id);
}

void ShaderProgram::setUniform(float a, const char* uniformName)
{
	glUniform1f(findUniformLocation(uniformName), a);
}

void ShaderProgram::setUniform(glm::mat4 mat, const char* uniformName)
{
	glUniformMatrix4fv(findUniformLocation(uniformName), 1, GL_FALSE, &mat[0][0]);
}

GLint ShaderProgram::findUniformLocation(const char* uniformName) const
{
	GLint id = glGetUniformLocation(m_id, uniformName);
	if (id == -1) {
		printf("Uniform: %s\n", uniformName);
		App::s_throwRuntimeError("Failed to find uniform");
	}
	return id;
}
