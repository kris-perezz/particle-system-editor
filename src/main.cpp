#include <src/SOUP_pch.h>

#include <src/Renderer/Buffer.h>
#include <src/Renderer/Renderer.h>
#include <src/Renderer/Shader.h>
#include <src/Renderer/VertexArray.h>

int main(int argc, char **argv) {

  SOUP::Log::init();
  std::cout << "Cout works?" << std::endl;
  LOG_INFO("Logger works?");

  if (!SDL_Init(SDL_INIT_VIDEO)) {
    LOG_ERROR("Failed to init SDL3: {}", SDL_GetError());
    return -1;
  }

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

  LOG_INFO("Creating window");
  SDL_Window *window = SDL_CreateWindow("SOUP Renderer Test", 1280, 720, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

  if (!window) {
    LOG_INFO("Failed to create SDL3 window: {}", SDL_GetError());
    throw std::runtime_error(std::string("Error: SDL_CreateWindow(): ") + SDL_GetError());
    return -1;
  }

  LOG_INFO("Creating context");
  SDL_GLContext glContext = SDL_GL_CreateContext(window);
  LOG_INFO("Context created");
  if (!glContext) {
    LOG_INFO("Failed to create OpenGL context: {}", SDL_GetError());
    throw std::runtime_error(std::string("Error: SDL_GL_CreateContext(): ") + SDL_GetError());
    return -1;
  }

  LOG_INFO("Loading GLAD");
  if (!gladLoadGL((GLADloadfunc)SDL_GL_GetProcAddress)) {
    LOG_ERROR("gladLoadGL failed");
    throw std::runtime_error("Error: gladLoadGL failed");
  }
  LOG_INFO("OpenGL context initialized");

  int w, h;
  SDL_GetWindowSize(window, &w, &h);
  glViewport(0, 0, w, h);

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

    SDL_GL_SwapWindow(window);
  }

  SDL_GL_DestroyContext(glContext);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}