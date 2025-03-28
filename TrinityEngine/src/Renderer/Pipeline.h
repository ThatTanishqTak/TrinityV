#pragma once

#include "../Device/Device.h"

#include <string>
#include <vector>

namespace Engine
{
	struct PipelineConfigInfo
	{

	};

	class Pipeline
	{
	public:
		Pipeline(Device& device, const std::string& vert, const std::string& frag, const PipelineConfigInfo& info);
		~Pipeline() {}

		Pipeline(const Pipeline&) = delete;
		void operator=(const Pipeline&) = delete;

		static PipelineConfigInfo DefaultPipelineConfigInfo(uint32_t width, uint32_t height);

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