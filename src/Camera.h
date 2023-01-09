#pragma once
#include <memory>
#include "types.h"
#include <glm/gtx/transform.hpp>

class Entity;
struct Transform;


class Camera
{
public:
	Camera(float, float, float, float);
	~Camera();

	void SetFollowEntity(Entity* followed);

	Mat4 view() const;
	Mat4 projection() const;
	Mat4 followerModel() const;

	Transform& followerTransform() const;
private:
	Entity* m_follower;
	Mat4 m_view;
	Transform* m_transform;
	float m_angle;
	float m_pcomp;
	float m_near;
	float m_far;
};




