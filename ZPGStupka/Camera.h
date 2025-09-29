#pragma once
#include "Libraries.h"

class Camera
{
public:
	Camera();
	void HandleMouseInput(double xpos, double ypos);
	void HandleMouseClick(uint32_t button, uint32_t action);
	void HandleScroll(double scrollOffset);

	const glm::vec3& GetPosition() const { return m_position; }
	const glm::vec2& GetRotation() const { return m_rotation; }
	const glm::vec3& GetForwardVector() const;
	bool GetLeftClickedThisFrame();
	bool GetRightClickedThisFrame();
	void PrepareWindow(GLFWwindow* window);
	void HandleInputs(float deltaTime, GLFWwindow* window);

private:
	glm::vec3 m_position = glm::vec3(-2.0f, 0.0f, 0.0f);
	glm::vec2 m_rotation = glm::vec2(0.0f, 0.0f); 
	glm::vec3 m_forward;
	float m_movementSpeed = 50.0f;
	float m_minMovementSpeed = 0.1f;
	float m_maxMovementSpeed = 150.0f;
	float m_scrollSensitivity = 1.0f;
	float m_mouseSensitivity = 0.002f;

	bool m_firstMouse = true;
	double m_lastX = 0.0, m_lastY = 0.0;

	bool m_leftClickedThisFrame = false;
	bool m_rightClickedThisFrame = false;

	glm::vec3 calculateForwardVector() const;

	void FirstMouse();

	static void s_framebufferResizeCallback(GLFWwindow* window, int32_t width, int32_t height);
	static void s_mouseCallback(GLFWwindow* window, double xpos, double ypos);
	static void s_mouseButtonCallback(GLFWwindow* window, int32_t button, int32_t action, int32_t mods);
	static void s_scrollCallback(GLFWwindow* window, double xoffset, double yoffset);
};