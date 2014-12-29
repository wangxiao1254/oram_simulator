#ifndef BUCKET_H__
#define BUCKET_H__
#include <vector>

template<typename label_t>
class Bucket
{
   public:
      std::vector<label_t> blocks;
      int bsize;
      Bucket(int c)
         : bsize(0)
      {
         blocks.assign(c, -1);
      }

      void clear()
      {
         bsize = 0;
         blocks.assign(blocks.size(), -1);
      }

      bool readAndRemove(label_t pos)
      {
         if(bsize == 0)
            return false;
         for(auto &v : blocks)
         {
            if(v == pos)
            {
               v = -1;
               --bsize;
               return true;
            }
         }
         return false;
      }

      bool add(label_t pos)
      {
         if(bsize == blocks.size())
            return false;
         for(auto &v : blocks)
            if(v == -1)
            {
               v = pos;
               ++bsize;
               return true;
            }
         return false;
      }

      label_t pop()
      {
         for(auto &v: blocks)
         {
            if(v != -1)
            {
               label_t res = v;
               v = -1;
               --bsize;
               return res;
            }
         }
         return -1;
      }

      int size()
      {
         return bsize;
      }

      int capacity()
      {
         return blocks.size();
      }
};
#endif// BUCKET_H__
