#include <iostream>
#include <thread>
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
    //thr1.join();
    thr2.join();

    //3、分离，线程脱离主程序后可以自己运行
    //thr1.detach();
    
    //4、返回一个bool值，看能不能调用join函数，
    bool flag = thr1.joinable();
    cout << flag << endl;
    if(flag){
        thr1.join();
    }

    return 0;
}