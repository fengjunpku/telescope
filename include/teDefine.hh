#ifndef TEDEFINE_HH
#define TEDEFINE_HH 1

#include <TString.h>
#include <TMath.h>
#include <TROOT.h>

namespace teleDef
{
  static const int teMaxHit = 4;
  static const Double_t deg = TMath::DegToRad();
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

  //========cali pars============
  //w1***************************************************
  static const float tel0wi = 0;//inter----l0
  static const float tel0ws = 1;//slope
  //bb7 dssd
  static const float tel0di = 0;
  static const float tel0ds = 1;
  //ssd
  static const float tel0si = 0;
  static const float tel0ss = 1;
  //w1***************************************************
  static const float ter0wi = 0;//inter----r0
  static const float ter0ws = 1;//slope
  //bb7 dssd
  static const float ter0di = 0;
  static const float ter0ds = 1;
  //ssd
  static const float ter0si = 0;
  static const float ter0ss = 1;
  //w1***************************************************
  static const float tel1wi = 0;//inter----l1
  static const float tel1ws = 1;//slope
  //ssd
  static const float tel1si = 0;
  static const float tel1ss = 1;
  //w1***************************************************
  static const float ter1wi = 0;//inter----r1
  static const float ter1ws = 1;//slope
  //ssd
  static const float ter1si = 0;
  static const float ter1ss = 1;
  //bb7***************************************************
  static const float tel2di = 0;//inter----l2
  static const float tel2ds = 1;//slope
  //ssd
  static const float tel2si = 0;
  static const float tel2ss = 1;
  //bb7***************************************************
  static const float ter2di = 0;//inter----r2
  static const float ter2ds = 1;//slope
  //ssd
  static const float ter2si = 0;
  static const float ter2ss = 1;

}
#endif
