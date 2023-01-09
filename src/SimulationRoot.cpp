#include "SimulationRoot.h"
#include "ContentLoader.h"
#include "AssetLibrary.h"
#include "Material.h"
#include "RenderTarget.h"
#include "Timer.h"
#include "Scene.h"
#include <glm/glm.hpp>
#include <iostream>
#include <glew.h>
#include <glfw3.h>
#include "buffergen.h"
#include "Entity.h"
#include "Camera.h"
#include "types.h"

GLFWwindow* gameWindow;
std::unique_ptr<Scene> testScene;

Vector3 obj_position;

std::unique_ptr<SimulationRoot> SimulationRoot::m_instance = nullptr;

uint32 vbo;
uint32 ebo;
uint32 vao;
uint32 programId;
uint32 vShaderId;
uint32 fShaderId;
Timer uniformTimer;

void change_framebuffer_size(GLFWwindow* window, int w, int h) 
{
	glViewport(0, 0, w, h);
}
bool SimulationRoot::Initialize() 
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	gameWindow = glfwCreateWindow(800, 640, "Super Window Bros 2.0", NULL, NULL);
	if (gameWindow == nullptr)
	{
		std::cout << "Failed to create glfw Window" << std::endl;
		glfwTerminate();
		return false;
	}
	glfwMakeContextCurrent(gameWindow);

	bool glewDead = glewInit();
	if (glewDead) 
	{
		std::cout << "Glew is dead, and you killed it!" << std::endl;
		glfwTerminate();
		return false;
	}

	glViewport(0, 0, 800, 640);

	glfwSetFramebufferSizeCallback(gameWindow, change_framebuffer_size);

	m_instance = std::unique_ptr<SimulationRoot>(new SimulationRoot());

	float verts[] =
	{
		-1.f, -1.f, 0.f,
		1.f, -1.f, 0.f,
		1.f, 1.f, 0.f,
		-1.f, 1.f, 0.f
	};

	float uvs[] =
	{
		0.f, 0.f,
		1.f, 0.f,
		1.f, 1.f,
		0.f, 1.f
	};
	uint32 indices[]
	{
		0, 1, 2,
		0, 3, 2
	};

	const char* vertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"void main()\n"
		"{\n"
		" gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"}\0";
	
	const char* fragmentShaderSource = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		"FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
		"}\0";


	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);

	glGenVertexArrays(1, &vao);

	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo); //vertex buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(verts) + sizeof(uvs), 0, GL_STATIC_DRAW);
	//putting each set of a single attribute as a block one after another.
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(verts), &verts); //set vertex position data 
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(verts), sizeof(uvs), &uvs); //set vertex uv data
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0); //attrib pointer 1
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)(sizeof(verts))); //attrib pointer 2
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	fShaderId = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fShaderId, 1, &fragmentShaderSource, NULL);
	glCompileShader(fShaderId);

	vShaderId = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vShaderId, 1, &vertexShaderSource, NULL);
	glCompileShader(vShaderId);

	programId = glCreateProgram();
	glAttachShader(programId, fShaderId);
	glAttachShader(programId, vShaderId);
	glLinkProgram(programId);

	ContentLoader::load_all_shaders();

	testScene = std::unique_ptr<Scene>(new Scene(Vector3(0.f, 0.f, 3.5f), Vector3(0, 0, 0)));

	uniformTimer.Start();
	obj_position = Vector3(0.1f, 0.4, 0);

	const char* err;
	while (glfwGetError(&err) != GLFW_NO_ERROR) 
	{
		std::cout << err << std::endl;
	}

	genNumberedBuffers(1, 2, 3, 4, 5, 6, 7, 8);
	return true;
}

void SimulationRoot::Step() 
{
	Entity& testEntity = testScene->get_testEntity();

	testEntity.Update(gameWindow);
}

void SimulationRoot::Cleanup() 
{
	glfwTerminate();

	glDeleteProgram(programId);
	glDeleteShader(vShaderId);
	glDeleteShader(fShaderId);

	glDeleteBuffers(1, &vbo);
	glDeleteVertexArrays(1, &vao);

	uniformTimer.Stop();
}

void SimulationRoot::Draw() 
{
	const Material& mat = AssetLibrary<Material>::GetNamed("BasicShader");
	mat.Apply();
	float secs = uniformTimer.GetElapsedTime().get_seconds();
	const Camera& cam = testScene->get_camera();
	Mat4 model = cam.followerModel();
	Mat4 view = Mat4(1.f);
	Mat4 projection = Mat4(1.f);
	mat.SetUniform("uTime", secs);
	mat.SetUniform("uTransform", model);
	mat.SetUniform("uView", view);
	mat.SetUniform("uProjection", projection);
	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void SimulationRoot::RunGame(int* ext) 
{
	bool init = SimulationRoot::Initialize();
	if (init) {
		while (!glfwWindowShouldClose(gameWindow)) 
		{
			try {
				glClearColor(0.5f, 0.9f, 0.2f, 1.f);
				glClear(GL_COLOR_BUFFER_BIT);
				m_instance->Step();
				m_instance->Draw();
				glfwSwapBuffers(gameWindow);
				glfwPollEvents();
			}
			catch (std::exception ex) 
			{
				std::cout << "Exception In Main Loop!\n Message: \n" << ex.what() << std::endl;
			}
		}
	}
	else 
	{
		ext = 0;
		m_instance->Cleanup();
	}

	ext = 0;
}