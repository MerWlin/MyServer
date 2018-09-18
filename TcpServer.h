#ifndef TCPSERVER_H
#define TCPSERVER_H

#include "EventLoop.h"

namespace MyServer
{
    
class TcpServer
{
    public:
        TcpServer(EventLoop* loop);
        ~TcpServer();
        void start();

    private:
        EventLoop* loop;
};

}
#endif