#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;  // New normal attribute

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 Normal;  // New Normal variable
out vec3 FragPos;  // New Fragment Position variable

void main()
{
    gl_Position = projection * view * model * vec4(position, 1.0);
    FragPos = vec3(model * vec4(position, 1.0));
    Normal = mat3(transpose(inverse(model))) * normal;  // Normal in world space coordinates
}
