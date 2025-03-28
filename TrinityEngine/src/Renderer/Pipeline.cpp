#include "Pipeline.h"

#include <fstream>
#include <iostream>
#include <stdexcept>

namespace Engine
{
	Pipeline::Pipeline(Device& device, const std::string& vert, const std::string& frag, const PipelineConfigInfo& info) : m_Device(device)
	{
		CreateGraphicsPipeline(vert, frag, info);
	}

	PipelineConfigInfo Pipeline::DefaultPipelineConfigInfo(uint32_t width, uint32_t height)
	{
		PipelineConfigInfo config{};

		return config;
	}

	std::vector<char> Pipeline::ReadFile(const std::string& filePath)
	{
		std::ifstream file{ filePath, std::ios::ate | std::ios::binary };

		if (!file.is_open())
		{
			throw std::runtime_error("Failed to open file: " + filePath);
		}

		size_t fileSize = static_cast<size_t>(file.tellg());
		std::vector<char> buffer(fileSize);

		file.seekg(0);
		file.read(buffer.data(), fileSize);

		file.close();

		return buffer;
	}
	
	void Pipeline::CreateGraphicsPipeline(const std::string& vert, const std::string& frag, const PipelineConfigInfo& info)
	{
		auto vertexCode = ReadFile(vert);
		auto fragmentCode = ReadFile(frag);

		std::cout << "Vertex Shader Size: " << vert.size() << std::endl;
		std::cout << "Fragment Shader Size: " << frag.size() << std::endl;
	}

	void Pipeline::CreateShaderModule(const std::vector<char>& code, VkShaderModule* shaderModule)
	{
		VkShaderModuleCreateInfo createInfo{};

		createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
		createInfo.codeSize = code.size();
		createInfo.pCode = reinterpret_cast<const uint32_t*>(code.data());

		if (vkCreateShaderModule(m_Device.GetDevice(), &createInfo, nullptr, shaderModule) != VK_SUCCESS)
		{
			throw std::runtime_error("Failed to create module");
		}
	}
}