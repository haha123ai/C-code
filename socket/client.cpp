#include <iostream>
#include "client_socket.h"
#include <string>
using namespace std;

int main(){
    // // 1、创建socket
    // Socket client;

    // //2、连接服务器
    // client.connect("127.0.0.1",8080);
    client_socket client("127.0.0.1",8080);

    
    //3、发送数据
    string data = "hahahahha,nanan ";
    client.send(data.c_str(),sizeof(data));

    //4、读取数据
    char buf[1024] = {0};
    client.recv(buf,sizeof(data));
    cout << "客户端接收到的数据是：" << buf << endl;

    //5、关闭客户端
    client.close();

    return 0;

}