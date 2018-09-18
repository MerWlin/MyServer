#include "Acceptor.h"
#include "Connection.h"
#include <sys/socket.h>
#include <unistd.h>
#include<fcntl.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/epoll.h>

using namespace MyServer; 

Acceptor::Acceptor(EventLoop* loop):loop(loop)
{}
Acceptor::~Acceptor()
{}

int Acceptor::bindAndListen()
{
    int on = 1;
    int listenfd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in servaddr;
    fcntl(listenfd, F_SETFL, O_NONBLOCK); 
    setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(12345);
    
    if(-1 == bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr)))
    {
        std::cout << "bind error, errno:" << errno << std::endl; 
    }

    if(-1 == listen(listenfd, MAX_LISTENFD))
    {
        std::cout << "listen error, errno:" << errno << std::endl; 
    }
    return listenfd;
}

std::shared_ptr<Channel> Acceptor::getAcceptChannel()
{
    int listenFd = bindAndListen();
    std::shared_ptr<Channel>acceptChannel(new Channel(listenFd));
    acceptChannel->setEvents(EPOLLIN);
    acceptChannel->setEventHandler(std::bind(&Acceptor::onAccept, shared_from_this(), listenFd, loop));
    return acceptChannel;
}


void Acceptor::onAccept(int sockFd, EventLoop* loop)
{
    struct sockaddr_in clientAddr;
    socklen_t clilen = sizeof(struct sockaddr_in);
    int ioFd = accept(sockFd,(sockaddr*)&clientAddr, (socklen_t*)&clilen);
    if(ioFd > 0)
    {
        std::cout<<"new connection accepted: "
        <<inet_ntoa(clientAddr.sin_addr) 
        <<ntohs(clientAddr.sin_port)
        <<std::endl;
    }
    fcntl(ioFd, F_SETFL, O_NONBLOCK);

    std::shared_ptr<Channel> channel(new Channel(ioFd));
    channel->setEvents(EPOLLIN);
    Connection conn;
    channel->setEventHandler(std::bind(&Connection::onRead, &conn, ioFd, loop, channel));
    loop->addChannel(channel);
}