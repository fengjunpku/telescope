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
    sprintf(errStr,"Can not open input file %s",rootfile.Data());
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

  ReadPars(npl0wf,"pax.txt");
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

void teles::ReadPars(float par[][2],const char* filename)
{
  ifstream parfile(filename);
  if(!parfile || !parfile.is_open())
  {
    char errStr[36];
    sprintf(errStr,"Can not open par file %s",filename);
    MiaoError(errStr);
  }
}

void teles::LoadData()
{
  cout<<"   =======Loading Data "<<runNum<<" ======="<<endl;
  if(!dtree) MiaoError("data::loop the tree is null");
  long nentries = dtree->GetEntriesFast();
  for(long ientry=0;ientry<nentries;ientry++)
  {
    if(!(ientry%100000))
      printf(" %10ld : %5.2f %%\n",ientry,(double)ientry/(double)nentries*100.);
      //cout<<ientry<<"    "<<(double)ientry/(double)nentries*100.<<" %"<<endl;
    dtree->GetEntry(ientry);
    LoadL0();
    otree->Fill();
    Reset();
  }
}

void teles::LoadL0()
{
  for(int i=0;i<16;i++)
  {
    int tvx = mdc[0][15-i];
    int tvy = mdc[0][i+16];
    if(tvx>0&&tvx<8000)
      l0->w1.xv[i] = tvx;
    if(tvy>0&&tvy<8000)
      l0->w1.yv[i] = tvy;
  }
  for(int i=0;i<32;i++)
  {
    int tvx,tvy;
    if(i<16) {tvx = mdc[2][15-i]; tvy = mdc[1][16+i];}
    else     {tvx = mdc[2][47-i]; tvy = mdc[1][i-16];}
    if(tvx>0&&tvx<8000)
      l0->bb7.xv[i] = tvx;
    if(tvy>0&&tvy<8000)
      l0->bb7.yv[i] = tvy;
  }
  if(adc[4][17]>0&&adc[4][17]<4000)
    l0->sv = adc[4][17];
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