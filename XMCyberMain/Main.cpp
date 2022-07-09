#include <Windows.h>
#include <algorithm>
#include <iostream>
#include "XMCyber\FileSort.h"


const int maxFileSizeBytes = 130;
const int numberOfLinesPerSegment = 2;
const int lineSizeBytes = 5;


int main() {
	clock_t start = clock();
	FileSort hi = FileSort(maxFileSizeBytes, numberOfLinesPerSegment, lineSizeBytes);
	hi.sort("C:\\Users\\dolev\\source\\repos\\XMCyber\\XMCyberTests\\TestsFiles\\unsorted_small_file.txt", 
		"C:\\Users\\dolev\\source\\repos\\XMCyber\\XMCyberTests\\TestsFiles\\expected_sorted_small_file.txt");
	clock_t end = clock();
	double elapsed_secs = double(end - start) / CLOCKS_PER_SEC;
	std::cout << "Runtime: " << elapsed_secs << " seconds" << std::endl;
	return 0;
}