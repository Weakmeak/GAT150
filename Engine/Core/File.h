#pragma once
#include <string>

namespace digi {
	
	void SetFilepath(const std::string& pathname);
	std::string GetFilepath();

	bool FileExists(const std::string& filename);
	bool GetFileSize(const std::string& filename, size_t& size);
	bool ReadFile(const std::string& pathname, std::string& buffer);
}