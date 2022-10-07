#pragma once
#include<Texture.h>

namespace LowRendere
{
	class Material
	{
	public:
		Material();
		~Material();

		Resources::Texture* texture;

		Vector3D ambiant;
		Vector3D diffuse;
		Vector3D specular;

		float intensity;
		float shininess;

	private:

	};
}
