#include "ParticleTestLayer.h"
#include <glm/gtc/random.hpp>
#include <src/Renderer/RenderCommand.h>
#include <src/Renderer/Renderer.h>

namespace SOUP {
  void ParticleTestLayer::onAttach() {
    //glEnable(GL_BLEND);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    m_camera.setPosition({0.0f, 0.0f, 0.0f});
    m_camera.setOrthographic(-10.0f, 10.0f, -5.625f, 5.625f);

    m_ps = std::make_unique<ParticleSystem>(2000);
  }

  void ParticleTestLayer::onUpdate(DeltaTime dt) {
    m_cameraController.onUpdate(dt);
    RenderCommand::setClearColour({0.1f, 0.1f, 0.1f, 1.0f});
    RenderCommand::clear();

    m_emitAccumulator += dt.seconds();
    while (m_emitAccumulator > 0.016f) {
      ParticleProps p;
      p.position = {0.0f, 0.0f};
      // crude RNG for velocity
      p.velocity   = {(float)(((rand() % 400) / 100.0) - 2.0), (float)(((rand() % 300) / 100.0) + 2.0)};
      p.lifeTime   = 3.0f;
      p.sizeBegin  = 5.0f;
      p.sizeEnd    = 0.0f;
      p.colorBegin = {1.0f, 0.7f, 0.3f, 1.0f};
      p.colorEnd   = {1.0f, 0.2f, 0.0f, 0.0f};
      m_ps->emit(p);
      m_emitAccumulator -= 0.016f;
    }

    m_ps->update(dt);
    m_ps->upload();

    Renderer::beginScene(m_camera);
    Renderer::submit(m_ps->shader(), m_ps->vao());
    Renderer::endScene();
  }

  bool ParticleTestLayer::onEvent(const Event &e) {
    m_cameraController.onEvent(e);
    return false;
  }
} // namespace SOUP