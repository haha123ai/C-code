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
    int server_socekt = socket(AF_INET,SOCK_STREAM,0);

    if(server_socekt == -1){
        cout << "server_socket build false" << endl;
        return 0;
    }else{
        cout << "server_socket build success" << endl;
    }


    //2、绑定ip port
    string ip = "127.0.0.1";
    int port = 8080;
    struct sockaddr_in sockaddr;
    memset(&sockaddr,0,sizeof(sockaddr));
    sockaddr.sin_port = htons(port);
    sockaddr.sin_addr.s_addr = inet_addr(ip.c_str());
    sockaddr.sin_family = AF_INET;

    if(::bind(server_socekt,(struct sockaddr *)&sockaddr,sizeof(sockaddr)) < 0){
        cout << "bind false" << endl;
        return 0;
    }else{
        cout << "bind success" << endl;
    }

    //3、进行监听
    if(::listen(server_socekt,1024) < 0){
        cout << "listen false" << endl;
        return 0;
    }else{
        cout << "listen success " << endl;
    }


    //4、接受连接
    while(true){
        int client_socket = ::accept(server_socekt,nullptr,nullptr);

        if(client_socket < 0){
            cout << "no clients accept" << endl;
            return 0;
        }else{
            cout << "accept success" << endl;
        }

        //5、接受信息
        char data[1024] = {0};
        ssize_t len = ::recv(client_socket,data,sizeof(data),0);

        cout << "server get data: " << data << endl;
        ::send(client_socket,data,len,0);
    }


    //6、关闭socket
    close(server_socekt);


    return 0;
}