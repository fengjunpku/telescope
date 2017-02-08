#include "caliNT.hh"

caliNT::caliNT(int runNo, TString tName, TString dName)
{
  char filename[20];
  run_num = runNo;
  sprintf(filename,"seda%04d.root",run_num);
  TString telefile = teleDir+ filename;
  inputFile = TFile::Open(telefile.Data());
  if(!inputFile || !inputFile->IsOpen())
  {
    char errStr[36];
    sprintf(errStr,"Can not open input file %s, Exit !",telefile.Data());
    MiaoError(errStr);
  }
  
  inputFile->GetObject("tree",dtree);
  h_data = new TH1F("h_data","h_data",500,200,700);
  
  det_name = tName+dName;
  char expr[20];
  sprintf(expr,"%s.%s.xv>>h_data",tName.Data(),dName.Data());
  dtree->Draw(expr);
  char outname[20];
  sprintf(outname,"%04d_%s.root",run_num,det_name.Data());
  h_data->SaveAs(outname);
}

caliNT::~caliNT()
{}

void caliNT::FillHist()
{
  
}

void Output()
{
  
}