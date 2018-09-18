#ifndef CHANNEL_H
#define CHANNEL_H
#include <functional>

namespace MyServer
{
class Channel
{
    public:
        Channel(int sockFd);
        ~Channel();
        int getEvents();
        void setEvents(int events);
        int getREvents();
        void setREvents(int rEvents);
        int getSockFd();
        void handleEvent();
        void setEventHandler(std::function<void(void*)> handler);
    private:
        int sockFd;
        int events;
        int rEvents;
        std::function<void(void*)> handler;
};
}
#endif