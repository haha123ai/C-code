#include <iostream>
#include <thread>
#include <string>
using namespace std;

void fun1(){
    cout << "多线程使用fun1" << endl;
}
void fun2(int data){
    cout << "多线程使用参数fun2:" << data << endl;
}

int main(){

    //1、创建线程
    thread thr1(fun1);
    thread thr2(fun2,222); 

    //2、主程序等待线程执行
    thr1.join();
    thr2.join();

    return 0;
}