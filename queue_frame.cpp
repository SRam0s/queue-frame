#include "queue_frame.hpp"

QueueFrame::QueueFrame(int sync_max_num ,int total_tasks)    
:   stop(false)
{
    this->enqueue_tasks_remaining = total_tasks;

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
                            condition_producers.notify_one(); // notify the destructor that the queue is empty
                        }
                    }

                    task();
                }
            }
        );
}

QueueFrame::~QueueFrame()
{
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

int QueueFrame::start()
{
    std::unique_lock<std::mutex> lock(this->start_mutex);
    this->condition_start.wait(lock,
        [this]{ return (this->enqueue_tasks_remaining == 0); });

    for(int i = 0; i < tasks_vec.size(); i++)
    {
        {
            std::unique_lock<std::mutex> lock(queue_mutex);

            for(int j = 0; j < tasks_vec[i].size(); j++)
            {
                ret_vec.emplace_back(this->tasks_vec[i][j].get_future());
                tasks.emplace_back(std::move(this->tasks_vec[i][j]));

                condition.notify_one();
            }
        }
        for(int j = 0; j < tasks_vec[i].size(); j++)
        {
            ret_vec[j].wait();
        }

        ret_vec.clear();
    }
}