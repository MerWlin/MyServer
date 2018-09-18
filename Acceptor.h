#ifndef ACCEPTER_H
#define ACCEPTER_H

#include "Channel.h"
#include <memory>
#include <functional>
#include "EventLoop.h"

namespace MyServer 
{
#define MAX_LISTENFD 10000

class Acceptor:public std::enable_shared_from_this<Acceptor>
{
    public:
        Acceptor(EventLoop* loop);
        ~Acceptor();
        void onAccept(int sockFd, EventLoop* loop);
        std::shared_ptr<Channel> getAcceptChannel();
    private:
        int bindAndListen();
        EventLoop* loop;
};
}
#endif