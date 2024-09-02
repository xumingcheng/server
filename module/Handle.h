//
// Created by 请输入我的名字 on 2024/9/2.
//

#ifndef SERVER_HANDLE_H
#define SERVER_HANDLE_H
class session;
//#include "dep.hpp"
//#include "network.hpp"
class handler
{

public:
    handler(SOCKET fd,session *sess):_fd(fd),_session(sess)
    {

    }
    void connect_make()
    {

    }
private:
    SOCKET _fd;
    session *_session;

};
#endif //SERVER_HANDLE_H
