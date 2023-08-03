#include "queue_frame.hpp"

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
    // std::cout << "enter start" << std::endl;

    std::unique_lock<std::mutex> lock(this->start_mutex);
    this->condition_start.wait(lock,
        [this]{ return (this->enqueue_tasks_remaining == 0); });

    // std::cout << "pass start" << std::endl;

    for(int i = 0; i < tasks_vec.size(); i++)
    {
        {
            std::unique_lock<std::mutex> lock(queue_mutex);

            for(int j = 0; j < tasks_vec[i].size(); j++)
            {
                ret_vec.emplace_back(this->tasks_vec[i][j].get_future());
                tasks.emplace_back(std::move(this->tasks_vec[i][j]));

                //  std::cout << "prepare to notify_one" << std::endl;


                condition.notify_one();
            }
        }
        for(int j = 0; j < tasks_vec[i].size(); j++)
        {
            ret_vec[j].wait();
            // std::cout << "pass" << std::endl;
        }

        ret_vec.clear();
    }
}