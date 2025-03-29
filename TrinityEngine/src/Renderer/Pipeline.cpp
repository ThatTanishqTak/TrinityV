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

		config.inputAssemblyInfo.sType					  = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
		config.inputAssemblyInfo.topology				  = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
		config.inputAssemblyInfo.primitiveRestartEnable   = VK_FALSE;

		config.viewport.x	       = 0.0f;
		config.viewport.y	       = 0.0f;
		config.viewport.width	   = static_cast<float>(width);
		config.viewport.height	   = static_cast<float>(height);
		config.viewport.minDepth   = 0.0f;
		config.viewport.maxDepth   = 1.0f;

		config.scissor.offset   = { 0, 0 };
		config.scissor.extent   = { width, height };

		config.viewportInfo.sType           = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
		config.viewportInfo.viewportCount   = 1;
		config.viewportInfo.pViewports      = &config.viewport;
		config.viewportInfo.scissorCount    = 1;
		config.viewportInfo.pScissors       = &config.scissor;

		config.rasterizationInfo.sType                     = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
		config.rasterizationInfo.depthClampEnable          = VK_FALSE;
		config.rasterizationInfo.rasterizerDiscardEnable   = VK_FALSE;
		config.rasterizationInfo.polygonMode               = VK_POLYGON_MODE_FILL;
		config.rasterizationInfo.lineWidth                 = 1.0f;
		config.rasterizationInfo.cullMode                  = VK_CULL_MODE_NONE;
		config.rasterizationInfo.frontFace                 = VK_FRONT_FACE_CLOCKWISE;
		config.rasterizationInfo.depthBiasEnable           = VK_FALSE;
		config.rasterizationInfo.depthBiasConstantFactor   = 0.0f;           // Optional
		config.rasterizationInfo.depthBiasClamp            = 0.0f;           // Optional
		config.rasterizationInfo.depthBiasSlopeFactor      = 0.0f;           // Optional

		config.multisampleInfo.sType                   = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
		config.multisampleInfo.sampleShadingEnable     = VK_FALSE;
		config.multisampleInfo.rasterizationSamples    = VK_SAMPLE_COUNT_1_BIT;
		config.multisampleInfo.minSampleShading        = 1.0f;                // Optional
		config.multisampleInfo.pSampleMask             = nullptr;             // Optional
		config.multisampleInfo.alphaToCoverageEnable   = VK_FALSE;            // Optional
		config.multisampleInfo.alphaToOneEnable        = VK_FALSE;            // Optional

		config.colorBlendAttachment.colorWriteMask        = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
		config.colorBlendAttachment.blendEnable           = VK_FALSE;
		config.colorBlendAttachment.srcColorBlendFactor   = VK_BLEND_FACTOR_ONE;          // Optional
		config.colorBlendAttachment.dstColorBlendFactor   = VK_BLEND_FACTOR_ZERO;         // Optional
		config.colorBlendAttachment.colorBlendOp          = VK_BLEND_OP_ADD;              // Optional
		config.colorBlendAttachment.srcAlphaBlendFactor   = VK_BLEND_FACTOR_ONE;          // Optional
		config.colorBlendAttachment.dstAlphaBlendFactor   = VK_BLEND_FACTOR_ZERO;         // Optional
		config.colorBlendAttachment.alphaBlendOp          = VK_BLEND_OP_ADD;              // Optional

		config.colorBlendInfo.sType               = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
		config.colorBlendInfo.logicOpEnable       = VK_FALSE;
		config.colorBlendInfo.logicOp             = VK_LOGIC_OP_COPY;  // Optional
		config.colorBlendInfo.attachmentCount     = 1;
		config.colorBlendInfo.pAttachments        = &config.colorBlendAttachment;
		config.colorBlendInfo.blendConstants[0]   = 0.0f;              // Optional
		config.colorBlendInfo.blendConstants[1]   = 0.0f;              // Optional
		config.colorBlendInfo.blendConstants[2]   = 0.0f;              // Optional
		config.colorBlendInfo.blendConstants[3]   = 0.0f;              // Optional

		config.depthStencilInfo.sType                   = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
		config.depthStencilInfo.depthTestEnable         = VK_TRUE;
		config.depthStencilInfo.depthWriteEnable        = VK_TRUE;
		config.depthStencilInfo.depthCompareOp          = VK_COMPARE_OP_LESS;
		config.depthStencilInfo.depthBoundsTestEnable   = VK_FALSE;
		config.depthStencilInfo.minDepthBounds          = 0.0f;      // Optional
		config.depthStencilInfo.maxDepthBounds          = 1.0f;      // Optional
		config.depthStencilInfo.stencilTestEnable       = VK_FALSE;
		config.depthStencilInfo.front                   = {};        // Optional
		config.depthStencilInfo.back                    = {};        // Optional

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