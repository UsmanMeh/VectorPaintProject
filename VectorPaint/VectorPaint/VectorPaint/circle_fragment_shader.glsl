#version 330 core

#define MARKER_RADIUS 500
#define THICCNESS 1
uniform 
struct Material
{
	vec4 color;
	sampler2D mainTexture;
};
uniform 
struct Circle
{
	vec2 start;
	vec2 end;
	vec2 scale;
};

in vec2 fragmentUv;
out vec4 fragmentColor;
uniform Material material;
uniform Circle circle;

void main() 
{
    fragmentColor = vec4(0.0);
	vec2 viewport = vec2(1024.0f,680.0f);
	vec2 currentRect = (abs(circle.scale));
    vec2 st = fragmentUv.xy * currentRect;
	vec2 mid = currentRect/2;
    //line equation
	if(length(mid-st)<(mid.x<mid.y?mid.x:mid.y))
		fragmentColor = material.color;

}