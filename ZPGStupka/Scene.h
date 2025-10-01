#pragma once
#include "Libraries.h"
#include "DrawableObject.h"
#include "Camera.h"

class Scene {
public:
	Scene() = default;
	virtual ~Scene() = default;
	virtual void load() = 0;
	const std::vector<DrawableObject>& GetDrawableObjects() const;
	const bool UseCamera() const;
protected:
	std::vector<DrawableObject> m_objects;
	bool m_useCamera = true;
};
