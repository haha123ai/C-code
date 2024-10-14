#include <iostream>
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
    Socket(int socket);
    ~Socket();
    bool bind(const string ip,int port);
    bool listen(int size);
    int accept();
    int connect(const string ip,int port);
    int recv(char * buf,int len);
    int send(const char * buf,int len);
    void close();

    protected:
    string ip;
    int port;
    int socket;
};