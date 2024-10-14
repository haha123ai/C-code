#include <iostream>
#include "socket.h"
using namespace std;

int main(){
    Socket server;
    server.bind("127.0.0.1",8080);
    if(!server.listen(1024))
    {
        return  0;
    }
    while(true){
        int client = server.accept();
        if(client < 0){
            break;
        }
        char data[1024];
        Socket clients(client);
        //接受客户端数据
        ssize_t len = clients.recv(data,sizeof(data));
        cout << "recv data:" << data << endl;

        //发送客户端数据
        clients.send(data,len);
    }

    server.close();
    return 0;
}