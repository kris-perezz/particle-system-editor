cmake_minimum_required(VERSION 4.1.1)

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
  GIT_TAG f7485100cb16498f202f64d21b567c3788efa234
)
FetchContent_MakeAvailable(glm)

FetchContent_Declare(
  spdlog
  GIT_REPOSITORY https://github.com/gabime/spdlog.git
  GIT_TAG v1.15.3
)
FetchContent_MakeAvailable(spdlog)


find_package(OpenGL REQUIRED)


set(SOUP_HEADER 
    src/Renderer/Buffer.h
    src/Renderer/Renderer.h
    src/Renderer/Shader.h
    src/Renderer/VertexArray.h
    src/Layers/Layer.h
    src/Layers/LayerList.h
    src/Application.h
    src/Events/Event.h
    src/Events/EventBuffer.h
    src/Events/Events.h
    src/GUI.h
    src/Style.h
    src/Window.h
    src/Log.h
    src/Timer.h
    src/DeltaTime.h
    src/EngineTime.h)


set(SOUP_SOURCE
    src/Renderer/Buffer.cpp
    src/Renderer/Renderer.cpp
    src/Renderer/Shader.cpp
    src/Renderer/VertexArray.cpp
    src/Layers/Layer.cpp
    src/Layers/LayerList.cpp
    src/Events/Event.cpp
    src/Events/EventBuffer.cpp
    src/Events/Events.cpp
    src/Application.cpp
    src/GUI.cpp
    src/Style.cpp
    src/Window.cpp
    src/Log.cpp)

add_subdirectory(include/glad)
add_subdirectory(include/imgui)
add_subdirectory(include/stb)
add_subdirectory(include/ImGuiFileDialog)
add_subdirectory(include/dirent)

add_library(SOUP_Engine ${SOUP_SOURCE} ${SOUP_HEADER})
target_precompile_headers(SOUP_Engine PRIVATE src/SOUP_pch.h)

target_include_directories(
  SOUP_Engine 
  PUBLIC ${SOUP_ROOT_PATH}
  PUBLIC ${SOUP_ROOT_PATH}/src
  PUBLIC ${SOUP_ROOT_PATH}/include)

target_link_libraries(
  SOUP_Engine 
  glad
  glm::glm
  spdlog::spdlog_header_only
  imgui
  ImGuiFileDialog
  stb
  dirent
  SDL3::SDL3
  OpenGL::GL)

add_executable(SOUP src/main.cpp)

target_link_libraries(SOUP PRIVATE SOUP_Engine)

if (WIN32)
  add_custom_command(TARGET SOUP POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
      "$<TARGET_FILE:SDL3::SDL3>"
      $<TARGET_FILE_DIR:SOUP>)

  add_custom_command(TARGET SOUP POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
      "${CMAKE_SOURCE_DIR}/data"
      "$<TARGET_FILE_DIR:SOUP>/data")
else() # linux
  set(RUN_DATA_DIR ${CMAKE_BINARY_DIR}/data)
  execute_process(COMMAND ${CMAKE_COMMAND} -E rm -rf "${RUN_DATA_DIR}")
  execute_process(COMMAND ${CMAKE_COMMAND} -E create_symlink
                          "${CMAKE_SOURCE_DIR}/data" "${RUN_DATA_DIR}")
  target_include_directories(SOUP_Engine PUBLIC "${RUN_DATA_DIR}")
endif()


# SECTION FOR CLANGD COMPATIBILITY BECAUSE ITS SO USEFUL BUT SO DAMN FUSSY

set(PREFIX_HEADER "${CMAKE_SOURCE_DIR}/src/SOUP_pch.h")
set(CLANG_PCH_OUTPUT "${CMAKE_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/SOUP_Engine.dir/cmake_pch.hxx.pch")

# collect include directories from SOUP_Engine target
get_target_property(_inc_dirs SOUP_Engine INCLUDE_DIRECTORIES)

# add include paths for subprojects that don't propagate automatically
list(APPEND _inc_dirs
  "${CMAKE_SOURCE_DIR}/include/glad/include"
  "${CMAKE_SOURCE_DIR}/include/imgui"
  "${CMAKE_SOURCE_DIR}/include/ImGuiFileDialog"
  "${CMAKE_SOURCE_DIR}/include/stb"
  "${CMAKE_SOURCE_DIR}/include/dirent"
  "${CMAKE_BINARY_DIR}/data"
)

# flatten into -I flags
set(_clang_includes "")
foreach(dir ${_inc_dirs})
  list(APPEND _clang_includes -I${dir})
endforeach()

# create fake Clang-compatible PCH
add_custom_command(
  OUTPUT "${CLANG_PCH_OUTPUT}"
  COMMAND clang++ -std=c++23
          -x c++-header
          ${_clang_includes}
          ${PREFIX_HEADER}
          -Xclang -emit-pch
          -o ${CLANG_PCH_OUTPUT}
  COMMENT "Creating Clang precompiled header for clangd/clang-tidy."
)

add_custom_target(clang-pch ALL DEPENDS ${CLANG_PCH_OUTPUT})
add_dependencies(SOUP_Engine clang-pch)
