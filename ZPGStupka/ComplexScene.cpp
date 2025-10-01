#include "ComplexScene.h"

#include "models/suzi_flat.h"

ComplexScene::~ComplexScene()
{
	if (m_suziModel) delete m_suziModel;
	if (m_normalShaderProgram) delete m_normalShaderProgram;
}

void ComplexScene::load() {
	m_useCamera = true;
	m_suziModel = new Model(suziFlat, 17424, 2);
	m_normalShaderProgram = new ShaderProgram("Shaders/normal.vert.glsl", "Shaders/normal.frag.glsl");
	m_objects.push_back(DrawableObject(m_suziModel, m_normalShaderProgram));
}
