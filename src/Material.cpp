#include "Material.h"
#include "types.h"

#include <iostream>


Material::Material(const char* fShaderSource, const char* vShaderSource) 
{
	m_programId = glCreateProgram();
	uint32 fShaderId = glCreateShader(GL_FRAGMENT_SHADER);
	uint32 vShaderId = glCreateShader(GL_VERTEX_SHADER);

	glShaderSource(fShaderId, 1, &fShaderSource, NULL);
	glShaderSource(vShaderId, 1, &vShaderSource, NULL);

	int success;
	glCompileShader(fShaderId);
	glGetShaderiv(fShaderId, GL_COMPILE_STATUS, &success);

	char shaderLog[512];

	if (!success) 
	{
		glGetShaderInfoLog(fShaderId, 512, NULL, shaderLog);
		std::cout << "ERROR COMPILING FRAGMENT SHADER: \n" << shaderLog << std::endl;
	}

	glCompileShader(vShaderId);
	glGetShaderiv(fShaderId, GL_COMPILE_STATUS, &success);

	if (!success) 
	{
		glGetShaderInfoLog(vShaderId, 512, NULL, shaderLog);
		std::cout << "ERROR COMPILING VERTEX SHADER: \n" << shaderLog << std::endl;
	}

	glAttachShader(m_programId, fShaderId);
	glAttachShader(m_programId, vShaderId);
	glLinkProgram(m_programId);
	glDeleteShader(fShaderId);
	glDeleteShader(vShaderId);

	glGetProgramiv(m_programId, GL_LINK_STATUS, &success);

	if (!success) 
	{
		glGetProgramInfoLog(m_programId, 512, NULL, shaderLog);
		std::cout << "ERROR COMPILING PROGRAM: \n" << shaderLog << std::endl;
	}

}

void Material::Apply() const
{
	glUseProgram(m_programId);
}

Material::~Material() 
{
	glDeleteProgram(m_programId);
}

