#include <GameObject.h>

using namespace LowRendere;
using namespace Resources;
using namespace Core;
using namespace Maths;

LowRendere::GameObject::GameObject(Model* model,Shader* shader,Texture* texture)
{
	modelMatrix = Matrix4D::CreateTransformMatrix(transform);
	mesh = new Mesh;
	mesh->material = new Material;
	mesh->gameObject = this;
	mesh->model = model;
	mesh->shader = shader;
	mesh->material->texture = texture;
}

LowRendere::GameObject::~GameObject()
{
	delete mesh->material;
	delete mesh;
}

template<typename t>
void LowRendere::GameObject::AddChild(const t& args)
{
	children.emplace_back(std::make_unique<GameObject>(args));
	children.back->parent = this;
}

Matrix4D LowRendere::GameObject::LocalModelMatrix()
{
	Matrix4D modelMatrix = Matrix4D::CreateTransformMatrix(transform);

	 return modelMatrix;
}

void LowRendere::GameObject::UpdateSelfAndChild()
{
	if (parent)
	{
		modelMatrix = parent->modelMatrix * LocalModelMatrix();
	}
	else
		modelMatrix = LocalModelMatrix();

	for (auto&& child : children)
	{
		child->UpdateSelfAndChild();
	}
}