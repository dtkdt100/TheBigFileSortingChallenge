#include "TempFile.h"

TempFile::TempFile(const std::string& path, bool createNew): m_file(File(path, createNew)), path(path) {
	
}

File& TempFile::getFile() {
	return m_file;
}

TempFile::~TempFile() {
	m_file.close();
	File::deleteFile(path);
}
