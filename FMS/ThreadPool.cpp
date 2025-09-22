#include "ThreadPool.h"

ThreadPool::ThreadPool(size_t _threadCount)
	: m_maxThreadCount(_threadCount)
	, m_stopAll(false)
{
	m_workes.reserve(m_maxThreadCount);
	for (int i = 0; i < m_maxThreadCount; i++)
	{
		m_workes.emplace_back([this]() { WorkerThread(); });
	}
}

void ThreadPool::WorkerThread()
{
	while (true)
	{
		std::unique_lock<std::mutex> lock(m_jobMetex);
		m_jobCv.wait(lock, [this]()
			{
				return true == m_jobs.empty() || true == m_stopAll;
			}
		);

		if (true == m_stopAll
			&& true == m_jobs.empty())
		{
			return;
		}

		std::function<void()> job = std::move(m_jobs.front());
		m_jobs.pop();
		lock.unlock();

		job();
	}
}

void ThreadPool::Enqueue(std::function<void()> job)
{
	if (true == m_stopAll)
	{
		return;
	}

	std::lock_guard<std::mutex> lock(m_jobMetex);
	m_jobs.push(std::move(job));
	
	m_jobCv.notify_one();
}
