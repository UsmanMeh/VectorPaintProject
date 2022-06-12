

#version 330 core

#define MARKER_RADIUS 500
#define THICKNESS 1
uniform 
struct Material
{
	vec4 color;
	sampler2D mainTexture;
};
uniform 
struct Line
{
	vec2 start;
	vec2 end;
	vec2 scale;
	vec2 viewport;

    float thickness;
};

in vec2 fragmentUv;
out vec4 fragmentColor;
uniform Material material;
uniform Line line;

void main() 
{
    fragmentColor = vec4(0.0);
	vec2 currentRect = (abs(line.scale ) * line.viewport );
    vec2 st = fragmentUv.xy * currentRect;
    vec2 p1 = vec2(0.0, 0.0);
    vec2 p2 = currentRect;
    float thickness = 50.0f;
    //line equation
    float m = (p1.y - p2.y)/(p1.x - p2.x);
    float c = p1.y - m*p1.x;
    //fragmentColor.a = 1;
    vec2 l = vec2((st.y-c)/m, st.x*m+c);
    if ((st.y > l.y - thickness && st.y < l.y + thickness) || (st.x > l.x- thickness && st.x < l.x+ thickness))
          fragmentColor = material.color;
}