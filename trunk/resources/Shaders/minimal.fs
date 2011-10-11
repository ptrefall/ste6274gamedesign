#version 120

uniform sampler2D tex_ao;
//uniform sampler2D tex_bu;
uniform sampler2D tex_di;
uniform sampler2D tex_il;
uniform sampler2D tex_sp;


varying vec2 vTexCoord;
varying vec3 vNormal;
varying vec3 vLightDir;
varying vec3 vHalfVec;

void main()
{
	vec4 sp = texture2D(tex_sp, vTexCoord);
	vec4 il = texture2D(tex_il, vTexCoord);
	vec4 di = texture2D(tex_di, vTexCoord);
	vec4 ao = texture2D(tex_ao, vTexCoord);
	//vec3 bu = 2.0 * texture2D(tex_bu, vTexCoord).rgb - 1.0;
	
	vec3 N = normalize(vNormal);
	vec3 L = normalize(vLightDir);
	vec3 H = normalize(vHalfVec);
	
	float NdotL = max(dot(N, -L), 0.0);
	float shininess = pow(max(dot(-H, N), 0.0), 2.0);
	
	gl_FragColor = vec4((di.rgb*NdotL + sp.rgb*shininess + il.rgb*di.rgb + ao.rgb)*di.rgb - (di.rgb*NdotL*0.1), 1.0);
	gl_FragColor = gl_FragColor+gl_FragColor;
	//out_color = vec4(1.0,0.0,0.0, 1.0);
}
