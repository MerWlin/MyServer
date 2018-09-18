#include "TcpServer.h"
#include "Acceptor.h"
#include <memory>
#include<iostream>

using namespace MyServer;
TcpServer::TcpServer(EventLoop* loop):loop(loop)
{
}

TcpServer::~TcpServer()
{
}
void TcpServer::start()
{
    //Acceptor ac(loop);
    std::shared_ptr<Acceptor>ac(new Acceptor(loop));
    loop->addChannel(ac->getAcceptChannel());
    std::cout<<"Test server started"<<std::endl;
}