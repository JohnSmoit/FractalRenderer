#pragma once
#include "SimulationRoot.h"

class RenderingPipeline;
class SimulationRoot;

static class Finder 
{
public:
	const static RenderingPipeline* get_pipeline();
	const static SimulationRoot* get_instance();
};

const inline RenderingPipeline* Finder::get_pipeline()
{
	return SimulationRoot::m_instance->basePipeline.get();
}
const inline SimulationRoot* Finder::get_instance() 
{
	return SimulationRoot::m_instance.get();
}
