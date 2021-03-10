#version 330 core

in vec3 position;
in vec3 color;
in vec3 normal;

out vec3 Color;
out vec3 Normal;
out vec3 FragPos;

uniform mat4 proj;
uniform mat4 view;
uniform mat4 model;

void main()
{
    Color = color;
    Normal = normal;
    FragPos = vec3(model * vec4(position, 1.0));
    gl_Position = proj * view * model * vec4(position.x, position.y, position.z, 1.0);
}