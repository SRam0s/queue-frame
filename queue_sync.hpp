#ifndef QUEUE_FRAME_HPP
#define QUEUE_FRAME_HPP

#include <functional>
#include <future>
#include <queue>
#include <iostream>

class QueueSync
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
    int total_tasks;
    bool stop;

public:
    /** @brief 构造函数

    @param sync_max_num 同时运行的任务最大数 例如最多需要同时跑4个任务 即填4
    @param total_tasks 任务总和 即后边需要入队的任务总数

    @return 无
    */
    QueueSync(int sync_max_num ,int total_tasks);
    ~QueueSync();

    template<class F, class... Args>
    decltype(auto) enqueue(int&& queue_num , F&& f, Args&&... args);


    /** @brief 任务开始

    @return 0
    */
    int start();

};


/** @brief 将要执行的任务加入执行队列

    @param queue_num 所加入任务所处的队列序号 从1开始 本框架先同时执行编号为1的任务 
                    再依次执行标号2、3、4的任务 以此类推
    @param f 要执行的任务函数
    @param args 任务函数的输入参数

    @return 任务函数的返回值为std::future<return_type>
*/
template<class F, class... Args>
decltype(auto) QueueSync::enqueue(int&& queue_num, F&& f, Args&&... args)
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
