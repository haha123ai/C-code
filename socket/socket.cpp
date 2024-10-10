#include "socket.h"

Socket::Socket(){  // 创建socket
    m_socketfd = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    if(m_socketfd == -1){
        cout << "socket build failed" << endl;
        return;
    }else{
        cout << "socket build success" << endl;
    }
}

Socket::Socket(int sockfd):m_ip(""),m_port(0),m_socketfd(sockfd){

}

Socket::~Socket(){
    close();
}

bool Socket::bind(const string &ip,int port){  // 实现连接
    struct sockaddr_in sockaddr;
    memset(&sockaddr,0,sizeof(sockaddr));
    sockaddr.sin_family = AF_INET;
    sockaddr.sin_port = htons(port);
    if(ip.empty()){
        sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    }else{
        sockaddr.sin_addr.s_addr = inet_addr(ip.c_str());
    }

    if(::bind(m_socketfd,(struct sockaddr *)&sockaddr,sizeof(sockaddr)) < 0){
        cout << "socket bind error,error = "<< errno << ",errmsg = " << strerror(errno) << endl;
        return false;
    }else{
        cout << "socket bind success,ip = " << ip << ",port = " << port << endl;
        m_ip = ip;
        m_port = port;
        return true;
    }
}

bool Socket::listen(int backlog){  //实现监听
    int lis = ::listen(m_socketfd,backlog);
    if(lis < 0){
        cout << "socket listen error " << endl;
        return false;
    }else{
        cout << "socket listen success" << endl;
        return true;
    }
}

bool Socket::connect(const string &ip,int port){
    struct sockaddr_in sockaddr;
    memset(&sockaddr,0,sizeof(sockaddr));
    sockaddr.sin_family = AF_INET;
    //sockaddr.sin_addr.s_addr = inet_addr(ip.c_str());
    sockaddr.sin_port = htons(port);

        // 使用 inet_pton 代替 inet_addr
    if (inet_pton(AF_INET, ip.c_str(), &sockaddr.sin_addr) <= 0) {
        cout << "Invalid IP address format: " << ip << endl;
        return false;
    }

    // 尝试连接
    if (::connect(m_socketfd, (struct sockaddr *)&sockaddr, sizeof(sockaddr)) < 0) {
        cout << "Socket connect error: error = " << errno << ", errmsg = " << strerror(errno) << endl;
        return false;
    }
    m_ip = ip;
    m_port = port;
    return true;
}

int Socket::accept(){
    int conffd = ::accept(m_socketfd,nullptr,nullptr);
    if(conffd < 0){
        cout << "socket accept error:error = " << errno << ",errmsg = " << strerror(errno) << endl;
        return -1;
    }else{
        cout << "socket accept success" << endl;
        return conffd;
    }
}

void Socket::send(const char * buf,int len){
    ::send(m_socketfd,buf,len,0);
}

int Socket::recv(char * buf,int len){
    return ::recv(m_socketfd,buf,len,0);
}

void Socket:: close(){
    if(m_socketfd > 0){
        ::close(m_socketfd);
        m_socketfd = 0;
    }

}

