#include "Mesh.h"
#include "libgl.h"

Mesh::Mesh() 
{
	// generate vertex buffer, element buffer, and array objects.
	glGenBuffers(1, &m_vbo);
	glGenBuffers(1, &m_ebo);
	glGenVertexArrays(1, &m_vao);

	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	//since this constructor creates no starting vertices
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0); 
}