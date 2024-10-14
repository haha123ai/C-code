#include <iostream>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>
using namespace std;

int main(){

    //1、创建socket
    int clien_socket = socket(AF_INET,SOCK_STREAM,0);
    if(clien_socket < 0 ){
        cout << "client_socket build false" << endl;
        return 0;
    }else{
        cout << "client_socket build success" << endl;
    } 

    //2、发起连接 
    string ip = "127.0.0.1";
    int port = 8080;
    struct sockaddr_in sockaddr;
    sockaddr.sin_family = AF_INET;
    sockaddr.sin_port = htons(port);
    sockaddr.sin_addr.s_addr = inet_addr(ip.c_str());
    if(::connect(clien_socket,(struct sockaddr *)&sockaddr,sizeof(sockaddr)) < 0){
        cout << "client connect false" << endl;
        return 0;
    }else{
        cout << "client connect success" << endl;
    }

    //3、发送数据
    cout << "请输入需要发送的信息： " ;
    string data;
    cin >> data;
    ::send(clien_socket,&data,sizeof(data),0);

    //4、接受数据
    ::recv(clien_socket,&data,sizeof(data),0);
    cout << "recv data:"<< data << endl;

    //5、关闭socket
    close(clien_socket);
    return 0;
}
