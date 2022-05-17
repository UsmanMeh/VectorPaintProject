

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
    float maxX = 1.0 - .1;
   float minX = .1;
   float maxY = maxX / 1;
   float minY = minX / 1;

   // fragmentColor = texture(material.mainTexture, fragmentUv.yx);
   fragmentColor = material.color;
}