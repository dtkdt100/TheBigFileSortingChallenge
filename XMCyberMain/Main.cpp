#include <Windows.h>
#include <algorithm>
#include <iostream>
#include "XMCyber\FileSort.h"


const int maxFileSizeBytes = 150;
const int numberOfLinesPerSegment = 2;
const int lineSizeBytes = 5;


int main() {
	clock_t start = clock();
	FileSort hi = FileSort(maxFileSizeBytes, numberOfLinesPerSegment, lineSizeBytes);
	hi.sort("C:\\temp\\test.txt", "C:\\temp\\result.txt");
	clock_t end = clock();
	double elapsed_secs = double(end - start) / CLOCKS_PER_SEC;
	std::cout << "Runtime: " << elapsed_secs << " seconds" << std::endl;
	return 0;
}