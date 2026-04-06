#include <glad/glad.h>
#include "window.hpp"
#include <iostream>

Window::Window(int width, int height, const std::string& title)
    : m_width(width), m_height(height), m_title(title), m_window(nullptr) 
{
    if (!glfwInit()) 
    {
        std::cerr << "Error: Couldn't initialize GLFW" << std::endl;
        return;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_window = glfwCreateWindow(m_width, m_height, m_title.c_str(), nullptr, nullptr);
    if (!m_window) 
    {
        std::cerr << "Error: Couldn't create GLFW window" << std::endl;
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(m_window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) 
    {
        std::cerr << "Error: Couldn't initialize GLAD" << std::endl;
        return;
    }
}

Window::~Window() 
{
    if (m_window) 
    {
        glfwDestroyWindow(m_window);
    }
    glfwTerminate();
}

void Window::SwapBuffers() 
{
    glfwSwapBuffers(m_window);
}

bool Window::ShouldClose() const 
{
    return glfwWindowShouldClose(m_window);
}