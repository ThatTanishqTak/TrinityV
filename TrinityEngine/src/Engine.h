#pragma once

#include "WindowsWindow/WindowsWindow.h"
#include "Renderer/Pipeline.h"

namespace Engine
{
	class Engine
	{
	public:
		Engine();
		~Engine();

		void Run();

	private:
		WindowsWindow m_WindowsWindow;
		Pipeline m_Pipeline{ "Shaders/Shader.vert.spv", "Shaders/Shader.frag.spv" };
	};
}