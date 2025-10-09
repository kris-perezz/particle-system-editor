
#include <src/Application.h>
#include <src/GUI.h>

#include <src/Editor/TestLayer.h>

#include "Renderer/Buffer.h"
#include "Renderer/Renderer.h"
#include "Renderer/Shader.h"
#include <Events/Event.h>
#include <Renderer/RenderCommand.h>
#include <SDL3/SDL_video.h>

#include <src/Inputs/Input.h>

#include <src/Camera.h>
#include <src/CameraController.h>

namespace SOUP {
  void Test::onAttach() {
    m_camera.setPosition({0.0f, 0.0f, 0.0f});
    // Setup triangle geometry
    float vertices[] = {
        -0.5f,
        -0.5f,
        0.0f,
        1.f,
        0.f,
        0.f,
        0.5f,
        -0.5f,
        0.0f,
        0.f,
        1.f,
        0.f,
        0.0f,
        0.5f,
        0.0f,
        0.f,
        0.f,
        1.f,
    };
    uint32_t indices[] = {0, 1, 2};

    vao = std::make_shared<VertexArray>();

    auto vbo = std::make_shared<VertexBuffer>(vertices, sizeof(vertices));

    BufferLayout layout = {
        {ShaderDataType::Float3, "a_Position"},
        {ShaderDataType::Float3, "a_Color"   }
    };
    vbo->setLayout(layout);
    vao->addVertexBuffer(vbo);

    auto ibo = std::make_shared<IndexBuffer>(indices, 3);
    vao->setIndexBuffer(ibo);

    // Load shader
    const char *base  = SDL_GetBasePath();
    std::string vPath = std::string(base) + "data/basic.vert";
    std::string fPath = std::string(base) + "data/basic.frag";

    shader           = std::make_shared<Shader>(vPath.c_str(), fPath.c_str());
    m_cameraPosition = {0.2f, 0.2f, 0.2f};
    m_camera.setPosition(m_cameraPosition);
    m_camera.setSpeed(5.0f);

  }

  void Test::onDetach() {}

  void Test::onUpdate(DeltaTime deltaTime) {

    m_cameraController.onUpdate(deltaTime);

    RenderCommand::setClearColour({0.1f, 0.1f, 0.1f, 1.0f});
    RenderCommand::clear();

    Renderer::beginScene(m_camera);

    LOG_INFO("cleared viewport");


    // Draw triangle
    Renderer::submit(shader, vao);
    LOG_INFO("drawed Index");
  }

  bool Test::onEvent(const Event &event) { 
    m_cameraController.onEvent(event);
    return false; }

} // namespace SOUP