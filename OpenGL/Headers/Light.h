#pragma once
#include <Material.h>

namespace LowRendere
{
    class DirLight
    {
    public :

        DirLight();

        int activeLight;
        float intensity;
        Vector3D direction;
       
        Vector3D ambiant;
        Vector3D diffuse;
        Vector3D specular;

        void LightSetUp(int shaderProgram, int lightId);
    };

    class PointLight
    {
    public:

        PointLight();

         int activeLight;
         float intensity;
        Vector4D position;

        Vector3D ambiant ;
        Vector3D diffuse ;
        Vector3D specular ;

        float constant;
        float linear;
        float quadratic;

        void LightSetUp(int shaderProgram, int lightId);

    };

    class SpotLight
    {
    public:

        SpotLight();

        int activeLight;
        float intensity;
        Vector3D direction ;
        Vector4D position ;

        float innerCone;
        float outerCutOff;

        Vector3D ambiant;
        Vector3D diffuse;
        Vector3D specular;

        

        void LightSetUp(int shaderProgram, int lightId);

    };
    
}