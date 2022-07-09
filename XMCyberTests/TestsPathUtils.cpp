#include "pch.h"
#include "TestsPathUtils.h"

std::string TestsPathUtils::getCurrentTestsDir() {
	// convert __FILE__ to std::string
	std::string file = __FILE__;
	std::string::size_type pos = file.find_last_of("\\/");
	file = file.substr(0, pos);
	return file;
}

std::string TestsPathUtils::getCurrentTestsFilesDir() {
	return FilePathUtils::appendPath(getCurrentTestsDir(), "TestsFiles");
}
