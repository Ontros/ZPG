#include "TriangleScene.h"

TriangleScene::~TriangleScene()
{
	if (m_triangleModel) delete m_triangleModel;
	if (m_shaderProgram2D) delete m_shaderProgram2D;
}

void TriangleScene::load()
{
	m_useCamera = false;
	float trianglePoints[] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f, 0.5f, 0.0f,
	};
	m_triangleModel = new Model(trianglePoints, 9, 1);
	m_shaderProgram2D = new ShaderProgram("Shaders/2d.vert.glsl", "Shaders/2d.frag.glsl");
	m_objects.push_back(DrawableObject(m_triangleModel, m_shaderProgram2D));
}
