#pragma once

#include "Scene.h"

class ComplexScene: public Scene {
public:
	ComplexScene() : Scene() {};
	~ComplexScene();
	void load();
private:
	Model* m_suziModel = nullptr;
	ShaderProgram* m_normalShaderProgram = nullptr;
};
