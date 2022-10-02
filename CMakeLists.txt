cmake_minimum_required(VERSION 3.23)
set(CMAKE_CXX_STANDARD 20)
project(EasingFunctionsVisualizer)

## Vulkan
find_package(Vulkan REQUIRED)

## VulkanImGui, ImGui and GLFW
set(VULKAN_IMGUI_SOURCE_DIR deps/VulkanImGui)
add_subdirectory(${VULKAN_IMGUI_SOURCE_DIR} EXCLUDE_FROM_ALL)

## CoreGame and Godot
set(CoreGame_DIR /usr/local/lib)
find_package(CoreGame REQUIRED)

## Main Executable
add_executable(
        EasingFunctionsVisualizer main.cpp
        src/EasingFunctionVisualizer.cpp include/EasingFunctionVisualizer.hpp
)
set(LIBRARIES VulkanImGui CoreGame::CoreGame CoreGame::godot-cpp)
target_link_libraries(EasingFunctionsVisualizer PRIVATE ${LIBRARIES})
target_include_directories(EasingFunctionsVisualizer PRIVATE ${CMAKE_SOURCE_DIR}/include ${VULKAN_IMGUI_SOURCE_DIR})
