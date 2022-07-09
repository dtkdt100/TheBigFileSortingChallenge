#pragma once
#include "File.h"

class TempFile {
public:
	TempFile(const std::string& path, bool createNew = false);
	File& getFile();
	~TempFile();
private:
	std::string path;
	File m_file;
};

