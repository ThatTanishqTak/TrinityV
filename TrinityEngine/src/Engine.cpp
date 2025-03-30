#include "Engine.h"

#include <stdexcept>

namespace Engine
{
	Engine::Engine()
	{
		CreatePipelineLayout();
		CreatePipeline();
		CreateCommandBuffer();
	}

	Engine::~Engine()
	{
		vkDestroyPipelineLayout(m_Device.GetDevice(), m_PipelineLayout, nullptr);
	}

	void Engine::Run()
	{
		while (!m_WindowsWindow.ShouldClose())
		{
			glfwPollEvents();

			DrawFrame();
		}
	}

	void Engine::CreatePipelineLayout()
	{
		VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
		pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
		pipelineLayoutInfo.setLayoutCount = 0;
		pipelineLayoutInfo.pSetLayouts = nullptr;
		pipelineLayoutInfo.pushConstantRangeCount = 0;
		pipelineLayoutInfo.pPushConstantRanges = nullptr;

		if (vkCreatePipelineLayout(m_Device.GetDevice(), &pipelineLayoutInfo, nullptr, &m_PipelineLayout) != VK_SUCCESS)
		{
			throw std::runtime_error("Failed to create pipeline layout");
		}
	}

	void Engine::CreatePipeline()
	{
		PipelineConfigInfo pipelineConfig{};
		Pipeline::DefaultPipelineConfigInfo(pipelineConfig, m_Swapchain.GetWidth(), m_Swapchain.GetHeight());

		pipelineConfig.renderPass = m_Swapchain.GetRenderPass();
		pipelineConfig.pipelineLayout = m_PipelineLayout;

		m_Pipeline = std::make_unique<Pipeline>(m_Device, "Shaders/Shader.vert.spv", "Shaders/Shader.frag.spv", pipelineConfig);
	}

	void Engine::CreateCommandBuffer()
	{

	}

	void Engine::DrawFrame()
	{

	}
}