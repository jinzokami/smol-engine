#version 450

in vec2 uv_frag;
layout(location = 0) out vec4 color;

uniform vec3 col;
uniform float timer;

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

//see, chunky? give it a bit of effort and it's easy.
//did you really have to put this off for a month?
void main()
{
	float alpha = 1;//(sin(timer)+1.0)/2;
	if (alpha > 0.975)
	{
		alpha = 1;
	}

	if (alpha < 0.025)
	{
		alpha = 0;
	}

	//for whatever reason, the range of this function is: [-3/8, 12/8]
	float c = lerp(alpha, -0.3751, 1.5);
	//the much anticipated algorithm.
	if (c + 2 * (thresh_map[int(gl_FragCoord.x) % 4][int(gl_FragCoord.y) % 4] - 0.5) < 0.5)
	{
		discard;
	}

	color = vec4(col, 1.0) * texture(tex, uv_frag);
}