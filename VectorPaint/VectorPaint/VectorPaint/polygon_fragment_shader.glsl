

#version 330 core

uniform 

struct Material
{
	vec4 color;
	sampler2D mainTexture;
};

in vec2 fragmentUv;
out vec4 fragmentColor;
uniform Material material;

void main() 
{
   fragmentColor = material.color;
   fragmentColor = texture(material.mainTexture, fragmentUv.yx) * material.color;
}