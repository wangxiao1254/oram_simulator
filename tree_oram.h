 #ifndef TREE_ORAM_H__
#define TREE_ORAM_H__
#include "bucket.h"
#include <vector>
#include <set>
#include <random>
#include <iostream>
using std::vector;
using std::set;
using std::cout;
using std::endl;

#ifndef STASH_CAP
#define STASH_CAP 10000
#endif
class TreeOram
{
   public: 
      vector<Bucket<int>*> tree;
      vector<int> index;
      std::mt19937 rg;
      std::uniform_int_distribution<int> uni;
      int N, logN, h;
      Bucket<int> * stash;
      TreeOram(int _logN, int buck_size, int _h)
      {
         rg.seed(time(0));
         logN = _logN;
         h = _h;
         N = 1<<logN;
         uni = std::uniform_int_distribution<int>(0, (1<<(h-1))-1);
         tree.push_back(new Bucket<int>(STASH_CAP));
         for(int i = 1; i < 1<<h; ++i)
            tree.push_back(new Bucket<int>(buck_size));
         index.assign(N+1, -1);
         for(unsigned int i = 0; i < index.size(); ++i)
            index[i] = uni(rg);
         stash = tree[0];
      }

      ~TreeOram() {
         for(auto & v : tree) 
            delete v;
      }
      int stash_size() {
         return stash->size();
      }

      void update_pos(int identifier)
      {
         index[identifier] = uni(rg);
      }

      int push_distance(int l1, int l2)
      {
         if(l1 == l2)return h;
         l1 += (1UL<<(h-1)) ;
         l2 += (1UL<<(h-1)) ;
         int res = 0;
         unsigned int diff = l1 ^ l2;
         if( (diff & 0xFFFF0000) == 0)
         {
            res += 16;
            diff <<= 16;
         }
         if( (diff & 0xFF000000) == 0)
         {
            res +=8;
            diff <<= 8;
         }
         if((diff & 0xF0000000) == 0)
         {
            res += 4;
            diff <<=4;
         }
         if((diff & 0xC0000000) == 0)
         {
            res += 2;
            diff <<=2;
         }
         if((diff & 0x80000000)==0)
         {
            res +=1;
         }
         return res-32+h;
      }

      int bucketAt(int leaf_label, int level)
      {
         int label_in_tree = leaf_label + (1UL<<(h-1)) ;
         return (label_in_tree >> (h - level));
      }

      bool readAndRemove(int pos)
      {
         int index_pos = index[pos];
         for(int level = 0; level <= h; ++level)
         {
            int iter = bucketAt(index_pos, level);
            if (tree[iter]->readAndRemove(pos) )
               return true;
         }
         return false;
      }
};
#endif //TREE_ORAM_H__
