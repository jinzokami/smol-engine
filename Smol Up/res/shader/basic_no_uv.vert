#version 450

layout(location = 0) in vec3 position_vert;
layout(location = 2) in vec3 normal_vert;

out vec3 normal_frag;
out vec3 pos_frag;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	mat4 mvp = projection * view * model;
	vec4 pos = mvp * vec4(position_vert, 1.0);
	
	mat3 normal_matrix = mat3(mvp);
	normal_matrix = inverse(normal_matrix);
	normal_matrix = transpose(normal_matrix);
	normal_frag = normalize(normal_vert * normal_matrix);

	gl_Position = pos;
	pos_frag = vec3(pos.xyz);
}