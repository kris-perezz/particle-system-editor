#pragma once

#include <src/SOUP_pch.h>

namespace SOUP {
class Shader {
public:
  Shader(const char *vertexPath, const char *fragmentPath);
  ~Shader();

  void bind() const;
  void unBind() const;

private:
  uint32_t m_rendererID;
};
} // namespace SOUP