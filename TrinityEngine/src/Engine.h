#pragma once

#include "WindowsWindow/WindowsWindow.h"

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
	};
}