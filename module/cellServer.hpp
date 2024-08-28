//
// Created by 请输入我的名字 on 2024/8/13.
//

#ifndef UN_CELLSERVER_HPP
#define UN_CELLSERVER_HPP
#include "Event.h"
#include "cellTask.hpp"
#include "cellThread.hpp"
#include <cstdio>

//#include<functional>
#include "cellClient.hpp"
#include <mutex>
//#include <vector>
class cellServer
{
   private :
    NetEvent *ptEvent;
   std::map<SOCKET,cellClient*> _pCellClientbuf;
    cellThread _cellThread;
    cellTask _cellTask;
    bool _isRun = FALSE;
    std::vector<cellClient *> _pCellClient;
    int count = 0;
    std::mutex _mutex;
    int _serverId = 0;
    bool _statuschange = FALSE;
    fd_set _fdbk ;


   //typedef std::func
   public:
    cellServer(int serverId):_serverId(serverId)
    {
        std::cout<<"cell server construct"<<std::endl;
    }
    void SetEvent(NetEvent *pEvent)
    {
        ptEvent = pEvent;
    }
    void cellOnRun(cellThread *pcellthread)
    {

        for(;pcellthread->isRun;)
        {
            if(!_pCellClient.empty())
            {
                std::lock_guard<std::mutex> lock(_mutex);
                for(auto _tmpClient : _pCellClient)
                {
                    _pCellClientbuf[_tmpClient->getSock()] = _tmpClient;
                    _tmpClient->setServerId(getServerId());
                    if(ptEvent)
                        ptEvent->ClientEventAdd(_tmpClient);
                    _statuschange =TRUE;
                }
                _pCellClient.clear();
            }
            fd_set fdRead;
            fd_set fdWrite;
            SOCKET maxSock = _pCellClientbuf.begin()->second->getSock();
            if(_statuschange ==TRUE)
            {
                //SOCKET maxSock = _pCellClientbuf.begin()->second->getSock();
                FD_ZERO(&fdRead);
                for(auto pclient : _pCellClientbuf)
                {
                    FD_SET (pclient.second->getSock(),&fdRead);
                    if(maxSock < pclient.second->getSock())
                    {
                        maxSock = pclient.second->getSock();
                    }
                }
                memcpy(&_fdbk,&fdRead,sizeof (fd_set));
            }
            memcpy(&fdWrite,&_fdbk,sizeof(fdWrite));
            timeval t = {0,1};
            int ret = select(maxSock+1,&fdRead,&fdWrite,0,&t);
            if(ret < 0)
            {
                LOG_MSG(2,"Select Fail");
                pcellthread->EXIT();
                return;
            }
            cellRead(&fdWrite);
        }

    }
    void cellRead(fd_set *fdRead )
    {
        for(auto _client :_pCellClientbuf)
        {
            if(FD_ISSET(_client.second->getSock(),fdRead) > 0)
            {

            }
        }
    }
    void cellWrite( fd_set* fdWrite )
    {

    }
    void cellStart()
    {
        _cellTask.cellTaskStart();
        _cellThread.cellThreadStart(nullptr,
                                    [this](cellThread *pcellthread)
                                    {
                                        cellOnRun(pcellthread) ;
                                    },
                                    nullptr);
    }
    size_t getclientcount()
    {
        return _pCellClientbuf.size()+_pCellClient.size();
    }
    void cellAddClient(cellClient*pccellCLient)
    {
        std::lock_guard<std::mutex> lock(_mutex);
        _pCellClient.push_back(pccellCLient);
    }
    int getServerId()
    {
        return _serverId;
    }

};
#endif //UN_CELLSERVER_HPP
