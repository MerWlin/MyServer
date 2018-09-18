#ifndef EVENTLOOP_H
#define EVENTLOOP_H
#include "Channel.h"
#include <memory>
#include <vector>
#include <map>

namespace MyServer
{
class Epoll;

class EventLoop
{
    public:
        EventLoop();
        ~EventLoop();
        void loop();
        void addChannel(const std::shared_ptr<Channel>& channel);
        std::map<int, std::shared_ptr<Channel>> channelRecord;

    private:
        std::shared_ptr<Epoll> poller;     
};
}
#endif