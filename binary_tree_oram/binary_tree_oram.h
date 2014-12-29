#ifndef BINARY_TREE_ORAM_H__
#define BINARY_TREE_ORAM_H__
#include "tree_oram.h"

/*
Binary Tree ORAM simulator.
https://eprint.iacr.org/2011/407
*/

class BinaryTreeOram: public TreeOram
{
   public:
      BinaryTreeOram(int logN, int capacity)
         :TreeOram(logN, capacity, logN)
      {
      }

      bool access(int identifier)
      {
         bool res = readAndRemove(identifier);
         update_pos(identifier);
         tree[1]->add(identifier);
         eviction();
         return res;
      }

      void eviction()
      {
      }
};
#endif// PATH_ORAM_H__
