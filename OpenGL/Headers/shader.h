#pragma once
#include <Camera.h>


namespace Resources
{
	class Shader : public IResource
	{
	public:
		int vertexShader;
		int fragmentShader;
		int shaderProgram;

		std::string openFile(const char* path);

		Shader();
		~Shader();
		bool SetVertexShader(const char* vertexPath);
		bool SetFragmentShader(const char* fragmentShaderpath);
		bool Link();

		

		void IResource::Load(const std::string& path)override;
		void IResource::UnLoad()override;
	private:
	};
}