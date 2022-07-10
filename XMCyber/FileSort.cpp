#include <algorithm>
#include "Exceptions.h"
#include "FilePathUtils.h"
#include "FileSort.h"
#include "FilePathGenerator.h"
#include "TempFile.h"
#include "LayerMerger.h"


FileSort::FileSort(int maxFileSizeBytes, int numberOfLinesPerSegment, int lineSizeBytes):
	maxFileSizeBytes(maxFileSizeBytes),
	numberOfLinesPerSegment(numberOfLinesPerSegment), 
	lineSizeBytes(lineSizeBytes), basePath("C:\\temp") {
	if (maxFileSizeBytes < 0) {
		throw std::exception(MAX_FILE_SIZE_TOO_SMALL);
	}
	if (numberOfLinesPerSegment <= 1) {
		throw std::exception(LINES_PER_SEGEMENT_GREATER_THEN_ONE);
	}
}

bool FileSort::isFileVaild(int fileSize) {
	std::string error = NO_EXCEPTION;
	if (fileSize > maxFileSizeBytes) {
		error = FILE_TOO_BIG_EXCEPTION;
	}
	else if (fileSize < numberOfLinesPerSegment * lineSizeBytes) {
		error = FILE_TOO_SMALL_EXCEPTION;
	}
	else if (fileSize % (numberOfLinesPerSegment * lineSizeBytes) != 0) {
		error = FILE_SIZE_NOT_MULTIPLE_OF_LINES_PER_SEGMENT;
	}
	if (error != NO_EXCEPTION) {
		throw std::exception(error.c_str());
	}
	return true;
}

void FileSort::sort(const std::string& inFilePath, const std::string& outFilePath) {
	File inputFile(inFilePath);

	int fSize = inputFile.getSize();
	if (!isFileVaild(fSize)) return;

	basePath = FilePathUtils::getFileBasePath(inFilePath);
	int numberOfSegements = fSize / (numberOfLinesPerSegment * lineSizeBytes);
	
	splitFile(inputFile, numberOfSegements);	

	mergeFiles(outFilePath, numberOfSegements);
}

void FileSort::sort(const std::vector<std::string>& inFilePaths, const std::string& outFilePath) {
	std::vector<File> files;
	std::vector<int> sizes;
	for (auto& filePath : inFilePaths) {
		files.push_back(File(filePath));
		sizes.push_back(files.back().getSize());
		if (!isFileVaild(sizes.back())) return;
	}
	basePath = FilePathUtils::getFileBasePath(inFilePaths[0]);

	int numberOfSegements = 0;

	for (int i = 0; i < files.size(); i++) {
		int numberOfSegementsPerFile = sizes[i] / (numberOfLinesPerSegment * lineSizeBytes);
		splitFile(files[i], numberOfSegementsPerFile, numberOfSegements);
		numberOfSegements += numberOfSegementsPerFile;
	}
	mergeFiles(outFilePath, numberOfSegements);
}

void FileSort::mergeFiles(const std::string& outFilePath, int numberOfSegements) {
	LayerMerger layerMerger(outFilePath, basePath, numberOfLinesPerSegment);
	layerMerger.merge(numberOfSegements, lineSizeBytes);
}

void FileSort::splitFile(File& file, int numberOfSegements, int startInex) {
	for (int i = 0; i < numberOfSegements; i++) {
		proccessSegment(file, i, startInex);
	}
}

void FileSort::proccessSegment(File& file, int segIndex, int startInex) {
	LinesBuffer sortedLines = sortSegment(file, segIndex);
	
	std::string path = FilePathGenerator::generateFilePathFromLayerAndIndex(basePath, 0, startInex+segIndex);
	File f(path, true);
	
	f.writeLines(sortedLines);
}

LinesBuffer FileSort::sortSegment(File& file, int segIndex) {
	int bytesToRead = numberOfLinesPerSegment * lineSizeBytes;
	int startFilePointer = segIndex * bytesToRead;
	
	LinesBuffer lines = file.readLines(bytesToRead, startFilePointer);
	
	std::sort(lines.begin(), lines.end());

	return lines;
}


