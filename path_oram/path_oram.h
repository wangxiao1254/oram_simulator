#ifndef PATH_ORAM_H__
#define PATH_ORAM_H__
#include "tree_oram.h"

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
         stash.insert(identifier);
         update_pos(identifier);
         flush(old_pos);
         return res;
      }

      void flush(int path)
      {
         vector<int> temp_stash;

         for(int level = 1; level <= h; ++level)
         {
            auto buc = tree[bucketAt(path, level)];
            for(auto &v : buc->blocks)
            {
               if(v != -1)
                  temp_stash.push_back(v);
            }
         buc->clear();
         }

         for(auto &v: stash)
            temp_stash.push_back(v);

         for(int level = h; level >=1; --level)
         {
            auto buc = tree[bucketAt(path, level)];
            for(auto &v:temp_stash)
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
         stash.clear();
         for(auto &v:temp_stash)
            if(v != -1)
               stash.insert(v);
      }
};
#endif// PATH_ORAM_H__
