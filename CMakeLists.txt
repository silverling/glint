cmake_minimum_required(VERSION 3.12)

project(EventCameraViewer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# Build Metavision SDK (openeb)
include(cmake/build_metavision_sdk.cmake)

find_package(OpenCV COMPONENTS core imgproc highgui imgcodecs REQUIRED)
find_package(Vulkan REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_check_modules(GLFW REQUIRED IMPORTED_TARGET glfw3)

add_executable(viewer
    src/main.cpp
    src/engine.cpp
    src/engine_ext.cpp
    src/texture.cpp
    src/app.cpp
    src/app_cli.cpp
    src/app_utils.cpp
    src/camera_util.cpp
    vendors/imgui/imgui.cpp
    vendors/imgui/imgui_demo.cpp
    vendors/imgui/imgui_draw.cpp
    vendors/imgui/imgui_widgets.cpp
    vendors/imgui/imgui_tables.cpp
    vendors/imgui/backends/imgui_impl_glfw.cpp
    vendors/imgui/backends/imgui_impl_vulkan.cpp
)

target_include_directories(viewer PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/vendors/imgui)
target_link_libraries(viewer PkgConfig::GLFW Vulkan::Vulkan)
target_link_libraries(viewer opencv_core opencv_imgproc opencv_imgcodecs)
target_link_libraries(viewer MetavisionSDK::core MetavisionSDK::stream)
target_compile_options(viewer PRIVATE -Wall -Wextra -Wpedantic) # Enable all warnings
target_compile_definitions(viewer PRIVATE IMGUI_USE_WCHAR32) # ImGui Configs


if(CMAKE_BUILD_TYPE STREQUAL Release)
    target_compile_definitions(viewer PRIVATE NDEBUG)
endif()
