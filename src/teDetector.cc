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
  memset(nv,0,sizeof(nv));
  memset(e,0,sizeof(e));
  hit = 0;
  for(int i=0;i<teMaxHit;i++)
  {
    xs[i] = -1;
    ys[i] = -1;
  }
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
  for(int i=0;i<32;i++)
  {
    mv[i] = 0;
    for(int j=0;j<20;j++)
      tv[i][j] = teNan;
  }
  for(int i=0;i<teMaxHit;i++)
  {
    t[i] = teNan;
    m[i] = 0;
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
  memset(w1e,0,sizeof(w1e));
  memset(b7e,0,sizeof(b7e));
  for(int i=0;i<teMaxHit;i++)
  {
    w1x[i] = -1;
    w1y[i] = -1;
    b7x[i] = -1;
    b7y[i] = -1;
  }
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
