#include "threadPool.hpp"

// the destructor joins all threads
ThreadPool::~ThreadPool() {
	{
		std::unique_lock<std::mutex> lock(queue_mutex);
		condition_producers.wait(lock, [this] { return tasks.empty(); });
		stop = true;
	}
	condition.notify_all();
	for (std::thread& worker : workers) {
		worker.join();
	}
}
