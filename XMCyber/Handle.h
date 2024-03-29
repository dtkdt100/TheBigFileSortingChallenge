#pragma once
#include <exception>
#include <utility>
#include "Defs.h"

class Handle final {
public:
	
	Handle(Handle&& other);

	Handle(HANDLE handle);
	
	Handle() = delete;
	Handle(const Handle&) = delete;
	Handle& operator=(const Handle&) = delete;
	Handle& operator=(Handle&&) = delete;
	
	void close();

	~Handle();
	
	HANDLE getRawHandle();
	
	bool isValid() const;
	
private:
	HANDLE m_handle;
};