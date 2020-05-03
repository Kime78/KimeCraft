#pragma once
#include <vector>
#include <array>
#include <glm.hpp> 
#include <glad/glad.h>
class IRenderable 
{
public:
    virtual void render() = 0;
    virtual ~IRenderable() noexcept = default;
    IRenderable() = default;
};

struct Block 
{
    Block(glm::vec3 origin);
    std::vector<glm::vec3> vert_data;
private:
    void make_triangle(std::vector<glm::vec3> corners, glm::vec3 color, std::array<int,3> idx);    
};

class Chunk : public IRenderable
{
public:
    std::vector<glm::vec3> mesh;
    Chunk() = default;
    virtual ~Chunk() = default;
    std::vector<Block> blocks;
    void bind_mesh();
    void generate_mesh();
    void render() override;
};
//to do a shader class for the uniforms
class Camera 
{
    glm::vec3 cameraPos;
    glm::vec3 cameraFront;
    glm::vec3 cameraUp;
    glm::mat4 view;

public:
    Camera();
    void handle_input();
    void upload_uniform();
};
struct Shader
{
    GLuint shaderProgram;
    Shader();    
};