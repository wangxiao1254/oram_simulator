#ifndef TEST_H__
#define TEST_H__

#include <map>
#include <fstream>
#include <cmath>
#include <string>
#include <cstdlib>
using std::cout;
using std::endl;
using std::map;
using std::string;

void pruint64_t(long long i, map<long long, long long >& m2, string filename, int bucket_size)
{
   if(system("mkdir -p res"));
   filename = "res/"+filename+"_"+std::to_string(bucket_size);
   cout <<i<<" "<<filename<<endl;
   std::ofstream fout(filename);
   fout << i<<endl<<endl;
   long long cum = 0;
   for(auto & v:m2)
   {
      double fre = i - cum;
      double sp = log(i)/log(2.0) - log(fre)/log(2.0);
      cum += v.second;
      fout << v.first<<"\t"<<v.second<<"\t"<<sp<< endl;
   }
   fout.close();
}
#endif// TEST_H__
