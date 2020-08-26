#pragma once

#include "block.hpp"

class IRenderable {
public:
  virtual void render() = 0;
  virtual ~IRenderable() noexcept = default;
  IRenderable() = default;
};

class Chunk : public IRenderable {
public:
  std::vector<glm::vec3> mesh;
  Chunk() = default;
  virtual ~Chunk() = default;
  std::vector<Block> blocks;
  void bind_mesh();
  void generate_mesh();
  void render() override;
};