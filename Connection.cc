#include "Connection.h"
using namespace MyServer;

Connection::Connection(){}

Connection::~Connection(){}

void Connection::onRead(int sockFd, EventLoop* loop, const std::shared_ptr<Channel>&channel)
{
    // Read sth.
    char buf[20];
    int rLen = read(sockFd, buf, 10);
    if(rLen == 0)
    {
        std::cout<<"Connection close by peer."<<std::endl;
        loop->rmvChannel(channel);
    }
    std::cout<<"Data read: ";
    for(int i = 0; i < rLen; ++i)
        std::cout<<buf[i];
    std::cout<<std::endl;
   
   //write sth;
   /*
    buf[rLen-1] = '2';
    buf[rLen] = '3';
    buf[rLen+1] = '3';
    buf[rLen+2] = '\n';*/
    write(sockFd, buf, rLen);
}