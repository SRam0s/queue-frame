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
    bool stop;

public:
    /** @brief 

    @param out_filename 编码的输出文件名，编码器会根据此名称的后缀来推断封装格式
    @param enc_name 要使用的ffmpeg的编码器名称，例如：h264_qsv
    @param width 输入图像的width
    @param height 输入图像的height
    @param fps 编码的帧率
    @param fmt 输入图像的格式,目前支持：E_PIX_FMT_NV12 ,
                                    E_PIX_FMT_NV21 ,
                                    E_PIX_FMT_YUV420P ,
                                    E_PIX_FMT_YUYV422 , 
                                    E_PIX_FMT_UYVY422
    @return 成功：0 异常：其他值
    */
    QueueSync(int sync_max_num ,int total_tasks);
    ~QueueSync();

    template<class F, class... Args>
    decltype(auto) enqueue(int&& queue_num , F&& f, Args&&... args);

    int start();

};

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
