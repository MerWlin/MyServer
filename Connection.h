#ifndef CONNECTION_H
#define CONNECTION_H

#include<iostream>
#include<unistd.h>
#include "EventLoop.h"
#include "Channel.h"
#include <memory>
namespace MyServer
{
class Connection
{
    public:
        Connection();
        ~Connection();
        void onRead(int sockFd, EventLoop* loop, const std::shared_ptr<Channel>&channel);
};
}
#endif