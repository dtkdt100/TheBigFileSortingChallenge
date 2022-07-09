#include <memory>
#include "LayerMerger.h"
#include "FilePathGenerator.h"
#include "File.h"
#include "TempFile.h"

LayerMerger::LayerMerger(const std::string& outFilePath, const std::string& basePath, 
	int maxLinesInRam) :
	outFilePath(outFilePath),
	basePath(basePath), maxLinesInRam(maxLinesInRam) {
	
}

void LayerMerger::merge(int numberOfSegements, int lineSizeBytes) {
	int layer = 0;
	int numberOfFiles = numberOfSegements;

	while (numberOfFiles > 1) {
		mergeLayer(outFilePath, layer, numberOfFiles, lineSizeBytes);
		// if numberOfFiles is odd, the number of merged files is numberOfFiles / 2 + 1
		if (numberOfFiles % 2 == 0) numberOfFiles /= 2;
		else numberOfFiles = numberOfFiles / 2 + 1;
		layer++;
	}
}

void LayerMerger::mergeLayer(const std::string& outPath, int layer, int numOfFiles, int lineSizeBytes) {
	int maxThreads = getMaxThreadSize();

	int i = 0;
	
	while (i < numOfFiles) {
		int j = 0;
		std::vector<HANDLE> threads;
		while (j < maxThreads && j + i < numOfFiles) {
			std::string outPathForFiles = FilePathGenerator::generateFilePathFromLayerAndIndex(basePath, layer + 1, i / 2);
			std::string path1 = FilePathGenerator::generateFilePathFromLayerAndIndex(basePath, layer, i);
			if (i + 1 >= numOfFiles) {
				File::rename(path1, outPathForFiles);
			}
			else {
				std::string path2 = FilePathGenerator::generateFilePathFromLayerAndIndex(basePath, layer, i + 1);

				// use heap memory
				auto paramsPtr = std::make_unique<MergeTwoFilesParams>(std::move(path1), std::move(path2), numOfFiles == 2 ? outPath : outPathForFiles, lineSizeBytes);
				
				HANDLE thread = CreateThread(NULL, 0, 
					reinterpret_cast<LPTHREAD_START_ROUTINE>(mergeTwoFiles), 
					paramsPtr.release(), 0, NULL);
				threads.push_back(thread);
			}
			i+=2; // two files at a time
			j++;
		}

		size_t threadSize = threads.size();
		if (threadSize != 0) { 
			DWORD waitStatus = WaitForMultipleObjects(threadSize, threads.data(), true, INFINITE); 
			if (waitStatus < WAIT_OBJECT_0 || waitStatus >= WAIT_OBJECT_0 + threadSize) {
				throw std::exception(WAITING_FOR_THREADS_EXCEPTION);
			}
		}
	}
}

DWORD __stdcall LayerMerger::mergeTwoFiles(MergeTwoFilesParams* mergeParamsRawPtr) {
	std::unique_ptr<MergeTwoFilesParams> mergeParams(mergeParamsRawPtr);
	TempFile f1(mergeParams->path1);
	TempFile f2(mergeParams->path2);

	int lineSizeBytes = mergeParams->lineSizeBytes;

	int f1Size = f1.getFile().getSize() / lineSizeBytes;
	int f2Size = f2.getFile().getSize() / lineSizeBytes;
	int i = 0, j = 0;

	LinesBuffer linesFile1, linesFile2;

	File outFile(mergeParams->outFilePath, true);

	while (i < f1Size && j < f2Size) {
		linesFile1 = f1.getFile().readLines(lineSizeBytes, i * lineSizeBytes);
		linesFile2 = f2.getFile().readLines(lineSizeBytes, j * lineSizeBytes);

		if (linesFile1.size() > 1 || linesFile2.size() > 1 || linesFile1.front().size() != lineSizeBytes - 2 || linesFile2.front().size() != lineSizeBytes - 2) {
			throw std::exception(FILE_LINES_NOT_THE_SAME_LEN);
		}

		if (linesFile2.front().compare(linesFile1.front()) == 1) {
			outFile.writeLines(linesFile1);
			i++;
		}
		else {
			outFile.writeLines(linesFile2);
			j++;
		}

	}

	while (i < f1Size) {
		linesFile1 = f1.getFile().readLines(lineSizeBytes, i * lineSizeBytes);
		outFile.writeLines(linesFile1);
		i++;
	}

	while (j < f2Size) {
		linesFile2 = f2.getFile().readLines(lineSizeBytes, j * lineSizeBytes);
		outFile.writeLines(linesFile2);
		j++;
	}
	return 0;
}

int LayerMerger::getMaxThreadSize() {
	int threadsFitInRam = maxLinesInRam / 2;
	if (threadsFitInRam > 8) {
		return 8;
	}
	else {
		return threadsFitInRam;
	}
}
