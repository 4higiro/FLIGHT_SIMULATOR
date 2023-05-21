#version 330 core

in vec3 vertex_normal;
in vec2 vertex_texture;
in vec4 fragment_position;

out vec4 color;

uniform sampler2D texture_sample;
uniform vec3 light_color;
uniform vec3 light_position;
uniform vec3 view_position;

void main()
{
	vec4 precolor = texture(texture_sample, vertex_texture);
	precolor = vec4(0.1f, 0.5f, 1.0f, 1.0f);

	vec4 ambient = vec4(light_color * 0.15f, 1.0f);

	vec3 ld = light_position - fragment_position.xyz;
	float diff = max(dot(normalize(ld), normalize(vertex_normal)), 0.0f);

	vec4 vd = vec4(normalize(view_position - fragment_position.xyz), 1.0f);
	vec4 rd = vec4(reflect(-normalize(ld), normalize(vertex_normal)), 1.0f);
	float spec = pow(max(dot(vd.xyz, rd.xyz), 0.0f), 128.0f);

	vec4 sp = vec4(0.3f * spec * light_color, 1.0f); 
	vec4 df = precolor * diff;
	vec4 bg = precolor * ambient;
	color = bg + df + sp;
}