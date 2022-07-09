#include <algorithm>
#include <iostream>
#include <vector>
#include "Exceptions.h"
#include "File.h"
#include "FilePathUtils.h"
#include "FileSort.h"
#include "FilePathGenerator.h"


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

FileSort::~FileSort() { 

}

ExceptionStatus FileSort::isFileVaild(int fileSize) {
	if (fileSize > maxFileSizeBytes) {
		return FILE_TOO_BIG_EXCEPTION;
	}
	if (fileSize < numberOfLinesPerSegment * lineSizeBytes) {
		return FILE_TOO_SMALL_EXCEPTION;
	}
	if (fileSize % (numberOfLinesPerSegment * lineSizeBytes) != 0) {
		throw std::exception(FILE_SIZE_NOT_MULTIPLE_OF_LINES_PER_SEGMENT);
	}
	return EMPTY;
}

void FileSort::sort(const std::string& inFilePath, const std::string& outFilePath) {
	File f = File(inFilePath);
	int fSize = f.getSize();
	ExceptionStatus errorMsg = isFileVaild(fSize);

	if (errorMsg != EMPTY) {
		throw std::exception(errorMsg);
	}

	
	
	basePath = FilePathUtils::getFileBasePath(inFilePath);
	int numberOfSegements = fSize / (numberOfLinesPerSegment * lineSizeBytes);


	splitFile(&f, numberOfSegements);
		
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
	File f1(path1, false);
	File f2(path2, false);
	
	int f1Size = f1.getSize()/lineSizeBytes;
	int f2Size = f2.getSize()/lineSizeBytes;
	int i = 0, j = 0;

	LinesBuffer l1, l2;
	
	File outFile(outPath, true);
	
	while (i < f1Size && j < f2Size) {
		l1 = f1.readLines(lineSizeBytes, i * lineSizeBytes);
		l2 = f2.readLines(lineSizeBytes, j * lineSizeBytes);
		
		if (l1.size() != lineSizeBytes-2 || l2.size() != lineSizeBytes-2) {
			throw std::exception(FILE_SIZE_NOT_MULTIPLE_OF_LINES_PER_SEGMENT);
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
		l1 = f1.readLines(lineSizeBytes, i * lineSizeBytes);
		outFile.writeLines(l1);
		i++;
	}

	while (j < f2Size) {
		l2 = f2.readLines(lineSizeBytes, j * lineSizeBytes);
		outFile.writeLines(l2);
		j++;
	}

	f1.close();
	f2.close();
	File::deleteFile(path1);
	File::deleteFile(path2);
}

void FileSort::splitFile(File* file, int numberOfSegements) {
	for (int i = 0; i < numberOfSegements; i++) {
		proccessSegment(file, i);
	}
}

void FileSort::proccessSegment(File* file, int segIndex) {
	LinesBuffer sortedLines = sortSegment(file, segIndex);
	
	std::string path = FilePathGenerator::generateFilePathFromLayerAndIndex(basePath, 0, segIndex);
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


