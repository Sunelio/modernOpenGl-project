#include <shader.h>
#include<sstream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include<unordered_map>
#include<sstream>
#include <fstream>
#include <string>

using namespace Resources;
using namespace std;

Shader::Shader()
{
	fragmentShader = 0;
	vertexShader = 0;
	shaderProgram = 0;
}

string Shader::openFile(const char* path)
{
	string content;
	ifstream file(path, ios::in);

	if (!file.is_open())
	{
		cout << "can not be open";
		return "";
	}

	string line = "";
	while (!file.eof())
	{
		getline(file, line);
		content.append(line + "\n");
	}
	file.close();
	return content;
}

bool Shader::SetVertexShader(const char* vertexPath)
{

	//----------vertex Shader source----------------\\

	string fileContent = openFile(vertexPath);
	const char* vertexShaderSource = fileContent.c_str();

	// build and compile our shader program
// ------------------------------------
// vertex shader
	vertexShader = glCreateShader(GL_VERTEX_SHADER);

	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	// check for shader compile errors
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		return false;
	}
	else
		return true;
}

bool Shader::SetFragmentShader(const char* fragmentShaderpath)
{
	string fileContent = openFile(fragmentShaderpath);
	const char* fragmentShaderSource = fileContent.c_str();
	// fragment shader
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	int success;
	char infoLog[512];
	// check for shader compile errors
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
		return false;
	}
	else
		return true;
}

bool Shader::Link()
{
	int success;
	char infoLog[512];
	// link shaders
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	// check for linking errors
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
		return false;
	}
	else
	{
		glDeleteShader(fragmentShader);
		glDeleteShader(vertexShader);
		return true;
	}

}

Shader::~Shader()
{

}

void Shader::Load(const std::string& path)
{
}

void Shader::UnLoad()
{

}