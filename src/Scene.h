#pragma once
#include "types.h"

class Entity;
class Camera;
/// <summary>
/// holds all game objects within a single loaded space. 
/// A camera is required. (otherwise nothing will render)
/// Fast and synchronized storage of all game objects.
/// </summary>
class Scene
{
public:
	Scene(Vector3 spawnPosition, Vector3 spawnDirection);
	~Scene();
	const Camera& get_camera() const;
	Entity& get_testEntity();
private:
	Entity* m_cameraHolder;
	Camera* m_mainCamera;
};

const inline Camera& Scene::get_camera() const 
{
	return *m_mainCamera;
}
inline Entity& Scene::get_testEntity() 
{
	return *m_cameraHolder;
}

