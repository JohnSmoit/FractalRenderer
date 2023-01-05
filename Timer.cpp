#include "Timer.h"
#include <glew.h>
#include <glfw3.h>
void Timer::Start() 
{
	m_current = glfwGetTime();
	m_elapsed = m_current - m_start;
	m_stopped = false;
}
void Timer::Stop() 
{
	m_stopped = true;
	m_current = glfwGetTime();
	m_elapsed = m_current - m_start;
}
void Timer::Reset() 
{
	m_start = 0;
	m_current = 0;
	m_elapsed = 0;
}

TimeSpan Timer::GetElapsedTime()
{
	if (!m_stopped)
		m_current = glfwGetTime();
	m_elapsed = m_current - m_start;

	return TimeSpan(m_elapsed);
}