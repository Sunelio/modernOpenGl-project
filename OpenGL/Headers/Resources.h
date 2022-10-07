#pragma once
#include<unordered_map>
#include<shader.h>



namespace Resources
{

	
	class ResourceManager
	{
	public:
		static void Create(IResource* resource, const std::string& name, const std::string& path);
		static IResource* Get(const std::string& path);
		static void Delete(const std::string& path);
		static void DeleteAll();

	private:
		static std::unordered_map<std::string, IResource*> resourceMap;
	};
}
