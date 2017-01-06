#include <teDetector.hh>

teDetector::teDetector()
{
}

teDetector::~teDetector()
{
}

void teDetector::Reset()
{
  memset(xv,0,sizeof(xv));
  memset(yv,0,sizeof(yv));
  memset(xs,0,sizeof(xs));  
  memset(ys,0,sizeof(ys));
  memset(xnv,0,sizeof(xnv));
  memset(ynv,0,sizeof(ynv));
  memset(e,0,sizeof(e));
}

//==============================================================

teTele::teTele()
{

}

teTele::~teTele()
{

}

void teTele::Clear()
{
  sv = 0;
  se = 0;
  hit = 0;
  for(int i=0;i<teMaxHit;i++)
  {
    t[i] = -999;
    tm[i] = 0;
  }
}

//==============================================================

teT0::teT0()
{
}

teT0::~teT0()
{
}

void teT0::Reset()
{
  Clear();
  w1.Reset();
  bb7.Reset();
}
//---------------------------------------------------
teT1::teT1()
{
}

teT1::~teT1()
{
}

void teT1::Reset()
{
  Clear();
  w1.Reset();
}
//---------------------------------------------------
teT2::teT2()
{
}

teT2::~teT2()
{
}

void teT2::Reset()
{
  Clear();
  bb7.Reset();
}