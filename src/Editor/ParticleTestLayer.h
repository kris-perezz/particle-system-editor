#pragma once

#include <src/Camera/Camera.h>
#include <src/Camera/CameraController.h>
#include <src/Layers/Layer.h>
#include <src/Particles/ParticleSystem.h>
#include <src/SOUP_pch.h>

namespace SOUP {
  class ParticleTestLayer : public Layer {
  public:
    ParticleTestLayer()
        : Layer(50), m_camera(CameraType::Orthographic), m_cameraController(m_camera) {}

    void onAttach() override;
    void onUpdate(DeltaTime deltaTime) override;
    bool onEvent(const Event &event) override;
    void onGUIRender() override;

  private:
    Camera m_camera;
    CameraController m_cameraController;
    std::shared_ptr<Shader> m_shader;
    int m_capacity = 1000;
    std::unique_ptr<ParticleSystem> m_particleSystem;

    float m_emitAccumulator{0.0f};
    float m_spawnRate = 60.0f;
    ParticleEmitter m_particleEmitter;

    const glm::vec2 m_worldMin{-10.0f, -5.625f};
    const glm::vec2 m_worldMax{+10.0f, +5.625f};

    float m_speed                = 3.0f;
    bool m_linkStartSize         = false;
    bool m_linkEndSize           = false;
    bool m_linkEmitterSize       = false;
    bool m_linkEmitterToParticle = true;

    bool m_startup = true;

    int m_spawnRateDummy;

    struct RunStats {
      float window_sec          = 60.0f;
      bool active               = false;
      double elapsed_sec        = 0.0;
      uint64_t frames           = 0;
      double sum_ms             = 0.0;
      float min_ms              = FLT_MAX;
      float max_ms              = 0.0f;
      uint64_t sum_alive        = 0;
      int peak_alive            = 0;
      uint32_t last_draw_calls  = 0;
      uint64_t total_draw_calls = 0;
      std::string gpu_name;
    } m_stats;

    void startProfiling(DeltaTime deltaTime);
  };
} // namespace SOUP