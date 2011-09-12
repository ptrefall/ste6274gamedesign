#version 330 core

#define VERTEX	 0
#define NORMAL	 1
#define TANGENT	 2
#define COLOR	 3
#define TEXCOORD 4
#define FRAG_COLOR 0

in block
{
	smooth vec3 Color;
} In;

layout(location = FRAG_COLOR, index = 0) out vec4 out_color;

void main()
{
	out_color = vec4(1.0,0.0,0.0, 1.0);
}
