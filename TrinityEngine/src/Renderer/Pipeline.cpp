#include "Pipeline.h"

#include <fstream>
#include <iostream>
#include <stdexcept>

namespace Engine
{
	Pipeline::Pipeline(const std::string& vert, const std::string& frag)
	{
		CreateGraphicsPipeline(vert, frag);
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
	
	void Pipeline::CreateGraphicsPipeline(const std::string& vert, const std::string& frag)
	{
		auto vertexCode = ReadFile(vert);
		auto fragmentCode = ReadFile(frag);

		std::cout << "Vertex Shader Size: " << vert.size() << std::endl;
		std::cout << "Fragment Shader Size: " << frag.size() << std::endl;
	}
}