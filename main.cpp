#include "queue_frame.hpp"
#include <unistd.h>
#include <iostream>
//#include <threadPool.hpp>
// #include "ttt.hpp"

std::vector<std::future<int> > ret_vec;
int a;
int b;

int test()
{
    sleep(3);    
    printf("this is the test1 fun\n");
    return 9;
}

int test2()
{
   // printf("bbb\n");
    sleep(3);
    printf("this is the test2 fun\n");
    return 10;
}

int main()
{
    QueueFrame q(2 , 2);  

    q.enqueue(1 , test);
    q.enqueue(1 , test2);
    q.start();

    sleep(10);

    return 0;
}