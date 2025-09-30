cmake_minimum_required(VERSION 3.24)

project(SOUP VERSION 1.0)

include(FetchContent)

cmake_policy(SET CMP0072 NEW)

set(SOUP_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)



option(SDL_VENDORED "Build SDL3 from source" OFF)

if(SDL_VENDORED)
  set(SDL_SHARED OFF CACHE BOOL "" FORCE)
  set(SDL_STATIC ON CACHE BOOL "" FORCE)

  FetchContent_Declare(
      SDL3
      GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
      GIT_TAG release-3.2.22
      OVERRIDE_FIND_PACKAGE
  )
  FetchContent_MakeAvailable(SDL3)
else()
  find_package(SDL3 CONFIG REQUIRED COMPONENTS SDL3-shared)
endif()

FetchContent_Declare(
  glm
  GIT_REPOSITORY https://github.com/g-truc/glm.git
  GIT_TAG 1.0.1
)
FetchContent_MakeAvailable(glm)

find_package(OpenGL REQUIRED)

set(SOUP_HEADER 
    src/Shader.h
    src/Application.h
    src/GUI.h
    src/Renderer.h
    src/Style.h
    src/Window.h)


set(SOUP_SOURCE
    src/Shader.cpp
    src/Application.cpp
    src/GUI.cpp
    src/Renderer.cpp
    src/Style.cpp
    src/GUICommands.cpp
    src/Window.cpp)

add_subdirectory(include/glad)
add_subdirectory(include/imgui)
add_subdirectory(include/stb)
add_subdirectory(include/ImGuiFileDialog)
add_subdirectory(include/dirent)

add_library(SOUP_Engine ${SOUP_SOURCE} ${SOUP_HEADER})
target_precompile_headers(SOUP_Engine PRIVATE src/SOUP_pch.h)

target_include_directories(
  SOUP_Engine 
  PUBLIC ${SOUP_ROOT_PATH}/src
  PUBLIC ${SOUP_ROOT_PATH}/include)

target_link_libraries(
  SOUP_Engine 
  glad
  glm::glm
  imgui
  ImGuiFileDialog
  stb
  dirent
  SDL3::SDL3
  OpenGL::GL)

add_executable(SOUP src/main.cpp)

target_link_libraries(SOUP PRIVATE SOUP_Engine)

if (WIN32)
  set_target_properties(SOUP PROPERTIES WIN32_EXECUTABLE TRUE)

    target_link_options(SOUP PRIVATE /ENTRY:mainCRTStartup)

endif()
