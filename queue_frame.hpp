#ifndef QUEUE_FRAME_HPP
#define QUEUE_FRAME_HPP

#include <functional>
#include <future>
#include <queue>
#include <iostream>

class QueueFrame
{
private:

    std::vector<std::vector<std::packaged_task<void()> > > tasks_vec;
    std::vector<std::packaged_task<void()> > tasks;
    std::mutex queue_mutex;
    std::mutex start_mutex;
    std::condition_variable condition;
    std::condition_variable condition_start;
    std::condition_variable condition_producers;
    std::vector<std::future<void> > ret_vec;
    std::vector<std::thread > workers;

    int enqueue_tasks_remaining;
    bool stop;

public:
    QueueFrame(int sync_max_num ,int total_tasks);
    ~QueueFrame();

    template<class F, class... Args>
    decltype(auto) enqueue(int&& queue_num , F&& f, Args&&... args);

    int start();

};

inline QueueFrame::QueueFrame(int sync_max_num ,int total_tasks)    
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

template<class F, class... Args>
decltype(auto) QueueFrame::enqueue(int&& queue_num, F&& f, Args&&... args)
{
    using return_type = std::invoke_result_t<F, Args...>;

    std::packaged_task<return_type()> task(
            std::bind(std::forward<F>(f), std::forward<Args>(args)...)
        );

    std::future<return_type> res = task.get_future();
    {
        std::unique_lock<std::mutex> lock(queue_mutex);
        std::vector<std::packaged_task<void()> > queue_tmp;

        if(tasks.size() < queue_num)
        {
            queue_tmp.emplace_back(std::move(task));
            tasks_vec.emplace_back(std::move(queue_tmp));

        }else
        {
            tasks_vec[queue_num].emplace_back(std::move(task));
        }


    }
    {
        std::unique_lock<std::mutex> lock(this->start_mutex);
        this->enqueue_tasks_remaining--;
        condition_start.notify_one();
    }

    return res;
}


#endif
