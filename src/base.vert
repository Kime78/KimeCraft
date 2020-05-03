#version 330 core
in vec3 position;
in vec3 color;
out vec3 Color;
uniform mat4 proj;
uniform mat4 view;
void main()
{
    Color = color;
    gl_Position = proj * view * vec4(position.x, position.y, position.z, 1.0);
}