//
// Created by 请输入我的名字 on 2024/8/13.
//
#include "network.hpp"
#include "cellClient.hpp"

#ifndef UN_MYSERVER_HPP
#define UN_MYSERVER_HPP
class MyServer :public FServer
{
    virtual void ClientEventAdd(cellClient *ptClient ){

        FServer::ClientEventAdd(ptClient);
   }
    virtual void ClientEventLeave(cellClient *ptClient ){

        FServer::ClientEventLeave(ptClient);
    }
    virtual void ClientEventRec(cellClient *ptClient ){

        FServer::ClientEventRec(ptClient);
    }
};
#endif //UN_MYSERVER_HPP
