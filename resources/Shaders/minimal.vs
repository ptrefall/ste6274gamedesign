#version 330 core

#define VERTEX		0
#define NORMAL	 	1
#define TEXCOORD 	2
#define COLOR		3
#define FRAG_COLOR	0

layout(location = VERTEX) in vec3 Vertex;
layout(location = COLOR) in vec3 Color;

uniform mat4 mvp;

out block
{
	smooth vec3 Color;
} Out;

void main()
{
	gl_Position = mvp * vec4(Vertex, 1.0);
	Out.Color = vec3(Color.r, Color.g, Color.b);
}
