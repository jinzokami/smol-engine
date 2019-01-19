#version 450

in vec2 uv_frag;
in vec3 normal_frag;

layout(location = 0) out vec4 color;

uniform vec3 col;

uniform sampler2D tex;

void main()
{
	color = vec4(col, 0.5) * texture(tex, uv_frag);
}