#include "Thread.h"


Thread::Thread(LPTHREAD_START_ROUTINE lpThreadFunc, LPVOID lpParameter): 
	m_thread(createThread(lpThreadFunc, lpParameter)) {
}

HANDLE Thread::getRawHandle() {
	return m_thread.getRawHandle();
}

Handle Thread::createThread(LPTHREAD_START_ROUTINE lpThreadFunc, LPVOID lpParameter) const {
	const auto threadHandle = CreateThread(nullptr, 
		0, lpThreadFunc, 
		lpParameter, 
		0, 
		nullptr);
	return Handle(threadHandle);
}