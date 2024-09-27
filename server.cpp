#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>
#include <string>


using namespace std;

int main(){
    //1、创建套接字
    int server_socket = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);

    if (server_socket == -1){
        cout << "error ,socket 创建失败" << endl;
        return 0;
    }
    else{
        cout << "socket 创建成功" << endl;
    }
        

    //2、绑定socket 
    string ip = "127.0.0.1";
    int port = 8080;

    struct sockaddr_in sockaddr;
    memset(&sockaddr,0,sizeof(sockaddr));
    sockaddr.sin_family = AF_INET;
    sockaddr.sin_addr.s_addr = inet_addr(ip.c_str());
    sockaddr.sin_port = htons(port);

    if(::bind(server_socket,(struct sockaddr *)&sockaddr,sizeof(sockaddr)) < 0){
        printf("socket bind error ,error = %d errmsg = %s",errno,strerror(errno));
        return 0;
    }else{
        cout << "socket bind success:ip = " << ip.c_str() <<", port = " << port << endl;
    }

    //3、监听
    if(::listen(server_socket,1024)< 0){
        cout << "socket listen error:error = " << errno << ", errmsg = " << strerror(errno) << endl;
    }else{
        cout << "socket listen success "<< endl;
    }

    // 4、接受连接
    while(true){
        int connfd = accept(server_socket,nullptr,nullptr);
        if(connfd < 0){
            cout << "socket accept error:error = " << errno << ", errmsg = " << strerror(errno) << endl;
            return 0;
        }
        char data[1024] = {0};

        // 5、接受客户端数据
        size_t len = recv(connfd,data,sizeof(data),0);
        cout << "recv: connfd = " << connfd << ",msg = " << data << endl;

        // 6、向客户端发送数据
        send(connfd,data,len,0);
    }

    // 7、关闭socket
    close(server_socket);

    return 1;

}