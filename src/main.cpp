#include <src/SOUP_pch.h>

#include <src/Renderer/Buffer.h>
#include <src/Renderer/Renderer.h>
#include <src/Renderer/Shader.h>
#include <src/Renderer/VertexArray.h>
#include <src/Window.h>

int main(int argc, char **argv) {

  SOUP::Log::init();
  std::cout << "Cout works?" << std::endl;
  LOG_INFO("Logger works?");

  SOUP::WindowProperties properties = {};

  LOG_INFO("adding new Window");
  auto window = std::make_unique<SOUP::Window>(properties);

  float vertices[] = {
      -0.5f, -0.5f, 0.0f, 1.f, 0.f, 0.f, 
      0.5f, -0.5f, 0.0f, 0.f, 1.f, 0.f, 
      0.0f, 0.5f, 0.0f, 0.f, 0.f, 1.f,
  };
  uint32_t indices[] = {0, 1, 2};

  auto vao = std::make_shared<SOUP::VertexArray>();

  auto vbo = std::make_shared<SOUP::VertexBuffer>(vertices, sizeof(vertices));
  SOUP::BufferLayout layout = {
      {SOUP::ShaderDataType::Float3, "a_Position"},
      {SOUP::ShaderDataType::Float3, "a_Color"   }
  };
  
  vbo->setLayout(layout);
  vao->addVertexBuffer(vbo);

  auto ibo = std::make_shared<SOUP::IndexBuffer>(indices, 3);
  vao->setIndexBuffer(ibo);

  const char *base = SDL_GetBasePath();
  std::string vPath = std::string(base) + "data/basic.vert";
  std::string fPath = std::string(base) + "data/basic.frag";

  SOUP::Shader shader(vPath.c_str(), fPath.c_str());

  SOUP::Renderer renderer;

  bool running = true;
  SDL_Event event;
  while (running) {
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_EVENT_QUIT) {
        running = false;
      }
    }

    renderer.setClearColour({0.1f, 0.1f, 0.1f, 1.0f});
    renderer.clear();

    shader.bind();
    vao->bind();
    renderer.drawIndexed(vao);

    window->onUpdate();
  }
  return 0;
}
