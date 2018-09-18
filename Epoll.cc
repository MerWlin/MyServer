#include "Epoll.h"
#include "EventLoop.h"
using namespace MyServer;

Epoll::Epoll(EventLoop* loop):loop(loop)
{
    epollFd = ::epoll_create(MAXEVENTNUM);
    if(epollFd < 0)
        std::cout<<"Epoll create failure"<<std::endl;
}

Epoll::~Epoll()
{

}

void Epoll::poll(std::vector<std::shared_ptr<Channel>>& channelList)
{
    std::cout<<"Polling ......"<<std::endl;
    int fdCnt = ::epoll_wait(epollFd, epollEventList, MAXEVENTNUM, -1);
    if(fdCnt == -1)
    {
        std::cout<<"Epoll wait failed."<<std::endl;
    }
    for(int i = 0; i < fdCnt; ++i)
    {
        std::shared_ptr<Channel>eventChannel(loop->channelRecord[epollEventList[i].data.fd]);
        eventChannel->setREvents(epollEventList[i].events);
        channelList.push_back(eventChannel);
    }
}

void Epoll::updateList(const std::shared_ptr<Channel> &channel, int op)
{
    switch(op) // ADD
    {
        default:
            struct epoll_event ev;
            int channelFd = channel->getSockFd();
            ev.data.fd = channelFd;
            ev.events = channel->getEvents();      
            if(::epoll_ctl(epollFd, EPOLL_CTL_ADD, channelFd, &ev) < 0)
                std::cout<<"Epoll ctrl failed: fd"<<channelFd<<std::endl;
            else
                loop->channelRecord[channelFd] = channel;
    }
}