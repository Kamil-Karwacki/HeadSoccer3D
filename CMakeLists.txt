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

add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME} PRIVATE
    src/engine/core/application.cpp
    src/engine/core/debug.cpp
    src/engine/core/input.cpp
    src/engine/core/window.cpp
    src/engine/graphics/mesh.cpp
    src/engine/graphics/model.cpp
    src/engine/graphics/shader.cpp
    src/engine/graphics/renderSystem.cpp
    src/engine/physics/contact.cpp
    src/engine/physics/physicsSystem.cpp
    src/engine/world/scene.cpp
    src/engine/world/components/collider.cpp
    src/engine/world/components/rigidbody.cpp
    src/engine/world/components/transform.cpp
    src/game/scripts/playerController.cpp
    src/game/scripts/baseScene.cpp
    src/game/scripts/cameraController.cpp
    src/third_party/stb_implementation.cpp
    src/third_party/tinyobjloader_implementation.cpp
    src/main.cpp
)

target_compile_options(${PROJECT_NAME} PRIVATE ${COMPILER_WARNINGS})

target_include_directories(${PROJECT_NAME} PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/engine
    ${CMAKE_CURRENT_SOURCE_DIR}/src/game
    ${CMAKE_CURRENT_SOURCE_DIR}/src/third_party
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