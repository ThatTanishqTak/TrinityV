#include "Engine.h"

namespace Engine
{
	Engine::Engine()
	{
		m_WindowsWindow.Init();
	}

	Engine::~Engine()
	{
		m_WindowsWindow.Shutdown();
	}

	void Engine::Run()
	{
		m_WindowsWindow.Run();
	}
}