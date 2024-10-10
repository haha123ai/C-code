#include <iostream>
#include "socket.h"
#include <string>
using namespace std;
#pragma once

class server_socekt :public Socket{
    public:
    server_socekt(const string &ip,int port);

};