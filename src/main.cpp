#include <src/SOUP_pch.h>

#include "Application.h"
#include <src/Events/Event.h>
#include <src/Renderer/Buffer.h>
#include <src/Renderer/Renderer.h>
#include <src/Renderer/Shader.h>
#include <src/Renderer/VertexArray.h>
#include <src/Window.h>
#include <type_traits>

int main(int argc, char **argv) {

  static_assert(std::is_trivially_copyable_v<SOUP::Event>);
  static_assert(std::is_trivially_copyable_v<SOUP::EventHeader>);
  static_assert(std::is_trivially_copyable_v<SOUP::WindowResize>);
  static_assert(std::is_trivially_copyable_v<SOUP::WindowMoved>);
  static_assert(std::is_trivially_copyable_v<SOUP::KeyPayload>);
  static_assert(std::is_trivially_copyable_v<SOUP::MouseMovePayload>);
  static_assert(std::is_trivially_copyable_v<SOUP::MouseButtonPayload>);
  static_assert(std::is_trivially_copyable_v<SOUP::MouseWheelPayload>);
  static_assert(std::is_trivially_copyable_v<SOUP::TextInputPayload>);


  auto *app = new SOUP::Application;
  app->run();

  return 0;
}
