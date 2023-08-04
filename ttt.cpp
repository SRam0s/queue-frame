#include "ttt.hpp"

// the constructor just launches some amount of workers
ThreadPool::ThreadPool(size_t threads)
    :   stop(false)
{
    for(size_t i = 0;i<threads;++i)
        workers.emplace_back(
            [this]
            {
                for(;;)
                {
                    std::packaged_task<void()> task;

                    {
                        std::unique_lock<std::mutex> lock(this->queue_mutex);
                        this->condition.wait(lock,
                            [this]{ return this->stop || !this->tasks.empty(); });
                        if(this->stop && this->tasks.empty())
                            return;
                        task = std::move(this->tasks.back());
                        this->tasks.pop_back();
                        if (tasks.empty()) {
                            condition_producers.notify_one(); // notify the destructor that the queue is empty
                        }
                    }

                    task();
                }
            }
        );
}

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

// add new work item to the pool
template<class F, class... Args>
decltype(auto) ThreadPool::enqueue(F&& f, Args&&... args)
{
    using return_type = std::invoke_result_t<F, Args...>;

    std::packaged_task<return_type()> task(
            std::bind(std::forward<F>(f), std::forward<Args>(args)...)
        );

    std::future<return_type> res = task.get_future();

    return res;
}