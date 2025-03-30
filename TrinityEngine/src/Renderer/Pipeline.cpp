#include "Pipeline.h"

#include <fstream>
#include <iostream>
#include <stdexcept>
#include <cassert>

namespace Engine
{
	Pipeline::Pipeline(Device& device, const std::string& vert, const std::string& frag, const PipelineConfigInfo& info) : m_Device(device)
	{
		CreateGraphicsPipeline(vert, frag, info);
	}

	Pipeline::~Pipeline()
	{
		vkDestroyShaderModule(m_Device.GetDevice(), m_FragShaderModule, nullptr);
		vkDestroyShaderModule(m_Device.GetDevice(), m_VertShaderModule, nullptr);
		vkDestroyPipeline(m_Device.GetDevice(), m_GraphicsPipeline, nullptr);
	}

	void Pipeline::DefaultPipelineConfigInfo(PipelineConfigInfo& config, uint32_t width, uint32_t height)
	{
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

		config.viewportInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
		config.viewportInfo.viewportCount = 1;
		config.viewportInfo.pViewports = &config.viewport;
		config.viewportInfo.scissorCount = 1;
		config.viewportInfo.pScissors = &config.scissor;

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
		assert(info.pipelineLayout != VK_NULL_HANDLE && "Cannot create pipeline:: no pipeline layout provided in the config info");
		assert(info.renderPass != VK_NULL_HANDLE && "Cannot create pipeline:: no render pass provided in the config info");

		auto vertexCode = ReadFile(vert);
		auto fragmentCode = ReadFile(frag);

		CreateShaderModule(vertexCode, &m_VertShaderModule);
		CreateShaderModule(fragmentCode, &m_FragShaderModule);

		VkPipelineShaderStageCreateInfo shaderStages[2] = {};
		shaderStages[0].sType                 = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
		shaderStages[0].stage                 = VK_SHADER_STAGE_VERTEX_BIT;
		shaderStages[0].module                = m_VertShaderModule;
		shaderStages[0].pName                 = "main";
		shaderStages[0].flags                 = 0;
		shaderStages[0].pNext                 = nullptr;
		shaderStages[0].pSpecializationInfo   = nullptr;

		shaderStages[1].sType                 = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
		shaderStages[1].stage                 = VK_SHADER_STAGE_FRAGMENT_BIT;
		shaderStages[1].module                = m_FragShaderModule;
		shaderStages[1].pName                 = "main";
		shaderStages[1].flags                 = 0;
		shaderStages[1].pNext                 = nullptr;
		shaderStages[1].pSpecializationInfo   = nullptr;

		VkPipelineVertexInputStateCreateInfo vertexInputInfo{};
		vertexInputInfo.sType                             = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
		vertexInputInfo.vertexAttributeDescriptionCount   = 0;
		vertexInputInfo.vertexBindingDescriptionCount     = 0;
		vertexInputInfo.pVertexAttributeDescriptions      = nullptr;
		vertexInputInfo.pVertexBindingDescriptions        = nullptr;

		VkGraphicsPipelineCreateInfo pipelineInfo{};
		pipelineInfo.sType                 = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
		pipelineInfo.stageCount            = 2;
		pipelineInfo.pStages               = shaderStages;
		pipelineInfo.pVertexInputState     = &vertexInputInfo;
		pipelineInfo.pInputAssemblyState   = &info.inputAssemblyInfo;
		pipelineInfo.pViewportState        = &info.viewportInfo;
		pipelineInfo.pRasterizationState   = &info.rasterizationInfo;
		pipelineInfo.pMultisampleState     = &info.multisampleInfo;
		pipelineInfo.pColorBlendState      = &info.colorBlendInfo;
		pipelineInfo.pDepthStencilState    = &info.depthStencilInfo;
		pipelineInfo.pDynamicState         = nullptr;

		pipelineInfo.layout       = info.pipelineLayout;
		pipelineInfo.renderPass   = info.renderPass;
		pipelineInfo.subpass      = info.subpass;

		pipelineInfo.basePipelineIndex    = -1;
		pipelineInfo.basePipelineHandle   = VK_NULL_HANDLE;

		if (vkCreateGraphicsPipelines(m_Device.GetDevice(), VK_NULL_HANDLE, 1, &pipelineInfo, nullptr, &m_GraphicsPipeline) != VK_SUCCESS)
		{
			throw std::runtime_error("Failed to create Graphics Pipeline");
		}
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