#include "FilePathGenerator.h"

std::string FilePathGenerator::generateFilePathFromLayerAndIndex(const std::string& basePath, int layerNumber, int index)
{
    std::string path = basePath;
    std::string filename = std::to_string(layerNumber);
    filename += std::to_string(index);
    filename += ".txt";
    return FilePathUtils::generateFilePath(path, filename);
}
