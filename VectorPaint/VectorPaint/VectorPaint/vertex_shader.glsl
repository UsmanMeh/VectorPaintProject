#version 330 core

layout (location = 0) in vec3 vertex_position;
layout (location = 1) in vec2 vertex_texcoord;

uniform mat4 ModelMatrix;
out vec2 fragmentUv;

void main()
{
    gl_Position = ModelMatrix * vec4(vertex_position, 1);
    fragmentUv = vec2(vertex_texcoord.x, vertex_texcoord.y);
}