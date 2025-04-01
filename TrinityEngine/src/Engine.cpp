#include "Engine.h"

#include <stdexcept>
#include <array>

namespace Engine
{
	Engine::Engine()
	{
		LoadModel();

		CreatePipelineLayout();
		RecreateSwapChain();
		CreateCommandBuffers();
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

		vkDeviceWaitIdle(m_Device.GetDevice());
	}

	void Engine::LoadModel()
	{
		std::vector<Model::Vertex> vertices
		{
			{ {  0.0f, -0.5f }, { 1, 0, 0 }, },
			{ {  0.5f,  0.5f }, { 0, 1, 0 }, },
			{ { -0.5f,  0.5f }, { 0, 0, 1 } }
		};

		m_Model = std::make_unique<Model>(m_Device, vertices);
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
		Pipeline::DefaultPipelineConfigInfo(pipelineConfig);

		pipelineConfig.renderPass = m_Swapchain->GetRenderPass();
		pipelineConfig.pipelineLayout = m_PipelineLayout;

		m_Pipeline = std::make_unique<Pipeline>(m_Device, "Shaders/Shader.vert.spv", "Shaders/Shader.frag.spv", pipelineConfig);
	}

	void Engine::RecreateSwapChain()
	{
		auto extent = m_WindowsWindow.GetExtent();
		while (extent.width == 0 || extent.height == 0)
		{
			extent = m_WindowsWindow.GetExtent();

			glfwWaitEvents();
		}

		vkDeviceWaitIdle(m_Device.GetDevice());

		if (m_Swapchain == nullptr)
		{
			m_Swapchain = std::make_unique<SwapChain>(m_Device, extent);
		}

		else
		{
			m_Swapchain = std::make_unique<SwapChain>(m_Device, extent, std::move(m_Swapchain));

			if (m_Swapchain->GetImageCount() != m_CommandBuffers.size())
			{
				FreeCommandBuffers();

				CreateCommandBuffers();
			}
		}

		CreatePipeline();
	}

	void Engine::CreateCommandBuffers()
	{
		m_CommandBuffers.resize(m_Swapchain->GetImageCount());

		VkCommandBufferAllocateInfo allocInfo{};
		allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
		allocInfo.commandPool = m_Device.GetCommandPool();
		allocInfo.commandBufferCount = static_cast<uint32_t>(m_CommandBuffers.size());

		if (vkAllocateCommandBuffers(m_Device.GetDevice(), &allocInfo, m_CommandBuffers.data()) != VK_SUCCESS)
		{
			throw std::runtime_error("Failed to allocate command buffer");
		}
	}

	void Engine::FreeCommandBuffers()
	{
		vkFreeCommandBuffers(m_Device.GetDevice(), m_Device.GetCommandPool(), static_cast<uint32_t>(m_CommandBuffers.size()), m_CommandBuffers.data());

		m_CommandBuffers.clear();
	}

	void Engine::RecordCommandBuffer(int imageIndex)
	{
		VkCommandBufferBeginInfo beginInfo{};
		beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

		if (vkBeginCommandBuffer(m_CommandBuffers[imageIndex], &beginInfo) != VK_SUCCESS)
		{
			throw std::runtime_error("Command buffer failed to begin recording");
		}

		VkRenderPassBeginInfo renderPassInfo{};
		renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
		renderPassInfo.renderPass = m_Swapchain->GetRenderPass();
		renderPassInfo.framebuffer = m_Swapchain->GetFrameBuffer(imageIndex);
		renderPassInfo.renderArea.offset = { 0, 0 };
		renderPassInfo.renderArea.extent = m_Swapchain->GetSwapChainExtent();

		std::array<VkClearValue, 2> clearvValues{};
		clearvValues[0].color = { 0.1f, 0.1f, 0.1f, 1.0f };
		clearvValues[1].depthStencil = { static_cast<uint32_t>(1.0f), static_cast<uint32_t>(0.0f) };

		renderPassInfo.clearValueCount = static_cast<uint32_t>(clearvValues.size());
		renderPassInfo.pClearValues = clearvValues.data();

		vkCmdBeginRenderPass(m_CommandBuffers[imageIndex], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

		VkViewport viewport{};
		viewport.x = 0.0f;
		viewport.y = 0.0f;
		viewport.width = static_cast<float>(m_Swapchain->GetSwapChainExtent().width);
		viewport.height = static_cast<float>(m_Swapchain->GetSwapChainExtent().height);
		viewport.minDepth = 0.0f;
		viewport.maxDepth = 1.0f;

		VkRect2D scissor{ {0, 0}, m_Swapchain->GetSwapChainExtent() };
		vkCmdSetViewport(m_CommandBuffers[imageIndex], 0, 1, &viewport);
		vkCmdSetScissor(m_CommandBuffers[imageIndex], 0, 1, &scissor);

		m_Pipeline->Bind(m_CommandBuffers[imageIndex]);

		m_Model->Bind(m_CommandBuffers[imageIndex]);
		m_Model->Draw(m_CommandBuffers[imageIndex]);

		vkCmdEndRenderPass(m_CommandBuffers[imageIndex]);

		if (vkEndCommandBuffer(m_CommandBuffers[imageIndex]) != VK_SUCCESS)
		{
			throw std::runtime_error("Failed to record command buffer");
		}
	}

	void Engine::DrawFrame()
	{
		uint32_t imageIndex;
		auto result = m_Swapchain->AcquireNextImage(&imageIndex);

		if (result == VK_ERROR_OUT_OF_DATE_KHR)
		{
			RecreateSwapChain();

			return;
		}

		if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR)
		{
			throw std::runtime_error("Failed to acquire swap chain image");
		}

		RecordCommandBuffer(imageIndex);

		result = m_Swapchain->SubmitCommandBuffers(&m_CommandBuffers[imageIndex], &imageIndex);

		if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR || m_WindowsWindow.WasWindowResized())
		{
			m_WindowsWindow.ResetWindowResizeFlag();
			RecreateSwapChain();

			return;
		}

		if (result != VK_SUCCESS)
		{
			throw std::runtime_error("Failed to present swap chain image");
		}
	}
}