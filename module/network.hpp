//
// Created by 请输入我的名字 on 2024/8/12.
//


#ifndef UN_NETWORK_HPP
#define UN_NETWORK_HPP
#ifdef _WIN32
#define FD_SETSIZE      256
#define WIN32_LEAN_AND_MEAN
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include<windows.h>
#include<WinSock2.h>
#pragma comment(lib,"ws2_32.lib")
#else
#include<unistd.h> //uni std
	#include<arpa/inet.h>
	#include<string.h>
	#include<signal.h>
	#include<sys/socket.h>
#include <array>

	#define SOCKET int
	#define INVALID_SOCKET  (SOCKET)(~0)
	#define SOCKET_ERROR            (-1)
#endif
#include "Event.h"
#include <map>
#include <vector>
#include "dep.hpp"
#include "cellServer.hpp"
enum {
    EV_TYPE = 0,
    EPOLL_TYPE  ,
    SELECT_TYPE  ,
};
std::array<int, 3>typeIO{0};
#define EV  typeIO[EV_TYPE]
#define EPOLL  typeIO[EPOLL_TYPE]
#define SELECT typeIO[SELECT_TYPE]
#if EV
#include <ev.h>
#endif
struct worker
{
    ev_io _io;
//private:
    struct ev_loop *loop;

};
void workerRun(std::unique_ptr<worker> pworker)
{

}
int get_ev_loop_flags() {
    if (ev_supported_backends() & ~ev_recommended_backends() & EVBACKEND_KQUEUE) {
        return ev_recommended_backends() | EVBACKEND_KQUEUE;
    }

    return 0;
}
void worker_acceptcb(struct ev_loop *loop, ev_async *w, int revents)
{

}
class FServer :public  NetEvent{
public :
    FServer():_socket(INVALID_SOCKET)
    {

    }
    void initsoket()
    {
       otherdep::Init();
       if(_socket != INVALID_SOCKET)
       {
           LOG_MSG(1,"config is wrong Close Server socket [%lld]",_socket);
           Close();
       }
       _socket = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
       if(_socket == INVALID_SOCKET)
       {
           LOG_MSG(1,"create Socket fail  Close Server socket [%lld]",_socket);
           Close();
       }
        LOG_MSG(0,"create Socket Success   socket [%lld]",_socket);
    }
    SOCKET getSocket()
    {
      return _socket;
    }
    void Bind(const char*Ip ,int port)
    {
        int ret= 0;
        sockaddr_in _sin = {0};
        _sin.sin_port = htons(port);
        _sin.sin_family= AF_INET;
        _sin.sin_addr.S_un.S_addr = inet_addr(Ip);
        ret = bind(_socket,(sockaddr*)&_sin,sizeof(_sin));
        if(ret != 0)
        {
            LOG_MSG(1,"bind Socket fail  Close Server socket [%lld]",_socket);
            Close();
        }
        else
        {
            LOG_MSG(0,"bind Socket Success   socket [%lld]",_socket);
        }
    }
    void Listen( int n)
    {
       int ret = 0;
       ret = listen(_socket,n);
       if(ret != 0)
       {
           LOG_MSG(1,"listen  Socket fail  Close Server socket [%lld]",_socket);
           Close();
       }
        LOG_MSG(0,"listen  Socket success  Server socket [%lld]",_socket);
    }
    void Accept()
    {
       SOCKET cSocket = INVALID_SOCKET;
       struct sockaddr_in addr = {0};
       int n = sizeof(sockaddr_in);
        cSocket = accept(_socket, (sockaddr*)&addr, reinterpret_cast<socklen_t *>(&n));
        if(cSocket == INVALID_SOCKET)
        {
            LOG_MSG(1,"accept fail socket:[%lld]",_socket);
        }
        serverAddClient(new cellClient(cSocket));

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
          cellSer->SetEvent(this);
          cellSer->cellStart();
      }
    }
    void evStart(int n)
    {
      for(auto i= 0;i < n;i++)
      {
          auto _woker = std::make_unique<worker>();
          auto loop = ev_loop_new(get_ev_loop_flags());
          _woker->loop = &loop;
          _woker->_io.data = _woker.get();
          ev_async_init(_woker->_io, worker_acceptcb);
          ev_async_start(loop,&_woker->_io);
          std::thread t (workerRun,std::move(_woker));
          _pWorker.push_back(_woker);
      }

    }
   virtual void ClientEventAdd(cellClient *ptClient )
    {
      _clientcount ++;
    }
    virtual void ClientEventLeave(cellClient *ptClient )
    {
        _clientcount--;
    }
    virtual void ClientEventRec(cellClient *ptClient )
    {

    }
    void Close()
    {

    }
private:
    void ServerOnRun()
    {
      while(_serverIsRun)
      {
#if SELECT
          serverTimeMsg();
          fd_set fdRead;
          FD_ZERO(&fdRead);
          FD_SET (_socket,&fdRead);
          timeval t= {0,1};
          auto ret = select(_socket +1,&fdRead,0,0,&t);
          if(ret < 0)
          {
              LOG_MSG(2,"OnRun Select Fail exit");
              Close();
              break;
          }
          if(FD_ISSET(_socket,&fdRead))
          {
              FD_CLR(_socket,&fdRead);
              Accept();
          }
#elseif EV
          auto loop = EV_DEFAULT;

          ev_run(loop,0);


#endif
      }


    }
    void serverTimeMsg()
    {

    }
    int _clientcount;
    SOCKET _socket;
    std::vector<cellServer *> _pcellServer;
    std::vector<std::unique_ptr<worker>> _pWorker;
    bool _serverIsRun;



};



#endif //UN_NETWORK_HPP
