#include <src/Camera.h>
#include <src/Renderer/Shader.h>
#include <src/Renderer/VertexArray.h>
#include <src/SOUP_pch.h>

namespace SOUP {
  class Renderer {
  public:
    static void beginScene(Camera &camera);
    static void endScene();
    static void submit(const std::shared_ptr<Shader> &shader,
                       const std::shared_ptr<VertexArray> &vertexArray);

  private:
    struct SceneData {
      glm::mat4 ViewProjectionMatrix;
    };

    static SceneData *m_sceneData;
  };
} // namespace SOUP