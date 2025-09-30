#pragma once

#include <src/SOUP_pch.h>
#include <src/Renderer/Buffer.h>

namespace SOUP {
class VertexArray {
public:
  VertexArray();
  ~VertexArray();

  void bind() const;
  void unbind() const;

  void addVertexBuffer(const std::shared_ptr<VertexBuffer> &vertexBuffer);
  void setIndexBuffer(const std::shared_ptr<IndexBuffer> &indexBuffer);

  const std::vector<std::shared_ptr<VertexBuffer>> &getVertexBuffers() const { return m_vertexBuffers; }
  const std::shared_ptr<IndexBuffer> &getIndexBuffer() const { return m_indexBuffer; }

private:
  uint32_t m_rendererID;

  std::vector<std::shared_ptr<VertexBuffer>> m_vertexBuffers;
  std::shared_ptr<IndexBuffer> m_indexBuffer;
};
}; // namespace SOUP