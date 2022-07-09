#pragma once
#include <string>

class FilePathUtils {
public:
	FilePathUtils() = delete;
	static std::string getFileBasePath(const std::string& filePath);
	static std::string generateFilePath(const std::string& path, const std::string& fileName);
	static std::string getFileName(const std::string& filePath);
private:
	static bool isEndOfFilePath(const std::string::size_type& pos);
};

