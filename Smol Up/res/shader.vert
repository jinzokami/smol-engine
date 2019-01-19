#version 450

layout(location = 0) in vec3 position_vert;
layout(location = 1) in vec2 uv_vert;

out vec2 uv_frag;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform float timer;

void main()
{
	gl_Position = projection * view * model * vec4(position_vert, 1.0);
	uv_frag = uv_vert;
}