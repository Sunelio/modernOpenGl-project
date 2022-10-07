#pragma once
#include "Resources.h"

namespace LowRendere
{
	class GameObject;
}



namespace LowRendere
{


	class Mesh
	{
	public:
		Mesh();
		~Mesh();
		Resources::Shader* shader;
		Resources::Model* model;
		Material* material;
		GameObject *gameObject;
		void Draw();

	private:

	};


}