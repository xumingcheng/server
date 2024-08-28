//
// Created by 请输入我的名字 on 2024/8/14.
//

#ifndef UN_CELLCLIENT_HPP
#define UN_CELLCLIENT_HPP
//#include "network.hpp"

#define RECV_BUFF_SZIE 8192
#define SEND_BUFF_SZIE 10240
#include "cellBuf.hpp"
class cellClient
{
private:
    SOCKET _sockFd;
    cellBuf _recCellbuf;
    cellBuf _sendCellbuf;
    int _id;
    int _serverId;
public:
    cellClient(SOCKET csocket = INVALID_SOCKET,int sendSize = SEND_BUFF_SZIE,int Recsize = SEND_BUFF_SZIE): _recCellbuf(Recsize),
                                                                                                            _sendCellbuf(sendSize)
    {
        _sockFd = csocket;
        static int num = 1;;
        _id = num++;
    }
    long long getSock()
    {
        return _sockFd;
    }
    void setServerId(int Id)
    {
        _id = Id;
    };

};
#endif //UN_CELLCLIENT_HPP
