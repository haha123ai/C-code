#include "server_socket.h"

server_socekt::server_socekt(const string &ip,int port){
    set_send_buffer(10 * 1024);
    set_recv_buffer(10 * 1024);
    bind(ip,port);
    listen(1024);

}