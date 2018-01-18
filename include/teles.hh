#ifndef TELES_HH
#define TELES_HH 1

#include <fstream>
#include <map>
#include <string>

#include <TString.h>
#include <TFile.h>
#include <TTree.h>

#include "JunErrors.hh"
#include "teDetector.hh"

class teles
{
public:
  teles(TString rootpath, int runNo);
  virtual ~teles();
  void LoadData();
  void Save();
private:
  void Init();
  void Branch();
  void ReadPars(float par[][2], const char* filename, int parNum = 16);
  void SortDSSD(teDetector &dec, string det_name, int nums = 16, float window = 20);
  void LoadCaliNT(string det_name,const char* filename);
  void LoadL0();
  void LoadR0();
  void LoadL1();
  void LoadR1();
  void LoadL2();
  void LoadR2();
  void TimeInfo();
  void PosiT0(TString tname);
  void Reset();
  TFile *inputFile,*optFile;
  TTree *dtree,*otree;
  teT0 *l0,*r0;
  teT1 *l1,*r1;
  teT2 *l2,*r2;
  //trigger
  int l0m,r0m,l2s,r2s,fms,fsm,l0s,l1s,r0s,r1s,ssd,fmm;//only record multi & first time info
  double l0mt,r0mt,l2st,r2st,fmst,fsmt,l0st,l1st,r0st,r1st,ssdt,fmmt;
  int runNum;
  int adc[teADCNum][32];
  int mdc[teMDCNum][32];
  int gdc[teGDCNum][128][20];
  int gml[teGDCNum][128];
  //normalized pars for dssd //[0] inter;[1] slope
  float npl0wf[16][2],npl0wb[16][2];//l0 w1
  float npl0df[32][2],npl0db[32][2];//l0 bb7

  float npr0wf[16][2],npr0wb[16][2];//r0 w1
  float npr0df[32][2],npr0db[32][2];//r0 bb7

  float npl1wf[16][2],npl1wb[16][2];//l1 w1

  float npr1wf[16][2],npr1wb[16][2];//r1 w1

  float npl2df[32][2],npl2db[32][2];//l2 bb7

  float npr2df[32][2],npr2db[32][2];//r2 bb7
  //caliNT pars
  map<string,float> slope;
  map<string,float> inter;
};

#endif