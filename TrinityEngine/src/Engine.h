#pragma once

#include "WindowsWindow/WindowsWindow.h"
#include "Device/Device.h"

#include "Renderer/Swapchain.h"
#include "Renderer/Pipeline.h"
#include "Renderer/Model.h"

#include <memory>
#include <vector>

namespace Engine
{
	class Engine
	{
	public:
		static constexpr int WIDTH = 1920;
		static constexpr int HEIGHT = 1080;

	public:
		Engine();
		~Engine();

		Engine(const Engine&) = delete;
		Engine& operator=(const Engine&) = delete;
		
		void Run();

	private:
		WindowsWindow m_WindowsWindow{ WIDTH, HEIGHT, "TrinityV" };
		Device m_Device{ m_WindowsWindow };
		SwapChain m_Swapchain{ m_Device, m_WindowsWindow.GetExtent() };
		
		std::unique_ptr<Pipeline> m_Pipeline;
		VkPipelineLayout m_PipelineLayout;
		std::vector<VkCommandBuffer> m_CommandBuffers;
		std::unique_ptr<Model> m_Model;

	private:
		void LoadModel();

		void CreatePipelineLayout();
		void CreatePipeline();
		void CreateCommandBuffer();
		
		void DrawFrame();
	};
}