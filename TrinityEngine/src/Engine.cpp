#include "Engine.h"

namespace Engine
{
	void Engine::Run()
	{
		while (!m_WindowsWindow.ShouldClose())
		{
			glfwPollEvents();
		}
	}
}