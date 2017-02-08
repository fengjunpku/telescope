#include "stdio.h"
#include "stdlib.h"

#include <TStopwatch.h>

#include "caliNT.hh"

using namespace std;

int main(int argc,char** argv)
{
  TStopwatch watch;
  if(argc != 4)
    MiaoError("Bad input! Please give a run num!");
  int runNum = atoi(argv[1]);
  TString teleName(argv[2]);
  TString det_name(argv[3]);
 
  caliNT cali(runNum,teleName,det_name);
  cali.FitData();
  cout<<"   ======= Ending... ======="<<endl;
  printf("CPU_Time: %f s, RealTime: %f s\n",watch.CpuTime(),watch.RealTime());
}