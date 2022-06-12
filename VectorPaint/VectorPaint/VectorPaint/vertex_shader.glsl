#version 330 core

layout (location = 0) in vec3 vertex_position;
layout (location = 1) in vec2 vertex_texcoord;

uniform mat4 ModelMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ProjectionMatrix;
out vec2 fragmentUv;

void main()
{
vec4 worldPost = ViewMatrix * ModelMatrix* vec4(vertex_position.x,vertex_position.y,0, 1);
    gl_Position = ProjectionMatrix * worldPost;
    fragmentUv = vec2(vertex_texcoord.x, vertex_texcoord.y);
}