#include <iostream>
#include "socket.h"
#include <string>
using namespace std;

int main(){

    Socket server;

    string ip = "127.0.0.1";
    int port = 8080;
    server.bind(ip,port);
    server.listen(1024);

    while(true){
        int server_accept = server.accept();

        if(server_accept < 0){ 
           break;
        }
        
        Socket client(server_accept);

        char data[1024];
        // 接受客户端数据
        size_t len =  client.recv(data,sizeof(data));
        

        cout << "recver data:" << data << endl;

        // 向客户端发送数据
        client.send(data,len);
    
    }
    server.close();
    

    return 0;
}