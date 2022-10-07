#include "Mesh.h"
#include<GameObject.h>;
#include <glad/glad.h>
#include <GLFW/glfw3.h>

using namespace LowRendere;

Mesh::Mesh()
{
}
Mesh::~Mesh()
{
	model->~Model();
}

void Mesh::Draw()
{
	

	Matrix4D mvp;
	if (gameObject != nullptr)
	{
		mvp = Camera::GetProjection() * Camera::GetViewMatrix() * Matrix4D::CreateTransformMatrix(gameObject->transform);
		gameObject->UpdateSelfAndChild();
	}

	glUseProgram(shader->shaderProgram);
	if (material->texture != nullptr)
	{
		glBindTextureUnit(0, material->texture->textKey);
		glUniform1i(glGetUniformLocation(shader->shaderProgram, "texture1"), 0); // set it manually
	}

	glUniformMatrix4fv(glGetUniformLocation(shader->shaderProgram, "mvp"), 1, GL_FALSE, &mvp.e[0]);
	if (gameObject != nullptr)
		glUniformMatrix4fv(glGetUniformLocation(shader->shaderProgram, "modelMatrix"), 1, GL_FALSE, &gameObject->modelMatrix.e[0]);

	glUniform3fv(glGetUniformLocation(shader->shaderProgram, "material.ambient"), 1, &material->ambiant.x);
	glUniform3fv(glGetUniformLocation(shader->shaderProgram, "material.diffuse"), 1, &material->diffuse.x);
	glUniform3fv(glGetUniformLocation(shader->shaderProgram, "material.specular"), 1, &material->specular.x);
	glUniform1fv(glGetUniformLocation(shader->shaderProgram, "material.shininess"), 1, &material->shininess);

	glBindVertexArray(model->VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
	glDrawElements(GL_TRIANGLES, model->vertex.size() * sizeof(Resources::Vertex), GL_UNSIGNED_INT, 0);
}
