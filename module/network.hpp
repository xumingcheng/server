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
#include <wspiapi.h>
#include "dep.hpp"
#include "cellServer.hpp"
#include "evAcceptHandler.h"


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
class FServer;

namespace RUN{
    void listenAcceptcb(Ev_loop *loop,Ev_io *ioWatcher,int event)
    {
        auto* ser = static_cast<FServer*>ioWatcher->data ;
        //ser->_evs.
        ser->AcceptHandler();
    }
}
class FServer{
public :
    FServer(std::shared_ptr<evServer>pevs,Ev_loop *_loop):_socket(INVALID_SOCKET),_evs(std::move(pevs)),_loop(_loop)
    {
        initsoket();
        Bind("172.20.140.103",4569);
        Listen(64);
        ev_io_init(&_ioWatcher,RUN::listenAcceptcb,getSocket(),EV_READ);
        _ioWatcher.data = this;
        ev_io_start(_loop,&_ioWatcher);
    }
    FServer():_socket(INVALID_SOCKET)
    {
        initsoket();
        Bind("172.20.140.103",4569);
        Listen(64);
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
    void AcceptHandler()
    {
       SOCKET cSocket = INVALID_SOCKET;
       for(;true;)
       {
           cSocket = accept(_socket, nullptr, nullptr);
           if(cSocket == INVALID_SOCKET)
           {
               break;
           }
           _evs->acceptConnect(cSocket);

       }
       struct sockaddr_in addr = {0};
       int n = sizeof(sockaddr_in);
        cSocket = accept(_socket, (sockaddr*)&addr, reinterpret_cast<socklen_t *>(&n));
        if(cSocket == INVALID_SOCKET)
        {
            LOG_MSG(1,"accept fail socket:[%lld]",_socket);
        }

    }
    void Close()
    {

    }
private:
    void ServerOnRun()
    {
      while(_serverIsRun)
      {
#if 0
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
    bool _serverIsRun;
    std::shared_ptr<evServer> _evs;
    Ev_loop * _loop;
    Ev_io _ioWatcher;

};



#endif //UN_NETWORK_HPP
