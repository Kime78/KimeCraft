#pragma once

#include <array>
#include <glm/glm.hpp>
#include <vector>

struct Block
{
	Block(glm::vec3 origin);
	std::vector<glm::vec3> vert_data;

private:
	void make_triangle(std::vector<glm::vec3> corners, glm::vec3 color, glm::vec3 normal, std::array<int, 3> idx);
};