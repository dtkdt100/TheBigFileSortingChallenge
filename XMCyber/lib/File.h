#pragma once
#include "Handle.h"
#include "Defs.h"

class File final {
public:
	File(const std::string& path, bool createNew = false);
	Buffer read(uint32_t numberOfBytes, LONG startOffset);
	LinesBuffer readLines(uint32_t numberOfBytes, LONG startOffset);
	void write(const Buffer& buffer);
	void writeLines(const LinesBuffer& buffer);
	
	int getSize();
	bool compareFiles(File& other);
	void close();

	static void rename(const std::string& oldPath, const std::string& newPath);
	static bool exsits(const std::string& filePath);
	static void deleteFile(const std::string& filePath);
	static bool compareFiles(const std::string& path1, const std::string& path2);
	
private:
	Handle openFile(const std::string& filePath) const;
	Handle createNewFile(const std::string& filePath) const;
	Handle createFileInternal(const std::string& filePath, bool  createNew) const;
	
	Handle m_file;
};

