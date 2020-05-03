#include "renderer.hpp"
#include <stdexcept>
#include <glad/glad.h>
#include <random>
#include <stdlib.h> 
#include <gtc/matrix_transform.hpp>
#include <SFML/Window.hpp>
#include <gtc/type_ptr.hpp>
glm::vec3 random_color()
{
    int x1,x2,x3;
    float x,y,z;
    x1 = rand() % 100;
    x2 = rand() % 100;
    x3 = rand() % 100;

    x = x1 / 100.0f;
    y = x2 / 100.0f;
    z = x3 / 100.0f;
    return glm::vec3(x,y,z);
}
void Block::make_triangle(std::vector<glm::vec3> corners, glm::vec3 color, std::array<int,3> idx)
{
     //triangle 1 yey face 1 k
    vert_data.push_back(corners[idx[0]]); 
    vert_data.push_back(color);
    vert_data.push_back(corners[idx[1]]); 
    vert_data.push_back(color);
    vert_data.push_back(corners[idx[2]]);
    vert_data.push_back(color);

}
Block::Block(glm::vec3 origin)
{
    float x = origin.x;
    float y = origin.y;
    float z = origin.z;
    
    std::vector<glm::vec3> corners;
    corners.push_back(glm::vec3(x + 0.5f,y + 0.5f,z + 0.5f)); //+++ 0
    corners.push_back(glm::vec3(x + 0.5f,y + 0.5f,z - 0.5f)); //++- 1
    corners.push_back(glm::vec3(x + 0.5f,y - 0.5f,z - 0.5f)); //+-- 2
    corners.push_back(glm::vec3(x - 0.5f,y - 0.5f,z - 0.5f)); //--- 3 
    corners.push_back(glm::vec3(x - 0.5f,y - 0.5f,z + 0.5f)); //--+ 4
    corners.push_back(glm::vec3(x + 0.5f,y - 0.5f,z + 0.5f)); //+-+ 5 
    corners.push_back(glm::vec3(x - 0.5f,y + 0.5f,z - 0.5f)); //-+- 6
    corners.push_back(glm::vec3(x - 0.5f,y + 0.5f,z + 0.5f)); //-++ 7

    glm::vec3 color = random_color();

    make_triangle(corners,color,std::array<int,3> {3,2,1});
    make_triangle(corners,color,std::array<int,3> {1,6,3});

    make_triangle(corners,color,std::array<int,3> {4,5,0});
    make_triangle(corners,color,std::array<int,3> {0,7,4});
  
    make_triangle(corners,color,std::array<int,3> {7,6,3});
    make_triangle(corners,color,std::array<int,3>{3,4,7});

    make_triangle(corners,color,std::array<int,3> {0,1,2});
    make_triangle(corners,color,std::array<int,3> {2,5,0});

    make_triangle(corners,color,std::array<int,3> {3,2,5});
    make_triangle(corners,color,std::array<int,3> {5,4,3});

    make_triangle(corners,color,std::array<int,3> {6,1,0});
    make_triangle(corners,color,std::array<int,3> {0,7,6});


}

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

Camera::Camera() 
{
    cameraPos = glm::vec3(0.0f, 0.0f, 0.0f);
    cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
    view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
}

void Camera::handle_input()
{
    float yaw = 0;
    float pitch;
    float lastX = 0;
    float lastY = 0;
    float xpos = 0;
    float ypos = 0;

    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
            cameraPos += 0.01f * cameraFront;
            //cameraPos -= cameraUp * 0.0001f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
            cameraPos -= 0.01f * cameraFront;
            // cameraPos += cameraUp * 0.0001f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * 0.01f;

    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) *0.01f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        cameraPos += cameraUp * 0.01f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
    {
        cameraPos += cameraUp * -0.01f;
    }
    view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

    //camera
    xpos = sf::Mouse::getPosition().x;
    ypos = sf::Mouse::getPosition().y;

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    float sensitivity = 0.1;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw  += xoffset;
    pitch += yoffset;

    if(pitch > 89.0f)
        pitch = 89.0f;
    if(pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(direction);
}

void Camera::upload_uniform()
{
    Shader sh;
    GLint viewLocation = glGetUniformLocation(sh.shaderProgram, "view"); //get the shader mat4
    glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(view));//set the mat4 to our modified one

    GLint projLocation = glGetUniformLocation(sh.shaderProgram, "proj"); //get the shader mat4
    glm::mat4 projection = glm::perspective(glm::radians(90.0f), 1200.0f / 700.0f, 0.1f, 1000.0f);
    glUniformMatrix4fv(projLocation, 1, GL_FALSE, glm::value_ptr(projection));//set the mat4 to our modified one
}

Shader::Shader()
{
    {
        shaderProgram = glCreateProgram();
        //this could use file management
        const GLchar* vertexSource = R"glsl(
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
        )glsl";
        const GLchar* fragmentSource = R"glsl(
            #version 330 core
            in vec3 Color;
            out vec4 outColor;
            void main()
            {
                outColor = vec4(Color, 1.0);
            }
        )glsl";

        // Create and compile the vertex shader
        GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertexSource, NULL);
        glCompileShader(vertexShader);

        // Create and compile the fragment shader
        GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
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