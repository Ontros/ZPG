#include "Scene.h"

const std::vector<DrawableObject>& Scene::GetDrawableObjects() const
{
	return m_objects;
}

const bool Scene::UseCamera() const
{
	return m_useCamera;
}
