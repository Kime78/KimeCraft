#pragma once

#include <vector>
#include <array>
#include <glm.hpp>

struct Block 
{
    Block(glm::vec3 origin);
    std::vector<glm::vec3> vert_data;
private:
    void make_triangle(std::vector<glm::vec3> corners, glm::vec3 color, std::array<int,3> idx);    
};