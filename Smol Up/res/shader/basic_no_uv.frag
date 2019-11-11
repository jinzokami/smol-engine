#version 450

in vec3 pos_frag;
in vec3 normal_frag;

layout(location = 0) out vec4 color;

uniform vec3 color_frag;

uniform vec3 sun_vec;
uniform float ambient_light;

void main()
{
	vec3 light = normalize(sun_vec - pos_frag);
	light = (max(dot(normal_frag, light), 0.0) + ambient_light) * vec3(1.0, 1.0, 1.0);
	color = vec4(color_frag, 1.0) * vec4(light, 1.0);
}