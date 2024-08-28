//
// Created by 请输入我的名字 on 2024/8/13.
//
#ifndef UN_MYSERVER_HPP
#define UN_MYSERVER_HPP
#include "network.hpp"
#include "cellClient.hpp"
class sServer :public FServer
{
   public:
    sServer()
    {
        Bind("154",145);
    }

    void serverAddClient(cellClient *pcellClient)
    {
        auto _mincellserver = _pcellServer[0];
        for(auto _cellServer : _pcellServer)
        {
            if(_cellServer->getclientcount() > _mincellserver->getclientcount())
            {
                _mincellserver = _cellServer;
            }
        }
        _mincellserver->cellAddClient(pcellClient);
    }
    void start(int n)
    {
        for(int i = 0;i < n;i++)
        {
            auto cellSer = new cellServer(i+1);
            _pcellServer.push_back(cellSer);
           // cellSer->SetEvent(this);
            cellSer->cellStart();
        }
    }
    private :
    std::vector<cellServer *> _pcellServer;
};
#endif //UN_MYSERVER_HPP
