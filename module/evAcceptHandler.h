//
// Created by 请输入我的名字 on 2024/8/27.
//

#ifndef UN_EVACCEPTHANDLER_H
#define UN_EVACCEPTHANDLER_H
//#include <ev.h>
#include "cellClient.hpp"
#include <deque>
#include "worker.h"
void workerRun(worker* pworker)
{
    ev_asyn_run(pworker->get_loop(),0);
}
void acceptRun(ev_loop *loop)
{
    ev_run(loop,0);
}
int get_ev_loop_flags() {
    if (ev_supported_backends() & ~ev_recommended_backends() & EVBACKEND_KQUEUE) {
        return ev_recommended_backends() | EVBACKEND_KQUEUE;
    }

    return 0;
}
void worker_acceptcb(struct ev_loop *loop, ev_async *_w, int revents)
{

}
class evServer
{
public:
    evServer():_count(0)
    {

    }
    void evStart(int n)
    {
        for(auto i= 0;i < n;i++)
        {
            auto _woker = std::make_unique<worker>();
            auto loop = ev_loop_new(get_ev_loop_flags());
            _woker->set_loop(&loop) ;
            _woker->_io.data = _woker.get();
            ev_async_init(_woker->_io, worker_acceptcb);
            ev_async_start(loop,&_woker->_io);
            std::thread t (workerRun,_woker.get());
            _pWorker.push_back(_woker);
        }
    }
    void acceptConnect(SOCKET fd)
    {
        auto &_workerItem = _pWorker[_count];
        if(_count == 3)
        {
            _count++;
        }else
        {
            _count = 0;
        }
        //四个线程确保只有一个线程访问去访问worker




    }

private:
    std::vector<std::unique_ptr<worker>> _pWorker;
    int _count ;
};
#endif //UN_EVACCEPTHANDLER_H
