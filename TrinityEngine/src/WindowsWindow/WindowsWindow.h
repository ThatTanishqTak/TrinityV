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
		bool WasWindowResized() { return m_FrambufferResize; }

		void ResetWindowResizeFlag() { m_FrambufferResize = false; }

		VkExtent2D GetExtent() { return { static_cast<uint32_t>(m_Width), static_cast<uint32_t>(m_Height) }; }

	private:
		int m_Width;
		int m_Height;

		bool m_FrambufferResize = false;

		std::string m_WindowName;
		GLFWwindow* m_Window;

	private:
		void InitWindow();

		static void FrameBufferResizeCallback(GLFWwindow* window, int width, int height);
	};
}