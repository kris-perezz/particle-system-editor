#pragma once

#include <src/SOUP_pch.h>
#include <src/Renderer/VertexArray.h>

namespace SOUP {
class RenderCommand {
public:
  static void setClearColour(const glm::vec4 &colour);
  static void clear();
  static void drawIndexed(const std::shared_ptr<VertexArray> &vertexArray);
  static void setViewport(int width, int height);
};
} // namespace SOUP