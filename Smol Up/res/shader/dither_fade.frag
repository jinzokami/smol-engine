#version 450

in vec3 pos_frag;
in vec2 uv_frag;
in vec3 normal_frag;

layout(location = 0) out vec4 color;

uniform float alpha;

uniform vec3 color_frag;

uniform vec3 sun_vec;
uniform float ambient_light;

uniform sampler2D tex;

//the threshold map. a prerequisite for performing this algorithm
//can be procedurally calculated, but i refuse.
mat4 thresh_map = {
	vec4(0  * 0.0625, 8  * 0.0625, 2  * 0.0625, 10 * 0.0625),
	vec4(12 * 0.0625, 4  * 0.0625, 14 * 0.0625, 6  * 0.0625),
	vec4(3  * 0.0625, 11 * 0.0625, 1  * 0.0625, 9  * 0.0625),
	vec4(15 * 0.0625, 7  * 0.0625, 13 * 0.0625, 5  * 0.0625),
};

float lerp(float t, float a, float b)
{
	return (1-t)*a + t*b;
}

void main()
{
	if (alpha > 0.995)
	{
		color = texture(tex, uv_frag);
	}
	else if (alpha < 0.005)
	{
		discard;
	}
	else
	{
		//for whatever reason, the range of this function is: [-3/8, 12/8]
		float c = lerp(alpha, -0.3751, 1.5);
		if (c + 2 * (thresh_map[int(gl_FragCoord.x) % 4][int(gl_FragCoord.y) % 4] - 0.5) < 0.5)
		{
			discard;
		}
		vec3 light = normalize(sun_vec - pos_frag);
		light = (max(dot(normal_frag, light), 0.0) + ambient_light) * vec3(1.0, 1.0, 1.0);
		color = texture(tex, uv_frag) * vec4(color_frag, 1.0) * vec4(light, 1.0);
	}
}