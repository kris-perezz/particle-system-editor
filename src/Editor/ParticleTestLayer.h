#pragma once

#include "Camera.h"
#include "CameraController.h"
#include "Editor/ParticleSystem.h"
#include "Layers/Layer.h"
#include <src/SOUP_pch.h>

namespace SOUP {
  class ParticleTestLayer : public Layer {
  public:
    ParticleTestLayer()
        : Layer(50), m_camera(CameraType::Orthographic), m_cameraController(m_camera) {}

    void onAttach() override;
    void onUpdate(DeltaTime dt) override;
    bool onEvent(const Event &e) override;

  private:
    Camera m_camera;
    CameraController m_cameraController;
    std::unique_ptr<ParticleSystem> m_ps;
    float m_emitAccumulator{0.0f};
  };
} // namespace SOUP