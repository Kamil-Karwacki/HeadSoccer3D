#pragma once
#include <GLFW/glfw3.h>
#include <unordered_map>
#include <string>

class InputManager {
public:
    InputManager(GLFWwindow* window);

    void update();

    bool isKeyDown(int key) const;
    bool isKeyPressed(int key) const;
    bool isKeyReleased(int key) const;

    void bindAction(const std::string& actionName, int key);
    bool isActionPressed(const std::string& actionName);
    bool isActionHeld(const std::string& actionName);
    bool isActionReleased(const std::string& actionName);

    bool isMouseButtonDown(int button) const;
    bool isMouseButtonPressed(int button) const;
    bool isMouseButtonReleased(int button) const;

    double getMouseDeltaX() const { return m_mouseDeltaX; }
    double getMouseDeltaY() const { return m_mouseDeltaY; }
private:
    bool m_currentKeys[GLFW_KEY_LAST + 1];
    bool m_previousKeys[GLFW_KEY_LAST + 1];
    std::unordered_map<std::string, int> m_actionBindings;
    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

    bool m_currentMouse[GLFW_MOUSE_BUTTON_LAST + 1];
    bool m_previousMouse[GLFW_MOUSE_BUTTON_LAST + 1];

    double m_mouseX = 0.0;
    double m_mouseY = 0.0;
    double m_mouseDeltaX = 0.0;
    double m_mouseDeltaY = 0.0;
    
    bool m_firstMouse = true;

    static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
    static void cursorPosCallback(GLFWwindow* window, double xpos, double ypos);
};
