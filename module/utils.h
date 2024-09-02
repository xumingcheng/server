//
// Created by 请输入我的名字 on 2024/9/2.
//
#include "dep.hpp"
#include "network.hpp"
namespace utils
{
    int set_socket_no_delay(SOCKET fd)
    {
        const char yes = 1;
        if(setsockopt(fd,IPPROTO_TCP,TCP_NODELAY,&yes,sizeof(yes)) == -1)
        {
            return Handle_Ok;
        }
        else
        {
            return Handle_Fail;
        }
    }
}