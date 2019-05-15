#version 450

in vec2 uv_frag;

layout(location = 0) out vec4 color;

uniform vec3 col;

uniform sampler2D tex;

void main()
{
	color = vec4( col, 1.0 ) * texture( tex, uv_frag );
	if (color.a < 0.5) {
		discard;
	}
}