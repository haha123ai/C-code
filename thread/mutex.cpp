//
// Created by 戴晗 on 2024/10/16.
//
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>

using namespace std;

int a = 0;
mutex m,m1,m2;
void fun(){
    for(int i = 0;i < 100 ;i++){
        m.lock();  // 加锁
        a += 1;
        m.unlock();  // 解锁
    }
}

void fun1(){
    for(int i = 0;i < 100 ;i++){
        m1.lock();
        m2.lock();
        cout << "fun1" << i << endl;
        m1.unlock();
        m2.unlock();
    }
}

void fun2(){
    for(int i = 0;i < 100 ;i++){
        m1.lock();
        m2.lock();
        cout << "fun2" << i << endl;
        m1.unlock();
        m2.unlock();
    }
}

int b = 0;
void fun3(){
    for(int i = 0;i < 10000 ;i++){
        //使用lock_guard模版，构造函数会进行自动加锁，析构函数会进行自动解锁
        // 其对象不能复制或移动，智能在局部作用域中使用
        lock_guard<mutex> lg(m);
        b += 1;
    }
}

int c= 0;
timed_mutex timem;
void fun4(){
    for(int i = 0;i < 2 ;i++){
        /*
         unique_lock 可以对互斥信号量进行加锁解锁，主要特点可以更加灵活的管理
         包括：延迟加锁，条件变量，超时
         */
        //unique_lock<mutex> lg(m); 会自动加锁解锁
        unique_lock<timed_mutex> lg(timem,defer_lock); // 此时不会进行任何动作
        if(lg.try_lock_for(chrono::seconds(2))) //延迟加锁会等待2s，如果超过2s直接退出
        {
            this_thread::sleep_for(chrono::seconds(1));
            c += 1;
        }

    }
}

//生产者与消费者模型
queue<int> q_queue;
condition_variable g_cv;
mutex unmutex;
void producer(){
    for(int i = 0;i < 10;i++){
        {
            unique_lock<mutex> unlock(unmutex);
            q_queue.push(i);
            g_cv.notify_one(); // 通知消费者取任务
            cout << "task: " << i << endl;
        }
        this_thread::sleep_for(chrono::microseconds(100));
    }
}
void consumer(){
    while(1){
        unique_lock<mutex> unlock(unmutex);
        // 如果队列为空，需要等待

        g_cv.wait(unlock,[] (){
            return !q_queue.empty();
        });

        int value = q_queue.front();
        q_queue.pop();

        cout << "work: " << value << endl;
    }
}



int main(){
    thread t1(fun);
    thread t2(fun);

    if(t1.joinable()){
        t1.join();
    }

    if(t2.joinable()){
        t2.join();
    }

    cout << a << endl;

    //死锁案例
    thread th1(fun1);
    thread th2(fun2);

    th2.join();
    th1.join();

    cout << "over" << endl;

    // lock_guard
    thread tt1(fun3);
    thread tt2(fun3);
    tt1.join();
    tt2.join();
    cout << b << endl;

    //unqiue_lock
    thread ttt1(fun4);
    thread ttt2(fun4);
    ttt1.join();
    ttt2.join();
    cout << c << endl;


     // condition_variable 场景
     thread m1(producer);
     thread m2(consumer);
     m1.join();
     m2.join();


    return 0;

}