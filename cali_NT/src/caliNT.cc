#include "caliNT.hh"

caliNT::caliNT(int runNo, TString tName, TString dName, TString mode)
{
  //check input
  if(!tName.EqualTo("l0")&&!tName.EqualTo("l1")&&!tName.EqualTo("l2")
    &&!tName.EqualTo("r0")&&!tName.EqualTo("r1")&&!tName.EqualTo("r2"))
    MiaoError("Tele name should be l0/l1/l2/r0/r1/r2!");
  if(!dName.EqualTo("w1")&&!dName.EqualTo("bb7")&&!dName.EqualTo("ssd"))
    MiaoError("Detector name should be w1/bb7/ssd!");
  if(!mode.EqualTo("default")&&!mode.EqualTo("spec"))
    MiaoError("mode name should be default/spec!");
  //open tele root file
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
  //init the hist
  char htitle[20];
  sprintf(htitle,"run%04d_%s%s",run_num,tName.Data(),dName.Data());
  if(tName.EqualTo("l0")||tName.EqualTo("r0"))
  {
    if(dName.EqualTo("w1"))
      h_data = new TH1F("h_data",htitle,500,200,700);
    if(dName.EqualTo("bb7"))
      h_data = new TH1F("h_data",htitle,500,300,800);
    if(dName.EqualTo("ssd"))
      h_data = new TH1F("h_data",htitle,350,250,600);
  }
  if(tName.EqualTo("l1")||tName.EqualTo("r1"))
  {
    if(dName.EqualTo("w1"))
      h_data = new TH1F("h_data",htitle,2500,1500,4000);
    if(dName.EqualTo("ssd"))
      h_data = new TH1F("h_data",htitle,300,300,600);
  }
  if(tName.EqualTo("l2")||tName.EqualTo("r2"))
  {
    if(dName.EqualTo("bb7"))
      MiaoError("Have not be normalized !!!");
    if(dName.EqualTo("ssd"))
      h_data = new TH1F("h_data",htitle,900,700,1600);
  }
  //extract the hist from the tree
  char expr[20];
  if(dName.EqualTo("ssd"))
    sprintf(expr,"%s.sv>>h_data",tName.Data());
  else
    sprintf(expr,"%s.%s.nv>>h_data",tName.Data(),dName.Data());
  dtree->Draw(expr);
  //
  det_name = tName+dName;
  _mode = mode;
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
  Double_t *res = new Double_t[nfound]; 
  cout<<"--- peak_Spec  peak_Spec+Fit ---"<<endl;
  for(int i=0;i<nfound;i++)
  {
    if(_mode.EqualTo("spec"))
      xfound[i] = vpeaks[i];
    else
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
      
      if(pars[6*i]>pars[6*i+3]) 
      {
        xfound[i] = pars[6*i+1];
        res[i]    = 2.355*pars[6*i+2]/xfound[i];
      }
      else 
      {
        xfound[i] = pars[6*i+4];
        res[i]    = 2.355*pars[6*i+5]/xfound[i];
      }
    }
    cout<<" "<<vpeaks[i]<<"          "<<xfound[i]<<"     res: "<<res[i]*100<<" % "<<endl;
  }
  SortArrray(nfound,xfound);
  g_fit = new TGraph();
  g_fit->SetName("g_fit");
  for(int i=0;i<nfound;i++)
  {
    g_fit->SetPoint(i,xfound[i],energy[i]);
  }
  g_fit->Fit("pol1");
  p[0] = g_fit->GetFunction("pol1")->GetParameter(0);
  p[1] = g_fit->GetFunction("pol1")->GetParameter(1);
  e[0] = g_fit->GetFunction("pol1")->GetParError(0);
  e[1] = g_fit->GetFunction("pol1")->GetParError(1);
  chi2 = g_fit->GetFunction("pol1")->GetChisquare();
  
  char title[20];
  sprintf(title,"run%04d_%s_P0_%f_P1_%f",run_num,det_name.Data(),p[0],p[1]);
  g_fit->SetTitle(title);

  Output();
  Record();
}

void caliNT::Output()
{
  char outname[20];
  sprintf(outname,"ntCaliPars/%s_cali%04d.root",det_name.Data(),run_num);
  TFile *f = new TFile(outname,"RECREATE");
  g_fit->Write();
  h_data->Write();
  f->Close();
}

void caliNT::Record()
{
  char txtname[20];
  sprintf(txtname,"ntCaliPars/ntCali%04d_%s.txt",run_num,det_name.Data());
  ofstream of;
  of.open(txtname,ios::out);
  of<<setw(15)<<p[0];
  of<<setw(15)<<p[1];
  of<<setw(15)<<e[0];
  of<<setw(15)<<e[1];
  of<<setw(15)<<chi2<<endl;
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
