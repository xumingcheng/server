//
// Created by 请输入我的名字 on 2024/8/12.
//

#ifndef UN_EVENT_H
#define UN_EVENT_H
#include "cellClient.hpp"
class NetEvent{
public :
    //客戶端加入事件
    virtual void ClientEventAdd(cellClient *ptClient ) = 0;
    virtual void ClientEventLeave(cellClient *ptClient ) = 0;
    virtual void ClientEventRec(cellClient *ptClient ) = 0;
};
#endif //UN_EVENT_H
