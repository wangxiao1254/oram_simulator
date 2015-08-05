#ifndef CIRCUIT_ORAM_OPT_H__
#define CIRCUIT_ORAM_OPT_H__
#include "circuit_oram/circuit_oram.h"

/*
 */
class CircuitOramOpt : public CircuitOram
{
   public:
      int cnt = 0, cnt2 = 0;
      int naccess, nevict;
      CircuitOramOpt(int _logN, int capacity, int nace, int nevi)
         :CircuitOram(_logN, capacity),
         naccess(nace),
         nevict(nevi)
   {
   }


      bool access(int identifier)
      {
         bool res = readAndRemove(identifier);
         stash->add(identifier);
         update_pos(identifier);
         cnt2++;
         if(cnt2 == naccess) {
            cnt2 = 0;
            for(int i = 0; i < nevict; ++i) {
               flush(reverse_order());
            }
         }
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
