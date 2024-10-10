#include "client_socket.h"


client_socket::client_socket(const string &ip, int port){
    connect(ip,port);
}