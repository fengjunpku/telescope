#include "stdio.h"
#include "stdlib.h"

#include <TStopwatch.h>

#include "caliNT.hh"

using namespace std;

int main(int argc,char** argv)
{
  TStopwatch watch;
  if(argc != 4 && argc != 5)
  {
    MiaoHint("Usage: ./caliNT runnum tele detector [Mode]");
    MiaoHint("     Mode: default -- TSpectrum::Search(), two Gaus fit");
    MiaoHint("     Mode: spec    -- only TSpectrum::Search()");
    MiaoError("Bad input! Please give a run num!");
  }
  int runNum = atoi(argv[1]);
  TString teleName(argv[2]);
  TString det_name(argv[3]);
  TString mode("default");
  if(argc == 5) mode = argv[4];
  caliNT cali(runNum, teleName, det_name, mode);
  cali.FitData();
  cout<<"   ======= Ending... ======="<<endl;
  printf("CPU_Time: %f s, RealTime: %f s\n",watch.CpuTime(),watch.RealTime());
}