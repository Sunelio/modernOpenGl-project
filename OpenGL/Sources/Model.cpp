#define _CRT_SECURE_NO_WARNINGS
#include <Model.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include<unordered_map>
#include<sstream>
#include <fstream>
#include <string>
#include<sstream>


using namespace Resources;
using namespace std;

Model::Model()
{
	VAO = 0;
	VBO = 0;
	EBO = 0;
}

void Model::ModelParseur(const char* path)
{

		std::vector<Core::Maths::Vector3D> vertexPosition;
		std::vector<Core::Maths::Vector3D> vertexNormal;
		std::vector<Core::Maths::Vector2D> textureUV;


		std::vector<unsigned int> indices;
		std::vector<int> vertexPositionIndicies;
		std::vector<int> vertexNormalIndicies;
		std::vector<int> textureUVIndicies;

		std::stringstream ss;
		std::ifstream inFile(path);
		std::string line = "";
		std::string prefix = "";
		Core::Maths::Vector3D tempVec3;
		Core::Maths::Vector2D tempVec2;
		int tempInt = 0;

		//File open error check
		if (!inFile.is_open())
		{
			throw "ERROR::OBJLOADER::Could not open file.";
		}
		//Read 1 line at a time
		while (std::getline(inFile, line))
		{
			//Get the prefix of the line
			ss.clear();
			ss.str(line);
			ss >> prefix;

			if (prefix == "v")// Vertex position
			{
				ss >> tempVec3.x >> tempVec3.y >> tempVec3.z;
				vertexPosition.push_back(tempVec3);
			}
			else if (prefix == "vt")
			{
				ss >> tempVec2.x >> tempVec2.y;
				textureUV.push_back(tempVec2);
			}
			else if (prefix == "vn")
			{
				ss >> tempVec3.x >> tempVec3.y >> tempVec3.z;
				vertexNormal.push_back(tempVec3);
			}
			else if (prefix == "f")
			{
				int counter = 0;
				while (ss >> tempInt)
				{
					//Pushing indices into correct array
					if (counter == 0)
					{
						vertexPositionIndicies.push_back(tempInt);
					}
					else if (counter == 1)
					{
						textureUVIndicies.push_back(tempInt);
					}
					else if (counter == 2)
					{
						vertexNormalIndicies.push_back(tempInt);
					}

					//Handling characters
					if (ss.peek() == '/')
					{
						++counter;
						ss.ignore(1, '/');
					}
					else if (ss.peek() == ' ')
					{
						++counter;
						ss.ignore(1, ' ');
					}

					//Reset the counter
					if (counter > 2)
					{
						counter = 0;
					}
				}
			}
			else
			{

			}
			vertex.resize(vertexPositionIndicies.size(), Vertex());

		}
		//Load in all indices
		for (size_t i = 0; i < vertexNormalIndicies.size(); i++)
		{
			vertex[i].position = vertexPosition[vertexPositionIndicies[i] - 1];
			vertex[i].UV = textureUV[textureUVIndicies[i] - 1];
			vertex[i].normal = vertexNormal[vertexNormalIndicies[i] - 1];
			indices.push_back(i);
		}

		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);

		glGenVertexArrays(1, &VAO);

		// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
		glBindVertexArray(VAO);

		//glNamedBufferData(VBO, sizeof(vertices), vertices, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertex.size(), vertex.data(), GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), indices.data(), GL_STATIC_DRAW);

		// position attribute
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		// color attribute
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
		// texture coord attribute
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
		glEnableVertexAttribArray(2);

		//glBindVertexArray(vertexAttributes.VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
}

Model::~Model()
{
	// optional: de-allocate all resources once they've outlived their purpose:
		// ------------------------------------------------------------------------
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}


void Model::Load(const std::string& path)
{
	ModelParseur(path.c_str());
}

void Model::UnLoad()
{

}
