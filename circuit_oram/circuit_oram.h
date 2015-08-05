#ifndef CIRCUIT_ORAM_H__
#define CIRCUIT_ORAM_H__
#include "tree_oram.h"

/*
   Circuit ORAM.
   eprint.iacr.org/2014/672
 */

class CircuitOram: public TreeOram
{
   public:
      CircuitOram(int logN, int capacity)
         :TreeOram(logN, capacity, logN)
      {
      }

      bool access(int identifier)
      {
         bool res = readAndRemove(identifier);
         stash->add(identifier);
         update_pos(identifier);
         flush(uni(rg));
         flush(uni(rg));
         return res;
      }

      void flush(int path)
      {
         vector<int> deepest_index(logN+1, -1);
         vector<int> deepest_depth(logN+1, -1);
         vector<int> deepest(logN+1, -1);
         vector<int> target(logN+1, -1);
         int src = -1, goal = -1;
         for(int i = 0; i <= h; ++i) {
            for(auto v : tree[bucketAt(path, i)]->blocks) {
               if(v!=-1) {
                  int d = push_distance(path, index[v]);
                  if(d > deepest_depth[i]) {
                     deepest_index[i] = v;
                     deepest_depth[i] = d;
                  }
               }
            }
         }

         if(deepest_index[0] != -1) {
            src = 0;
            goal = deepest_depth[0];
         }

         for(int  i = 1; i <=h; ++i) {
            if(goal >= i)
               deepest[i] = src;
            int l = deepest_depth[i];
            if(l > goal) {
               goal = l;
               src = i;
            }
         }

         int dest = -1; src = -1;
         for(int  i = h; i >= 0; --i) {
            if(i == src) {
               target[i] = dest;
               dest = -1;
               src = -1;
            }
            bool has_empty = tree[bucketAt(path, i)]->size() < tree[bucketAt(path, i)]->capacity();
            if( ( (dest == -1 and has_empty) or target[i]!=-1 ) and deepest[i]!=-1) {
               src = deepest[i];
               dest = i;
            }
         }
         dest = -1;
         int hold = -1;
         int to_write = -1;
         for(int i = 0; i <= h; ++i) {
            to_write = -1;
            if(hold != -1 and i == dest) {
               to_write = hold;
               hold = -1;
               dest = -1;
            }
            if(target[i]!=-1) {
               hold = deepest_index[i];
               tree[bucketAt(path, i)]->readAndRemove(deepest_index[i]);
               dest = target[i];
            }
            if(to_write != -1)
               tree[bucketAt(path, i)]->add(to_write);
         }
      }
};
#endif// PATH_ORAM_H__
