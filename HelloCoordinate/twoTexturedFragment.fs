#version 330 core
in vec2 TexCoord;

out vec4 color;

uniform sampler2D ourTexture1;
uniform sampler2D ourTexture2;

uniform float mixValue;

void main()
{
	// Linearly interpolate between both textures (second texture is only slightly combined)
	color = mix(texture(ourTexture1, TexCoord), texture(ourTexture2, vec2(1.0f - TexCoord.x, TexCoord.y) ), mixValue);
}