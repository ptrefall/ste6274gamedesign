#version 120

uniform mat4 mvp;

varying vec2 vTexCoord;

void main()
{
	gl_Position = mvp * gl_Vertex;
	vTexCoord = gl_MultiTexCoord0.st;
}
