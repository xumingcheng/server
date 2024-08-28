//
// Created by 请输入我的名字 on 2024/8/14.
//

#ifndef UN_CELLBUF_HPP
#define UN_CELLBUF_HPP
class cellBuf
{
public:
   cellBuf(int nszie = 8192)
   {
       _nszie = nszie;
       if(_pcbuf == NULL)
       {
           _pcbuf = new char[_nszie];
       }
   }
   ~cellBuf()
   {
       if(_pcbuf != nullptr)
       {
          delete []_pcbuf;
       }
   }
private:
    size_t _nszie;
    char *_pcbuf = NULL;
};
#endif //UN_CELLBUF_HPP
