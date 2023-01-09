#pragma once
#include "types.h"
#include "Drawable.h"
#include "ComponentHolder.h"

#include <vector>


struct FlagSet;

enum PrimitiveType 
{
	primitive_plane_x,
	primitive_plane_y,
	primitive_plane_z
	//TODO: Sphere, Cube, and Capsule.
};

template <uint32 c, typename Ty> 
struct VAttribDef
{

};

template <typename... Attributes>
struct VertexTypeDef
{

};

/// <summary>
/// Mesh, basically a wrapper for a vertex array with triangles n stuff.
/// </summary>
class Mesh
{
public:
	Mesh();
	~Mesh();
	Mesh(int primitiveType = 0, const Vector3* scale = nullptr); //tbd

	/// <summary>
	/// This will eat your vertices
	/// </summary>
	/// <param name="verts"></param>
	void set_vertices(std::vector<IVertexType>&& verts); //for these, use move semantics instead of copy.
	/// <summary>
	/// this will eat your indices
	/// </summary>
	/// <param name="indices"></param>
	void set_triangles(std::vector<int>&& indices);

	void ResolveMesh();

	/// <summary>
	/// NOT IMPLEMENTED
	/// </summary>
	void autogen_normals(); //automatically generates normals from vertex and index data. 

	/// <summary>
	/// NOT IMPLEMENTED
	/// </summary>
	void autogen_uvs(); //automatically generates uv coordinates from vertex and index data.
private:

	uint32 m_vbo;
	uint32 m_ebo;
	uint32 m_vao;

	Vector3* m_vertices;
	Vector3* m_normals;
	Vector2* m_uvs;

	int* m_indices;
};
class DrawableComponent;


/// <summary>
/// 3d drawable object
/// </summary>
class Renderable3D : public Drawable, ComponentHolder<DrawableComponent>
{
public:
	void Draw();
	static Renderable3D* CreateRenderable(FlagSet flags);
private:
	Renderable3D();
};

