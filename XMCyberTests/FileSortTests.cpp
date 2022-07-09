#include "pch.h"
#include "TestsPathUtils.h"
#include "XMCyber/FileSort.h"
#include "XMCyber/FilePathUtils.h"

TEST(FileSortTest, SortSmallFile) {
	const auto dir = TestsPathUtils::getCurrentTestsFilesDir();
	const auto inputPath = FilePathUtils::generateFilePath(dir, "unsorted_small_file", "txt");
	const auto outPath = FilePathUtils::generateFilePath(dir, "sorted_small_file", "result");
	const auto expectedFilePath = FilePathUtils::generateFilePath(dir, "expected_sorted_small_file", "txt");


	FileSort fileSort(130, 3, 5);
	fileSort.sort(inputPath, outPath);

	EXPECT_EQ(true, File::compareFiles(outPath, expectedFilePath));
}

TEST(FileSortTest, SortBigFile) {
	const auto dir = TestsPathUtils::getCurrentTestsFilesDir();
	const auto inputPath = FilePathUtils::generateFilePath(dir, "unsorted_big_file", "txt");
	const auto outPath = FilePathUtils::generateFilePath(dir, "sorted_big_file", "result");
	const auto expectedFilePath = FilePathUtils::generateFilePath(dir, "expected_sorted_big_file", "txt");


	FileSort fileSort(900000, 10000, 7);
	fileSort.sort(inputPath, outPath);

	EXPECT_EQ(true, File::compareFiles(outPath, expectedFilePath));
}

int main(int argc, char* argv[]) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}