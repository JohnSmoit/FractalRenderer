#pragma once
#include "flagset.h"
#include "types.h"
#include "Owner.h"
#include <vector>
// this class should contain only the control flow of the rendering and should not directly access
// rendering data for drawable objects save for the screen buffer target.
// Also handles buffer swap operations and layer ordering.


/// <summary>
/// this class controls the flow of rendering and handles draw layers and serves as a starting point
/// for any post-processing operations and buffer swapping.
/// Things to look into:
/// - Framebuffers I don't know how to use these and that is not too good.
/// </summary>
class Drawable;
class RenderTarget;
class RenderingProfile; //Contains all clientside render data for all renderable objects.
class RenderDevice; //acts as an interface for drawing meshes and really anything so that you don't have to mess with openGL functions too much.
class RenderStep;
struct FlagSet;

typedef struct 
{
	Drawable* d;
	FlagSet flags;
} DrawableData;

/// <summary>
/// Needs a main rendertarget.
/// </summary>
class RenderingPipeline : IOwner<RenderStep>
{
public:
	RenderingPipeline() = delete;
	RenderingPipeline(RenderDevice&& device, RenderTarget* mainTarget = nullptr);



	void DrawScene(const RenderingProfile& context);

	/// <summary>
	/// Add a precreated render step to the pipeline. Ownership of the step will be taken.
	/// </summary>
	/// <param name="step"></param>
	void AddStep(RenderStep* step);

	/// <summary>
	/// Creates a new render step and takes ownership as well as adds it to the pipeline.
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <typeparam name="...Args"></typeparam>
	/// <param name="...args"></param>
	/// <returns>A pointer that can be used for further configuration</returns>
	template <typename T, typename... Args> 
	T* AddStep(Args... args)
	{
		T* step = createOwned<T>(args);
		return step;
	};

	RenderStep* own(std::unique_ptr<RenderStep>&& object) override;

	void freeAll() override;

	const RenderTarget& get_mainTarget();
private:
	RenderTarget* m_mainTarget;
	RenderTarget* m_currentTarget;

	std::unique_ptr<RenderDevice> m_device;

	std::vector<std::unique_ptr<RenderStep>> m_managed;
	std::vector<RenderStep*> m_pipelineSteps;
};

const inline RenderTarget& RenderingPipeline::get_mainTarget() 
{
	return *m_mainTarget;
}

struct RenderDeviceDef 
{

};

class Mesh;
class Texture2D;
class Material;

class RenderDevice 
{
public:
	RenderDevice(const RenderDeviceDef& d);
	~RenderDevice();

	void DrawMesh(const Mesh& mesh, Vector3 position, Quaternion rotation, Vector3 scale);
	void BlitScreen(const Texture2D& tex, Vector2 screenPos, float rotation, Vector3 scale, Rectangle src, Vector4 color, float layer);
	void ApplyScreenwide(const Material& screenEffect);
	
	void setBlendMode(uint32 blend);
	// void DrawPrimitives() for lower level drawing needs.

	void setTextureSlot(int slot, Texture2D* tex);
	void setRenderTarget(RenderTarget* target);

	void Clear(Vector4 clearColor);
private:
	RenderTarget* m_target;

};

class RenderStep 
{
public:
	virtual void Render(const RenderingProfile& context) = 0;

	virtual ~RenderStep() = default;
};

class RenderingProfile 
{
public:
	RenderingProfile();

	std::vector<Drawable>& allDrawables();

	RenderDevice* device();
};