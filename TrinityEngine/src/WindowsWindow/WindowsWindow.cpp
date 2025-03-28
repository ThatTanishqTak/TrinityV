#include "WindowsWindow.h"

#include <stdexcept>

namespace Engine
{
	WindowsWindow::WindowsWindow(int width, int height, std::string title) : WIDTH(width), HEIGHT(height), m_WindowName(title)
	{
		InitWindow();
	}

	WindowsWindow::~WindowsWindow()
	{
		glfwDestroyWindow(m_Window);
		glfwTerminate();
	}

	void WindowsWindow::CreateWindowSurface(VkInstance instance, VkSurfaceKHR* surface)
	{
		if (glfwCreateWindowSurface(instance, m_Window, nullptr, surface) != VK_SUCCESS)
		{
			throw std::runtime_error("Failed to create window surface");
		}
	}

	void WindowsWindow::InitWindow()
	{
		glfwInit();
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

		m_Window = glfwCreateWindow(WIDTH, HEIGHT, m_WindowName.c_str(), nullptr, nullptr);
	}
}