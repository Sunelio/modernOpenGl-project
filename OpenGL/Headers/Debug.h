#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#define ASSERT(BOOL) if(!BOOL) std::printf("Assertion Failed") throw;
#define __FILENAME__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)
#define DEBUGLINE(message) std::printf("%d",__LINE__)
namespace Core
{
	namespace Debug
	{
		class Log
		{
			static std::fstream fileType;
		public:
			void OpenFile(const char* fileName);
			void Print(std::string message);
			void CloseLogFile();

		private:

		};
	}
}