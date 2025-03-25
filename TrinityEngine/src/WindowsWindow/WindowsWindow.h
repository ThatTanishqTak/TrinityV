#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <vec4.hpp>
#include <mat4x4.hpp>

#include <iostream>

namespace Engine
{
	class WindowsWindow
	{
	public:
		void Init();
		void Shutdown();

		void Run();

	public:
		GLFWwindow* m_Window;
	};
}