#include"Light.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

using namespace LowRendere;


DirLight::DirLight()
{
    activeLight = 0;
    intensity = 0.1f;
    direction = Vector3D(0.0f, 0.0f, 1.0f);

    ambiant = Vector3D(1.0f, 1.0f, 1.0f);
    diffuse = Vector3D(1.0f, 1.0f, 1.0f);
    specular = Vector3D(1.0f, 1.0f, 1.0f);
}


#include <string>
void DirLight::LightSetUp(int shaderProgram, int lightId)
{

    glUseProgram(shaderProgram);

    //Directional light.
    glUniform1i(glGetUniformLocation(shaderProgram, "dirActiveLight"), activeLight);
    glUniform1fv(glGetUniformLocation(shaderProgram, "dirIntensity"), 1, &intensity);

   glUniform3fv(glGetUniformLocation(shaderProgram, ("dirlights[" + std::to_string(lightId) + "].direction").c_str()), 1, &direction.x);
   glUniform3fv(glGetUniformLocation(shaderProgram, ("dirlights[" + std::to_string(lightId) + "].ambient").c_str()), 1, &ambiant.x);
   glUniform3fv(glGetUniformLocation(shaderProgram, ("dirlights[" + std::to_string(lightId) + "].diffuse").c_str()), 1, &diffuse.x);
   glUniform3fv(glGetUniformLocation(shaderProgram, ("dirlights[" + std::to_string(lightId) + "].specular").c_str()), 1, &specular.x);
}

PointLight::PointLight()
{

     activeLight = 0;
     intensity = 0.1f;
     position = Vector4D::zero;

     ambiant = Vector3D(1.0f, 1.0f, 1.0f);
     diffuse = Vector3D(1.0f, 1.0f, 1.0f);
     specular = Vector3D(1.0f, 1.0f, 1.0f);

     constant = 1.0f;
     linear = 0.09f;
     quadratic = 0.032f;
}

void PointLight::LightSetUp(int shaderProgram, int lightId)
{

    glUseProgram(shaderProgram);

    glUniform1i(glGetUniformLocation(shaderProgram, "pointActiveLight"), activeLight);
    glUniform1fv(glGetUniformLocation(shaderProgram, "pointIntensity"), 1, &intensity);

    glUniform3fv(glGetUniformLocation(shaderProgram, ("pointLights[" + std::to_string(lightId) + "].position").c_str()), 1, &position.x);

    glUniform1fv(glGetUniformLocation(shaderProgram, ("pointLights[" + std::to_string(lightId) + "].constant").c_str()), 1, &constant);
    glUniform1fv(glGetUniformLocation(shaderProgram, ("pointLights[" + std::to_string(lightId) + "].linear").c_str()), 1, &linear);
    glUniform1fv(glGetUniformLocation(shaderProgram, ("pointLights[" + std::to_string(lightId) + "].quadratic").c_str()), 1, &quadratic);

    glUniform3fv(glGetUniformLocation(shaderProgram, ("pointLights[" + std::to_string(lightId) + "].ambient").c_str()), 1, &ambiant.x);
    glUniform3fv(glGetUniformLocation(shaderProgram, ("pointLights[" + std::to_string(lightId) + "].diffuse").c_str()), 1, &diffuse.x);
    glUniform3fv(glGetUniformLocation(shaderProgram, ("pointLights[" + std::to_string(lightId) + "].specular").c_str()), 1, &specular.x);
}

SpotLight::SpotLight()
{
     activeLight = 0;
     intensity = 0.1f;
     direction = Vector3D(1, 0, 0);
     position = Vector4D::zero;

     innerCone = cos(radToDeg(17.5f));
     outerCutOff = cos(radToDeg(12.5f));

     ambiant = Vector3D(1.0f, 1.0f, 1.0f);
     diffuse = Vector3D(1.0f, 1.0f, 1.0f);
     specular = Vector3D(1.0f, 1.0f, 1.0f);
}

void SpotLight::LightSetUp(int shaderProgram, int lightId)
{

    glUseProgram(shaderProgram);

    glUniform1i(glGetUniformLocation(shaderProgram, "spotActiveLight"), activeLight);
    glUniform1fv(glGetUniformLocation(shaderProgram, "spotIntensity"), 1, &intensity);

    glUniform3fv(glGetUniformLocation(shaderProgram, ("spotLight[" + std::to_string(lightId) + "].position").c_str()), 1, &position.x);
    glUniform3fv(glGetUniformLocation(shaderProgram, ("spotLight[" + std::to_string(lightId) + "].direction").c_str()), 1, &direction.x);

    glUniform1fv(glGetUniformLocation(shaderProgram, ("pointLights[" + std::to_string(lightId) + "].innerCone").c_str()), 1, &innerCone);
    glUniform1fv(glGetUniformLocation(shaderProgram, ("pointLights[" + std::to_string(lightId) + "].outerCutOff").c_str()), 1, &outerCutOff);

    glUniform3fv(glGetUniformLocation(shaderProgram, ("spotLight[" + std::to_string(lightId) + "].ambient").c_str()), 1, &ambiant.x);
    glUniform3fv(glGetUniformLocation(shaderProgram, ("spotLight[" + std::to_string(lightId) + "].diffuse").c_str()), 1, &diffuse.x);
    glUniform3fv(glGetUniformLocation(shaderProgram, ("spotLight[" + std::to_string(lightId) + "].specular").c_str()), 1, &specular.x);
}
