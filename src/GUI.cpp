
#include <src/Application.h>
#include <src/GUI.h>

#include "Events/Event.h"

#include <SDL3/SDL_video.h>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_opengl3.h>
#include <imgui/imgui_impl_sdl3.h>
#include <imgui/imgui_internal.h>

#include <src/Camera.h>
#include <src/Style.h>

namespace SOUP {
  void GUI::onAttach() {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();

    io.IniFilename = nullptr;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.ConfigFlags |= ImGuiConfigFlags_DpiEnableScaleFonts;
    io.ConfigFlags |= ImGuiConfigFlags_DpiEnableScaleViewports;

    styleSetup();

    const char *glslVersion = "#version 430";
    Application &app        = Application::get();
    SDL_Window *window      = app.getWindow().getSDLWindow();
    SDL_GLContext context   = app.getWindow().getContext();

    ImGui_ImplSDL3_InitForOpenGL(window, context);
    ImGui_ImplOpenGL3_Init(glslVersion);
  }

  void GUI::onDetach() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();
  }

  void GUI::onUpdate(DeltaTime deltaTime) {
    //LOG_INFO("on update imgui");
    //ImGui::ShowDemoWindow(); // This will show the ImGui demo window
    //OG_INFO("show");
  }

  bool GUI::onEvent(const Event &event) { return false; }

  void GUI::begin() {
    //LOG_INFO("new frame");
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL3_NewFrame();
    ImGui::NewFrame();
    //LOG_INFO("Done begin frame");
  }

  void GUI::end() {
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    ImGuiIO &io = ImGui::GetIO();

    Application &app = Application::get();
    io.DisplaySize = ImVec2((float)app.getWindow().getWidth(), (float)app.getWindow().getHeight());

    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
      SDL_Window *backup_current_window    = SDL_GL_GetCurrentWindow();
      SDL_GLContext backup_current_context = SDL_GL_GetCurrentContext();
      ImGui::UpdatePlatformWindows();
      ImGui::RenderPlatformWindowsDefault();
      SDL_GL_MakeCurrent(backup_current_window, backup_current_context);
    }
  }
} // namespace SOUP