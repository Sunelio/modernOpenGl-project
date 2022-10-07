#version 330 core
out vec4 FragColor;

in vec3 fragPos;
in vec2 TexCoord;
in vec3 normal;

uniform sampler2D texture1;
uniform vec3 viewPos;
uniform vec3 position;
uniform float dirIntensity;
uniform float pointIntensity;
uniform float spotIntensity;
uniform int dirActiveLight;
uniform int pointActiveLight;
uniform int spotActiveLight;




struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
}; 
uniform Material material;

struct DirLight {
    vec3 direction;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};  

struct PointLight {    
    vec3 position;
    
    float constant;
    float linear;
    float quadratic;  

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};  

struct SpotLight 
{
    vec3 direction;
    vec3  position;
    float outerCutOff;
    float innerCone;
    
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
}; 

uniform DirLight dirlights[7];
uniform PointLight pointLights[7];
uniform SpotLight spotLight[7];


  

  vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
  {
    vec3 lightDir = normalize(-light.direction);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // combine results
    vec3 ambient = light.ambient * material.ambient;
    vec3 diffuse = light.diffuse * diff * material.diffuse;
    vec3 specular = light.specular * spec * material.specular;
    return (ambient + diffuse + specular) * dirIntensity;
  }

  vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance +
        light.quadratic * (distance * distance));
    // combine results
    vec3 ambient = light.ambient * material.diffuse;
    vec3 diffuse = light.diffuse * diff * material.diffuse;
    vec3 specular = light.specular * spec * material.specular;
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular) * pointIntensity;
}

vec3  CalcSpotLight(SpotLight light, vec3 normal, vec3 viewDir)
{
   // Compute lighting parameters.
vec3  lightDir = normalize(light.position - fragPos);
float cutoff   = dot(lightDir, -1 * light.direction);

// Stop if the fragment isn't lit by the spot light.
if (cutoff < light.outerCutOff) 
    return (light.ambient + light.diffuse + light.specular) * spotIntensity;

// Continue light computations.
float diff        = max(dot(normal, lightDir), 0.0);
vec3  reflectDir  = reflect(lightDir, normal);
float spec        = pow(max(dot(-viewDir, reflectDir), 0.0), material.shininess);
float attenuation = clamp((cutoff - light.outerCutOff) / (light.innerCone - light.outerCutOff), 0.0, 1.0);
}

void main()
{


    vec3 viewDir = normalize(viewPos - fragPos);
    vec3 result = vec3(0.0,0.0,0.0);

    for(int i = 0; i < dirActiveLight; i++)
    {
        result += CalcDirLight(dirlights[i], normal, viewDir);
    }
     for(int i = 0; i < pointActiveLight; i++)
    {
      result += CalcPointLight(pointLights[i], normal, fragPos, viewDir); 
    }
   for(int i = 0; i < spotActiveLight; i++)
   {
        result += CalcSpotLight(spotLight[i],normal,viewDir);
   }

    FragColor = texture(texture1, TexCoord) * vec4(result,1.0);
};
