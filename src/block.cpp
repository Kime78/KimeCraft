#include "block.hpp"
#include <array>

glm::vec3 random_color() {
  int x1, x2, x3;
  float x, y, z;
  x1 = rand() % 100;
  x2 = rand() % 100;
  x3 = rand() % 100;

  x = x1 / 100.0f;
  y = x2 / 100.0f;
  z = x3 / 100.0f;
  return glm::vec3(x, y, z);
}

void Block::make_triangle(std::vector<glm::vec3> corners, glm::vec3 color,
                          std::array<int, 3> idx) {
  // triangle 1 yey face 1 k
  vert_data.push_back(corners[idx[0]]);
  vert_data.push_back(color);
  vert_data.push_back(corners[idx[1]]);
  vert_data.push_back(color);
  vert_data.push_back(corners[idx[2]]);
  vert_data.push_back(color);
}
Block::Block(glm::vec3 origin) {
  float x = origin.x;
  float y = origin.y;
  float z = origin.z;

  std::vector<glm::vec3> corners;
  corners.push_back(glm::vec3(x + 0.5f, y + 0.5f, z + 0.5f)); //+++ 0
  corners.push_back(glm::vec3(x + 0.5f, y + 0.5f, z - 0.5f)); //++- 1
  corners.push_back(glm::vec3(x + 0.5f, y - 0.5f, z - 0.5f)); //+-- 2
  corners.push_back(glm::vec3(x - 0.5f, y - 0.5f, z - 0.5f)); //--- 3
  corners.push_back(glm::vec3(x - 0.5f, y - 0.5f, z + 0.5f)); //--+ 4
  corners.push_back(glm::vec3(x + 0.5f, y - 0.5f, z + 0.5f)); //+-+ 5
  corners.push_back(glm::vec3(x - 0.5f, y + 0.5f, z - 0.5f)); //-+- 6
  corners.push_back(glm::vec3(x - 0.5f, y + 0.5f, z + 0.5f)); //-++ 7

  glm::vec3 color = random_color();

  make_triangle(corners, color, std::array<int, 3>{3, 2, 1});
  make_triangle(corners, color, std::array<int, 3>{1, 6, 3});

  make_triangle(corners, color, std::array<int, 3>{4, 5, 0});
  make_triangle(corners, color, std::array<int, 3>{0, 7, 4});

  make_triangle(corners, color, std::array<int, 3>{7, 6, 3});
  make_triangle(corners, color, std::array<int, 3>{3, 4, 7});

  make_triangle(corners, color, std::array<int, 3>{0, 1, 2});
  make_triangle(corners, color, std::array<int, 3>{2, 5, 0});

  make_triangle(corners, color, std::array<int, 3>{3, 2, 5});
  make_triangle(corners, color, std::array<int, 3>{5, 4, 3});

  make_triangle(corners, color, std::array<int, 3>{6, 1, 0});
  make_triangle(corners, color, std::array<int, 3>{0, 7, 6});
}