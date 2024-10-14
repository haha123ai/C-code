#include <iostream>
#include "socket.h"
#include <string>
using namespace std;

int main(){

    //1、创建客户端socket
    Socket client;
    //2、建立连接
    client.connect("127.0.0.1",8080);
    //3、发送数据
    string data = "练习socket,nnnnn";
    client.send(data.c_str(),sizeof(data));

    //4、接受数据
    char buf[1024] = {0};
    client.recv(buf,sizeof(data));
    cout << "客户端接受的信息：" << buf << endl;
    //5、关闭socket
    client.close();

    return 0;
}