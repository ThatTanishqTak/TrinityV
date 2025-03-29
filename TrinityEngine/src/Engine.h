#pragma once

#include "WindowsWindow/WindowsWindow.h"
#include "Renderer/Pipeline.h"
#include "Device/Device.h"

namespace Engine
{
	class Engine
	{
	public:
		void Run();

	private:
		WindowsWindow m_WindowsWindow{ 1920, 1080, "TrinityV" };
		Device m_Device{ m_WindowsWindow };
		Pipeline m_Pipeline{ m_Device, "Shaders/Shader.vert.spv", "Shaders/Shader.frag.spv", Pipeline::DefaultPipelineConfigInfo(1920, 1080) };
	};
}