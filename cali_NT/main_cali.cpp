#include "stdio.h"
#include "stdlib.h"

#include <TStopwatch.h>

#include "caliNT.hh"

using namespace std;

int main(int argc,char** argv)
{
  TStopwatch watch;
  if(argc != 2 && argc != 4)
    MiaoError("Bad input! Please give a run num!");
  int runNum = atoi(argv[1]);
 
  caliNT cali(runNum);
  cout<<"   ======= Ending... ======="<<endl;
  printf("CPU_Time: %f s, RealTime: %f s\n",watch.CpuTime(),watch.RealTime());
}