#include "Camera.h"

Camera::Camera() {
    m_forward = calculateForwardVector();
}

void Camera::HandleMouseInput(const double xpos, const double ypos)
{
    if (m_firstMouse) 
    {
        m_lastX = xpos;
        m_lastY = ypos;
        m_firstMouse = false;
    }

    double xoffset = xpos - m_lastX;
    double yoffset = ypos - m_lastY;

    m_lastX = xpos;
    m_lastY = ypos;

    m_rotation.y += static_cast<float>(xoffset) * m_mouseSensitivity;
    m_rotation.x -= static_cast<float>(yoffset) * m_mouseSensitivity;

    m_rotation.x = glm::clamp(m_rotation.x, glm::radians(-89.99f), glm::radians(89.99f));
    m_forward = calculateForwardVector();
}

void Camera::HandleMouseClick(const uint32_t button, const uint32_t action)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        m_leftClickedThisFrame = true;
    }
    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
    {
        m_rightClickedThisFrame = true;
    }
}

void Camera::HandleScroll(double scrollOffset)
{
    m_movementSpeed += static_cast<float>(scrollOffset) * m_scrollSensitivity;
    m_movementSpeed = glm::clamp(m_movementSpeed, m_minMovementSpeed, m_maxMovementSpeed);
}

const glm::vec3& Camera::GetForwardVector() const
{
    return m_forward;
}

bool Camera::GetLeftClickedThisFrame()
{
    bool res = m_leftClickedThisFrame;
    m_leftClickedThisFrame = false;
    return res;
}

bool Camera::GetRightClickedThisFrame()
{
    bool res = m_rightClickedThisFrame;
    m_rightClickedThisFrame = false;
    return res;
}

void Camera::s_framebufferResizeCallback(GLFWwindow* window, int32_t width, int32_t height)
{
    printf("Resize detected\n");
    Camera* camera = (Camera*)glfwGetWindowUserPointer(window);
}

void Camera::s_mouseCallback(GLFWwindow* window, double xpos, double ypos)
{
    Camera* camera = (Camera*)glfwGetWindowUserPointer(window);
    if (camera)
        camera->HandleMouseInput(xpos, ypos);
}

void Camera::s_mouseButtonCallback(GLFWwindow* window, int32_t button, int32_t action, int32_t mods)
{
    Camera* camera = (Camera*)glfwGetWindowUserPointer(window);
    if (camera)
        camera->HandleMouseClick(button, action);
}
void Camera::s_scrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
    Camera* camera = (Camera*)glfwGetWindowUserPointer(window);
    if (camera)
        camera->HandleScroll(yoffset);
}

void Camera::UseCamera(GLFWwindow* window)
{
	glfwSetWindowUserPointer(window, this);
	glfwSetCursorPosCallback(window, s_mouseCallback);
	glfwSetMouseButtonCallback(window, s_mouseButtonCallback);
	glfwSetScrollCallback(window, s_scrollCallback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	if (glfwRawMouseMotionSupported())
	glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
	glfwSetFramebufferSizeCallback(window, s_framebufferResizeCallback);
    FirstMouse();
}

void Camera::HandleInputs(const float deltaTime, GLFWwindow* window)
{

    glm::vec3 right = glm::normalize(glm::cross(m_forward, glm::vec3(0.0f, 1.0f, 0.0f)));
    glm::vec3 up = glm::normalize(glm::cross(right, m_forward));
    glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        m_position += m_forward * m_movementSpeed * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        m_position -= m_forward * m_movementSpeed * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        m_position -= right * m_movementSpeed * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        m_position += right * m_movementSpeed * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        m_position -= up * m_movementSpeed * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        m_position += up * m_movementSpeed * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        m_position -= worldUp * m_movementSpeed * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        m_position += worldUp * m_movementSpeed * deltaTime;
}

glm::vec3 Camera::calculateForwardVector() const
{
    return glm::normalize(glm::vec3(
        cos(m_rotation.y) * cos(m_rotation.x), 
        sin(m_rotation.x),                    
        sin(m_rotation.y) * cos(m_rotation.x)  
    ));
}

void Camera::FirstMouse()
{
    m_firstMouse = true;
}
