#version 330 core

in vec2 texCoord;

uniform sampler2D textureSampler;

void main()
{
	gl_FragColor = texture(textureSampler, texCoord);
}