#include<Material.h>

using namespace LowRendere;

Material::Material()
{
	intensity = 0.4f;

	ambiant = Vector3D(1.0f, 1.0f, 1.0f) * intensity;
	diffuse = Vector3D(1.0f, 1.0f, 1.0f);
	specular = Vector3D(1.0f, 1.0f, 1.0f);
	shininess = 32.0f;
}

Material::~Material()
{
	
}