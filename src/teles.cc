#include "teles.hh"

teles::teles(TString rootpath,int runNo)
{
  char filename[20];
  runNum = runNo;
  sprintf(filename,"data%04d.root",runNum);
  TString rootfile = rootpath + filename;
  inputFile = TFile::Open(rootfile.Data());
  if(!inputFile || !inputFile->IsOpen())
  {
    char errStr[36];
    sprintf(errStr,"Can not open input file %s, Exit !",rootfile.Data());
    MiaoError(errStr);
  }

  Init();

  l0 = new teT0();
  r0 = new teT0();
  l1 = new teT1();
  r1 = new teT1();  
  l2 = new teT2();
  r2 = new teT2();

  sprintf(filename,"seda%04d.root",runNum);
  TString optname = teOptP + filename;
  optFile = new TFile(optname.Data(),"RECREATE");

  otree = new TTree("tree","seda");
  Branch();
}

teles::~teles()
{
  inputFile->Close();
  delete l0;
  delete r0;
  delete l1;
  delete r1;
  delete l2;
  delete r2;
}

void teles::Init()
{
  inputFile->GetObject(teTreeName.Data(),dtree);
  dtree->SetBranchStatus("*",0);
  dtree->SetBranchStatus("adc",1);
  dtree->SetBranchStatus("gdc",1);
  dtree->SetBranchStatus("madc",1);
  dtree->SetBranchStatus("gmulti",1);

  dtree->SetBranchAddress("adc",adc);
  dtree->SetBranchAddress("madc",mdc);
  dtree->SetBranchAddress("gdc",gdc);
  dtree->SetBranchAddress("gmulti",gml);
  //-----------------------------------
  ReadPars(npl0wf,"./nPars/self/sn_l0w1f_0421.txt");
  ReadPars(npl0wb,"./nPars/self/sn_l0w1b_0421.txt");
  ReadPars(npl0df,"./nPars/self/sn_l0bb7f_0421.txt",32);
  ReadPars(npl0db,"./nPars/self/sn_l0bb7b_0421.txt",32);

  ReadPars(npr0wf,"./nPars/self/sn_r0w1f_0421.txt");
  ReadPars(npr0wb,"./nPars/self/sn_r0w1b_0421.txt");
  ReadPars(npr0df,"./nPars/self/sn_r0bb7f_0421.txt",32);
  ReadPars(npr0db,"./nPars/self/sn_r0bb7b_0421.txt",32);

  ReadPars(npl1wf,"./nPars/self/sn_l1w1f_0421.txt");
  ReadPars(npl1wb,"./nPars/self/sn_l1w1b_0421.txt");

  ReadPars(npr1wf,"./nPars/self/sn_r1w1f_0421.txt");
  ReadPars(npr1wb,"./nPars/self/sn_r1w1b_0421.txt");

  ReadPars(npl2df,"./nPars/self/sn_l2bb7f_0421.txt",32);
  ReadPars(npl2db,"./nPars/self/sn_l2bb7b_0421.txt",32);

  ReadPars(npr2df,"./nPars/self/sn_r2bb7f_0421.txt",32);
  ReadPars(npr2db,"./nPars/self/sn_r2bb7b_0421.txt",32);
  //ReadPars(npr2db,"../selfNorm/sn_r2bb7b_0765.txt",32);
  //----------------------------------
  //LoadCaliNT("l0w1","nPars/cali_snt/ntCali0310_l0w1.txt");
  //LoadCaliNT("r0w1","nPars/cali_snt/ntCali0311_r0w1.txt");
  LoadCaliNT("l0w1","../../pyAna_13C/cali_Au/result/au_0335_l0w1.txt");
  LoadCaliNT("r0w1","../../pyAna_13C/cali_Au/result/au_0335_r0w1.txt");
  //LoadCaliNT("l0bb7","nPars/cali_snt/ntCali0318_l0bb7.txt");
  //LoadCaliNT("r0bb7","nPars/cali_snt/ntCali0317_r0bb7.txt");
  LoadCaliNT("l0bb7","../../pyAna_13C/cali_Au/result/au_0329_l0bb7.txt");
  LoadCaliNT("r0bb7","../../pyAna_13C/cali_Au/result/au_0329_r0bb7.txt");
  
  //LoadCaliNT("l0ssd","nPars/cali_nt/ntCali0323_l0ssd.txt");
  //LoadCaliNT("r0ssd","nPars/cali_nt/ntCali0322_r0ssd.txt");
  LoadCaliNT("l0ssd","../../pyAna_13C/cali_Au/result/au_0999_l0ssd.txt");
  LoadCaliNT("r0ssd","../../pyAna_13C/cali_Au/result/au_0999_r0ssd.txt");
  
  LoadCaliNT("l1w1","nPars/cali_snt/ntCali0307_l1w1.txt");
  LoadCaliNT("r1w1","nPars/cali_snt/ntCali0305_r1w1.txt");
  //LoadCaliNT("l1ssd","nPars/cali_nt/ntCali0320_l1ssd.txt");
  //LoadCaliNT("r1ssd","nPars/cali_nt/ntCali0319_r1ssd.txt");
  LoadCaliNT("l1ssd","../../pyAna_13C/cali_Au/result/au_0999_l1ssd.txt");
  LoadCaliNT("r1ssd","../../pyAna_13C/cali_Au/result/au_0999_r1ssd.txt");
  
  LoadCaliNT("l2ssd","nPars/cali_nt/ntCali0314_l2ssd.txt");
  LoadCaliNT("r2ssd","nPars/cali_nt/ntCali0316_r2ssd.txt");
  LoadCaliNT("l2bb7","nPars/cali_snt/ntCali0312_l2bb7.txt");
  LoadCaliNT("r2bb7","nPars/cali_snt/ntCali0313_r2bb7.txt");
}

void teles::Branch()
{
  otree->Branch("l0","teT0",&l0);
  otree->Branch("r0","teT0",&r0);
  otree->Branch("l1","teT1",&l1);
  otree->Branch("r1","teT1",&r1);
  otree->Branch("l2","teT2",&l2);
  otree->Branch("r2","teT2",&r2);
}

void teles::ReadPars(float par[][2],const char* filename,int parNum)
{
  ifstream parfile(filename);
  if(!parfile || !parfile.is_open() || !parfile.good())
  {
    char warnStr[36];
    sprintf(warnStr,"Can not open par file %s, use defealt pars !",filename);
    MiaoWarn(warnStr);
    for(int i=0;i<parNum;i++) {par[i][0] = 0; par[i][1] = 1;}
    return;
  }
  float inter,slope;
  float ei,es;
  int lcnt = 0;
  while(1)
  {
    if(parfile.eof()) break;
    parfile>>inter>>ei>>slope>>es;
    par[lcnt][0] = inter;
    par[lcnt][1] = slope;
    lcnt++;
    if(lcnt>=parNum) break;
  }
  if(lcnt!=parNum)
  {
    char warnStr[36];
    sprintf(warnStr," %s does not contain enough pars !",filename);
    MiaoWarn(warnStr);
  }
  parfile.close();
}

void teles::LoadCaliNT(string det_name,const char* filename)
{
  ifstream califile(filename);
  if(!califile || !califile.is_open() || !califile.good())
  {
    char warnStr[36];
    sprintf(warnStr,"Can not open cali_NT file %s, use defealt pars !",filename);
    MiaoWarn(warnStr);
    slope[det_name] = 0;
    inter[det_name] = 1;
    return;
  }
  califile>>inter[det_name]>>slope[det_name];
  //cout<<inter[det_name]<<"  "<<slope[det_name]<<endl;
  califile.close();
}

void teles::LoadData()
{
  cout<<"   ======= Loading Data "<<runNum<<" ======="<<endl;
  if(!dtree) MiaoError("data::loop the tree is null");
  long nentries = dtree->GetEntriesFast();
  long onePC = nentries/100;
  for(long ientry=0;ientry<nentries;ientry++)
  {
    if(!(ientry%onePC))
    {
      printf("\r Progress Events %04d : %11ld : %6.1f %%",runNum,ientry,(float)ientry/(float)onePC);
      //cout<<ientry<<"    "<<(double)ientry/(double)nentries*100.<<" %"<<endl;
      fflush(stdout);
    }
    dtree->GetEntry(ientry);
    LoadL0();
    LoadR0();
    LoadL1();
    LoadR1();
    LoadL2();
    LoadR2();
    otree->Fill();
    Reset();
  }
  printf("\n");
}

void teles::LoadL0()
{
  //l0w1
  for(int i=0;i<16;i++)
  {
    float tvx = npl0wf[i][0] + npl0wf[i][1] * mdc[0][i];
    float tvy = npl0wb[i][0] + npl0wb[i][1] * mdc[0][i+16];
    if(tvx>0&&tvx<8000)
      l0->w1.xv[15-i] = tvx;
    if(tvy>0&&tvy<8000)
      l0->w1.yv[i] = tvy;
  }
  //l0bb7
  for(int i=0;i<32;i++)
  {
    float tvx = npl0db[i][0] + npl0db[i][1] * mdc[2][i];
    float tvy = npl0df[i][0] + npl0df[i][1] * mdc[1][i];
    if(tvx>0&&tvx<8000)
    {
      if(i<16) l0->bb7.xv[15-i] = tvx;
      else     l0->bb7.xv[47-i] = tvx;
    }
    if(tvy>0&&tvy<8000)
    {
      if(i<16) l0->bb7.yv[i+16] = tvy;
      else     l0->bb7.yv[i-16] = tvy;
    }

  }
  //l0ssd
  if(adc[4][17]>0&&adc[4][17]<4000)
  {
    l0->sv = adc[4][17];
    l0->se = inter["l0ssd"] + slope["l0ssd"] * l0->sv;
  }
  SortDSSD(l0->w1,"l0w1");
  SortDSSD(l0->bb7,"l0bb7",32);
}

void teles::LoadR0()
{
  //r0w1
  for(int i=0;i<16;i++)
  {
    float tvx = npr0wf[i][0] + npr0wf[i][1] * mdc[3][i];
    float tvy = npr0wb[i][0] + npr0wb[i][1] * mdc[3][i+16];
    if(tvx>0&&tvx<8000)
      r0->w1.xv[15-i] = tvx;
    if(tvy>0&&tvy<8000)
      r0->w1.yv[i] = tvy;
  }
  //r0bb7
  for(int i=0;i<32;i++)
  {
    float tvx = npr0db[i][0] + npr0db[i][1] * mdc[5][i];
    float tvy = npr0df[i][0] + npr0df[i][1] * mdc[4][i];
    if(tvx>0&&tvx<8000)
    {
      if(i<16) r0->bb7.xv[15-i] = tvx;
      else     r0->bb7.xv[47-i] = tvx;
    }
    if(tvy>0&&tvy<8000)
    {
      if(i<16) r0->bb7.yv[i+16] = tvy;
      else     r0->bb7.yv[i-16] = tvy;
    }

  }
  //r0ssd
  if(adc[4][18]>0&&adc[4][18]<4000)
  {
    r0->sv = adc[4][18];
    r0->se = inter["r0ssd"] + slope["r0ssd"] * r0->sv;
  }
  SortDSSD(r0->w1,"r0w1");
  SortDSSD(r0->bb7,"r0bb7",32);
}

void teles::LoadL1()
{
  //l1w1
  for(int i=0;i<16;i++)
  {
    float tvx = npl1wf[i][0] + npl1wf[i][1] * mdc[7][i];
    float tvy = npl1wb[i][0] + npl1wb[i][1] * mdc[8][i];
    if(tvx>0&&tvx<8000)
    {
      if(i<8) l1->w1.xv[7-i] = tvx;
      else    l1->w1.xv[i]   = tvx;
    }
    if(tvy>0&&tvy<8000)
    {
      if(i<8) l1->w1.yv[15-i] = tvy;
      else    l1->w1.yv[i-8]  = tvy;
    }
  }
  //l1ssd
  if(adc[4][16]>0&&adc[4][16]<4000)
  {
    l1->sv = adc[4][16];
    l1->se = inter["l1ssd"] + slope["l1ssd"] * l1->sv;
  }
  SortDSSD(l1->w1,"l1w1");
}

void teles::LoadR1()
{
  //r1w1
  for(int i=0;i<16;i++)
  {
    float tvx = npr1wf[i][0] + npr1wf[i][1] * mdc[7][i+16];
    float tvy = npr1wb[i][0] + npr1wb[i][1] * mdc[8][i+16];
    if(tvx>0&&tvx<8000)
    {
      if(i<8) r1->w1.xv[7-i] = tvx;
      else    r1->w1.xv[i]   = tvx;
    }
    if(tvy>0&&tvy<8000)
    {
      if(i<8) r1->w1.yv[15-i] = tvy;
      else    r1->w1.yv[i-8]  = tvy;
    }
  }
  //r1ssd
  if(adc[4][19]>0&&adc[4][19]<4000)
  {
    r1->sv = adc[4][19];
    r1->se = inter["r1ssd"] + slope["r1ssd"] * r1->sv;
  }
  SortDSSD(r1->w1,"r1w1");
}

void teles::LoadL2()
{
  //l2bb7
  for(int i=0;i<32;i++)
  {
    float tvx = npl2db[i][0] + npl2db[i][1] * 2 *adc[1][i];
    float tvy = npl2df[i][0] + npl2df[i][1] * mdc[6][i];
    if(tvx>0&&tvx<4000)
    {
      if(i<16) l2->bb7.xv[15-i] = tvx;
      else     l2->bb7.xv[47-i] = tvx;
    }
    if(tvy>0&&tvy<8000)
    {
      if(i<16) l2->bb7.yv[15-i] = tvy;
      else     l2->bb7.yv[47-i] = tvy;
    }

  }
  //l2ssd
  if(adc[4][21]>0&&adc[4][21]<4000)
  {
    l2->sv = adc[4][21];
    l2->se = inter["l2ssd"] + slope["l2ssd"] * l2->sv;
  }
  SortDSSD(l2->bb7,"l2bb7",32);
}

void teles::LoadR2()
{
  //r2bb7
  for(int i=0;i<32;i++)
  {
    float tvx = npr2db[i][0] + npr2db[i][1] * adc[3][i];
    float tvy = npr2df[i][0] + npr2df[i][1] * adc[2][i];
    if(tvx>0&&tvx<4000)
    {
      if(i<16) r2->bb7.xv[15-i] = tvx;
      else     r2->bb7.xv[47-i] = tvx;
    }
    if(tvy>0&&tvy<4000)
    {
      if(i<16) r2->bb7.yv[15-i] = tvy;
      else     r2->bb7.yv[47-i] = tvy;
    }

  }
  //r2ssd
  if(adc[4][20]>0&&adc[4][20]<4000)
  {
    r2->sv = adc[4][20];
    r2->se = inter["r2ssd"] + slope["r2ssd"] * r2->sv;
  }
  SortDSSD(r2->bb7,"r2bb7",32);
}

void teles::Reset()
{
  l0->Reset();
  r0->Reset();
  l1->Reset();
  r1->Reset();
  l2->Reset();
  r2->Reset();
}

void teles::Save()
{
  optFile->cd();
  otree->Write();
  optFile->Close();
}

void teles::SortDSSD(teDetector &dec, string det_name, int nums, float window)
{
  if(nums!=16 && nums!=32)
    MiaoError("Invalid value of index in teles::SortDSSD()");
  if(window==0) window = teCoinWindow;
  dec.hit = 0;
  int xI[32],yI[32];
  int xhit(0),yhit(0);
  int   tmpxs[teMaxHit],tmpys[teMaxHit];
  float tmpxe[teMaxHit],tmpye[teMaxHit];

  //chose the highest 4(teMaxHit) values in one dssd, decreasing order
  TMath::Sort(nums,dec.xv,xI,1);
  TMath::Sort(nums,dec.yv,yI,1);

  if(dec.xv[xI[0]]<=teLowTh||dec.yv[yI[0]]<=teLowTh) return;

  for(int i=0;i<teMaxHit;i++)
  {
    if(dec.xv[xI[i]]<=teLowTh) break;
    tmpxs[i] = xI[i];
    tmpxe[i] = dec.xv[xI[i]];
    xhit++;
  }
  for(int i=0;i<teMaxHit;i++)
  {
    if(dec.yv[yI[i]]<=teLowTh) break;
    tmpys[i] = yI[i];
    tmpye[i] = dec.yv[yI[i]];
    yhit++;
  }

  bool yflag[teMaxHit];//used to tell y hit bas been taken or not
  memset(yflag,0,sizeof(yflag));

  for(int i=0;i<xhit;i++)
  {
    float min = 10000;
    int tmpj = -1;
    for(int j=0;j<yhit;j++)
    {
      if(yflag[j]) continue;
      float delta = TMath::Abs(tmpxe[i]-tmpye[j]);
      if(min>delta)
      {
        min = delta;
        tmpj = j;
      }
    }
    if(tmpj==-1||min>window) continue;
    if(nums==16) //w1
      dec.nv[dec.hit] = tmpxe[i];
    else //bb7
      dec.nv[dec.hit] = tmpye[tmpj];
    dec.xs[dec.hit] = tmpxs[i];
    dec.ys[dec.hit] = tmpys[tmpj];
    dec.hit++;
    yflag[tmpj] = 1;
  }
  for(int i=0;i<xhit;i++)
  {
    dec.e[i] = inter[det_name] + slope[det_name] * dec.nv[i];
  }
}
