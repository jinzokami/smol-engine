#version 450

in vec2 uv_frag;
in vec3 normal_frag;

out vec4 color;

uniform vec3 col;

uniform sampler2D tex;

void main()
{
	color = texture(tex, uv_frag);
}