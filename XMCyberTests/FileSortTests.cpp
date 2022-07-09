#include "pch.h"
#include "TestsPathUtils.h"
#include "XMCyber/FileSort.h"
#include "XMCyber/lib/FilePathUtils.h"

TEST(FileSortTest, LinesNotInTheSameSize) {
	const auto dir = TestsPathUtils::getCurrentTestsFilesDir();
	const auto inputPath = FilePathUtils::generateFilePath(dir, "unsorted_small_file.txt");
	const auto outPath = FilePathUtils::generateFilePath(dir, "sorted_small_file.result");
	const auto expectedFilePath = FilePathUtils::generateFilePath(dir, "expected_sorted_small_file.txt");


	FileSort fileSort(130, 2, 5);
	fileSort.sort(inputPath, outPath);

	EXPECT_EQ(true, File::compareFiles(outPath, expectedFilePath));
}

int main(int argc, char* argv[]) {
	// init google testing
	testing::InitGoogleTest(&argc, argv);
	// run google testing
	
	return RUN_ALL_TESTS();
}