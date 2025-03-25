#include "WindowsWindow.h"

namespace Engine
{
    void WindowsWindow::Init()
    {
        glfwInit();

        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        GLFWwindow* window = glfwCreateWindow(1920, 1080, "TrinityV", nullptr, nullptr);

        m_Window = window;
    }

    void WindowsWindow::Shutdown()
    {
        glfwDestroyWindow(m_Window);

        glfwTerminate();
    }

    void WindowsWindow::Run()
    {
        while (!glfwWindowShouldClose(m_Window))
        {
            glfwPollEvents();
        }
    }
}