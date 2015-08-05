#ifndef CIRCUIT_ORAM_DETER_H__
#define CIRCUIT_ORAM_DETER_H__
#include "circuit_oram/circuit_oram.h"

/*
*/
class CircuitOramDeter : public CircuitOram
{
   public:
      int cnt = 0;
      CircuitOramDeter(int _logN, int capacity)
         :CircuitOram(_logN, capacity)
      {
      }

      bool access(int identifier)
      {
         bool res = readAndRemove(identifier);
         stash->add(identifier);
         update_pos(identifier);
         int a = reverse_order();
         flush(a);
         a = reverse_order();
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
#endif// CIRCUIT_ORAM_DETER_H__
