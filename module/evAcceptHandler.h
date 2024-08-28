//
// Created by 请输入我的名字 on 2024/8/27.
//

#ifndef UN_EVACCEPTHANDLER_H
#define UN_EVACCEPTHANDLER_H
#include <ev.h>
#include "network.hpp"
#include <memory>
class evServer
{
public:
    evServer(struct ev_loop *loop,std::shared_ptr<MyServer> ptServer):_psr(std::move(ptServer)),fd(INVALID_SOCKET)
    {
        _psr->initsoket();
        _psr->Bind("127.0.0.1",4567);
        _psr->Listen(64);
        _psr->start(4);
    }
    SOCKET handleAccept()
    {


    }
private:
    ev_io _io_watcher;
    std::shared_ptr<MyServer> _psr;
    cellThread cellTh;
    SOCKET fd ;

};
#endif //UN_EVACCEPTHANDLER_H
