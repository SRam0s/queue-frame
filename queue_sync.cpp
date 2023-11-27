#include "queue_sync.hpp"

QueueSync::QueueSync(int sync_max_num ,int total_tasks)    
:   stop(false)
{
    this->enqueue_tasks_remaining = total_tasks;
    this->total_tasks = total_tasks;

    for(size_t i = 0;i<sync_max_num;++i)
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
                            condition_producers.notify_one(); 
                        }
                    }

                    task();
                }
            }
        );
}

QueueSync::~QueueSync()
{
    {
		std::unique_lock<std::mutex> lock(queue_mutex);
		condition_producers.wait(lock, [this] { return tasks_vec.empty(); });
		stop = true;
	}
	condition.notify_all();
	for (std::thread& worker : workers) {
		worker.join();
	}
}

int QueueSync::start()
{
    std::unique_lock<std::mutex> lock(this->start_mutex);
    this->condition_start.wait(lock,
        [this]{ return (this->enqueue_tasks_remaining == 0); });

    for(int i = 0; i < tasks_vec.size(); ++i)
    {
        {
            std::unique_lock<std::mutex> lock(queue_mutex);

            for(int j = 0; j < tasks_vec[i].size(); ++j)
            {
                ret_vec.emplace_back(this->tasks_vec[i][j].get_future());
                tasks.emplace_back(std::move(this->tasks_vec[i][j]));

                condition.notify_one();
            }
        }
        for(int j = 0; j < tasks_vec[i].size(); ++j)
        {
            ret_vec[j].wait();
        }

        ret_vec.clear();
    }

    tasks_vec.clear();
    this->enqueue_tasks_remaining = this->total_tasks;

    return 0;
}