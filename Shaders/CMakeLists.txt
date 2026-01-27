cmake_minimum_required(VERSION 3.15)
cmake_policy(VERSION 3.10)
project(CS_Exam_Shaders)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_compile_options(-Wall -Wpedantic)

find_package(OpenGL REQUIRED)

include(FetchContent)

FetchContent_Declare(
  glew
  GIT_REPOSITORY https://github.com/Perlmint/glew-cmake.git
  GIT_TAG glew-cmake-2.0.0)
FetchContent_MakeAvailable(glew)

FetchContent_Declare(
  glfw
  GIT_REPOSITORY https://github.com/glfw/glfw.git
  GIT_TAG 3.4)
set(GLFW_BUILD_DOCS
    OFF
    CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS
    OFF
    CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES
    OFF
    CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(glfw)

FetchContent_Declare(
  glm
  GIT_REPOSITORY https://github.com/g-truc/glm.git
  GIT_TAG 1.0.1)
FetchContent_MakeAvailable(glm)

include_directories(src)
include_directories(third_party)

file(GLOB_RECURSE SRC_FILES src/**/*.cpp)
file(GLOB IMGUI_FILES third_party/imgui/*.cpp
     third_party/imgui/backends/imgui_impl_glfw.cpp
     third_party/imgui/backends/imgui_impl_opengl3.cpp)

add_compile_definitions(
  GLTF_ASSET_PATH="${PROJECT_SOURCE_DIR}/obj/"
  COMPILED_SHADER_DIR="${PROJECT_SOURCE_DIR}/shaders/"
  PROJECT_SOURCE_DIR="${PROJECT_SOURCE_DIR}")

add_executable(cs_exam_shaders src/main.cpp ${SRC_FILES} ${IMGUI_FILES})

target_link_libraries(cs_exam_shaders OpenGL::GL glfw libglew_static glm::glm)

# file(GLOB_RECURSE SHADER_FILES "${CMAKE_SOURCE_DIR}/shaders/*")
# add_custom_target(copy_shaders ALL
#   COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_SOURCE_DIR}/shaders" "${CMAKE_BINARY_DIR}/shaders"
#   DEPENDS ${SHADER_FILES}
#   COMMENT "Copying shaders to build directory...")
