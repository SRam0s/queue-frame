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