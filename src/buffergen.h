#pragma once
#include "types.h"
#include <iostream>


void genNumberedBuffers(uint32** stack);

template <class...Targs>
void genNumberedBuffers(Targs...args) 
{
	std::cout << "pack size: " << sizeof...(args) << std::endl;
}