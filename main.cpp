#include "queue_sync.hpp"
#include <unistd.h>

std::vector<std::future<int> > ret_vec;

int test()
{
    sleep(3);    
    printf("this is the test1 fun\n");
    return 9;
}

int test2()
{
    sleep(1);
    printf("this is the test2 fun\n");
    return 10;
}

int test3()
{
    sleep(4);
    printf("this is the test3 fun\n");
    return 11;
}

int main()
{
    QueueSync q(2 , 3);  

    ret_vec.emplace_back(q.enqueue(1 , test));
    ret_vec.emplace_back(q.enqueue(1 , test3));
    ret_vec.emplace_back(q.enqueue(2 , test2));
    q.start();

    std::cout << ret_vec[0].get() << std::endl
              << ret_vec[1].get() << std::endl
              << ret_vec[2].get() << std::endl;
    return 0;
}