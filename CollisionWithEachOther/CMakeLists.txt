cmake_minimum_required(VERSION 3.24)
project(BouncingBallsWithCollisionOnEachOther)

include(FetchContent)

set(RAYLIB_VERSION 5.0.0)
FetchContent_Declare(
  raylib
  URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
  FIND_PACKAGE_ARGS ${RAYLIB_VERSION}
)

set(BUILD_EXAMPLES OFF CACHE INTERNAL "")
FetchContent_MakeAvailable(raylib)

set(SOURCE_FILES main.cc)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} raylib)

if(APPLE)
    message(STATUS "Building for macOS")

    find_package(raylib REQUIRED)
    target_link_libraries(${PROJECT_NAME} raylib)
endif()

if (EMSCRIPTEN)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -s USE_GLFW=3 -s ASSERTIONS=1 -s WASM=1 -s ASYNCIFY -s GL_ENABLE_GET_PROC_ADDRESS=1")
    set(CMAKE_EXECUTABLE_SUFFIX ".html") # This line is used to set your executable to build with the emscripten html template so that you can directly open it.
endif ()