#pragma once
#include <Light.h>
#include<vector>


namespace Resources
{
	struct Vertex
	{
		Core::Maths::Vector3D position;
		Core::Maths::Vector3D normal;
		Core::Maths::Vector2D UV;
	};
	class Model : public IResource
	{
	public:
		unsigned int VBO, VAO, EBO;
		std::vector<Vertex> vertex;

		Model();
		
		void Load(const std::string& filepath) override;
		void UnLoad() override;

		~Model();

	private : 
		void ModelParseur(const char* path);
	};
}