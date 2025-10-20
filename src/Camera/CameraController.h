#pragma once

#include <src/Camera/Camera.h>
#include <Core/DeltaTime.h>
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

    void setWorldBounds(float left, float right, float bottom, float top);
    void enableWorldBounds(bool enabled);

  private:
    void updateCameraProjection();
    void clampCameraToWorld();
    void getViewDimensions(float &outWidth, float &outHeight) const;

    Camera &m_camera;
    float m_aspectRatio;
    float m_zoomLevel = 1.0f;

    glm::vec3 m_cameraPosition = {0.0f, 0.0f, 0.0f};

    bool m_worldBoundsEnabled = false;
    float m_worldLeft         = -10.0f;
    float m_worldRight        = 10.0f;
    float m_worldBottom       = -5.625f;
    float m_worldTop          = 5.625f;

    float m_worldWidth       = 20.0f;
    float m_worldHeight      = 11.25f;
    float m_worldAspectRatio = 16.0f / 9.0f;
  };
} // namespace SOUP