//
// Created by 请输入我的名字 on 2024/8/13.
//

#ifndef UN_CELLTHREAD_HPP
#define UN_CELLTHREAD_HPP
#include <functional>
#include<thread>
#include<mutex>
class cellThread {
private:
    typedef std::function<void(cellThread*)>  FUNCCALL;
    FUNCCALL _fCreate;
    FUNCCALL _fRun;
    FUNCCALL _fClear;
public:
    cellThread()
    {
        std::cout<<"cell thread construct"<<std::endl;
    }
    void cellThreadStart(FUNCCALL pCreate = nullptr,FUNCCALL pRun= nullptr,FUNCCALL pClear = nullptr)
    {
        if(!isRun)
        {
            if(pCreate)
            {
                _fCreate = pCreate;
            }
            if(pRun)
            {
                _fRun = pRun;
            }
            if(pClear)
            {
               _fClear = pClear;
            }
        }
        //std::thread t (std::bind(&cellThread::cellThreadRun,this));
        std::thread t1 (std::mem_fn(&cellThread::cellThreadRun),this);
        t1.detach();

    }
    void cellThreadRun()
    {
        if(_fCreate)
        {
            _fCreate(this);
        }
        if(_fRun)
        {
            _fRun(this);
        }
        if(_fCreate)
        {
            _fClear(this);
        }
    }
    void EXIT()
    {
        std::lock_guard<std::mutex> lock(_mutex);
        if(isRun)
        {
            isRun = false;
        }

    }
    int isRun = FALSE;
private:
    std::mutex _mutex;


};

#endif //UN_CELLTHREAD_HPP
