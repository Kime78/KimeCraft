#include "shaders.hpp"
#include <fstream>

std::string Shader::open_shader(std::string path)
{
    std::string data;
    std::string res;
    std::ifstream fin(path.c_str(), std::ios::in);
    while(!fin.eof())
    {
        fin >> data;
        res += data;
        if(data == "core")
            res += '\n';
        res += " ";
    }
        
    return res;
}
Shader::Shader()
{
    {
        shaderProgram = glCreateProgram();
        std::string vert = open_shader("src\\base.vert");
        std::string frag = open_shader("src\\base.frag");
        const GLchar* vertex_source = vert.c_str();
        const GLchar* fragment_source = frag.c_str();

        // Create and compile the vertex shader
        GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertex_source, NULL);
        glCompileShader(vertexShader);

        // Create and compile the fragment shader
        GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragment_source, NULL);
        glCompileShader(fragmentShader);

        // Link the vertex and fragment shader into a shader program
    
        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader);
        glBindFragDataLocation(shaderProgram, 0, "outColor");
        glLinkProgram(shaderProgram);
        glUseProgram(shaderProgram);

    // Specify the layout of the vertex data
        GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
        glEnableVertexAttribArray(posAttrib);
        glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);

        GLint colAttrib = glGetAttribLocation(shaderProgram, "color");
        glEnableVertexAttribArray(colAttrib);
        glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    }
}