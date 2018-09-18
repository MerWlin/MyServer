#include "EventLoop.h"
#include "Epoll.h"
using namespace MyServer;

EventLoop::EventLoop()
{
    poller = std::shared_ptr<Epoll>(new Epoll(this));
}

EventLoop::~EventLoop()
{

}

void EventLoop::loop()
{
    std::cout<<"EventLoop started"<<std::endl;
    while(1)
    {
        std::vector<std::shared_ptr<Channel>> channelList;
        poller->poll(channelList);
        for(int i = 0; i < static_cast<int>(channelList.size()); ++i)
        {
            channelList[i]->handleEvent();
        }
    }
}

void EventLoop::addChannel(const std::shared_ptr<Channel>& channel)
{
    poller->updateList(channel);
}

void EventLoop::rmvChannel(const std::shared_ptr<Channel>& channel)
{
    poller->updateList(channel, 1);
}