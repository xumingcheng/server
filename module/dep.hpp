//
// Created by 请输入我的名字 on 2024/8/12.
//

#ifndef UN_DEP_HPP
#define UN_DEP_HPP
class otherdep{

private:
    otherdep()
    {
#ifdef _WIN32
        //启动Windows socket 2.x环境
        WORD ver = MAKEWORD(2, 2);
        WSADATA dat;
        WSAStartup(ver, &dat);
#endif

#ifndef _WIN32
        //if (signal(SIGPIPE, SIG_IGN) == SIG_ERR)
		//	return (1);
		//忽略异常信号，默认情况会导致进程终止
		signal(SIGPIPE, SIG_IGN);
#endif
    }

    ~otherdep()
    {
#ifdef _WIN32
        //清除Windows socket环境
        WSACleanup();
#endif
    }
public:
    static void Init()
    {
        static  otherdep obj;
    }
};

#define LOG_MSG(level,format,...) \
printf("%s <%s:%d> " format "\n",level==0? "INFO":"ERROR",__FUNCTION__,__LINE__,##__VA_ARGS__);
typedef struct ev_loop Ev_loop;
typedef  ev_io Ev_io;
#define Handle_Ok 1
#define Handle_Fail 0
#endif //UN_DEP_HPP
