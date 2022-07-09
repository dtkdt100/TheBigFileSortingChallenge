#pragma once
#include "File.h"

class FileSort final {
public:
	FileSort(int maxFileSizeBytes, int numberOfLinesPerSegment, int lineSizeBytes);
	void sort(const std::string& inFilePath, const std::string& outFilePath);
	void sort(const std::vector<std::string>& inFilePaths, const std::string& outFilePath);

private:
	bool isFileVaild(int fileSize);
	
	void mergeFiles(const std::string& outPath, int numberOfSegements);
	
	void splitFile(File& file, int numberOfSegements, int startIndex = 0);
	void proccessSegment(File& file, int segIndex, int startInex = 0);
	LinesBuffer sortSegment(File& file, int segIndex);

	int maxFileSizeBytes;
	int numberOfLinesPerSegment;
	int lineSizeBytes;
	std::string basePath;

};

