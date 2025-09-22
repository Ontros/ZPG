#include "Model.h"

Model::Model(float* points, int size)
{

	//vertex buffer object (VBO)
	glGenBuffers(1, &m_VBO); // generate the VBO
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * size, points, GL_STATIC_DRAW);

	//Vertex Array Object (VAO)
	glGenVertexArrays(1, &m_VAO); //generate the VAO
	glBindVertexArray(m_VAO); //bind the VAO
	glEnableVertexAttribArray(0); //enable vertex attributes
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	m_triangles = size / 3;
}

void Model::drawModel()
{
	glBindVertexArray(m_VAO);
	glDrawArrays(GL_TRIANGLES, 0, m_triangles); 
}
