#ifndef EPOLL_H
#define EPOLL_H
#define MAXEVENTNUM 1000
#include <sys/epoll.h>
#include "Channel.h"
#include <iostream>
#include <vector>
#include <memory>


namespace MyServer
{
class EventLoop;

class Epoll
{
    public:
        Epoll(EventLoop* loop);
        ~Epoll();
        void poll(std::vector<std::shared_ptr<Channel>>& channelList);
        void updateList(const std::shared_ptr<Channel> &channel, int op = 0);
    private:
        int epollFd;
        struct epoll_event epollEventList[MAXEVENTNUM];
        EventLoop* loop;
};

}
#endif