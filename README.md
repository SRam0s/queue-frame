# Queue-sync-framework

# 一个基于线程池的队列同步执行框架



​		在平常的开发过程中，我们常遇到这样的需求：我们需要在同时执行完几个函数之后再开始执行另外几个函数。

​		例如：我们同时调用三个函数采取三个传感器的数据，在同时运行三个算法函数对得到的数据进行处理，然后再运行融合处理的函数进行最终处理。

​		在这种场景下，我们通常会采用加锁配合条件变量或者状态值循环读取的方式来进行多线程同步，这两种方式虽然可以实现上述需求，但是第一种方法在函数

过多或者项目需求修改时显得极为不便，第二种方法又占用了太多的CPU资源。

​		本框架可以极为方便的实现以上应用场景，在提供的例子中，我们直观的展示了如何使用本框架：

```c++
#include "queue_sync.hpp"
#include <unistd.h>
#include <string>

using namespace std;

string test(int num , int sleep_time)
{
    sleep(sleep_time);    
    printf("num:%d,sleep:%d\n" , num , sleep_time);
    std::string r = "queue num:" + to_string(num) + "||sleep for " + to_string(sleep_time) + "s";
    return r;
}

int main()
{
    QueueSync q(3 , 7);  
    std::vector<std::future<std::string> > ret_vec;

    while (1)
    {
        ret_vec.emplace_back(q.enqueue(1,test,1,1));
        ret_vec.emplace_back(q.enqueue(1,test,1,2));
        ret_vec.emplace_back(q.enqueue(2,test,2,1));
        ret_vec.emplace_back(q.enqueue(2,test,2,2));
        ret_vec.emplace_back(q.enqueue(2,test,2,3));
        ret_vec.emplace_back(q.enqueue(3,test,3,1));
        ret_vec.emplace_back(q.enqueue(3,test,3,3));

        std::cout<<"<<<<<<<<<<<<work<<<<<<<<<<<"<<std::endl;
        q.start();

        std::cout<<"<<<<<<<<<<<<done<<<<<<<<<<<"<<std::endl;
        
        std::cout << ret_vec[0].get() << std::endl
                << ret_vec[1].get() << std::endl
                << ret_vec[2].get() << std::endl   
                << ret_vec[3].get() << std::endl   
                << ret_vec[4].get() << std::endl   
                << ret_vec[5].get() << std::endl   
                << ret_vec[6].get() << std::endl;   


        ret_vec.clear(); 
    }
    return 0;
}
```

​		运行之后，程序会循环打印：

```shell
<<<<<<<<<<<<work<<<<<<<<<<<
num:1,sleep:1
num:1,sleep:2
num:2,sleep:1
num:2,sleep:2
num:2,sleep:3
num:3,sleep:1
num:3,sleep:3
<<<<<<<<<<<<done<<<<<<<<<<<
queue num:1||sleep for 1s
queue num:1||sleep for 2s
queue num:2||sleep for 1s
queue num:2||sleep for 2s
queue num:2||sleep for 3s
queue num:3||sleep for 1s
queue num:3||sleep for 3s
```

