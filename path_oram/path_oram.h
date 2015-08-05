#ifndef PATH_ORAM_H__
#define PATH_ORAM_H__
#include "tree_oram.h"

/*
   Path ORAM simulator.
http://dl.acm.org/citation.cfm?id=2516660
 */

class PathOram: public TreeOram
{
   public:
      PathOram(int logN, int capacity)
         :TreeOram(logN, capacity, logN)
      {
      }

      bool access(int identifier)
      {
         int old_pos = index[identifier];
         bool res = readAndRemove(identifier);
         stash->add(identifier);
         update_pos(identifier);
         flush(old_pos);
         return res;
      }

      void flush(int path)
      {
         vector<int> temp;

         for(int level = 0; level <= h; ++level)
         {
            auto buc = tree[bucketAt(path, level)];
            for(auto &v : buc->blocks)
            {
               if(v != -1)
                  temp.push_back(v);
            }
            buc->clear();
         }

         for(int level = h; level >=1; --level)
         {
            auto buc = tree[bucketAt(path, level)];
            for(auto &v:temp)
            {
               if( v != -1
                     and (bucketAt(path,level) == bucketAt(index[v],level) )
                     and (buc->size() < buc->capacity())
                 )
               {
                  buc->add(v);
                  v = -1;
               }
            }
         }
         stash->clear();
         for(auto &v:temp)
            if(v != -1)
               stash->add(v);
      }
};
#endif// PATH_ORAM_H__
