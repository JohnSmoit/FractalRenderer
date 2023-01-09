#pragma once
#include "types.h"


class Texture2D 
{
public:
	Texture2D() {}
	Texture2D(const char* fileName);
	uint32 id();
};
/// <summary>
/// TODO: implement texture
/// </summary>
/// <returns></returns>
inline uint32 Texture2D::id() 
{
	return 0; 
}
