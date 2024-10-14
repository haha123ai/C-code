#include "socket.h"

Socket::Socket(){
    int socket = ::socket(AF_INET,SOCK_STREAM,0);
    if(socket < 0){
        cout << "socket build false" << endl;
        return;
    }
    this->socket = socket;
}

Socket::Socket(int socket){
    this->socket = socket;
}
Socket::~Socket(){
    close();
}

bool Socket::bind(const string ip,int port){
    struct sockaddr_in sockaddr;
    sockaddr.sin_family = AF_INET;
    sockaddr.sin_port = htons(port);
    sockaddr.sin_addr.s_addr = inet_addr(ip.c_str());
    if(::bind(this->socket,(struct sockaddr *)&sockaddr,sizeof(sockaddr)) < 0){
        cout << "socket bind false" << endl;
        return false;
    }else{
        cout << "socket bind success" << endl;
        this->port = port;
        this->ip = ip;
    }
    return true;
}

bool Socket::listen(int size){
    if(::listen(this->socket,size) < 0){
        cout << "socket listen false" << endl;
        return false;
    }else{
        cout << "socket is listening " << endl;
    }
    return true;
}

int Socket::accept(){
    int socket_accept = ::accept(this->socket,nullptr,nullptr);
    if(socket_accept < 0){
        cout << "socket accept false" << endl;
        return -1;
    }
    return socket_accept;
}

int Socket::connect(const string ip,int port){
    struct sockaddr_in sockaddr;
    sockaddr.sin_family = AF_INET;
    sockaddr.sin_addr.s_addr = inet_addr(ip.c_str());
    sockaddr.sin_port = htons(port);

    int sock_connect = ::connect(this->socket,(struct sockaddr *)&sockaddr,sizeof(sockaddr));
    if(sock_connect < 0){
        cout << "socket connect false" << endl;
        return -1;
    }else{
        cout << "socket connect success" << endl;
    }
    return sock_connect;
}

int Socket::recv(char * buf,int len){
    ssize_t sock_recv = ::recv(this->socket,buf,len,0);
    if (sock_recv < 0)
    {
        cout << "no msg" << endl;
        return -1;
    }
    return sock_recv;
}

int Socket::send(const char * buf,int len){
    ssize_t sock_send = ::send(this->socket,buf,len,0);
    if (sock_send < 0)
    {
        cout << "send false" << endl;
        return -1;
    }
    return sock_send;
}

void Socket::close(){
    if(this->socket > 0){
        ::close(this->socket);
        this->socket = 0;
    }
}