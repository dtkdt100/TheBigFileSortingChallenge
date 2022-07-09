#pragma once
#include <Windows.h>
#include <string>
#include "File.h"

//class FileSortTest_FileSortStartsEmpty_Test;

class FileSort final {
public:
	FileSort(int maxFileSizeBytes, int numberOfLinesPerSegment, int lineSizeBytes);
	void sort(const std::string& inFilePath, const std::string& outFilePath);
	void sort(const std::vector<std::string>& inFilePaths, const std::string& outFilePath);

private:
	bool isFileVaild(int fileSize);
	
	void mergeFiles(const std::string& outPath, int numberOfSegements);
	void mergeLayer(const std::string& outPath, int layer, int numOfFiles);
	void mergeTwoFiles(const std::string& path1, const std::string& path2, const std::string& outPath);
	
	void splitFile(File* file, int numberOfSegements, int startIndex = 0);
	void proccessSegment(File* file, int segIndex, int startInex = 0);
	LinesBuffer sortSegment(File* file, int segIndex);

	int maxFileSizeBytes;
	int numberOfLinesPerSegment;
	int lineSizeBytes;
	std::string basePath;

};

