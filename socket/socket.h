#include <iostream>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>
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

    protected:
    string m_ip;
    int m_port;
    int m_socketfd;
};
