#ifndef PATH_ORAM_DETER_H__
#define PATH_ORAM_DETER_H__
#include "path_oram/path_oram.h"

class PathOramDeter : public PathOram
{
   public:
      int cnt = 0;
      PathOramDeter(int _logN, int capacity)
         :PathOram(_logN, capacity)
      {
      }

      bool access(int identifier)
      {
         bool res = readAndRemove(identifier);
         stash.insert(identifier);
         update_pos(identifier);
         int a = reverse_order();
         flush(a);
         return res;
      }

      int reverse_order()
      {
         int res = 0;
         int tmp = cnt;
         for(int i = 1; i < h; ++i)
         {
            res<<=1;
            res|=((tmp&1)==1);
            tmp>>=1;
         }
         cnt = (cnt + 1 )%(1<<(h-1));
         return res;
      }
};
#endif// PATH_ORAM_DETER_H__
