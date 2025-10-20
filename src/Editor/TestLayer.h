#pragma once

#include <imgui.h>
#include <src/Camera/Camera.h>
#include <src/Camera/CameraController.h>
#include <src/Layers/Layer.h>
#include <src/Renderer/Shader.h>
#include <src/Renderer/VertexArray.h>
#include <src/SOUP_pch.h>

namespace SOUP {
  class Test : public Layer {
  public:
    Test() : Layer(50), m_camera(CameraType::Orthographic), m_cameraController(m_camera) {}
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
    CameraController m_cameraController;

    glm::vec3 m_cameraPosition;
  };
} // namespace SOUP