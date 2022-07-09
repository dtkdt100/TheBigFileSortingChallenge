#pragma once
#include "Handle.h"


class Thread {
public:
	Thread(LPTHREAD_START_ROUTINE, LPVOID);
	HANDLE getRawHandle();
private:
	Handle createThread(LPTHREAD_START_ROUTINE, LPVOID) const;
	Handle m_thread;
};

