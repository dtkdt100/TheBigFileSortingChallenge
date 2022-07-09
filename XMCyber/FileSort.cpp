#include <algorithm>
#include <iostream>
#include <vector>
#include "Exceptions.h"
#include "FilePathUtils.h"
#include "FileSort.h"
#include "FilePathGenerator.h"
#include "TempFile.h"


FileSort::FileSort(int maxFileSizeBytes, int numberOfLinesPerSegment, int lineSizeBytes):
	maxFileSizeBytes(maxFileSizeBytes),
	numberOfLinesPerSegment(numberOfLinesPerSegment), 
	lineSizeBytes(lineSizeBytes) {
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
	if (fileSize < numberOfLinesPerSegment * lineSizeBytes) {
		error = FILE_TOO_SMALL_EXCEPTION;
	}
	if (fileSize % (numberOfLinesPerSegment * lineSizeBytes) != 0) {
		error = FILE_SIZE_NOT_MULTIPLE_OF_LINES_PER_SEGMENT;
	}
	if (error != NO_EXCEPTION) {
		throw std::exception(error.c_str());
	}
	return true;
}

void FileSort::sort(const std::string& inFilePath, const std::string& outFilePath) {
	File f = File(inFilePath);

	int fSize = f.getSize();
	if (!isFileVaild(fSize)) return;

	basePath = FilePathUtils::getFileBasePath(inFilePath);
	int numberOfSegements = fSize / (numberOfLinesPerSegment * lineSizeBytes);
	
	splitFile(&f, numberOfSegements);	
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
		splitFile(&files[i], numberOfSegementsPerFile, numberOfSegements);
		numberOfSegements += numberOfSegementsPerFile;
	}
	mergeFiles(outFilePath, numberOfSegements);
}

void FileSort::mergeFiles(const std::string& outPath, int numberOfSegements) {
	int layer = 0;
	int numberOfFiles = numberOfSegements;
	while (numberOfFiles > 1) {
		mergeLayer(outPath, layer, numberOfFiles);
		// if numberOfFiles is odd, the number of merged files is numberOfFiles / 2 + 1
		if (numberOfFiles % 2 == 0) numberOfFiles /= 2;
		else numberOfFiles = numberOfFiles / 2 + 1;
		layer++;
	}
}

void FileSort::mergeLayer(const std::string& outPath, int layer, int numOfFiles) {
	for (int i = 0; i < numOfFiles; i+=2) {
		std::string outPathForFiles = FilePathGenerator::generateFilePathFromLayerAndIndex(basePath, layer + 1, i / 2);
		std::string path1 = FilePathGenerator::generateFilePathFromLayerAndIndex(basePath, layer, i);
		if (i + 1 >= numOfFiles) {
			File::rename(path1, outPathForFiles);
		}
		else {
			std::string path2 = FilePathGenerator::generateFilePathFromLayerAndIndex(basePath, layer, i+1);
			mergeTwoFiles(path1, path2, numOfFiles == 2 ? outPath : outPathForFiles);
		}	
	}
}

void FileSort::mergeTwoFiles(const std::string& path1, const std::string& path2, const std::string& outPath) {
	TempFile f1(path1);
	TempFile f2(path2);
	
	int f1Size = f1.getFile()->getSize() / lineSizeBytes;
	int f2Size = f2.getFile()->getSize() / lineSizeBytes;
	int i = 0, j = 0;

	LinesBuffer l1, l2;
	
	File outFile(outPath, true);
	
	while (i < f1Size && j < f2Size) {
		l1 = f1.getFile()->readLines(lineSizeBytes, i * lineSizeBytes);
		l2 = f2.getFile()->readLines(lineSizeBytes, j * lineSizeBytes);
		
		if (l1.size() > 1 || l2.size() > 1 || l1.front().size() != lineSizeBytes - 2 || l2.front().size() != lineSizeBytes - 2) {
			throw std::exception(FILE_LINES_NOT_THE_SAME_LEN);
		}

		if (l2.front().compare(l1.front()) == 1) {
			outFile.writeLines(l1);
			i++;
		}
		else {
			outFile.writeLines(l2);
			j++;
		}

	}

	while (i < f1Size) {
		l1 = f1.getFile()->readLines(lineSizeBytes, i * lineSizeBytes);
		outFile.writeLines(l1);
		i++;
	}

	while (j < f2Size) {
		l2 = f2.getFile()->readLines(lineSizeBytes, j * lineSizeBytes);
		outFile.writeLines(l2);
		j++;
	}
}

void FileSort::splitFile(File* file, int numberOfSegements, int startInex) {
	for (int i = 0; i < numberOfSegements; i++) {
		proccessSegment(file, i, startInex);
	}
}

void FileSort::proccessSegment(File* file, int segIndex, int startInex) {
	LinesBuffer sortedLines = sortSegment(file, segIndex);
	
	std::string path = FilePathGenerator::generateFilePathFromLayerAndIndex(basePath, 0, startInex+segIndex);
	File f(path, true);
	
	f.writeLines(sortedLines);
}

LinesBuffer FileSort::sortSegment(File* file, int segIndex) {
	int bytesToRead = numberOfLinesPerSegment * lineSizeBytes;
	int startFilePointer = segIndex * bytesToRead;
	
	LinesBuffer lines = file->readLines(bytesToRead, startFilePointer);
	
	std::sort(lines.begin(), lines.end());

	return lines;
}


