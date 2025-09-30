#include <src/Renderer/VertexArray.h>

namespace SOUP {
static GLenum ShaderDataTypeToBaseType(ShaderDataType type) {
  switch (type) {
  case ShaderDataType::Float:
    return GL_FLOAT;
  case ShaderDataType::Float2:
    return GL_FLOAT;
  case ShaderDataType::Float3:
    return GL_FLOAT;
  case ShaderDataType::Float4:
    return GL_FLOAT;
  case ShaderDataType::Mat3:
    return GL_FLOAT;
  case ShaderDataType::Mat4:
    return GL_FLOAT;
  case ShaderDataType::Int:
    return GL_INT;
  case ShaderDataType::Int2:
    return GL_INT;
  case ShaderDataType::Int3:
    return GL_INT;
  case ShaderDataType::Int4:
    return GL_INT;
  case ShaderDataType::Bool:
    return GL_BOOL;
  }

  return 0;
}

VertexArray::VertexArray() { glCreateVertexArrays(1, &m_rendererID); }

VertexArray::~VertexArray() { glDeleteVertexArrays(1, &m_rendererID); }

void VertexArray::bind() const { glBindVertexArray(m_rendererID); }
void VertexArray::unbind() const { glBindVertexArray(0); }
void VertexArray::addVertexBuffer(const std::shared_ptr<VertexBuffer> &vertexBuffer) {
  glBindVertexArray(m_rendererID);
  vertexBuffer->bind();

  uint32_t index = 0;

  const auto &layout = vertexBuffer->getLayout();
  for (const auto &element : layout) {
    glEnableVertexAttribArray(index);
    glVertexAttribPointer(index, 
                          element.GetComponentCount(), 
                          ShaderDataTypeToBaseType(element.type),
                          element.isNormalized ? GL_TRUE : GL_FALSE, 
                          layout.getStride(), 
                          (const void *)element.offset);
                          
    LOG_INFO("index:{}, component count: {}, type:{}, normalized;{}, stride:{}, offset:{}",
             index, element.GetComponentCount(), ShaderDataTypeToBaseType(element.type), element.isNormalized,
             layout.getStride(), (const void *)element.offset);
    index++;
  }
  m_vertexBuffers.push_back(vertexBuffer);
}
void VertexArray::setIndexBuffer(const std::shared_ptr<IndexBuffer> &indexBuffer) {
  glBindVertexArray(m_rendererID);
  indexBuffer->bind();
  m_indexBuffer = indexBuffer;
}

} // namespace SOUP