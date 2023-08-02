#include "queue_frame.hpp"

QueueFrame::QueueFrame(int sync_max_num)
{
    pool = new ThreadPool(sync_max_num);
}
QueueFrame::~QueueFrame(){}