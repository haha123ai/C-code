//
// Created by 戴晗 on 2024/10/16.
//
#include <iostream>
#include <thread>

using namespace std;

void fun(int &a){
    a += 1;
    cout << "a: " << a << endl;
}

void fun1(int *a){
    cout << "fun1 a: " << *a << endl;
}

int main(){
    int a = 1;
    thread t1(fun, ref(a)); //ref 会将a转换成引用变量

    if(t1.joinable()){
        t1.join();
    }
    cout <<"local a: " << a << endl;

    // 传递指针或引用指向局部变量的问题
    int *ptr = new int(2);
    thread t2(fun1,ptr);
    //delete(ptr);  // 线程还未运行，就被释放会报错
    t2.join();


    return 0;
}
