#include "Scene.h"
#include "Entity.h"
#include "Camera.h"

Scene::Scene(Vector3 spawnPosition, Vector3 spawnDirection) 
{
	m_cameraHolder = new Entity(spawnPosition, Quaternion(0.f, UP));
	m_mainCamera = new Camera(45.f, 800.f / 640.f, 0.01f, 10000.f);
	m_mainCamera->SetFollowEntity(m_cameraHolder);
}

Scene::~Scene() 
{
	delete m_mainCamera;
	delete m_cameraHolder;
}