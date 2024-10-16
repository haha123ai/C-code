//
// Created by 戴晗 on 2024/10/16.
//
#include <iostream>
#include <thread>
#include <mutex>

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
    for(int i = 0;i < 100000 ;i++){
        m1.lock();
        m2.lock();
        cout << "fun1" << i << endl;
        m1.unlock();
        m2.unlock();
    }
}

void fun2(){
    for(int i = 0;i < 100000 ;i++){
        m2.lock();
        m1.lock();
        cout << "fun2" << i << endl;
        m1.unlock();
        m2.unlock();
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

    return 0;

}