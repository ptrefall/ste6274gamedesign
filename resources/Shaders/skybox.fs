#version 120

uniform sampler2D tex_di;

varying vec2 vTexCoord;

void main()
{
	vec4 di = texture2D(tex_di, vTexCoord);
	gl_FragColor = vec4(di.rgb, 1.0);
	gl_FragColor = gl_FragColor+(gl_FragColor*0.75);
	//out_color = vec4(1.0,0.0,0.0, 1.0);
}
