//
// Created by 戴晗 on 2024/10/17.
//
#include <iostream>
#include <string>
#include <thread>
#include <queue>
#include <condition_variable>
#include <mutex>
#include <vector>
#include <functional>
using namespace std;

class ThreadPool{
public:
    ThreadPool(int number){
        for(int i = 0;i < number;i++){
            threads.emplace_back([this]{
                while(1){
                    unique_lock<mutex> lock(mtx);
                    condition.wait(lock,[this]{
                        return !tasks.empty() || stop;
                    });
                    if(stop && tasks.empty()){
                        return;
                    }
                    function<void() > task(::move(tasks.front()));
                    tasks.pop();
                    lock.unlock();
                    task();
                }
            });
        }
    }
    ~ThreadPool(){
        {
            unique_lock<mutex> lock(mtx);
            stop = true;
        }
        condition.notify_all();
        for(auto &t:threads){
            t.join();
        }
    }

    template<class F,class... Args>
    void enqueue(F &&f,Args&&... args){
        function<void()>task = bind(forward<F>(f), forward<Args>(args)...);
        {
            unique_lock<mutex> lock(mtx);
            tasks.emplace(move(task));
        }
        condition.notify_one();
    }
private:
    vector<thread> threads; // 线程数组
    queue <function<void ()>> tasks;  // 任务队列
    mutex mtx;  // 互斥信号量
    condition_variable condition; // 条件变量
    bool stop;  // 标示位
};
int main(){
    return 0;
}
