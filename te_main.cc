// ************************************************************************* 
#include <iostream>
#include <string>
#include <vector>
#include "stdio.h"
#include "stdlib.h"

//#include <TApplication.h>
//#include <TCanvas.h>
//#include <TH2D.h>
//#include <TMath.h>
//#include <TCutG.h>

#include <TStopwatch.h>


#include "JunErrors.hh"
#include "teles.hh"

using namespace std;
using namespace teleDef;


int main(int argc,char** argv)
{
  TStopwatch watch;
  if(argc != 2 && argc != 4)
    MiaoError("Bad input! Please give a run num!");
  int runNum = atoi(argv[1]);
 
  teles te(tePath.Data(),runNum);
  te.LoadData();
  te.Save();
  cout<<"   ======= Ending... ======="<<endl;
  printf("CPU_Time: %f s, RealTime: %f s\n",watch.CpuTime(),watch.RealTime());
}
