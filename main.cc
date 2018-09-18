#include "TcpServer.h"
#include "EventLoop.h"
using MyServer::EventLoop;
using MyServer::TcpServer;

int main(int args, char** argv)
{
    EventLoop loop;
    TcpServer tcpserver(&loop);
    tcpserver.start();
    loop.loop();
    return 0;
}