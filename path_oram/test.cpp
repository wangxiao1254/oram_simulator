#include "path_oram.h"
#include <iostream>
#include <map>
#include <fstream>
#include <cmath>
#include "test.h"
using namespace std;


int main(int argc, char ** argv )
{
   int logN = stoi(string(argv[1]));
   int cap = stoi(string(argv[2]));
   long long N = (1<<logN);
   PathOram oram(logN, cap);
   long long i = 0;
   int warmup = 1<<20;
   map<long long, long long> counter;
   
   cout <<"Starting warmming up with "<<warmup<<" operations."<<endl;
   for(int i = 0; i < (N > warmup ? N : warmup); ++i)
      oram.access(i%N);
   i = 0;
   cout <<"Warmup completed."<<endl;
   while(true)
   {
      bool res = oram.access(i%N);
      if(not res)
      {
         cout<<"tree oram invariance is broken"<<i<<endl;
      }
      ++counter[oram.stash_size()];
      ++i;
      if((i%1000000) == 0)
         pruint64_t(i, counter, string("path")+"_"+string(argv[1]), cap);
   }
}
