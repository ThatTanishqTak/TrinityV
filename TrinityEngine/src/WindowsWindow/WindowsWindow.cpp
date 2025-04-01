#include "WindowsWindow.h"

#include <stdexcept>

namespace Engine
{
	WindowsWindow::WindowsWindow(int width, int height, std::string title) : m_Width(width), m_Height(height), m_WindowName(title)
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
		glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

		m_Window = glfwCreateWindow(m_Width, m_Height, m_WindowName.c_str(), nullptr, nullptr);
		glfwSetWindowUserPointer(m_Window, this);
		glfwSetFramebufferSizeCallback(m_Window, FrameBufferResizeCallback);
	}

	void WindowsWindow::FrameBufferResizeCallback(GLFWwindow* window, int width, int height)
	{
		auto localWindow = reinterpret_cast<WindowsWindow*>(glfwGetWindowUserPointer(window));
		localWindow->m_FrambufferResize = true;
		localWindow->m_Width = width;
		localWindow->m_Height = height;
	}
}