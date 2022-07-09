#pragma once
#include <Windows.h>
#include <string>
#include "File.h"

//class FileSortTest_FileSortStartsEmpty_Test;

class FileSort final {
public:
	FileSort(int maxFileSizeBytes, int numberOfLinesPerSegment, int lineSizeBytes);
	~FileSort();
	void sort(const std::string& inFilePath, const std::string& outFilePath);
	
	// for tests
	//friend class FileSortTest_FileSortStartsEmpty_Test;
private:
	ExceptionStatus isFileVaild(int fileSize);
	
	void mergeFiles(const std::string& outPath, int numberOfSegements);
	void mergeLayer(const std::string& outPath, int layer, int numOfFiles);
	void mergeTwoFiles(const std::string& path1, const std::string& path2, const std::string& outPath);
	
	void splitFile(File* file, int numberOfSegements);
	void proccessSegment(File* file, int segIndex);
	LinesBuffer sortSegment(File* file, int segIndex);

	int maxFileSizeBytes;
	int numberOfLinesPerSegment;
	int lineSizeBytes;
	std::string basePath;

};

