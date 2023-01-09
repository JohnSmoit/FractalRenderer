#include "Camera.h"
#include "Entity.h"
#include <iostream>

Camera::Camera(float rot, float frust, float near, float far) 
{
	m_follower = nullptr;
	m_angle = rot;
	m_pcomp = frust;
	m_near = near;
	m_far = far;

	m_view = glm::translate(Mat4(1.f), ZERO3D);
	m_transform = new Transform(ZERO3D, 0.f, UP, ONE3D);
}

Camera::~Camera() 
{
	delete m_transform;
}

void Camera::SetFollowEntity(Entity* followed) 
{
	m_follower = followed;

#ifdef FOD_DEBUGLOG
	if (m_follower == nullptr)
	{
		std::cout << "First Time ";
	}
	std::cout << " Binding camera to a new entity! \n";
#endif
}

Mat4 Camera::followerModel() const 
{
	return m_follower != nullptr ? m_follower->m_transform.model() : Mat4(0.f);
}

/// <summary>
/// Just throws an exception if follower is nullptr because I am lazy.
/// </summary>
/// <returns></returns>
Transform& Camera::followerTransform() const 
{
	return m_follower != nullptr ? m_follower->m_transform : *m_transform;
}

Mat4 Camera::view() const
{
	return m_follower != nullptr ? m_follower->m_transform.invModel() : m_view;
}
Mat4 Camera::projection() const
{
	return glm::perspective(glm::radians(m_angle), m_pcomp, m_near, m_far);
}



