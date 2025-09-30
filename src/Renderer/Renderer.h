#pragma once

#include <src/SOUP_pch.h>
#include <src/Renderer/VertexArray.h>

namespace SOUP {
class Renderer {
public:
  virtual void setClearColour(const glm::vec4 &colour);
  virtual void clear();
  virtual void drawIndexed(const std::shared_ptr<VertexArray> &vertexArray);
};
} // namespace SOUP