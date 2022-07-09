#include "pch.h"
#include "TestsPathUtils.h"
#include "XMCyber/FileSort.h"
#include "XMCyber/FilePathUtils.h"
#include "XMCyber/Exceptions.h"

std::string errorToString(const std::exception& e) {
	std::stringstream stringstream;
	stringstream << e.what();
	return stringstream.str();
}

//TEST(FileSortTest, SortSmallFile) {
//	const auto dir = TestsPathUtils::getCurrentTestsFilesDir();
//	const auto inputPath = FilePathUtils::generateFilePath(dir, "unsorted_small_file", "txt");
//	const auto outPath = FilePathUtils::generateFilePath(dir, "sorted_small_file", "result");
//	const auto expectedFilePath = FilePathUtils::generateFilePath(dir, "expected_sorted_small_file", "txt");
//
//	FileSort fileSort(130, 3, 5);
//	fileSort.sort(inputPath, outPath);
//
//	EXPECT_EQ(true, File::compareFiles(outPath, expectedFilePath));
//}

//TEST(FileSortTest, SortBigFile) {
//	const auto dir = TestsPathUtils::getCurrentTestsFilesDir();
//	const auto inputPath = FilePathUtils::generateFilePath(dir, "unsorted_big_file", "txt");
//	const auto outPath = FilePathUtils::generateFilePath(dir, "sorted_big_file", "result");
//	const auto expectedFilePath = FilePathUtils::generateFilePath(dir, "expected_sorted_big_file", "txt");
//
//
//	FileSort fileSort(900000, 10000, 7);
//	fileSort.sort(inputPath, outPath);
//
//	EXPECT_EQ(true, File::compareFiles(outPath, expectedFilePath));
//}

// test and points and errors
//TEST(FileSortTest, FileWithDifferentLinesLength) {
//	const auto dir = TestsPathUtils::getCurrentTestsFilesDir();
//	const auto inputPath = FilePathUtils::generateFilePath(dir, "unsorted_big_file", "txt");
//	const auto outPath = FilePathUtils::generateFilePath(dir, "out_file_with_different_lines_length", "result");
//
//	try {
//		FileSort fileSort(130, 2, 5);
//		fileSort.sort(inputPath, outPath);
//	} catch (const std::exception& e) {
//		EXPECT_EQ(FILE_SIZE_NOT_MULTIPLE_OF_LINES_PER_SEGMENT, errorToString(e));
//	}
//}

TEST(FileSortTest, FileLargerThenExpectedSize) {
	const auto dir = TestsPathUtils::getCurrentTestsFilesDir();
	const auto inputPath = FilePathUtils::generateFilePath(dir, "unsorted_small_file", "txt");
	const auto outPath = FilePathUtils::generateFilePath(dir, "", "");

	try {
		FileSort fileSort(20, 2, 5);
		fileSort.sort(inputPath, outPath);
	}
	catch (const std::exception& e) {
		EXPECT_EQ(FILE_TOO_BIG_EXCEPTION, errorToString(e));
	}
}

TEST(FileSortTest, LinesPerSegementIsOne) {
	const auto dir = TestsPathUtils::getCurrentTestsFilesDir();
	const auto inputPath = FilePathUtils::generateFilePath(dir, "unsorted_small_file", "txt");
	const auto outPath = FilePathUtils::generateFilePath(dir, "", "");

	try {
		FileSort fileSort(20, 1, 5);
		fileSort.sort(inputPath, outPath);
	}
	catch (const std::exception& e) {
		EXPECT_EQ(LINES_PER_SEGEMENT_GREATER_THEN_ONE, errorToString(e));
	}
}

TEST(FileSortTest, InvaildFilePath) {
	const auto dir = TestsPathUtils::getCurrentTestsFilesDir();
	const auto inputPath = FilePathUtils::generateFilePath(dir, "not_exsiting_file", "txt");
	const auto outPath = FilePathUtils::generateFilePath(dir, "", "");

	try {
		FileSort fileSort(20, 2, 5);
		fileSort.sort(inputPath, outPath);
	}
	catch (const std::exception& e) {
		EXPECT_EQ(INAVILD_HANDLE_EXCEPTION, errorToString(e));
	}
}

int main(int argc, char* argv[]) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}