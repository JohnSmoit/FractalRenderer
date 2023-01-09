#include "Entity.h"
#include <glm/ext/matrix_transform.hpp>
#include <glfw3.h>

Mat4 Transform::model() const 
{
	Mat4 model(1.f);

	model = glm::scale(model, scale);
	model = glm::rotate(model, rot.angle(), rot.axis());
	model = glm::translate(model, pos);

	return model;
}

Mat4 Transform::invModel() const 
{
	Mat4 invModel(1.f);

	//glm::scale(invModel, scale);
	invModel = glm::rotate(invModel, -rot.angle(), -rot.axis());
	invModel = glm::translate(invModel, -pos);

	return invModel;
}

Entity::Entity(Vector3 sp, Quaternion srot) 
{
	m_transform = Transform(sp, srot, ONE3D);

}

void Entity::Update(GLFWwindow* window) 
{
	//basic player control goes here.

	const float camSpeed = 0.05f;
	Vector3 camFront(0.f, 0.f, -1.f);
	Vector3 camRight(1.f, 0.f, 0.f);
	Vector3 camUp(0.f, 1.f, 0.f);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) m_transform.pos += camFront * camSpeed;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) m_transform.pos -= camRight * camSpeed;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) m_transform.pos -= camFront * camSpeed;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) m_transform.pos += camRight * camSpeed;
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) m_transform.pos += camUp * camSpeed;
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) m_transform.pos -= camUp * camSpeed;
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) m_transform.rot.change_by(camSpeed * 0.1f);
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) m_transform.rot.change_by(-camSpeed * 0.1f);

}