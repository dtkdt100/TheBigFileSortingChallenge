#include "FilePathUtils.h"
#include <Windows.h>

std::string FilePathUtils::getFileBasePath(const std::string& filename) {
	std::string::size_type pos = filename.find_last_of("\\");

	if (isEndOfFilePath(pos)) {
		throw std::exception("BLa bla");
	}
			
	return filename.substr(0, pos);
}

std::string FilePathUtils::getFileName(const std::string& filePath) {
	std::string::size_type pos = filePath.find_last_of("\\");

	if (isEndOfFilePath(pos)) {
		return filePath;
	}
			
	return filePath.substr(pos + 1);
}

std::string FilePathUtils::generateFilePath(const std::string& path, const std::string& fileName) {
	return path + "\\" + fileName;
}

bool FilePathUtils::isEndOfFilePath(const std::string::size_type& pos) {
	return pos == std::string::npos;
}
