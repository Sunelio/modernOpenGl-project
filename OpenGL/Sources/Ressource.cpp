
#include <Resources.h>
#include<sstream>


using namespace Resources;
using namespace std;

unordered_map<string, IResource*> ResourceManager::resourceMap;

//--------------Resource Manager------------\\

void ResourceManager::Create(IResource* resource, const std::string& name, const std::string& path)
{
	resource->Load(path);
	if (!resource)
	{
		return;
	}
	resourceMap.emplace(name, resource);
}

IResource* ResourceManager::Get(const string& name)
{
	if (resourceMap[name])
	{
		return resourceMap[name];
	}
}

void ResourceManager::Delete(const string& name)
{
	if (resourceMap[name])
	{
		resourceMap[name]->UnLoad();
	}
}

void ResourceManager::DeleteAll()
{
	resourceMap.clear();
}






