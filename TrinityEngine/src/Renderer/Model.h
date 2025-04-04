#pragma once

#include "Device/Device.h"

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>

#include <vector>

namespace Engine
{
	class Model
	{
	public:
		struct Vertex
		{
			glm::vec2 Position;
			glm::vec3 Color;

			static std::vector<VkVertexInputBindingDescription> GetBindingDescriptions();
			static std::vector<VkVertexInputAttributeDescription> GetAttributeDescriptions();
		};

	public:
		Model(Device& device, std::vector<Vertex>& vertices);
		~Model();

		Model(const Model&) = delete;
		Model& operator=(const Model&) = delete;

		void Bind(VkCommandBuffer commandBuffer);
		void Draw(VkCommandBuffer commandBuffer);

	private:
		Device& m_Device;

		VkBuffer m_VertexBuffer;
		VkDeviceMemory m_VertexBufferMemory;

		uint32_t m_VertexCount;

	private:
		void CreateVertexBuffer(const std::vector<Vertex>& vertices);
	};
}