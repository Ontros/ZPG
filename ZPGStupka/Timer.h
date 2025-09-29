#pragma once

#include "Libraries.h"

class Timer {
public:
	Timer() {
		m_timeOfLastFrame = (float)glfwGetTime();
		m_timeOfLastSecond = m_timeOfLastFrame;
	}
	void timeFrame() {
		m_currentTime = (float)glfwGetTime();
		m_deltaTime = m_currentTime - m_timeOfLastFrame;
		m_timeSinceStart += m_deltaTime;
		m_timeOfLastFrame = m_currentTime;
		m_framesThisSecond++;
		if (m_currentTime > m_timeOfLastSecond + 1.0f) {
			printf("FPS: %d\n", m_framesThisSecond);
			m_framesThisSecond = 0;
			m_timeOfLastSecond = m_currentTime;
		}
	}
	float getDeltaTime() const {
		return m_deltaTime;
	}
	float getTimeSinceStartOfSecond() const {
		return m_currentTime - m_timeOfLastSecond;
	}
	float getTimeSinceStart() const {
		return m_timeSinceStart;
	}
private:
	float m_currentTime = (float)glfwGetTime();
	float m_timeOfLastFrame = 0;
	float m_deltaTime = 0;
	int m_framesThisSecond = 0;
	float m_timeOfLastSecond = 0;
	float m_timeSinceStart = 0;
};
