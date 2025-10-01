#include "DrawableObject.h"

DrawableObject::DrawableObject(Model* model, ShaderProgram* shaderProgram)
{
	m_model = model;
	m_shaderProgram = shaderProgram;
}

void DrawableObject::draw()
{
	m_shaderProgram->setShader();
	m_model->drawModel();
}

void DrawableObject::draw(glm::mat4 translation, const char* matrixUniformName)
{
	m_shaderProgram->setShader();
	m_shaderProgram->setUniform(translation, matrixUniformName);
	m_model->drawModel();
}
