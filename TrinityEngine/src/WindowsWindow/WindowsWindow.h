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

		void CreateWindowSurface(VkInstance instance, VkSurfaceKHR* surface);

		bool ShouldClose() { return glfwWindowShouldClose(m_Window); }

		VkExtent2D GetExtent() { return { static_cast<uint32_t>(WIDTH), static_cast<uint32_t>(HEIGHT) }; }

	private:
		const int WIDTH;
		const int HEIGHT;

		std::string m_WindowName;
		GLFWwindow* m_Window;

	private:
		void InitWindow();
	};
}