#pragma once
#include <memory>

class RenderingPipeline;

class SimulationRoot
{
public:
	friend class Finder;
	static void RunGame(int* ext); //root call & game loop
private:
	SimulationRoot() {}
	static std::unique_ptr<SimulationRoot> m_instance;
	static bool Initialize();
	void Step(); //deetee mabois
	void Draw();
	void Cleanup();

	//std::unique_ptr<RenderingPipeline> basePipeline;
};

