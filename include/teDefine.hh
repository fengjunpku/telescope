#ifndef TEDEFINE_HH
#define TEDEFINE_HH 1

#include <TString.h>
#include <TMath.h>
#include <TROOT.h>

namespace teleDef
{
  static const int teMaxHit = 4;
  static const Double_t teDeg = TMath::DegToRad();
  static const Double_t teNan = TMath::QuietNaN();
  //static const TString tePath = "/Volumes/JunData/data/rootfile/";
  static const TString tePath = "/data/d2/CIAE_2016_BCO_data/datafile/";
  //static const TString teOptP = "./";
  static const TString teOptP = "/data/d2/CIAE_Jan2017_13C/telefile/";
  static const TString teTreeName = "tree";
  static const int teADCNum = 5;//num of adc
  static const int teMDCNum = 11;//num of madc
  static const int teGDCNum = 2;//num of madc

  static const float teCoinWindow = 20;//default CoinWindow of front & back of DSSD
  static const float teLowTh = 100;//bin
  //
  static const float teW1w = 3.125;
  static const float teB7w = 2.0;
  //l0
  static const float teL0W1dis = 160.0;
  static const float teL0B7dis = 205.0;
  //r0
  static const float teR0W1dis = 160.0;
  static const float teR0B7dis = 205.0;
}
#endif
