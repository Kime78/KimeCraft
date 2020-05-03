#include "chunk.hpp"
#include "shaders.hpp"
#include <glad/glad.h>
#include <stdexcept>
void Chunk::generate_mesh()
{
    for(auto block : blocks)
    {
        for(auto vert : block.vert_data)
        {
            mesh.push_back(vert);
        }
    }
}

void Chunk::bind_mesh()
{

    //this needs a shader class but this will work rn
    // Create Vertex Array Object
    if(!gladLoadGL())
    {
        //std::cout << "EXTRA BAD";
        throw std::runtime_error("Glad is not loading");
    }
 
    //glEnable(GL_CULL_FACE);
    //glCullFace(GL_BACK);
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glDepthRange(-100,100);

    // Create a Vertex Buffer Object and copy the vertex data to it
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glEnable(GL_DEPTH_TEST);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, mesh.size() * sizeof(float) * 3, mesh.data(), GL_STATIC_DRAW);
    Shader sh;
}

void Chunk::render() 
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDrawArrays(GL_TRIANGLES, 0, mesh.size());
}
