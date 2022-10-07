#pragma once
#include<Debug.h>
#include <GameObject.h>
namespace Core
{
	struct AppInitializer
	{
		const unsigned int width;
		const unsigned int height;
		unsigned int major;
		unsigned int minor;
		const char* name;
		void(*Framebuffer_size_callback)(GLFWwindow* window, int width, int height);
		void(*glDebugOutput)(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei lenght, const GLchar* message, const void* userParam);
	};



	class  App
	{
	public:

		GLFWwindow* window;
		static int width, height;
		static bool mouseCaptured ;
		static float mouseDeltaX  ;
		static float mouseDeltaY;

		Resources::Texture texture;
		Resources::Shader shader;
		Resources::ResourceManager resource;

		LowRendere::DirLight dirLights[7];
		LowRendere::PointLight pointLights[7];
		LowRendere::SpotLight spotLights[7];

		void CameraInputApp(LowRendere::Camera& camera, LowRendere::CameraInputs& inputs, bool& mouseCaptured, double mouseDeltaX, double mouseDeltaY, GLFWwindow* window);
		void Init(AppInitializer init);
		void Update();
		App();
	private:
	};

	

}