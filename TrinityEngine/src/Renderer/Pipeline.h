#pragma once

#include "Device/Device.h"

#include <string>
#include <vector>

namespace Engine
{
	struct PipelineConfigInfo
	{
		PipelineConfigInfo(const PipelineConfigInfo&) = delete;
		PipelineConfigInfo & operator=(const PipelineConfigInfo&) = delete;

		VkPipelineViewportStateCreateInfo viewportInfo{};
		VkPipelineInputAssemblyStateCreateInfo inputAssemblyInfo{};
		VkPipelineRasterizationStateCreateInfo rasterizationInfo{};
		VkPipelineMultisampleStateCreateInfo multisampleInfo{};
		VkPipelineColorBlendAttachmentState colorBlendAttachment;
		VkPipelineColorBlendStateCreateInfo colorBlendInfo{};
		VkPipelineDepthStencilStateCreateInfo depthStencilInfo{};

		std::vector<VkDynamicState> dynamicStateEnables;
		VkPipelineDynamicStateCreateInfo dynamicStateInfo;

		VkPipelineLayout pipelineLayout = nullptr;
		VkRenderPass renderPass = nullptr;
		uint32_t subpass = 0;
	};

	class Pipeline
	{
	public:
		Pipeline(Device& device, const std::string& vert, const std::string& frag, const PipelineConfigInfo& info);
		~Pipeline();

		Pipeline() = default;
		Pipeline(const Pipeline&) = delete;
		Pipeline& operator=(const Pipeline&) = delete;

		void Bind(VkCommandBuffer commandBuffer);

		static void DefaultPipelineConfigInfo(PipelineConfigInfo& configInfo);

	private:
		Device& m_Device;
		
		VkPipeline m_GraphicsPipeline;
		VkShaderModule m_VertShaderModule;
		VkShaderModule m_FragShaderModule;

	private:
		static std::vector<char> ReadFile(const std::string& filePath);

		void CreateGraphicsPipeline(const std::string& vert, const std::string& frag, const PipelineConfigInfo& info);
		void CreateShaderModule(const std::vector<char>& code, VkShaderModule* shaderModule);
	};
}