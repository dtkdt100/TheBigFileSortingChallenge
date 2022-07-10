#pragma once
#include "Exceptions.h"

struct MergeTwoFilesParams {
	std::string path1;
	std::string path2;
	std::string outFilePath;
	int lineSizeBytes;

	MergeTwoFilesParams(std::string path1, std::string path2, std::string outFilePath, int lineSizeBytes) :
		path1(path1), path2(path2), outFilePath(outFilePath), lineSizeBytes(lineSizeBytes) {}
};

class LayerMerger final {

public:
	LayerMerger(const std::string& outFilePath, const std::string& basePath, int maxLinesInRam);
	void merge(int numberOfSegements, int lineSizeBytes) const;

private:
	void mergeLayer(const std::string& outPath, int layer, int numOfFiles, int lineSizeBytes) const;
	static DWORD WINAPI mergeTwoFiles(MergeTwoFilesParams* mergeParams);
	int getMaxThreadSize() const;
	std::string outFilePath;
	std::string basePath;
	int maxLinesInRam;
};

