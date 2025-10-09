#include <src/Renderer/RenderCommand.h>

namespace SOUP {
void RenderCommand::setClearColour(const glm::vec4 &colour) { glClearColor(colour.r, colour.g, colour.b, colour.a); }

void RenderCommand::clear() { glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); }

void RenderCommand::drawIndexed(const std::shared_ptr<VertexArray> &vertexArray) {
  glDrawElements(GL_TRIANGLES, vertexArray->getIndexBuffer()->getCount(), GL_UNSIGNED_INT, nullptr);
}

} // namespace SOUP