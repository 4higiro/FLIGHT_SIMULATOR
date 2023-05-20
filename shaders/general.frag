#version 330 core

in vec3 vertex_norm;
in vec2 vertex_texture;
out vec4 color;

uniform sampler2D texture_sample;
uniform vec3 light_color;

void main()
{
	vec4 ambient = vec4(light_color * 0.15f, 1.0f);
	vec4 obj_color = texture(texture_sample, vertex_texture);
	color = obj_color;
}