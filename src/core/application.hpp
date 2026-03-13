#pragma once

#include "graphics/shader.hpp"
#include "window.hpp"
#include "input.hpp"
#include <memory>
#include "world/scene.hpp"

class Application
{
public:
    Application();
    ~Application();

    void run();
    void close();

    static Application& Get() { return *s_Instance; }
    
    InputManager& GetInput() { return *m_inputManager; }

    int getWindowWidth() { return m_window->getWidth(); }
    int getWindowHeight() { return m_window->getHeight(); }
    
    void loadShader(const std::string& name, const char* vertexPath, const char* fragmentPath);
    std::shared_ptr<Shader> getShader(const std::string& name);
    unsigned int getWhiteTexture() { return whiteTexture; }
private:
    std::unique_ptr<Window> m_window;
    std::unique_ptr<InputManager> m_inputManager;

    float m_lastFrameTime = 0.0f;

    bool m_isRunning;
    static Application* s_Instance;

    unsigned int whiteTexture;
    std::unordered_map<std::string, std::shared_ptr<Shader>> m_shaders;

    std::unique_ptr<Scene> m_activeScene;
};