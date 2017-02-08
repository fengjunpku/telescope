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
  
}

caliNT::~caliNT()
{}

void caliNT::FitData()
{
  sp = new TSpectrum(nEpeaks+1);
  int nfound = sp->Search(h_data);
  
  float *vpeaks = sp->GetPositionX();
  
  fitPeak = new TF1("fitPeak","gaus(0)+gaus(3)",200,700);// for sub peak
  Double_t *pars = new Double_t[nfound*6];
  Double_t *xfound = new Double_t[nfound];
  for(int i=0;i<nfound;i++)
  {
    float xp = vpeaks[i];
    int xbin = h_data->GetXaxis()->FindBin(xp);
    float yp = h_data->GetBinContent(xbin);
    float sigma = 5;
    float sub_xp = xp-5;
    float sub_yp = 0.2*yp;
    float sub_sigma = 5;
    
    fitPeak->SetParameters(sub_yp,sub_xp,sub_sigma,yp,xp,sigma);
    fitPeak->SetParLimits(1,xp-20,xp+20);
    fitPeak->SetParLimits(4,xp-20,xp+20);
    h_data->Fit(fitPeak,"Q+","",xp-30,xp+30);
    fitPeak->GetParameters(pars+6*i);
    
    if(pars[6*i]>pars[6*i+3]) xfound[i] = pars[6*i+1];
    else xfound[i] = pars[6*i+4];
    cout<<xp<<" "<<xfound[i]<<endl;
  }
  SortArrray(nfound,xfound);
  g_fit = new TGraph();
  g_fit->SetName("g_fit");
  for(int i=0;i<nfound;i++)
  {
    g_fit->SetPoint(i,xfound[i],energy[i]);
  }
  g_fit->Fit("pol1");
  
  Output();
}

void caliNT::Output()
{
  char outname[20];
  sprintf(outname,"%04d_%s.root",run_num,det_name.Data());
  TFile *f = new TFile(outname,"RECREATE");
  g_fit->Write();
  h_data->Write();
  f->Close();
}

void caliNT::SortArrray(int n, Double_t *array)
{
  Double_t *tmp = new Double_t[n];
  int *index = new int[n];
  TMath::Sort(n, array, index, 0);
  for(int i=0;i<n;i++)
  {
    tmp[i] = array[index[i]];
  }
  memcpy(array, tmp, sizeof(Double_t)*n);
}