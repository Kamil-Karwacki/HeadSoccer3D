#include <glad/glad.h>
#include "application.hpp"
#include "input.hpp"
#include "window.hpp"
#include "graphics/shader.hpp"
#include "graphics/mesh.hpp"
#include "world/entity.hpp"
#include "world/component.hpp"
#include "world/components/transform.hpp"
#include "world/components/meshRenderer.hpp"
#include "world/components/playerController.hpp"
#include <iostream>
#include "core/debug.hpp"

Application* Application::s_Instance = nullptr;

Application::Application() : m_isRunning(true)
{
    s_Instance = this;
    
    m_window = std::make_unique<Window>(1280, 720, "Projekt GK");

    m_inputManager = std::make_unique<InputManager>(m_window->getNativeWindow());

    m_inputManager->bindAction("forward", GLFW_KEY_W);
    m_inputManager->bindAction("back", GLFW_KEY_S);
    m_inputManager->bindAction("left", GLFW_KEY_A);
    m_inputManager->bindAction("right", GLFW_KEY_D);
    loadShader("default", PROJECT_DIR "assets/shaders/default.vert", PROJECT_DIR "assets/shaders/default.frag");
    loadShader("lineDebug", PROJECT_DIR "assets/shaders/lineDebug.vert", PROJECT_DIR "assets/shaders/lineDebug.frag");
    Debug::init();
}

Application::~Application()
{
    glfwTerminate();
}

void Application::run()
{
    glfwSetInputMode(m_window->getNativeWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glEnable(GL_DEPTH_TEST);

    glGenTextures(1, &whiteTexture);
    glBindTexture(GL_TEXTURE_2D, whiteTexture);

    unsigned char whitePixel[] = { 255, 255, 255, 255 };

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, whitePixel);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    m_activeScene = std::make_unique<Scene>();
    m_activeScene->init();

    std::shared_ptr<Shader> defaultShader = getShader("default");
    std::shared_ptr<Shader> debugShader = Application::Get().getShader("lineDebug");
    
    double accumulator = 0.0;
    const double fixedDeltaTime = 1.0 / 60.0;

    while (m_isRunning)
    {
        double currentFrameTime = glfwGetTime();
        double deltaTime = currentFrameTime - m_lastFrameTime;
        m_lastFrameTime = currentFrameTime;

        if (deltaTime > 0.25) deltaTime = 0.25;

        accumulator += deltaTime;

        m_inputManager->update();
        glfwPollEvents();
        
        glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        Debug::update(static_cast<float>(deltaTime));

        defaultShader->use();
        m_activeScene->update(static_cast<float>(deltaTime));
        while (accumulator >= fixedDeltaTime)
        {
            m_activeScene->fixedUpdate(static_cast<float>(fixedDeltaTime));
            accumulator -= fixedDeltaTime;
        }
        m_activeScene->draw();
        
        // Drawing debug lines.
        debugShader->use();
        debugShader->setMat4("view", 1, GL_FALSE, &m_activeScene->getMainViewMatrix()[0][0]);
        debugShader->setMat4("projection", 1, GL_FALSE, &m_activeScene->getMainProjectionMatrix()[0][0]);
        Debug::render(*debugShader);

        if (m_window->ShouldClose())
        {
            close();
        }

        m_window->SwapBuffers();
    }
}

void Application::close()
{
    m_isRunning = false;
}

void Application::loadShader(const std::string& name, const char* vertexPath, const char* fragmentPath)
{
    m_shaders[name] = std::make_shared<Shader>(vertexPath, fragmentPath);
}

std::shared_ptr<Shader> Application::getShader(const std::string& name)
{
    auto it = m_shaders.find(name);
    if (it != m_shaders.end())
    {
        return it->second;
    }

    std::cerr << "Error: Couldn't find shader with this name: " << name << "\n";
    return nullptr;
}