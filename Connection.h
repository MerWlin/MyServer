#ifndef CONNECTION_H
#define CONNECTION_H

#include<iostream>
#include<unistd.h>

namespace MyServer
{
class Connection
{
    public:
        Connection();
        ~Connection();
        void onRead(int sockFd);
};
}
#endif