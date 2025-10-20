#pragma once
#define GLM_ENABLE_EXPERIMENTAL
#include "Camera.h"
#include "DeltaTime.h"
#include "Renderer/Shader.h"
#include "Renderer/VertexArray.h"
#include "glm/gtc/random.hpp"
#include <cstdint>
#include <glm/gtx/rotate_vector.hpp>
#include <src/SOUP_pch.h>

namespace SOUP {
  typedef struct Particles {
    std::vector<glm::vec2> positions;
    std::vector<glm::vec2> velocities;
    std::vector<glm::vec2> sizeBegin;
    std::vector<glm::vec2> sizeEnd;
    std::vector<glm::vec4> colourBegin;
    std::vector<glm::vec4> colourEnd;
    std::vector<float> lifeRemaining;
    std::vector<float> lifeTime;
    std::vector<bool> active;
  } Particles;

  struct ParticleProps {
    glm::vec2 position{0};
    glm::vec2 velocity{0};
    float lifeTime{1.0f};
    glm::vec2 sizeBegin{1.0f, 1.0f};
    glm::vec2 sizeEnd{0};
    glm::vec4 colourBegin{1.0f, 1.0f, 1.0f, 1.0f};
    glm::vec4 colourEnd{1.0f, 1.0f, 1.0f, 0};
  };

  struct QuadVertex {
    glm::vec2 pos;
    glm::vec4 colour;
  };

  struct VelocityRandomizer {
    float coneDeg     = 1.0f;
    float speedMinMul = 0.5f;
    float speedMaxMul = 1.5f;
    float noiseSigma  = 1.0f;
  };

  inline glm::vec2 sampleVelocityFromBase(glm::vec2 baseVelocity, const VelocityRandomizer &vRand) {
    float baseSpeed     = glm::length(baseVelocity);
    glm::vec2 direction = (baseSpeed > 0) ? baseVelocity / baseSpeed : glm::vec2{0, 1};

    float theta = glm::radians(glm::linearRand(-vRand.coneDeg, vRand.coneDeg));
    direction   = glm::rotate(direction, theta);

    float k     = glm::linearRand(vRand.speedMinMul, vRand.speedMaxMul);
    float speed = baseSpeed * k;

    glm::vec2 noise{glm::linearRand(-vRand.noiseSigma, vRand.noiseSigma),
                    glm::linearRand(-vRand.noiseSigma, vRand.noiseSigma)};
    return direction * speed + noise;
  }

  struct ParticleEmitter {
    glm::vec2 pos{0, 0};
    glm::vec2 size{1.0f, 1.0f};
    glm::vec4 colour{1.0f, 1.0f, 1.0f, 1.0f};
    VelocityRandomizer vRand{};

    ParticleProps props;
    int spawnRate         = 30;
    float emitAccumulator = 0;

    ParticleEmitter(const glm::vec2 &position = {0, 0},
                    const glm::vec2 &sz       = {1, 1},
                    const glm::vec4 &col      = {1, 1, 1, 1})
        : pos(position), size(sz), colour(col) {
      props.colourBegin = col;
      props.position    = position;
      props.sizeBegin   = sz;
    }
  };

  class ParticleSystem {
  public:
    explicit ParticleSystem(size_t maxParticles = 1000);

    void emit(const ParticleProps &props);

    void update(DeltaTime deltaTime);

    void upload();
    void clear();

    const std::shared_ptr<VertexArray> &vao() const { return m_vao; }
    std::shared_ptr<Shader> &shader() { return m_shader; }

    size_t capacity() const { return m_max; }

    void updateEmitter(ParticleEmitter &emitter, DeltaTime deltaTime);
    void updateEmitters(std::vector<ParticleEmitter> &emitters, DeltaTime deltaTime);

    int32_t aliveCount() const { return m_alive; }

  private:
    size_t m_max{0};
    int32_t m_alive{0};

    Particles m_particles;

    size_t m_poolIndex{0};             // ring index

    std::vector<QuadVertex> m_cpuQuad; // size = m_max * 4

    std::shared_ptr<VertexArray> m_vao;
    std::shared_ptr<VertexBuffer> m_vbo; // dynamic, max*4 vertices
    std::shared_ptr<IndexBuffer> m_ibo;  // static, max*6 indices
    std::shared_ptr<Shader> m_shader;
  };
} // namespace SOUP