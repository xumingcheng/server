#include <iostream>
#include <cstdio>
#include "myServer.hpp"
#include <getopt.h>
#include "evAcceptHandler.h"
#include <memory>

int main(int argc,char **argv) {
    int opt_index = 0;
    struct option long_options[]=
    {
            {"help",no_argument, nullptr,'h'},
            {"type",required_argument, nullptr,'t'},
            {"version",required_argument, nullptr,'v'},
            {"?",no_argument, nullptr,'?'},
            {nullptr,0, nullptr,0},
    };
    int options = 0;

    while( (options = getopt_long(argc, argv, "ht:v:?ak", long_options, &opt_index) )!= -1)
    {
      if(options == -1)
      {
          break;
      }
      switch (options)
      {
          case 'h':
              std::cout<<"you need help ,but I cant help you"<<std::endl;
              break;
          case 'a':
              std::cout<<"this is a short"<<std::endl;
              break;
          case 't':
              std::cout<<"type is "<<optarg<<std::endl;
              if(strcmp(optarg,"ev") == 0)
              {
                  typeIO[EV_TYPE] = true;
              }else if(strcmp(optarg,"epoll") == 0)
              {
                  typeIO[EPOLL_TYPE]= true;
              }else
                  typeIO[SELECT_TYPE] =true;
              break;
          case 'k':
              std::cout<<"this is a short "<<std::endl;
              break;
          case 'v':
              std::cout<<"this version is  "<<optarg<<std::endl;
              break;
          default:
              std::cout<<"this is default "<<std::endl;
              break;
      }
    }
    std::cout << "Hello, World!" << std::endl;
//#else
    Ev_loop loop = EV_DEFAULT;
   // auto evS = new evServer ;
    auto _evServer = std::make_shared<evServer>();

    _evServer->evStart(4);
    new FServer(_evServer,&loop);
    ev_run(loop,0);


     //evServer  v(&loop);


    //ev_run(loop,0);

}
