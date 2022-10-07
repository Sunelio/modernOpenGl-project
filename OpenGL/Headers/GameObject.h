#pragma once
#include <Mesh.h>

namespace LowRendere
{
	class GameObject
	{
	public:
		
	//-------Construct-----\\

		GameObject(Resources::Model* model,Resources::Shader* shaderl, Resources::Texture* texture);

	//-------Destruct-----\\

		~GameObject();

		//value
		static inline Matrix4D modelMatrix;


		// transform object.
		Transform transform;

		Mesh* mesh;
		
		//define parent and children .
		std::list<std::unique_ptr<GameObject>> children;
		GameObject* parent = nullptr;

		// Fonction
		Matrix4D LocalModelMatrix();

		void UpdateSelfAndChild();

		template<typename t>
		void AddChild(const t& args);

	private:

	};
}