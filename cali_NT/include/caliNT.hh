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

#include <iomanip>
#include <fstream>

const float energy[] = {3182,5156,5486};
const int nEpeaks = int(sizeof(energy)/sizeof(float));
const TString teleDir = "/data/d2/CIAE_Jan2017_13C/telefile/";

class caliNT
{
public:
  caliNT(int runNo, TString tName, TString dName, TString mode);
  virtual ~caliNT();
  void FitData();
  void Output();
  void Record();
  void SortArrray(int n, Double_t *array);
  
  int run_num;
  TString det_name;
  TString _mode;
  
  TFile *inputFile;
  TTree *dtree;
  TH1F *h_data;
  TGraph *g_fit;
  TSpectrum *sp;
  TF1 *fitPeak;
  TF1 *line;
  Double_t p[2];
  Double_t e[2];
  Double_t chi2;
};

#endif
