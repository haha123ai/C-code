#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>
#include <string>
using namespace std;

int main(){
    //1、创建一个socket
    int client_socket = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    if (client_socket == -1){
        cout << "error ,socket 创建失败" << endl;
        return 0;
    }
    else{
        cout << "socket 创建成功" << endl;
    }

    // 2、连接服务端
    string ip = "127.0.0.1";
    int port = 8080;
    struct sockaddr_in sockaddr;
    memset(&sockaddr,0,sizeof(sockaddr));
    sockaddr.sin_family = AF_INET;
    sockaddr.sin_addr.s_addr = inet_addr(ip.c_str());
    sockaddr.sin_port = htons(port);
    if(connect(client_socket,(struct sockaddr *)&sockaddr,sizeof(sockaddr)) < 0){
        cout << "socket connect error:error = " << errno << ",errmsg = " << strerror(errno) << endl;
        return 1;
    }

    // 3、向服务端发送数据
    string data = "hahahahhaha,woocao";
    send(client_socket,data.c_str(),data.size(),0);

    // 4、接受服务端的数据
    char  rev[1024] = { };
    recv(client_socket,rev,sizeof(rev),0);
    cout << "rev : " << rev << endl;

    //5、关闭socket
    close(client_socket);

    return 0;
}