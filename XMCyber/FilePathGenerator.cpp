#include "FilePathGenerator.h"

std::string FilePathGenerator::generateFilePathFromLayerAndIndex(const std::string& basePath, int layerNumber, int index)
{
    std::string filename = std::to_string(layerNumber) + std::to_string(index);
    return FilePathUtils::generateFilePath(basePath, filename, "txt");
}
