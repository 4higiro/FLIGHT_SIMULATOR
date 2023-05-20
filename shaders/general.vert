#version 330 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 norm;
layout (location = 2) in vec2 tex;
out vec3 vertex_norm;
out vec2 vertex_texture;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	vertex_norm = norm;
	vertex_texture = tex;
	gl_Position = projection * view * model * vec4(pos, 1.0f);
}