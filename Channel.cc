#include "Channel.h"
using namespace MyServer;

Channel::Channel(int sockFd):sockFd(sockFd), events(-1), rEvents(-1)
 {
 }

Channel::~Channel()
{
}

int Channel::getEvents()
{
    return events;
}

void Channel::setEvents(int events)
{
    this->events = events;
}

int Channel::getREvents()
{
    return rEvents;
}

void Channel::setREvents(int rEvents)
{
    this->rEvents = rEvents;
}

int Channel::getSockFd()
{
    return sockFd;
}

void Channel::setEventHandler(std::function<void(void*)> handler)
{
    this->handler = handler;
}

void Channel::handleEvent()
{
    handler(NULL);
}