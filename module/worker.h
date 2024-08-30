//
// Created by 请输入我的名字 on 2024/8/29.
//

#ifndef SERVER_WORKER_H
#define SERVER_WORKER_H
#include <deque>
typedef struct ev_loop Ev_loop;
typedef  ev_io Ev_io;
struct worker
{
public:
    ev_async _io;
    Ev_loop* get_loop()
    {
        return _loop;
    }
    void set_loop(Ev_loop *loop)
    {
        _loop = loop;
    }
private:
    Ev_loop *_loop;
    std::deque<cellClient *>_cellClientbuf;
};
#endif //SERVER_WORKER_H
