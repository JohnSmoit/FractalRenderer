#pragma once
#include "types.h"
#include <glm/matrix.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glew.h>
#include <glfw3.h>
/// <summary>
/// Basically, a wrapper for a shader.
/// Does some cool stuff like uniform setting n stuff.
/// </summary>
class Material
{
public:
	Material(const char* fshaderData, const char* vShaderData);
	~Material();


	void Apply() const;

	void SetUniform(const char* name, float val) const;
	void SetUniform(const char* name, Vector2 val) const;
	void SetUniform(const char* name, Vector3 val) const;
	void SetUniform(const char* name, Vector4 val) const;
	void SetUniform(const char* name, Mat4 val) const;
	void SetUniform(const char* name, int val) const;
	void SetUniform(const char* name, bool val) const;
private:
	uint32 m_programId;
};

inline void Material::SetUniform(const char* name, float val) const
{
	glUniform1f(glGetUniformLocation(m_programId, name), val);
}
inline void Material::SetUniform(const char* name, Vector2 val) const
{
	glUniform2f(glGetUniformLocation(m_programId, name), val.x, val.y);
}
inline void Material::SetUniform(const char* name, Vector3 val) const
{
	glUniform3f(glGetUniformLocation(m_programId, name), val.x, val.y, val.z);
}
inline void Material::SetUniform(const char* name, Vector4 val) const
{
	glUniform4f(glGetUniformLocation(m_programId, name), val.x, val.y, val.z, val.w);

}
inline void Material::SetUniform(const char* name, int val) const
{
	glUniform1i(glGetUniformLocation(m_programId, name), val);
}
inline void Material::SetUniform(const char* name, bool val) const
{
	glUniform1i(glGetUniformLocation(m_programId, name), val);
}

inline void Material::SetUniform(const char* name, Mat4 val) const 
{
	glUniformMatrix4fv(glGetUniformLocation(m_programId, name), 1, GL_FALSE, glm::value_ptr(val));
}