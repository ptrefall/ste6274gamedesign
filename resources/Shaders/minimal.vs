#version 120

uniform mat4 proj;
uniform mat4 mvp;
uniform mat4 mv;
uniform mat3 norm;

varying vec2 vTexCoord;
varying vec3 vNormal;
varying vec3 vLightDir;
varying vec3 vHalfVec;

void main()
{
	gl_Position = mvp * gl_Vertex;
	vTexCoord = gl_MultiTexCoord0.st;
	vNormal = normalize(norm * gl_Normal);
	vLightDir = normalize(proj * vec4(0.0, 0.3, -0.75, 0.0)).xyz;
	
	vec3 pos = normalize(mv * gl_Vertex).xyz;
	vHalfVec = normalize((pos + vLightDir)/2.0);
}
