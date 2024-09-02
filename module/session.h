//
// Created by 请输入我的名字 on 2024/9/2.
//

#ifndef SERVER_SESSION_H
#define SERVER_SESSION_H
#include "utils.h"
#include "Handle.h"
#include <set>
class session
{
public:
    session(Ev_loop* loop):_loop(loop){}
    Ev_loop *get_loop()
    {
        return _loop;
    }
    void acceptConnect_handle(cellClient *client)
    {
       if(Handle_Fail == utils::set_socket_no_delay(client->getSock()))
       {
           return;
       }
        auto handler_ =  std::make_unique<handler>(client->getSock(),this);
       handler_->connect_make();
        addHandler(handler_.release());

    }
    void addHandler(handler * handler)
    {
        handler_set.insert(handler);
    }
private:
    Ev_loop* _loop;
   std::set<handler*> handler_set;


};
#endif //SERVER_SESSION_H
