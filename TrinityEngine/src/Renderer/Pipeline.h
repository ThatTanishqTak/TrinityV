#pragma once

#include <string>
#include <vector>

namespace Engine
{
	class Pipeline
	{
	public:
		Pipeline(const std::string& vert, const std::string& frag);

	private:
		static std::vector<char> ReadFile(const std::string& filePath);

		void CreateGraphicsPipeline(const std::string& vert, const std::string& frag);
	};
}