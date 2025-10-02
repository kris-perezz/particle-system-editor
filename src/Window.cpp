#include <src/Window.h>

namespace SOUP {
Window::Window(const WindowProperties &properties) { init(properties); }

void Window::init(const WindowProperties &properties) {
  m_windowProperties.title = properties.title;
  m_windowProperties.width = properties.width;
  m_windowProperties.height = properties.height;

  if (!SDL_Init(SDL_INIT_VIDEO)) {
    LOG_ERROR("Failed to init SDL3: {}", SDL_GetError());
  }
  
  constexpr SDL_WindowFlags flags = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE;
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
  m_window = SDL_CreateWindow(m_windowProperties.title.c_str(),
                              m_windowProperties.width,
                              m_windowProperties.height,
                              flags);

  LOG_INFO("Creating window");
  if (!m_window) {
    LOG_INFO("Failed to create SDL3 window: {}", SDL_GetError());
    throw std::runtime_error(std::string("Error: SDL_CreateWindow(): ") + SDL_GetError());
  }

  LOG_INFO("Creating context");
  m_context = SDL_GL_CreateContext(m_window);
  if (!m_context) {
    LOG_INFO("Failed to create OpenGL context: {}", SDL_GetError());
    throw std::runtime_error(std::string("Error: SDL_GL_CreateContext(): ") + SDL_GetError());
  }

  LOG_INFO("Loading GLAD");
  if (!gladLoadGL((GLADloadfunc)SDL_GL_GetProcAddress)) {
    LOG_ERROR("gladLoadGL failed");
    throw std::runtime_error("Error: gladLoadGL failed");
  }

  LOG_INFO("OpenGL context initialized");
}

Window::~Window() { shutdown(); }

void Window::shutdown() {
  SDL_GL_DestroyContext(m_context);
  SDL_DestroyWindow(m_window);
  LOG_INFO("Destroyed window");
  SDL_Quit();
  LOG_INFO("SDL Quit");
}

void Window::onUpdate() { SDL_GL_SwapWindow(m_window); }

uint32_t Window::getWidth() { return m_windowProperties.width; }

uint32_t Window::getHeight() { return m_windowProperties.height; }

bool Window::isVsyncOn() { return m_windowProperties.vsync; }

void Window::setVsync(bool on) {
  if (on) {
    m_windowProperties.vsync = true;
    SDL_GL_SetSwapInterval(1);
  } else {
    m_windowProperties.vsync = false;
    SDL_GL_SetSwapInterval(0);
  }
}

} // namespace SOUP