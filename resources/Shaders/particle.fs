#version 120

uniform sampler2D tex_di;

varying vec4 vColor;
varying vec2 vTexCoord;

void main()
{
	vec4 di = texture2D(tex_di, vTexCoord);
	gl_FragColor = vec4(di.rgb*vColor.rgb, di.r*vColor.a);
	//out_color = vec4(1.0,0.0,0.0, 1.0);
}
