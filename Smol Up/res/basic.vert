#version 330

in vec3 position_vert;
in vec2 uv_vert;
in vec3 normal_vert;

out vec2 uv_frag;
out vec3 normal_frag;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	vec4 pos = projection * view * model * vec4(position_vert, 1.0);
	gl_Position = pos;
	uv_frag = uv_vert;
	normal_frag = normal_vert;
}