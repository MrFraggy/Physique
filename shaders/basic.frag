#version 330

uniform sampler2D textureChannel0;

in vec2 vertUV;
in vec4 vertColor;

out vec4 fragColor;

void main()
{
	fragColor = texture2D(textureChannel0, vertUV)*vertColor;
}