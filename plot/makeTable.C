#include <iostream>
#include <utility>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>

#include "TROOT.h"
#include "TLatex.h"
#include "TString.h"
#include "TH2.h"
#include "THStack.h"
#include "TLegend.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TH1.h"
#include "TPaveText.h"
#include "TStyle.h"
#include "TKey.h"

#include "CMS_lumi.C"
#include "Math/QuantFuncMathCore.h"

using namespace std;

//_______________________________________________________________________________
void printTable( vector<TString> files , vector<TString> names , vector<TString> nplots, vector<TString> SRdirs, int mtbin = -1 , TString caption = "") {
  
  // read off yields from h_mt2bins hist in each topological region
  
  const unsigned int n = files.size();
  const unsigned int ndirs = SRdirs.size();
  
  vector<double> bgtot(ndirs,0.);
  vector<double> bgerr(ndirs,0.);
  
  std::cout << "\\begin{table}[!ht]" << std::endl;
//  std::cout << "\\scriptsize" << std::endl;
  std::cout << "\\centering" << std::endl;
  std::cout << "\\begin{tabular}{r";
  for (unsigned int idir=0; idir < ndirs; ++idir) std::cout << "|c";
  std::cout << "}" << std::endl;
  std::cout << "\\hline" << std::endl;
  
  cout << endl << "\\hline" << endl
  << "Sample";
  
  // header
  for (unsigned int idir = 0; idir < ndirs; ++idir) {
    cout << " & " << SRdirs.at(idir);
    //cout << " & " << getJetBJetTableLabel(samples.at(0), dirs.at(idir));
  }
  cout << " \\\\" << endl
  << "\\hline\\hline" << endl;
  
  // backgrounds first -- loop backwards
//  for( int i = n-1 ; i >= 0 ; --i ){
  for( int i = 0 ; i < n ; i++ ){
    if( TString(names.at(i)).Contains("C2N4")  ) continue;
    cout << names.at(i);
    TFile f1( files[i], "READ");
    if(!f1.IsOpen()){
      std::cout<<"File "<<files[i]<<" can't be found, will not be used for histogram "<<nplots[i]<<std::endl;
      continue;
    }
    if(f1.Get(nplots[i].Data())==0){
      std::cout<<"Histogram "<<nplots[i]<<" not found in file "<<files[i]<<std::endl;
      continue;
    }
    for ( unsigned int idir = 0; idir < ndirs; ++idir ) {
      TH1D* h = (TH1D*) f1.Get(nplots[i]);
      double yield = 0.;
      double err = 0.;
      if (h) {
        // use all bins
        if (mtbin < 0) {
          yield = h->IntegralAndError(0,-1,err);
          bgtot.at(idir) += yield;
          bgerr.at(idir) = sqrt(pow(bgerr.at(idir),2) + pow(err,2));
        }
        else {
          int bin = h->GetXaxis()->FindBin(mtbin);
          yield = h->IntegralAndError(bin,-1,err);
          bgtot.at(idir) += yield;
          bgerr.at(idir) = sqrt(pow(bgerr.at(idir),2) + pow(err,2));
        }
      }
      if (yield > 10.) {
        //  	cout << "  &  " << Form("%.0f $\\pm$ %.0f",yield,err);
        cout << "  &  " << Form("%.1f $\\pm$ %.1f",yield,err);
      } else {
        //  	cout << "  &  " << Form("%.1f $\\pm$ %.1f",yield,err);
        cout << "  &  " << Form("%.2f $\\pm$ %.2f",yield,err);
      }
    }
    cout << " \\\\" << endl;
  } // loop over samples
  
  // print bg totals
  cout << "\\hline" << endl;
  cout << "Total SM";
  for ( unsigned int idir = 0; idir < ndirs; ++idir ) {
    double yield = bgtot.at(idir);
    double err = bgerr.at(idir);
    if (yield > 10.) {
      //  	cout << "  &  " << Form("%.0f $\\pm$ %.0f",yield,err);
      cout << "  &  " << Form("%.1f $\\pm$ %.1f",yield,err);
    } else {
      //  	cout << "  &  " << Form("%.1f $\\pm$ %.1f",yield,err);
      cout << "  &  " << Form("%.2f $\\pm$ %.2f",yield,err);
    }
  }
  cout << " \\\\" << endl;
  cout << "\\hline" << endl;
  
  // finally print signals
  for( unsigned int i = 0 ; i < n ; i++ ){
    if( !TString(names.at(i)).Contains("C2N4") ) continue;
    cout << names.at(i);
    TFile f1( files[i], "READ");
    if(!f1.IsOpen()){
      std::cout<<"File "<<files[i]<<" can't be found, will not be used for histogram "<<nplots[i]<<std::endl;
      continue;
    }
    if(f1.Get(nplots[i].Data())==0){
      std::cout<<"Histogram "<<nplots[i]<<" not found in file "<<files[i]<<std::endl;
      continue;
    }
    for ( unsigned int idir = 0; idir < ndirs; ++idir ) {
      TH1D* h = (TH1D*) f1.Get(nplots[i]);
      double yield = 0.;
      double err = 0.;
      if (h) {
        // use all bins
        if (mtbin < 0) {
          yield = h->IntegralAndError(0,-1,err);
        }
        // last bin: include overflow
        else {
          int bin = h->GetXaxis()->FindBin(mtbin);
          yield = h->IntegralAndError(bin,-1,err);
        }
      }
      if (yield > 10.) {
        //  	cout << "  &  " << Form("%.0f $\\pm$ %.0f",yield,err);
        cout << "  &  " << Form("%.1f $\\pm$ %.1f",yield,err);
      } else {
        //  	cout << "  &  " << Form("%.1f $\\pm$ %.1f",yield,err);
        cout << "  &  " << Form("%.2f $\\pm$ %.2f",yield,err);
      }
    }
    cout << " \\\\" << endl;
    cout << "\\hline" << endl;
  } // loop over samples
  
  std::cout << "\\end{tabular}" << std::endl;
  std::cout << "\\caption{ "<< caption << "}" << std::endl;
  std::cout << "\\end{table}" << std::endl;
  
  cout << endl;
  return;
}

//_______________________________________________________________________________
void printDetailedTable( vector<TString> files , vector<TString> labels ,  vector<TString> nplots, vector<TString> purpose) {
  
  // read off yields from h_mt2bins hist in each topological region
  
  const unsigned int n = files.size();
  
  
//  TString nbinshistname = Form("%s/h_n_mt2bins",dir.c_str());
//  TH1D* h_n_mt2bins = (TH1D*) samples.at(0)->Get(nbinshistname);
//  int n_mt2bins;
//  if(h_n_mt2bins){
//    n_mt2bins = h_n_mt2bins->GetBinContent(1);
//  }
//  else{
//    std::cout << "Couldn't get number of mt2 bins" << std::endl;
//    return;
//  }
  
  TFile f1( files[0], "READ");
  if(!f1.IsOpen()){
    std::cout<<"File "<<files[0]<<" can't be found, will not be used for histogram "<<nplots[0]<<std::endl;
  }
  if(f1.Get(nplots[0].Data())==0){
    std::cout<<"Histogram "<<nplots[0]<<" not found in file "<<files[0]<<std::endl;
  }
  
  TH1D* h_mt2bins = (TH1D*) f1.Get(nplots[0]);
  int n_mt2bins = h_mt2bins->GetXaxis()->GetNbins();
  
  
  vector<double> bgtot(n_mt2bins,0.);
  vector<double> bgerr(n_mt2bins,0.);
  
//  TString binshistname = nplots[0];
//  TH1D* h_mt2bins(0);
//  for(unsigned int i=0; i<samples.size(); i++){//need to find a sample that has this hist filled
//    h_mt2bins = (TH1D*) samples.at(i)->Get(binshistname);
//    if(h_mt2bins) break;
//  }
  
  if(!h_mt2bins) std::cout << "Couldn't get the mt2 binning" << std::endl;
  
  std::cout << "\\begin{table}[htbp]" << std::endl;
  std::cout << "\\caption{Background and signal yields in bins of MTmin.}" << std::endl;
  std::cout << "\\scriptsize" << std::endl;
  std::cout << "\\centering" << std::endl;
  std::cout << "\\makebox[\\textwidth][c]{" << std::endl;
  std::cout << "\\begin{tabular}{r";
  for (int ibin=0; ibin < n_mt2bins; ++ibin) std::cout << "|c";
  std::cout << "}" << std::endl;
  std::cout << "\\hline" << std::endl;
  std::cout << "\\hline" << endl
  << "Sample";
  
  // header
  for (int ibin = 1; ibin < n_mt2bins; ++ibin) {
    cout << " & " << h_mt2bins->GetXaxis()->GetBinLowEdge(ibin) << " - " << h_mt2bins->GetXaxis()->GetBinLowEdge(ibin+1) << " GeV";
  }
  cout << " & MTmin $>$ " << h_mt2bins->GetXaxis()->GetBinLowEdge(n_mt2bins) << " GeV";
  cout << " \\\\" << endl
  << "\\hline\\hline" << endl;
  
  // backgrounds first -- loop backwards
  for( int isamp = n-1 ; isamp >= 0 ; --isamp ){
    if( TString(purpose.at(isamp)).Contains("data")  ) continue;
    if( TString(purpose.at(isamp)).Contains("sig")  ) continue;
    cout<<labels.at(isamp)<<endl;
//    cout << getTableName(names.at(isamp));
    for (int ibin = 1; ibin <= n_mt2bins; ++ibin) {
      TString fullhistname = nplots[isamp];
      TFile f( files[isamp], "READ");
      if(!f.IsOpen()){
        std::cout<<"File "<<files[isamp]<<" can't be found, will not be used for histogram "<<nplots[isamp]<<std::endl;
        continue;
      }
      if(f.Get(nplots[isamp].Data())==0){
        std::cout<<"Histogram "<<nplots[isamp]<<" not found in file "<<files[isamp]<<std::endl;
        continue;
      }
      TH1D* h = (TH1D*) f.Get(fullhistname);
      double yield = 0.;
      double err = 0.;
      if (h) {
        // not last bin
        if(ibin != n_mt2bins) {
          yield = h->GetBinContent(ibin);
          err = h->GetBinError(ibin);
          bgtot.at(ibin-1) += yield;
          bgerr.at(ibin-1) = sqrt(pow(bgerr.at(ibin-1),2) + pow(err,2));
        }
        // last bin: include overflow
        else if (ibin == h->GetXaxis()->GetNbins()) {
          yield = h->IntegralAndError(ibin,-1,err);
          bgtot.at(ibin-1) += yield;
          bgerr.at(ibin-1) = sqrt(pow(bgerr.at(ibin-1),2) + pow(err,2));
        }
        else {
          std::cout << "Shouldn't get here" << std::endl;
          return;
        }
      }
      if (yield > 10.) {
        //  	cout << "  &  " << Form("%.0f $\\pm$ %.0f",yield,err);
        cout << "  &  " << Form("%.1f $\\pm$ %.1f",yield,err);
      } else {
        //  	cout << "  &  " << Form("%.1f $\\pm$ %.1f",yield,err);
        cout << "  &  " << Form("%.2f $\\pm$ %.2f",yield,err);
      }
    }
    cout << " \\\\" << endl;
  } // loop over samples
  
  // print bg totals
  cout << "\\hline" << endl;
  cout << "Total SM";
  for ( int ibin = 0; ibin < n_mt2bins; ++ibin ) {
    double yield = bgtot.at(ibin);
    double err = bgerr.at(ibin);
    if (yield > 10.) {
      //  	cout << "  &  " << Form("%.0f $\\pm$ %.0f",yield,err);
      cout << "  &  " << Form("%.1f $\\pm$ %.1f",yield,err);
    } else {
      //  	cout << "  &  " << Form("%.1f $\\pm$ %.1f",yield,err);
      cout << "  &  " << Form("%.2f $\\pm$ %.2f",yield,err);
    }
  }
  cout << " \\\\" << endl;
  cout << "\\hline" << endl;
  
  for( unsigned int jsamp = 0 ; jsamp < n ; jsamp++ ){
    if( !TString(purpose.at(jsamp)).Contains("sig") ) continue;
    cout<<labels.at(jsamp)<<endl;
//    cout << getTableName(names.at(jsamp));
    for (int ibin = 1; ibin <= n_mt2bins; ++ibin) {
      TString fullhistname = nplots[jsamp];
      TFile f( files[jsamp], "READ");
      if(!f.IsOpen()){
        std::cout<<"File "<<files[jsamp]<<" can't be found, will not be used for histogram "<<nplots[jsamp]<<std::endl;
        continue;
      }
      if(f.Get(nplots[jsamp].Data())==0){
        std::cout<<"Histogram "<<nplots[jsamp]<<" not found in file "<<files[jsamp]<<std::endl;
        continue;
      }
      TH1D* h = (TH1D*) f.Get(fullhistname);
//      TH1D* h = (TH1D*) samples.at(jsamp)->Get(fullhistname);
      double yield = 0.;
      double err = 0.;
      if (h) {
        // not last bin
        if(ibin != n_mt2bins) {
          yield = h->GetBinContent(ibin);
          err = h->GetBinError(ibin);
        }
        // last bin: include overflow
        else if (ibin == h->GetXaxis()->GetNbins()) {
          yield = h->IntegralAndError(ibin,-1,err);
        }
        else {
          std::cout << "Shouldn't get here" << std::endl;
          return;
        }
      }
      if (yield > 10.) {
        //  	cout << "  &  " << Form("%.0f $\\pm$ %.0f",yield,err);
        cout << "  &  " << Form("%.1f $\\pm$ %.1f",yield,err);
      } else {
        //  	cout << "  &  " << Form("%.1f $\\pm$ %.1f",yield,err);
        cout << "  &  " << Form("%.2f $\\pm$ %.2f",yield,err);
      }
    }
    cout << " \\\\" << endl;
  } // loop over samples
  
  
  std::cout << "\\hline" << std::endl;
  std::cout << "\\end{tabular}}" << std::endl;
  std::cout << "\\end{table}" << std::endl;
  //std::cout << "\\pagebreak" << std::endl;
  std::cout << std::endl;
  
  return;
}



void makeTable() {
  
  string dir = "~/UCSD/Upgrade/Hists/";
  string dir2 = "~/UCSD/Upgrade/Hists/weights_2Jul17/";
  string dir3 = "~/UCSD/Upgrade/Hists/testNewDelphes/old/";
  string dir4 = "~/UCSD/Upgrade/Hists/testNewDelphes/new/";
  string dir5 = "~/UCSD/Upgrade/Hists/test/";
  string dir6 = "~/UCSD/Upgrade/Hists/advanced8Aug17_2Oct17/";
  string dir7 = "~/UCSD/Upgrade/Hists/advanced8Aug17_2Oct17_eta2p4/";
  string dir8 = "~/UCSD/Upgrade/Hists/advanced8Aug17_2Oct17_eta1p6/";

  string dirSigScan = "~/UCSD/Upgrade/Hists/advancedSignal14Nov17/";

  
  string BJFile = "Bjall.root"; 
  string BBFile = "BBall.root"; 
  string LLBFile = "LLBall.root";
  string BBFile700 = "BB0to700.root"; 
  string BBBFile = "BBBall.root";   
  string ttBFile = "ttBall.root"; 
  string sigFile = "C2N4full.root"; 
  
  
  
  vector<TString> files; std::vector<TString> labels; vector<TString> nplots; vector<TString> SRdirs; vector<TString> purpose;
  
  
  
  files.clear(); labels.clear(); nplots.clear(); SRdirs.clear(); purpose.clear(); 
  files.push_back(dir+BJFile);       labels.push_back("BJ (Fakes)");             nplots.push_back("Base/h_mtmin"); 
  files.push_back(dir+BBFile);       labels.push_back("BB");                     nplots.push_back("Base/h_mtmin"); 
  files.push_back(dir+BBBFile);     labels.push_back("BBB");              nplots.push_back("Base/h_mtmin"); 
  files.push_back(dir+ttBFile);     labels.push_back("ttB");                   nplots.push_back("Base/h_mtmin"); 
  files.push_back(dir+sigFile);     labels.push_back("C2N4");                   nplots.push_back("Base/h_mtmin"); 
  SRdirs.push_back("Yield");
  printTable(files, labels, nplots, SRdirs, 200);
  
  
  files.clear(); labels.clear(); nplots.clear(); SRdirs.clear(); purpose.clear(); 
  files.push_back(dir+BJFile);       labels.push_back("BJ (Fakes)");             nplots.push_back("lepVeto/h_mtmin"); 
  files.push_back(dir+BBFile);       labels.push_back("BB");                     nplots.push_back("lepVeto/h_mtmin"); 
  files.push_back(dir+BBBFile);     labels.push_back("BBB");              nplots.push_back("lepVeto/h_mtmin"); 
  files.push_back(dir+ttBFile);     labels.push_back("ttB");                   nplots.push_back("lepVeto/h_mtmin"); 
  files.push_back(dir+sigFile);     labels.push_back("C2N4");                   nplots.push_back("lepVeto/h_mtmin"); 
  SRdirs.push_back("Yield");
  printTable(files, labels, nplots, SRdirs, 200);
  
  
  
  files.clear(); labels.clear(); nplots.clear(); SRdirs.clear(); purpose.clear(); 
  files.push_back(dir+BJFile);       labels.push_back("BJ (Fakes)");             nplots.push_back("bVeto/h_mtmin"); 
  files.push_back(dir+BBFile);       labels.push_back("BB");                     nplots.push_back("bVeto/h_mtmin"); 
  files.push_back(dir+BBBFile);     labels.push_back("BBB");              nplots.push_back("bVeto/h_mtmin"); 
  files.push_back(dir+ttBFile);     labels.push_back("ttB");                   nplots.push_back("bVeto/h_mtmin"); 
  files.push_back(dir+sigFile);     labels.push_back("C2N4");                   nplots.push_back("bVeto/h_mtmin"); 
  SRdirs.push_back("Yield");
  printTable(files, labels, nplots, SRdirs, 200);
  
  
  files.clear(); labels.clear(); nplots.clear(); SRdirs.clear(); purpose.clear(); 
  files.push_back(dir+BJFile);       labels.push_back("BJ (Fakes)");             nplots.push_back("j4Veto/h_mtmin"); 
  files.push_back(dir+BBFile);       labels.push_back("BB");                     nplots.push_back("j4Veto/h_mtmin"); 
  files.push_back(dir+BBBFile);     labels.push_back("BBB");              nplots.push_back("j4Veto/h_mtmin"); 
  files.push_back(dir+ttBFile);     labels.push_back("ttB");                   nplots.push_back("j4Veto/h_mtmin"); 
  files.push_back(dir+sigFile);     labels.push_back("C2N4");                   nplots.push_back("j4Veto/h_mtmin"); 
  SRdirs.push_back("Yield");
  printTable(files, labels, nplots, SRdirs, 200);
  
  
  std::cout<<"----  With Weights ----"<<std::endl;
  files.clear(); labels.clear(); nplots.clear(); SRdirs.clear(); purpose.clear(); 
  files.push_back(dir2+BJFile);       labels.push_back("BJ (Fakes)");             nplots.push_back("j4Veto/h_mtmin"); 
  files.push_back(dir2+BBFile);       labels.push_back("BB");                     nplots.push_back("j4Veto/h_mtmin"); 
  files.push_back(dir2+BBBFile);     labels.push_back("BBB");              nplots.push_back("j4Veto/h_mtmin"); 
  files.push_back(dir2+ttBFile);     labels.push_back("ttB");                   nplots.push_back("j4Veto/h_mtmin"); 
  files.push_back(dir2+sigFile);     labels.push_back("C2N4");                   nplots.push_back("j4Veto/h_mtmin"); 
  SRdirs.push_back("Yield");
  printTable(files, labels, nplots, SRdirs, 200);
  
  std::cout<<"----  Without Weights, no MTmin cut ----"<<std::endl;
  files.clear(); labels.clear(); nplots.clear(); SRdirs.clear(); purpose.clear(); 
  files.push_back(dir5+BJFile);       labels.push_back("BJ (Fakes)");             nplots.push_back("j4Veto/h_mtmin"); 
  files.push_back(dir5+BBFile);       labels.push_back("BB");                     nplots.push_back("j4Veto/h_mtmin"); 
  files.push_back(dir5+BBBFile);     labels.push_back("BBB");              nplots.push_back("j4Veto/h_mtmin"); 
  files.push_back(dir5+ttBFile);     labels.push_back("ttB");                   nplots.push_back("j4Veto/h_mtmin"); 
  files.push_back(dir5+sigFile);     labels.push_back("C2N4");                   nplots.push_back("j4Veto/h_mtmin"); 
  SRdirs.push_back("Yield");
  printTable(files, labels, nplots, SRdirs, 0);
  
  
  
  
  files.clear(); labels.clear(); nplots.clear(); purpose.clear();  
  files.push_back(dir+BJFile);        labels.push_back("BJ (Fakes)");                     nplots.push_back("j4Veto/h_mtmin"); purpose.push_back("bkg");
  files.push_back(dir+BBFile);        labels.push_back("WZ");                     nplots.push_back("WZ/h_mtmin"); purpose.push_back("bkg");
  files.push_back(dir+BBFile);        labels.push_back("VG");                     nplots.push_back("other/h_mtmin"); purpose.push_back("bkg");
  files.push_back(dir+BBFile);        labels.push_back("WW");                     nplots.push_back("WW/h_mtmin"); purpose.push_back("bkg");
  files.push_back(dir+BBFile);        labels.push_back("ZZ");                     nplots.push_back("ZZ/h_mtmin"); purpose.push_back("bkg");
  files.push_back(dir+BBBFile);        labels.push_back("WWW");               nplots.push_back("WWW/h_mtmin"); purpose.push_back("bkg");
  files.push_back(dir+BBBFile);        labels.push_back("VVZ");               nplots.push_back("VVZ/h_mtmin"); purpose.push_back("bkg");
  files.push_back(dir+BBBFile);        labels.push_back("VH");               nplots.push_back("VH/h_mtmin"); purpose.push_back("bkg");
  files.push_back(dir+ttBFile);        labels.push_back("ttW");                     nplots.push_back("ttW/h_mtmin"); purpose.push_back("bkg");
  files.push_back(dir+ttBFile);        labels.push_back("ttZ");                     nplots.push_back("ttZ/h_mtmin"); purpose.push_back("bkg");
  files.push_back(dir+sigFile);       labels.push_back("C2N4");                   nplots.push_back("j4Veto/h_mtmin"); purpose.push_back("sig");
//  SRdirs.push_back("Yield");
  printTable(files, labels, nplots, SRdirs, 200);
  
  files.clear(); labels.clear(); nplots.clear(); SRdirs.clear(); purpose.clear(); 
  files.push_back(dir3+BBFile700);       labels.push_back("BB");                     nplots.push_back("Base/h_mtmin"); 
  files.push_back(dir4+BBFile700);       labels.push_back("BB");                     nplots.push_back("Base/h_mtmin"); 
  SRdirs.push_back("Yield");
  printTable(files, labels, nplots, SRdirs, 200);
  
  
  files.clear(); labels.clear(); nplots.clear(); SRdirs.clear(); purpose.clear(); 
  files.push_back(dir3+BBFile700);       labels.push_back("BB");                     nplots.push_back("bVeto/h_mtmin"); 
  files.push_back(dir4+BBFile700);       labels.push_back("BB");                     nplots.push_back("bVeto/h_mtmin"); 
  SRdirs.push_back("Yield");
  printTable(files, labels, nplots, SRdirs, 200);
  
  
  files.clear(); labels.clear(); nplots.clear(); purpose.clear();  
  files.push_back(dir6+BBFile);        labels.push_back("WZ");                     nplots.push_back("j2Veto/h_mtmin_WZ"); purpose.push_back("bkg");
  files.push_back(dir6+BBFile);        labels.push_back("VG");                     nplots.push_back("j2Veto/h_mtmin_VG"); purpose.push_back("bkg");
  files.push_back(dir6+BBFile);        labels.push_back("WW");                     nplots.push_back("j2Veto/h_mtmin_WW"); purpose.push_back("bkg"); 
  files.push_back(dir6+BBFile);        labels.push_back("ZZ");                     nplots.push_back("j2Veto/h_mtmin_ZZ"); purpose.push_back("bkg");
  files.push_back(dir6+BBFile);        labels.push_back("BBother");               nplots.push_back("j2Veto/h_mtmin_other"); purpose.push_back("bkg");
  files.push_back(dir6+LLBFile);        labels.push_back("LLB");                  nplots.push_back("j2Veto/h_mtmin"); purpose.push_back("bkg");
  files.push_back(dir6+BBBFile);        labels.push_back("WWW");                     nplots.push_back("j2Veto/h_mtmin_WWW"); purpose.push_back("bkg");
  files.push_back(dir6+BBBFile);        labels.push_back("VVZ");                     nplots.push_back("j2Veto/h_mtmin_VVZ"); purpose.push_back("bkg");
  files.push_back(dir6+ttBFile);        labels.push_back("ttW");                     nplots.push_back("j2Veto/h_mtmin_ttW"); purpose.push_back("bkg");
  files.push_back(dir6+ttBFile);        labels.push_back("ttZ");                     nplots.push_back("j2Veto/h_mtmin_ttZ"); purpose.push_back("bkg");
  files.push_back(dir6+sigFile);       labels.push_back("C2N4");                   nplots.push_back("j2Veto/h_mtmin"); purpose.push_back("sig");
  //  SRdirs.push_back("Yield");
  printTable(files, labels, nplots, SRdirs, 120, "Muon veto out to eta $<$ 2.8");
  
  
  files.clear(); labels.clear(); nplots.clear(); purpose.clear();  
  files.push_back(dir7+BBFile);        labels.push_back("WZ");                     nplots.push_back("j2Veto/h_mtmin_WZ"); purpose.push_back("bkg");
  files.push_back(dir7+BBFile);        labels.push_back("VG");                     nplots.push_back("j2Veto/h_mtmin_VG"); purpose.push_back("bkg");
  files.push_back(dir7+BBFile);        labels.push_back("WW");                     nplots.push_back("j2Veto/h_mtmin_WW"); purpose.push_back("bkg"); 
  files.push_back(dir7+BBFile);        labels.push_back("ZZ");                     nplots.push_back("j2Veto/h_mtmin_ZZ"); purpose.push_back("bkg");
  files.push_back(dir7+BBFile);        labels.push_back("BBother");               nplots.push_back("j2Veto/h_mtmin_other"); purpose.push_back("bkg");
  files.push_back(dir7+LLBFile);        labels.push_back("LLB");                  nplots.push_back("j2Veto/h_mtmin"); purpose.push_back("bkg");
  files.push_back(dir7+BBBFile);        labels.push_back("WWW");                     nplots.push_back("j2Veto/h_mtmin_WWW"); purpose.push_back("bkg");
  files.push_back(dir7+BBBFile);        labels.push_back("VVZ");                     nplots.push_back("j2Veto/h_mtmin_VVZ"); purpose.push_back("bkg");
  files.push_back(dir7+ttBFile);        labels.push_back("ttW");                     nplots.push_back("j2Veto/h_mtmin_ttW"); purpose.push_back("bkg");
  files.push_back(dir7+ttBFile);        labels.push_back("ttZ");                     nplots.push_back("j2Veto/h_mtmin_ttZ"); purpose.push_back("bkg");
  files.push_back(dir7+sigFile);       labels.push_back("C2N4");                   nplots.push_back("j2Veto/h_mtmin"); purpose.push_back("sig");
  //  SRdirs.push_back("Yield");
  printTable(files, labels, nplots, SRdirs, 120, "Muon veto out to eta $<$ 2.4");
  
  
  
  files.clear(); labels.clear(); nplots.clear(); purpose.clear();  
  files.push_back(dir8+BBFile);        labels.push_back("WZ");                     nplots.push_back("j2Veto/h_mtmin_WZ"); purpose.push_back("bkg");
  files.push_back(dir8+BBFile);        labels.push_back("VG");                     nplots.push_back("j2Veto/h_mtmin_VG"); purpose.push_back("bkg");
  files.push_back(dir8+BBFile);        labels.push_back("WW");                     nplots.push_back("j2Veto/h_mtmin_WW"); purpose.push_back("bkg"); 
  files.push_back(dir8+BBFile);        labels.push_back("ZZ");                     nplots.push_back("j2Veto/h_mtmin_ZZ"); purpose.push_back("bkg");
  files.push_back(dir8+BBFile);        labels.push_back("BBother");               nplots.push_back("j2Veto/h_mtmin_other"); purpose.push_back("bkg");
  files.push_back(dir8+LLBFile);        labels.push_back("LLB");                  nplots.push_back("j2Veto/h_mtmin"); purpose.push_back("bkg");
  files.push_back(dir8+BBBFile);        labels.push_back("WWW");                     nplots.push_back("j2Veto/h_mtmin_WWW"); purpose.push_back("bkg");
  files.push_back(dir8+BBBFile);        labels.push_back("VVZ");                     nplots.push_back("j2Veto/h_mtmin_VVZ"); purpose.push_back("bkg");
  files.push_back(dir8+ttBFile);        labels.push_back("ttW");                     nplots.push_back("j2Veto/h_mtmin_ttW"); purpose.push_back("bkg");
  files.push_back(dir8+ttBFile);        labels.push_back("ttZ");                     nplots.push_back("j2Veto/h_mtmin_ttZ"); purpose.push_back("bkg");
  files.push_back(dir8+sigFile);       labels.push_back("C2N4");                   nplots.push_back("j2Veto/h_mtmin"); purpose.push_back("sig");
  //  SRdirs.push_back("Yield");
  printTable(files, labels, nplots, SRdirs, 120, "Muon veto out to eta $<$ 1.6");
  
  
  files.clear(); labels.clear(); nplots.clear(); purpose.clear();  
  files.push_back(dirSigScan+BBFile);        labels.push_back("WZ");                     nplots.push_back("j2Veto/h_mtminbins_WZ"); purpose.push_back("bkg");
  files.push_back(dirSigScan+BBFile);        labels.push_back("VG");                     nplots.push_back("j2Veto/h_mtminbins_VG"); purpose.push_back("bkg");
  files.push_back(dirSigScan+BBFile);        labels.push_back("WW");                     nplots.push_back("j2Veto/h_mtminbins_WW"); purpose.push_back("bkg"); 
  files.push_back(dirSigScan+BBFile);        labels.push_back("ZZ");                     nplots.push_back("j2Veto/h_mtminbins_ZZ"); purpose.push_back("bkg");
  files.push_back(dirSigScan+BBFile);        labels.push_back("BBother");               nplots.push_back("j2Veto/h_mtminbins_other"); purpose.push_back("bkg");
  files.push_back(dirSigScan+LLBFile);        labels.push_back("LLB");                  nplots.push_back("j2Veto/h_mtminbins"); purpose.push_back("bkg");
  files.push_back(dirSigScan+BBBFile);        labels.push_back("WWW");                     nplots.push_back("j2Veto/h_mtminbins_WWW"); purpose.push_back("bkg");
  files.push_back(dirSigScan+BBBFile);        labels.push_back("VVZ");                     nplots.push_back("j2Veto/h_mtminbins_VVZ"); purpose.push_back("bkg");
  files.push_back(dirSigScan+ttBFile);        labels.push_back("ttW");                     nplots.push_back("j2Veto/h_mtminbins_ttW"); purpose.push_back("bkg");
  files.push_back(dirSigScan+ttBFile);        labels.push_back("ttZ");                     nplots.push_back("j2Veto/h_mtminbins_ttZ"); purpose.push_back("bkg");
  files.push_back(dirSigScan+"Decayed_C2N4_Baer_450_LSP_150_200PU.root");       labels.push_back("450/150");                   nplots.push_back("j2Veto/h_mtminbins"); purpose.push_back("sig");
  files.push_back(dirSigScan+"Decayed_C2N4_Baer_600_LSP_150_200PU.root");       labels.push_back("600/150");                   nplots.push_back("j2Veto/h_mtminbins"); purpose.push_back("sig");
  files.push_back(dirSigScan+"Decayed_C2N4_Baer_600_LSP_250_200PU.root");       labels.push_back("600/250");                   nplots.push_back("j2Veto/h_mtminbins"); purpose.push_back("sig");
  files.push_back(dirSigScan+"Decayed_C2N4_Baer_950_LSP_150_200PU.root");       labels.push_back("950/150");                   nplots.push_back("j2Veto/h_mtminbins"); purpose.push_back("sig");
  //  SRdirs.push_back("Yield");
  printTable(files, labels, nplots, SRdirs, 200, "Backgrounds (and old signal) after jet veto, MTmin$>$200");
  printDetailedTable(files, labels, nplots, purpose);
  //  void printDetailedTable( vector<TFile*> samples , vector<string> names , string dir) {

  
  files.clear(); labels.clear(); nplots.clear(); purpose.clear();  
  files.push_back(dirSigScan+BBFile);        labels.push_back("WZ");                     nplots.push_back("met250/h_mtminbins_WZ"); purpose.push_back("bkg");
  files.push_back(dirSigScan+BBFile);        labels.push_back("VG");                     nplots.push_back("met250/h_mtminbins_VG"); purpose.push_back("bkg");
  files.push_back(dirSigScan+BBFile);        labels.push_back("WW");                     nplots.push_back("met250/h_mtminbins_WW"); purpose.push_back("bkg"); 
  files.push_back(dirSigScan+BBFile);        labels.push_back("ZZ");                     nplots.push_back("met250/h_mtminbins_ZZ"); purpose.push_back("bkg");
  files.push_back(dirSigScan+BBFile);        labels.push_back("BBother");               nplots.push_back("met250/h_mtminbins_other"); purpose.push_back("bkg");
  files.push_back(dirSigScan+LLBFile);        labels.push_back("LLB");                  nplots.push_back("met250/h_mtminbins"); purpose.push_back("bkg");
  files.push_back(dirSigScan+BBBFile);        labels.push_back("WWW");                     nplots.push_back("met250/h_mtminbins_WWW"); purpose.push_back("bkg");
  files.push_back(dirSigScan+BBBFile);        labels.push_back("VVZ");                     nplots.push_back("met250/h_mtminbins_VVZ"); purpose.push_back("bkg");
  files.push_back(dirSigScan+ttBFile);        labels.push_back("ttW");                     nplots.push_back("met250/h_mtminbins_ttW"); purpose.push_back("bkg");
  files.push_back(dirSigScan+ttBFile);        labels.push_back("ttZ");                     nplots.push_back("met250/h_mtminbins_ttZ"); purpose.push_back("bkg");
  files.push_back(dirSigScan+"Decayed_C2N4_Baer_450_LSP_150_200PU.root");       labels.push_back("450/150");                   nplots.push_back("met250/h_mtminbins"); purpose.push_back("sig");
  files.push_back(dirSigScan+"Decayed_C2N4_Baer_600_LSP_150_200PU.root");       labels.push_back("600/150");                   nplots.push_back("met250/h_mtminbins"); purpose.push_back("sig");
  files.push_back(dirSigScan+"Decayed_C2N4_Baer_600_LSP_250_200PU.root");       labels.push_back("600/250");                   nplots.push_back("met250/h_mtminbins"); purpose.push_back("sig");
  files.push_back(dirSigScan+"Decayed_C2N4_Baer_950_LSP_150_200PU.root");       labels.push_back("950/150");                   nplots.push_back("met250/h_mtminbins"); purpose.push_back("sig");
  //  SRdirs.push_back("Yield");
  printDetailedTable(files, labels, nplots, purpose);
  
  files.clear(); labels.clear(); nplots.clear(); purpose.clear();
  files.push_back(dirSigScan+"Decayed_C2N4_Baer_400_LSP_150_200PU.root");       labels.push_back("400/150");                   nplots.push_back("bVeto/h_mtmin"); purpose.push_back("sig");
  files.push_back(dirSigScan+"Decayed_C2N4_Baer_450_LSP_150_200PU.root");       labels.push_back("450/150");                   nplots.push_back("bVeto/h_mtmin"); purpose.push_back("sig");
  files.push_back(dirSigScan+"Decayed_C2N4_Baer_450_LSP_250_200PU.root");       labels.push_back("450/250");                   nplots.push_back("bVeto/h_mtmin"); purpose.push_back("sig");
  files.push_back(dirSigScan+"Decayed_C2N4_Baer_500_LSP_150_200PU.root");       labels.push_back("500/150");                   nplots.push_back("bVeto/h_mtmin"); purpose.push_back("sig");
  files.push_back(dirSigScan+"Decayed_C2N4_Baer_500_LSP_250_200PU.root");       labels.push_back("500/250");                   nplots.push_back("bVeto/h_mtmin"); purpose.push_back("sig");
  files.push_back(dirSigScan+"Decayed_C2N4_Baer_550_LSP_150_200PU.root");       labels.push_back("550/150");                   nplots.push_back("bVeto/h_mtmin"); purpose.push_back("sig");
  files.push_back(dirSigScan+"Decayed_C2N4_Baer_550_LSP_250_200PU.root");       labels.push_back("550/250");                   nplots.push_back("bVeto/h_mtmin"); purpose.push_back("sig");
  files.push_back(dirSigScan+"Decayed_C2N4_Baer_600_LSP_150_200PU.root");       labels.push_back("600/150");                   nplots.push_back("bVeto/h_mtmin"); purpose.push_back("sig");
  files.push_back(dirSigScan+"Decayed_C2N4_Baer_600_LSP_250_200PU.root");       labels.push_back("600/250");                   nplots.push_back("bVeto/h_mtmin"); purpose.push_back("sig");
  files.push_back(dirSigScan+"Decayed_C2N4_Baer_650_LSP_150_200PU.root");       labels.push_back("650/150");                   nplots.push_back("bVeto/h_mtmin"); purpose.push_back("sig");
  files.push_back(dirSigScan+"Decayed_C2N4_Baer_650_LSP_250_200PU.root");       labels.push_back("650/250");                   nplots.push_back("bVeto/h_mtmin"); purpose.push_back("sig");
  files.push_back(dirSigScan+"Decayed_C2N4_Baer_700_LSP_150_200PU.root");       labels.push_back("700/150");                   nplots.push_back("bVeto/h_mtmin"); purpose.push_back("sig");
  files.push_back(dirSigScan+"Decayed_C2N4_Baer_700_LSP_250_200PU.root");       labels.push_back("700/250");                   nplots.push_back("bVeto/h_mtmin"); purpose.push_back("sig");
  files.push_back(dirSigScan+"Decayed_C2N4_Baer_750_LSP_150_200PU.root");       labels.push_back("750/150");                   nplots.push_back("bVeto/h_mtmin"); purpose.push_back("sig");
  files.push_back(dirSigScan+"Decayed_C2N4_Baer_750_LSP_250_200PU.root");       labels.push_back("750/250");                   nplots.push_back("bVeto/h_mtmin"); purpose.push_back("sig");
  files.push_back(dirSigScan+"Decayed_C2N4_Baer_800_LSP_150_200PU.root");       labels.push_back("800/150");                   nplots.push_back("bVeto/h_mtmin"); purpose.push_back("sig");
  files.push_back(dirSigScan+"Decayed_C2N4_Baer_800_LSP_250_200PU.root");       labels.push_back("800/250");                   nplots.push_back("bVeto/h_mtmin"); purpose.push_back("sig");
  files.push_back(dirSigScan+"Decayed_C2N4_Baer_850_LSP_150_200PU.root");       labels.push_back("850/150");                   nplots.push_back("bVeto/h_mtmin"); purpose.push_back("sig");
  files.push_back(dirSigScan+"Decayed_C2N4_Baer_850_LSP_250_200PU.root");       labels.push_back("850/250");                   nplots.push_back("bVeto/h_mtmin"); purpose.push_back("sig");
  files.push_back(dirSigScan+"Decayed_C2N4_Baer_900_LSP_150_200PU.root");       labels.push_back("900/150");                   nplots.push_back("bVeto/h_mtmin"); purpose.push_back("sig");
  files.push_back(dirSigScan+"Decayed_C2N4_Baer_900_LSP_250_200PU.root");       labels.push_back("900/250");                   nplots.push_back("bVeto/h_mtmin"); purpose.push_back("sig");
  files.push_back(dirSigScan+"Decayed_C2N4_Baer_950_LSP_150_200PU.root");       labels.push_back("950/150");                   nplots.push_back("bVeto/h_mtmin"); purpose.push_back("sig");
  files.push_back(dirSigScan+"Decayed_C2N4_Baer_950_LSP_250_200PU.root");       labels.push_back("950/250");                   nplots.push_back("bVeto/h_mtmin"); purpose.push_back("sig");
  printTable(files, labels, nplots, SRdirs, 120, "Signal Events, MTmin$>$120");

  
  files.clear(); labels.clear(); nplots.clear(); purpose.clear();
  files.push_back(dirSigScan+"Decayed_C2N4_Baer_400_LSP_150_200PU.root");       labels.push_back("400/150");                   nplots.push_back("bVeto/h_mtmin"); purpose.push_back("sig");
  files.push_back(dirSigScan+"Decayed_C2N4_Baer_450_LSP_150_200PU.root");       labels.push_back("450/150");                   nplots.push_back("bVeto/h_mtmin"); purpose.push_back("sig");
  files.push_back(dirSigScan+"Decayed_C2N4_Baer_450_LSP_250_200PU.root");       labels.push_back("450/250");                   nplots.push_back("bVeto/h_mtmin"); purpose.push_back("sig");
  files.push_back(dirSigScan+"Decayed_C2N4_Baer_500_LSP_150_200PU.root");       labels.push_back("500/150");                   nplots.push_back("bVeto/h_mtmin"); purpose.push_back("sig");
  files.push_back(dirSigScan+"Decayed_C2N4_Baer_500_LSP_250_200PU.root");       labels.push_back("500/250");                   nplots.push_back("bVeto/h_mtmin"); purpose.push_back("sig");
  files.push_back(dirSigScan+"Decayed_C2N4_Baer_550_LSP_150_200PU.root");       labels.push_back("550/150");                   nplots.push_back("bVeto/h_mtmin"); purpose.push_back("sig");
  files.push_back(dirSigScan+"Decayed_C2N4_Baer_550_LSP_250_200PU.root");       labels.push_back("550/250");                   nplots.push_back("bVeto/h_mtmin"); purpose.push_back("sig");
  files.push_back(dirSigScan+"Decayed_C2N4_Baer_600_LSP_150_200PU.root");       labels.push_back("600/150");                   nplots.push_back("bVeto/h_mtmin"); purpose.push_back("sig");
  files.push_back(dirSigScan+"Decayed_C2N4_Baer_600_LSP_250_200PU.root");       labels.push_back("600/250");                   nplots.push_back("bVeto/h_mtmin"); purpose.push_back("sig");
  files.push_back(dirSigScan+"Decayed_C2N4_Baer_650_LSP_150_200PU.root");       labels.push_back("650/150");                   nplots.push_back("bVeto/h_mtmin"); purpose.push_back("sig");
  files.push_back(dirSigScan+"Decayed_C2N4_Baer_650_LSP_250_200PU.root");       labels.push_back("650/250");                   nplots.push_back("bVeto/h_mtmin"); purpose.push_back("sig");
  files.push_back(dirSigScan+"Decayed_C2N4_Baer_700_LSP_150_200PU.root");       labels.push_back("700/150");                   nplots.push_back("bVeto/h_mtmin"); purpose.push_back("sig");
  files.push_back(dirSigScan+"Decayed_C2N4_Baer_700_LSP_250_200PU.root");       labels.push_back("700/250");                   nplots.push_back("bVeto/h_mtmin"); purpose.push_back("sig");
  files.push_back(dirSigScan+"Decayed_C2N4_Baer_750_LSP_150_200PU.root");       labels.push_back("750/150");                   nplots.push_back("bVeto/h_mtmin"); purpose.push_back("sig");
  files.push_back(dirSigScan+"Decayed_C2N4_Baer_750_LSP_250_200PU.root");       labels.push_back("750/250");                   nplots.push_back("bVeto/h_mtmin"); purpose.push_back("sig");
  files.push_back(dirSigScan+"Decayed_C2N4_Baer_800_LSP_150_200PU.root");       labels.push_back("800/150");                   nplots.push_back("bVeto/h_mtmin"); purpose.push_back("sig");
  files.push_back(dirSigScan+"Decayed_C2N4_Baer_800_LSP_250_200PU.root");       labels.push_back("800/250");                   nplots.push_back("bVeto/h_mtmin"); purpose.push_back("sig");
  files.push_back(dirSigScan+"Decayed_C2N4_Baer_850_LSP_150_200PU.root");       labels.push_back("850/150");                   nplots.push_back("bVeto/h_mtmin"); purpose.push_back("sig");
  files.push_back(dirSigScan+"Decayed_C2N4_Baer_850_LSP_250_200PU.root");       labels.push_back("850/250");                   nplots.push_back("bVeto/h_mtmin"); purpose.push_back("sig");
  files.push_back(dirSigScan+"Decayed_C2N4_Baer_900_LSP_150_200PU.root");       labels.push_back("900/150");                   nplots.push_back("bVeto/h_mtmin"); purpose.push_back("sig");
  files.push_back(dirSigScan+"Decayed_C2N4_Baer_900_LSP_250_200PU.root");       labels.push_back("900/250");                   nplots.push_back("bVeto/h_mtmin"); purpose.push_back("sig");
  files.push_back(dirSigScan+"Decayed_C2N4_Baer_950_LSP_150_200PU.root");       labels.push_back("950/150");                   nplots.push_back("bVeto/h_mtmin"); purpose.push_back("sig");
  files.push_back(dirSigScan+"Decayed_C2N4_Baer_950_LSP_250_200PU.root");       labels.push_back("950/250");                   nplots.push_back("bVeto/h_mtmin"); purpose.push_back("sig");
  printTable(files, labels, nplots, SRdirs, 200, "Signal Events, MTmin$>$200");
  

  

  
  return;
}
