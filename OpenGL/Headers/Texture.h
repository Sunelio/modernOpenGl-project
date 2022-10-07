#pragma once
#include<IResource.h>

namespace Resources
{
	class Texture : public IResource
	{
	public:

		unsigned int textKey;
		Texture();
		~Texture();
		void Load(const std::string& name)override;
		void UnLoad()override;

	protected:
	};
}
