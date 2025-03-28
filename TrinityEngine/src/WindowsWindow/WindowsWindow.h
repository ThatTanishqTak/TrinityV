#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <string>

namespace Engine
{
	class WindowsWindow
	{
	public:
		WindowsWindow(int width, int height, std::string title);
		~WindowsWindow();

		WindowsWindow(const WindowsWindow&) = delete;
		WindowsWindow &operator=(const WindowsWindow&) = delete;

		void CreateWindowSurface(VkInstance instance, VkSurfaceKHR* surface);

		bool ShouldClose() { return glfwWindowShouldClose(m_Window); }

	private:
		const int WIDTH;
		const int HEIGHT;

		std::string m_WindowName;
		GLFWwindow* m_Window;

	private:
		void InitWindow();
	};
}