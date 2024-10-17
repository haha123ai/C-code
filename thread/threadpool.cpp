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

    ~ThreadPool();
private:
    vector<thread> threads;
    queue <function<void ()>> tasks;
    mutex mtx;
    condition_variable condition;
    bool stop;
};
