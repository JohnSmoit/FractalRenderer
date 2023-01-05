#pragma once
#include "ComponentHolder.h"
#include "types.h"

struct GLFWwindow;
struct Transform 
{
	Vector3 pos;
	Quaternion rot;
	Vector3 scale;

	Mat4 model() const;

	Mat4 invModel() const;

	Transform(Vector3 pos, float angle, Vector3 axis, Vector3 scale) : 
		pos(pos), 
		rot(angle, axis), 
		scale(scale) 
	{}

	Transform(Vector3 pos, Quaternion rot, Vector3 scale) : 
		pos(pos),
		rot(rot),
		scale(scale)
	{}

	Transform() : pos(ZERO3D), rot(0.f, UP), scale(ONE3D) {}
};

class Entity
{
public:
	friend class Camera;

	Entity(Vector3 spos, Quaternion srot);
	~Entity() {}

	void Update(GLFWwindow* window);

	const Transform& transform() const;
private:

	Transform m_transform;
};

const inline Transform& Entity::transform() const 
{
	return m_transform;
}

