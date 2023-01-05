#include <glew.h>
#include <glfw3.h>
#include "RenderTarget.h"
#include <iostream>

RenderTarget::RenderTarget(uint32 w, uint32 h, bool useDepthTest) 
{
	m_height = h;
	m_width = w;

	glGenFramebuffers(1, &m_fb);
	glBindFramebuffer(GL_FRAMEBUFFER, m_fb);

	//m_colorTex = create_blank(m_width, m_height);
	m_useDepthTest = useDepthTest;

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_colorTex.id(), 0);

	if (useDepthTest) 
	{
		//m_depthTex = create_blank_depthstencil(m_width, m_height);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, m_depthTex.id(), 0);
	}

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) 
	{
		std::cout << "Framebuffer Initialization not complete!\n";
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void RenderTarget::Clear() 
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_fb);
	uint32 flags = GL_COLOR_BUFFER_BIT | (m_useDepthTest ? GL_DEPTH_BUFFER_BIT : 0);
	glClearColor(0, 0, 0, 0);
	glClear(flags);
}

void RenderTarget::Blit(const RenderTarget* renderTo, const uint32 mask = GL_COLOR_BUFFER_BIT) 
{
	glBindFramebuffer(GL_READ_FRAMEBUFFER, m_fb);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, renderTo->id());

	Vector2i dims1(m_width, m_height);
	Vector2i dims2(renderTo->width(), renderTo->height());
	glBlitFramebuffer(0, 0, dims1.x, dims1.y, 0, 0, dims2.x, dims2.y, mask, GL_LINEAR);

	glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
}

void RenderTarget::UseAsTarget() const 
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_fb);
	if (m_useDepthTest) 
	{
		glEnable(GL_DEPTH_TEST);
	}
}