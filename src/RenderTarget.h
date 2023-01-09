#pragma once
#include "types.h"
#include "texture.h"


class RenderTarget 
{
public:
	uint32 width() const;
	uint32 height() const;

	void UseAsTarget() const;
	void Blit(const RenderTarget* renderTo, const uint32 mask); //this blits the entirety of a single render target over another
	void Clear();
	RenderTarget(uint32 w, uint32 h, bool useDepthTest = false);

	const uint32 id() const;

	const Texture2D& get_frameBuffer(); //these two entrust ownership to the caller.
	const Texture2D& get_depthBuffer();
private:
	uint32 m_width, m_height;
	uint32 m_fb;

	bool m_useDepthTest;

	Texture2D m_colorTex;
	Texture2D m_depthTex;
};

const inline uint32 RenderTarget::id() const 
{
	return m_fb;
}
const inline Texture2D& RenderTarget::get_frameBuffer() 
{
	return m_colorTex;
}

const inline Texture2D& RenderTarget::get_depthBuffer() 
{
	return m_depthTex;
}

inline uint32 RenderTarget::width() const 
{
	return m_width;
}
inline uint32 RenderTarget::height() const
{
	return m_height;
}