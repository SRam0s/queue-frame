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

        if(tasks_vec.size() < queue_num)
        {
            queue_tmp.emplace_back(std::move(task));
            tasks_vec.emplace_back(std::move(queue_tmp));
        }else
        {
            tasks_vec[queue_num - 1].emplace_back(std::move(task));
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
