#pragma once
#include "FilePathUtils.h"

class FilePathGenerator {
public:
	FilePathGenerator() = delete;
	static std::string generateFilePathFromLayerAndIndex(const std::string& basePath, 
		int layerNumber, int index);
};

