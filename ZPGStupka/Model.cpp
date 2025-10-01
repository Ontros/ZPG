#include "Model.h"

Model::Model(const float* points, int size, int vec3s)
{
	//vertex buffer object (VBO)
	glGenBuffers(1, &m_VBO);	
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * size, points, GL_STATIC_DRAW);

	//Vertex Array Object (VAO)
	glGenVertexArrays(1, &m_VAO); 
	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	int stride = 3 * sizeof(float) * vec3s;
	for (int i = 0; i < vec3s; i++) {
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, 3, GL_FLOAT, GL_FALSE, stride, (GLvoid*)(3*sizeof(float)*i));
	}

	m_triangles = size / (vec3s*3);
}

Model::~Model()
{
	if (m_VBO) glDeleteBuffers(1, &m_VBO);
	if (m_VAO) glDeleteVertexArrays(1, &m_VAO);
}

void Model::drawModel() const
{
	glBindVertexArray(m_VAO);
	glDrawArrays(GL_TRIANGLES, 0, m_triangles); 
	glBindVertexArray(0);
}
