#pragma once

#include "Renderer/Shader.h"
#include "Renderer/VertexArray.h"
#include <src/SOUP_pch.h>

#include <imgui.h>
#include <src/Layers/Layer.h>

namespace SOUP {
  class GUI : public Layer {
  public:
    GUI() : Layer(100) {}
    ~GUI() = default;
    void onAttach() override;
    void onDetach() override;
    void onUpdate(DeltaTime deltaTime) override;
    bool onEvent(const Event &event) override;

    void begin();
    void end();

  private:
    std::shared_ptr<VertexArray> vao;
    std::shared_ptr<Shader> shader;
  };
} // namespace SOUP