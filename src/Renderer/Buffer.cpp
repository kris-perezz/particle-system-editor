#include <src/Renderer/Buffer.h>

namespace SOUP {
  // Vertex Buffer
  VertexBuffer::VertexBuffer(float *vertices, uint32_t size) {
    glCreateBuffers(1, &m_rendererID);
    glBindBuffer(GL_ARRAY_BUFFER, m_rendererID);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
  }

  VertexBuffer::~VertexBuffer() { glDeleteBuffers(1, &m_rendererID); }

  void VertexBuffer::bind() const { glBindBuffer(GL_ARRAY_BUFFER, m_rendererID); }
  void VertexBuffer::unbind() const { glBindBuffer(GL_ARRAY_BUFFER, 0); }

  void VertexBuffer::setData(const void *data, uint32_t size) {
    glBindBuffer(GL_ARRAY_BUFFER, m_rendererID);
    glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
  }

  // Index Buffer
  IndexBuffer::IndexBuffer(uint32_t *indices, uint32_t count) : m_count(count) {
    glCreateBuffers(1, &m_rendererID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
  }

  IndexBuffer::~IndexBuffer() { glDeleteBuffers(1, &m_rendererID); }

  void IndexBuffer::bind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererID); }
  void IndexBuffer::unbind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }

  uint32_t IndexBuffer::getCount() const { return m_count; }

  void IndexBuffer::setCount(uint32_t count) {
    m_count = count;
  }
} // namespace SOUP