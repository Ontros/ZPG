#include "ShaderProgram.h"

ShaderProgram::ShaderProgram(const char* vertexShaderCode, const char* fragmentShaderCode)
{
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderCode, NULL);
	glCompileShader(vertexShader);
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderCode, NULL);
	glCompileShader(fragmentShader);
	m_id = glCreateProgram();
	glAttachShader(m_id, fragmentShader);
	glAttachShader(m_id, vertexShader);
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
	}
}

void ShaderProgram::setShader()
{
	glUseProgram(m_id);
}

void ShaderProgram::setUniform(float a, const char* uniformName)
{
	glUniform1f(glGetUniformLocation(m_id, uniformName), a);
}

void ShaderProgram::setUniform(glm::mat4 mat, const char* uniformName)
{
	GLint id = glGetUniformLocation(m_id, uniformName);
	glUniformMatrix4fv(id, 1, GL_FALSE, &mat[0][0]);
}
