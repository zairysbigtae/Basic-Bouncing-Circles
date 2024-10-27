cmake_minimum_required(VERSION 3.10)
project(CameraTrackingCircle)

include(FetchContent)

set(RAYLIB_VERSION 5.0.0)

FetchContent_Declare(
  raylib
  URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
  FIND_PACKAGE_ARGS ${RAYLIB_VERSION}
)

set(BUILD_EXAMPLES OFF CACHE INTERNAL "")
FetchContent_MakeAvailable(raylib)

add_executable(${PROJECT_NAME} main.cc)
target_link_libraries(${PROJECT_NAME} raylib)

if(APPLE)
    message(STATUS "Building for macOS")

    find_package(raylib REQUIRED)
    target_link_libraries(${PROJECT_NAME} raylib)
endif()