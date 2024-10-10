#include <iostream>
#include <string>
#include "socket.h"
#pragma once

using namespace std;
class client_socket : public Socket{
    public:
    client_socket(const string &ip, int port);
};
