cmake_minimum_required(VERSION 3.15)

project(Projekt_GK 
        VERSION 1.0 
        LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(MSVC)
    set(COMPILER_WARNINGS /W4)
else()
    set(COMPILER_WARNINGS -Wall -Wextra -pedantic)
endif()

include(FetchContent)

FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG        3.4
)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(glfw)

FetchContent_Declare(
    glm
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG        1.0.3
)
FetchContent_MakeAvailable(glm)

FetchContent_Declare(
    stb
    GIT_REPOSITORY https://github.com/nothings/stb.git
    GIT_TAG        master
)
FetchContent_MakeAvailable(stb)

FetchContent_Declare(
    tinyobjloader
    GIT_REPOSITORY https://github.com/tinyobjloader/tinyobjloader.git
    GIT_TAG        v2.0-rc1
)
FetchContent_MakeAvailable(tinyobjloader)

add_subdirectory(external/glad)

add_definitions(-DPROJECT_DIR="${CMAKE_CURRENT_SOURCE_DIR}/")

add_executable(${PROJECT_NAME} ${SOURCES})

target_sources(${PROJECT_NAME} PRIVATE
    src/main.cpp
    src/stb_implementation.cpp
    src/tinyobjloader_implementation.cpp
    src/core/application.cpp
    src/core/input.cpp
    src/core/window.cpp
    src/core/debug.cpp
    src/graphics/shader.cpp
    src/graphics/mesh.cpp
    src/graphics/model.cpp
    src/world/entity.cpp
    src/world/scene.cpp
    src/world/components/transform.cpp
    src/world/components/playerController.cpp
    src/world/components/meshRenderer.cpp
    src/world/components/rigidbody.cpp
    src/world/components/collider.cpp
    src/physics/contact.cpp
    src/physics/physicsSystem.cpp
)

target_compile_options(${PROJECT_NAME} PRIVATE ${COMPILER_WARNINGS})

target_include_directories(${PROJECT_NAME} PRIVATE 
    src
    ${stb_SOURCE_DIR}
)

target_link_libraries(${PROJECT_NAME} PRIVATE 
    glfw
    glm::glm
    glad 
    tinyobjloader
)

if(UNIX AND NOT APPLE)
    find_package(OpenGL REQUIRED)
    target_link_libraries(${PROJECT_NAME} PRIVATE ${OPENGL_LIBRARIES} dl pthread)
endif()