#pragma once
#include <vector>
#include <queue>
#include <thread>
#include <functional>
#include <mutex>

class ThreadPool
{
private:
	size_t m_maxThreadCount;
	std::vector<std::thread> m_workes;
	std::queue<std::function<void()>> m_jobs;
	std::condition_variable m_jobCv;
	std::mutex m_jobMetex;
	bool m_stopAll;

public:
	ThreadPool(size_t _threadCount);
	void WorkerThread();
	void Enqueue(std::function<void()> job);
};

