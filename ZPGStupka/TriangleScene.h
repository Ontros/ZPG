#pragma once

#include "Scene.h"

class TriangleScene: public Scene {
public:
	TriangleScene() : Scene() {};
	~TriangleScene();
	void load();
private:
	Model* m_triangleModel = nullptr;
	ShaderProgram* m_shaderProgram2D = nullptr;
};
