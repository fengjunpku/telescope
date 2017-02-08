#ifndef caliNT_hh
#define caliNT_hh

#include <TROOT.h>
#include <TFile.h>
#include <TTree.h>
#include <TH1F.h>
#include <TF1.h>
#include <TGraph.h>
#include <TString.h>
#include <TSpectrum.h>

#include "JunErrors.hh"
#include "teDetector.hh"

const float energy[] = {3182,5156,5486};
const TString teleDir = "/data/d2/CIAE_Jan2017_13C/telefile/";

class caliNT
{
public:
  caliNT(int runNo, TString tName, TString dName);
  virtual ~caliNT();
  void FillHist();
  void FitData();
  void Outout();
  
  int run_num;
  TString det_name;
  
  TFile *inputFile;
  TTree *dtree;
  TH1F *h_data;
  TGraph *g_fit;
  TSpectrum *sp;
  TF1 *fit;
};

#endif