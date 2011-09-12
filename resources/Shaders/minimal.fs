#version 330 core

#define VERTEX		0
#define NORMAL	 	1
#define TEXCOORD 	2
#define COLOR		3
#define FRAG_COLOR	0


in block
{
	smooth vec3 Color;
} In;

layout(location = FRAG_COLOR, index = 0) out vec4 out_color;

void main()
{
	out_color = vec4(In.Color, 1.0);
}
