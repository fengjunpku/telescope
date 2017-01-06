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
  float xv[32],yv[32];//original value of adc
  int xs[teMaxHit],ys[teMaxHit];//strip after remap
  float xnv[teMaxHit],ynv[teMaxHit];//value after normalization
  float e[teMaxHit];//energy after cali
  int hit;

  ClassDef(teDetector,1);
};

class teTele  // basic class of telescope
{
public:
  teTele();
  virtual ~teTele();
  void Clear();

  float sv;//original value of ssd
  float se;//energy of ssd after cali
  int hit;
  int tv[32];//original value of gdc
  float t[teMaxHit];//value of gdc
  int tm[teMaxHit];//multi of gdc

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
  int w1x[teMaxHit];
  int w1y[teMaxHit];
  int b7x[teMaxHit];
  int b7y[teMaxHit];

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