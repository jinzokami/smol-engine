#version 450

layout(location = 0) in vec3 position_vert;
layout(location = 1) in vec2 uv_vert;

out vec2 uv_frag;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform float timer;

uniform vec2 img_dim;
uniform vec2 sub_img_pos;
uniform vec2 sub_img_dim;

void main()
{
	vec2 q_factor = vec2( sub_img_dim.x / img_dim.x, sub_img_dim.y / img_dim.y );
	vec2 offset = vec2( sub_img_pos.x * q_factor.x, sub_img_pos.y * q_factor.y );

	gl_Position = projection * view * model * vec4(position_vert, 1.0);
	uv_frag = vec2( ( uv_vert.x * q_factor.x ) + offset.x, ( uv_vert.y * q_factor.y ) + offset.y );
}