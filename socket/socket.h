#include <iostream>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#pragma once

using namespace std;
class Socket{
    public:
    Socket();
    Socket(int sockfd);
    ~Socket();
    bool bind(const string &ip,int port);
    bool listen(int backlog);
    bool connect(const string &ip,int port);
    int accept();
    void send(const char * buf,int len);
    int recv(char * buf,int len);
    void close();

    //将socket的阻塞IO转换成非阻塞IO
    bool set_non_blocking();

    //设置发送缓冲区的大小
    bool set_send_buffer(int size);

    //设置接受缓冲区大小
    bool set_recv_buffer(int size);

    protected:
    string m_ip;
    int m_port;
    int m_socketfd;
};
