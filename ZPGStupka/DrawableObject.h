#pragma once

#include "Libraries.h"
#include "Model.h"
#include "ShaderProgram.h"

class DrawableObject {
public:
	DrawableObject(Model* model, ShaderProgram* shaderProgram);
	void draw();
	void draw(glm::mat4 translation, const char* matrixUniformName);
private:
	Model* m_model;
	ShaderProgram* m_shaderProgram;
};
