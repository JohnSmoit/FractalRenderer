#pragma once
#include <string>
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <glm/vec4.hpp>
#include "settings.h"

typedef unsigned int uint32;
typedef signed int int32;
typedef unsigned long uint64;
typedef signed long int64;
typedef glm::mat4 Mat4;



typedef const char* cstring;

typedef glm::vec2 Vector2;

typedef glm::vec3 Vector3;

typedef glm::vec4 Vector4;

typedef glm::vec<2, int32, glm::packed_highp> Vector2i;

template <typename Ty>
std::string type_name_string()
{
	std::string out = typeid(Ty).name();
	size_t ind = out.find("struct ");
	size_t indc = out.find("class ");

	if (ind != std::string::npos)
	{
		out.erase(ind, strlen("struct "));
	}
	else if (indc != std::string::npos)
	{
		out.erase(indc, strlen("class "));
	}

	return out;
}
#define ZERO2D Vector3(0, 0)
#define ONE2D Vector3(1, 1)

#define ZERO3D Vector3(0, 0, 0)
#define ONE3D Vector3(1, 1, 1)

#define UP Vector3(0, 1, 0)

#define ZERO4D Vector4(0, 0, 0, 0)
#define ONE4D Vector3(1, 1, 1, 1)

/// <summary>
/// At the moment, this isn't really a quaternion. Hurrah.
/// </summary>
struct Quaternion
{
public:
	const float& angle() const
	{
		return m_angle;
	}
	const Vector3& axis() const
	{
		return m_axis;
	}
	Quaternion(float angle, Vector3 axis)
	{
		m_angle = angle;
		m_axis = glm::normalize(axis);
	}
	void change_by(float by) 
	{
		m_angle += by;
	}
private:
	float m_angle;
	Vector3 m_axis;
};

struct Rectangle 
{
};
