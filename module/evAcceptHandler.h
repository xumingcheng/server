//
// Created by 请输入我的名字 on 2024/8/27.
//

#ifndef UN_EVACCEPTHANDLER_H
#define UN_EVACCEPTHANDLER_H
#include <ev.h>
#include "network.hpp"
#include <memory>
struct worker
{
public:
    ev_io _io;
    struct ev_loop* get_loop()
    {
        return _loop;
    }
    void set_loop(ev_loop *loop)
    {
        _loop = loop;
    }
private:
    struct ev_loop *_loop;

};
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
void listenHandleCb(struct ev_loop *loop, ev_io *_w, int revents)
{
    FServer* Server = static_cast<FServer*>_w->data;
    Server->a;

}
class evServer :public FServer
{
public:
    evServer()
    {
        initsoket();
        Bind("144",112);
    }
    void evStart(int n)
    {
        for(auto i= 0;i < n;i++)
        {
            auto _woker = std::make_unique<worker>();
            auto loop = ev_loop_new(get_ev_loop_flags());
            _woker->set_loop() = &loop;
            _woker->_io.data = _woker.get();
            ev_async_init(_woker->_io, worker_acceptcb);
            ev_async_start(loop,&_woker->_io);
            std::thread t (workerRun,_woker.get());
            _pWorker.push_back(_woker);
        }

    }
private:
    ev_io _io_watcher;
    std::vector<std::unique_ptr<worker>> _pWorker;
};
#endif //UN_EVACCEPTHANDLER_H
