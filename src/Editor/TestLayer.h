#pragma once

#include "Renderer/Shader.h"
#include "Renderer/VertexArray.h"
#include <src/SOUP_pch.h>

#include <imgui.h>
#include <src/Layers/Layer.h>
#include <src/Camera.h>

namespace SOUP {
  class Test : public Layer {
  public:
    Test() : Layer(50), m_camera(CameraType::Orthographic) {}
    ~Test() = default;
    void onAttach() override;
    void onDetach() override;
    void onUpdate(DeltaTime deltaTime) override;
    bool onEvent(const Event &event) override;

    void begin();
    void end();

  private:
    std::shared_ptr<VertexArray> vao;
    std::shared_ptr<Shader> shader;
    Camera m_camera;

    glm::vec3 m_cameraPosition;
  };
} // namespace SOUP