//
// Created by 请输入我的名字 on 2024/8/29.
//

#ifndef SERVER_WORKER_H
#define SERVER_WORKER_H
#include <deque>
#include <mutex>
#include "session.h"
struct worker
{
public:
    ev_async _io;
    std::mutex _mutex;
    std::deque<cellClient *>_cellClientbuf;
    std::unique_ptr<session> _session;
    void addClient(cellClient *pclient)
    {
        std::lock_guard<std::mutex> lock(_mutex);
        _cellClientbuf.push_back(pclient);
    }

private:
    SOCKET _fd;
    //Ev_loop *_loop;

};
#endif //SERVER_WORKER_H
