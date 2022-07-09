#include <iostream>
#include "XMCyber\FileSort.h"


const int maxFileSizeBytes = 150;
const int numberOfLinesPerSegment = 2;
const int lineSizeBytes = 5;


int main() {
	clock_t start = clock();
	FileSort fileSort = FileSort(maxFileSizeBytes, numberOfLinesPerSegment, lineSizeBytes);
	std::vector<std::string> paths;
	paths.push_back("C:\\temp\\test1.txt");
	paths.push_back("C:\\temp\\test2.txt");
	fileSort.sort(paths, "C:\\temp\\result.txt");
	clock_t end = clock();
	double elapsed_secs = double(end - start) / CLOCKS_PER_SEC;
	std::cout << "Runtime: " << elapsed_secs << " seconds" << std::endl;
	return 0;
}