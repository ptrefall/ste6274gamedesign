#version 120

uniform mat4 mvp;

varying vec4 vColor;
varying vec2 vTexCoord;

void main()
{
	gl_Position = mvp * gl_Vertex;
	vTexCoord = gl_MultiTexCoord0.st;
	vColor = gl_Color; //vec3(0.6,0.6,0.9);
}
