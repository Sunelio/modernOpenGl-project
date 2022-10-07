#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoord;

out vec3 normal;
out vec2 TexCoord;
out vec3 fragPos;

uniform mat4 mvp;
uniform mat4 modelMatrix;

void main()
{
	fragPos = (modelMatrix * vec4(aPos,1.0)).xyz;
	gl_Position = mvp * vec4(aPos, 1.0);
	normal = normalize(modelMatrix * vec4(aNormal,0.0)).xyz;
	TexCoord = aTexCoord;
};