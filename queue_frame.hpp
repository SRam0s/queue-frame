#ifndef QUEUE_FRAME_HPP
#define QUEUE_FRAME_HPP

#include "threadPool.hpp"
#include "vector"

class QueueFrame
{
private:
    /* data */
    ThreadPool* pool;
public:
    QueueFrame(int sync_max_num);
    ~QueueFrame();
};

#endif
