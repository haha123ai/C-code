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
    /*socket(
        int af,  协议地址簇，IPV4、IPV6对应的分别是AF_INET,AF_INET6
        int type, 类型，流式协议，帧式协议 sock_stream,sock_DGRAM
        int protocol 保护协议，一般就是写0
    )
    */
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

    /*
    struct sockaddr_in {
	sa_family_t     sin_family; 协议地址簇，和创建的socket对应
	in_port_t       sin_port;  端口
	struct  in_addr sin_addr;  ip地址
	char            sin_zero[8];  保留地址
};*/
    struct sockaddr_in sockaddr;
    memset(&sockaddr,0,sizeof(sockaddr)); //具体来说，它的作用是将 sockaddr 结构的所有字节设置为 0。
    sockaddr.sin_family = AF_INET;
    sockaddr.sin_addr.s_addr = inet_addr(ip.c_str()); // inet_addr 将字符串ip转换成整数ip
    sockaddr.sin_port = htons(port); //存在大小端的问题，需要将小端序转大端序

    /*
    bind
    (int, 套接字
    const struct sockaddr *, 
    socklen_t
    )

    struct sockaddr {   使用此方便拓展   
	sa_family_t     sa_family;      
	char            sa_data[14];    
}
    */

    if(::bind(server_socket,(struct sockaddr *)&sockaddr,sizeof(sockaddr)) < 0){
        printf("socket bind error ,error = %d errmsg = %s",errno,strerror(errno));
        return 0;
    }else{
        cout << "socket bind success:ip = " << ip.c_str() <<", port = " << port << endl;
    }

    //3、监听
    /*
    int listen(
        socket s, 套接字
        int backlog 长度
    )
    */
    if(::listen(server_socket,1024)< 0){
        cout << "socket listen error:error = " << errno << ", errmsg = " << strerror(errno) << endl;
    }else{
        cout << "socket listen success "<< endl;
    }

    // 4、接受连接
    while(true){
/*
int accept(
    int, 监听套接字
    struct sockaddr * __restrict,  客户端的ip地址端口号
    socklen_t * __restrict  结构大小
)
accept 返回的客户端的socket才是根客户端可以通讯的一个socket
阻塞函数，等到客户端连接就接受连接，否则就返回连接
*/
        int connfd = accept(server_socket,nullptr,nullptr);
        if(connfd < 0){
            cout << "socket accept error:error = " << errno << ", errmsg = " << strerror(errno) << endl;
            return 0;
        }

        char data[1024] = {0}; //接受数据

        // 5、接受客户端数据
/*
int recv(
    socket s ,  //客户端socket
    char *buf,  // 接受数据存放位置
    int len,    //接受的长度
    int flags   //标示位 0
)
*/
        size_t len = recv(connfd,data,sizeof(data),0);
        cout << "recv: connfd = " << connfd << ",msg = " << data << endl;

        // 6、向客户端发送数据
        send(connfd,data,len,0);
    }

    // 7、关闭socket
    close(server_socket);

    return 1;

}