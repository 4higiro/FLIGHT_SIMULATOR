#version 330 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 norm;
layout (location = 2) in vec2 tex;

out vec3 vertex_normal;
out vec2 vertex_texture;
out vec4 fragment_position;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	vertex_normal = mat3(transpose(inverse(model))) * norm;
	vertex_texture = tex;
	fragment_position = model * vec4(pos, 1.0f);
	gl_Position = projection * view * fragment_position;
}