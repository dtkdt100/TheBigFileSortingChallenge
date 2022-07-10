#pragma once
#include "File.h"

class TempFile final {
public:
	TempFile(const std::string& path, bool createNew = false);
	File& getFile();
	~TempFile();
private:
	std::string path;
	File m_file;
};

