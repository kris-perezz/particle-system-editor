#pragma once

#include "DeltaTime.h"
#include <src/Camera.h>
#include <src/Events/Event.h>
#include <src/Inputs/Input.h>
#include <src/SOUP_pch.h>

namespace SOUP {
  class CameraController {
  public:
    CameraController(Camera &camera);
    void onUpdate(DeltaTime deltaTime);
    bool onEvent(const Event &event);

    bool onMouseScrolled(const Event &event);
    bool onWindowResize(const Event &event);

  private:
    Camera &m_camera;
    float m_aspectRatio;
    float m_zoomLevel = 1.0f;

    glm::vec3 m_cameraPosition = {0.0f, 0.0f, 0.0f};

  };
} // namespace SOUP