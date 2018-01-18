#ifndef TEDETECTOR_HH
#define TEDETECTOR_HH 1

#include "teDefine.hh"

using namespace teleDef;

class teDetector  // class for dssd: w1 or bb7
{
public:
  teDetector();
  virtual ~teDetector();
  void Reset();
  float xv[32],yv[32];//value of adc after normalization
  short xs[teMaxHit],ys[teMaxHit];//strip after remap
  float nv[teMaxHit];//front value after normalization
  float e[teMaxHit];//energy after cali
  short hit;

  ClassDef(teDetector,1);
};

//==============================================================================

class teTele  // basic class of telescope
{
public:
  teTele();
  virtual ~teTele();
  void Clear();

  float sv;//original value of ssd
  float se;//energy of ssd after cali
  short hit;//hit num of ssd
  int tv[32][20];//original value of gdc, gmulti less than 20
  short mv[32];//original value of gmulti
  double t[teMaxHit];//value of gdc
  short m[teMaxHit];//multi of gdc

  ClassDef(teTele,1);
};

class teT0 : public teTele
{
public:
  teT0();
  virtual ~teT0();
  teDetector w1;
  teDetector bb7;
  void Reset();
  //after pos. correlation
  float w1e[teMaxHit];
  float b7e[teMaxHit];
  short w1x[teMaxHit];
  short w1y[teMaxHit];
  short b7x[teMaxHit];
  short b7y[teMaxHit];

  ClassDef(teT0,1);
};

class teT1 : public teTele
{
public:
  teT1();
  virtual ~teT1();
  teDetector w1;
  void Reset();

  ClassDef(teT1,1);
};

class teT2 : public teTele
{
public:
  teT2();
  virtual ~teT2();
  teDetector bb7;
  void Reset();

  ClassDef(teT2,1);
};
#endif