#version 330

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 uv;
layout (location = 3) in vec4 color;

uniform mat4 mvpMatrix;

out vec4 vertColor;
out vec2 vertUV;

void main()
{
	gl_Position = mvpMatrix*vec4(position,1.0);
	vertUV = uv;
	vertColor = color;
}