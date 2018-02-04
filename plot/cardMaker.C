#include <iostream>
#include <utility>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <set>
#include <regex>
#include <sys/stat.h>

#include "TROOT.h"
#include "TLatex.h"
#include "TString.h"
#include "TFile.h"
#include "TH1.h"
#include "TH3.h"
#include "TList.h"
#include "TCollection.h"
#include "TKey.h"
#include "TBenchmark.h"
#include "RooHistError.h"

using namespace std;

TFile* f_BJ = 0;
TFile* f_TT = 0;
TFile* f_BB = 0;
TFile* f_LLB = 0;
TFile* f_BBB = 0;
TFile* f_ttB = 0;
TFile* f_sig = 0;
TFile* f_data = 0;

const bool verbose = false;

const bool printTable = false; //if true, prints additional .txt files with the data & bkg yields and uncertainties for plotmaking

inline bool FileExists(const TString name) {
  struct stat buffer;   
  return (stat (name.Data(), &buffer) == 0); 
}

//_______________________________________________________________________________
void ReplaceString(std::string& subject, const std::string& search, const std::string& replace) {
    size_t pos = 0;
    while((pos = subject.find(search, pos)) != std::string::npos) {
         subject.replace(pos, search.length(), replace);
         pos += replace.length();
    }
}

//_______________________________________________________________________________
double round(double d)
{
  return floor(d + 0.5);
}

void IncludeOverflow ( TH1D* h ) {
  
  // OverFlow
  double lastbin = h->GetBinContent(h->GetNbinsX());
  double lastbinErr = h->GetBinError(h->GetNbinsX());
  double overflow = h->GetBinContent(h->GetNbinsX()+1);
  double overflowErr = h->GetBinError(h->GetNbinsX()+1);
  h->SetBinContent(h->GetNbinsX(), lastbin + overflow);
  h->SetBinContent(h->GetNbinsX()+1, 0);
  h->SetBinError(h->GetNbinsX(), sqrt(lastbinErr*lastbinErr + overflowErr*overflowErr));
  h->SetBinError(h->GetNbinsX()+1, 0);
  
}


//_______________________________________________________________________________
int printCard( string dir_str , int mtbin , string signal, string output_dir, int scanM1 = -1, int scanM2 = -1) {

  // read off yields from h_mt2bins hist in each topological region
  if (verbose) cout<<"Looking at region "<<dir_str<<", mt bin "<<mtbin<<endl;
  TString dir = TString(dir_str);
  TString fullhistname = dir + "/h_mtminbins";
  TString fullhistnameScan = dir + "/h_mtminbins";
  TString fullhistnameFakes = "Base/h_mtminbins";
  
  TString signame(signal);
  if (scanM1 >= 0 && scanM2 >= 0) {
    signame = Form("%s_%d_%d",signal.c_str(),scanM1,scanM2);
  }

  double n_BB(0.);
  double err_BB_mcstat(0.);
  double err_BB_syst(0.2);
  double n_LLB(0.);
  double err_LLB_mcstat(0.);
  double err_LLB_syst(0.2);
  double n_BBB(0.);
  double err_BBB_mcstat(0.);
  double err_BBB_syst(0.2);
  double n_ttB(0.);
  double err_ttB_mcstat(0.);
  double err_ttB_syst(0.2);
  double n_BJ(0.);
  double err_BJ_mcstat(0.);
  double err_BJ_syst(0.5);
  double n_bkg(0.);
  double n_data(0.);
  double n_sig(0.);
  double err_sig_mcstat(0.);

  TH1D* h_sig(0);

  // pick point out of signal scan
  if (scanM1 >= 0 && scanM2 >= 0) {
    TH3D* h_sigscan = (TH3D*) f_sig->Get(fullhistnameScan);
    if (!h_sigscan) return 0;
    int bin1 = h_sigscan->GetYaxis()->FindBin(scanM1);
    int bin2 = h_sigscan->GetZaxis()->FindBin(scanM2);
    h_sig = h_sigscan->ProjectionX(Form("h_mtmin_%d_%d_%s",scanM1,scanM2,dir_str.c_str()),bin1,bin1,bin2,bin2);
  }
  // single point sample
  else {
    h_sig = (TH1D*) f_sig->Get(fullhistname);
    IncludeOverflow(h_sig);

  }
  
  if (!h_sig) {
    if (verbose) cout<<"No signal histogram found in this region"<<endl;
    return 0;
  }
  else if (h_sig->Integral(0,-1) == 0) {
    if (verbose) cout<<"No signal events found in this region"<<endl;
    return 0;
  }
  else {
    n_sig = h_sig->GetBinContent(mtbin);
    err_sig_mcstat = h_sig->GetBinError(mtbin);
  }
  
  int mt_LOW = h_sig ? h_sig->GetBinLowEdge(mtbin) : 0;
  int mt_HI = h_sig ? mt_LOW + h_sig->GetBinWidth(mtbin) : 1500;
  // hardcode the current edge of our highest bin..
  if ((mt_HI == 1500) || (mt_HI == 500)) mt_HI = -1;

  std::string mt_str = "m" + to_string(mt_LOW) + "to" + to_string(mt_HI);
  
  ReplaceString(mt_str, "-1", "Inf");
  
  std::string channel = mt_str;
  //  std::string topologicalR = ht_str + "_" + jet_str + "_" + bjet_str;
  
  TString cardname = Form("%s/datacard_%s_%s.txt",output_dir.c_str(),channel.c_str(),signame.Data());
  
  // get yields for each sample
  double totalPrompts = 0;
  TH1D* h_BB = (TH1D*) f_BB->Get(fullhistname);
  IncludeOverflow(h_BB);
  if (h_BB != 0) {
    n_BB = h_BB->GetBinContent(mtbin);
    err_BB_mcstat = h_BB->GetBinError(mtbin)/h_BB->GetBinContent(mtbin);
    totalPrompts += h_BB->Integral();
  } 
  
  TH1D* h_LLB = (TH1D*) f_LLB->Get(fullhistname);
  IncludeOverflow(h_LLB);
  if (h_LLB != 0) {
    n_LLB = h_LLB->GetBinContent(mtbin);
    err_LLB_mcstat = h_LLB->GetBinError(mtbin)/h_LLB->GetBinContent(mtbin);
    totalPrompts += h_LLB->Integral();
  } 
  
  TH1D* h_BBB = (TH1D*) f_BBB->Get(fullhistname);
  IncludeOverflow(h_BBB);
  if (h_BBB != 0) {
    n_BBB = h_BBB->GetBinContent(mtbin);
    err_BBB_mcstat = h_BBB->GetBinError(mtbin)/h_BBB->GetBinContent(mtbin);
    totalPrompts += h_BBB->Integral();
  } 
  
  TH1D* h_ttB = (TH1D*) f_ttB->Get(fullhistname);
  IncludeOverflow(h_ttB);
  if (h_ttB != 0) {
    n_ttB = h_ttB->GetBinContent(mtbin);
    err_ttB_mcstat = h_ttB->GetBinError(mtbin)/h_ttB->GetBinContent(mtbin);
    totalPrompts += h_ttB->Integral();
  } 
  
  TH1D* h_BJ = (TH1D*) f_BJ->Get(fullhistnameFakes);
  TH1D* h_TT = (TH1D*) f_TT->Get(fullhistnameFakes);
  IncludeOverflow(h_BJ);
  IncludeOverflow(h_TT);
  if (h_TT != 0) {
    // Rescale the fakes to the ratio of j2Veto / Base
    h_TT->Scale( 0.00529037*1.25);
  }
  if (h_BJ != 0) {
    // Rescale the fakes to the ratio of j2Veto / Base
    h_BJ->Scale( 0.07*1.25);
    if (h_TT) h_BJ->Add(h_TT);
    n_BJ = h_BJ->GetBinContent(mtbin);
    err_BJ_mcstat = h_BJ->GetBinError(mtbin) > 0 ? h_BJ->GetBinError(mtbin)/h_BJ->GetBinContent(mtbin) : 0;
  } 
  n_BJ = 0;
  err_BJ_mcstat = 0;
  
  int n_syst = 0;
  double BB_mcstat = 1. + err_BB_mcstat;
  double BB_syst = 1. + err_BB_syst;
  TString name_BB_mcstat     = Form("BB_MCstat_%s"        , channel.c_str());
  TString name_BB_syst     = "BB_syst";
  n_syst += 2; // BB_mcstat
  
  double LLB_mcstat = 1. + err_LLB_mcstat;
  double LLB_syst = 1. + err_LLB_syst;
  TString name_LLB_mcstat     = Form("LLB_MCstat_%s"        , channel.c_str());
  TString name_LLB_syst     = "LLB_syst";
  n_syst += 2; // LLB_mcstat
  
  double BBB_mcstat = 1. + err_BBB_mcstat;
  double BBB_syst = 1. + err_BBB_syst;
  TString name_BBB_mcstat     = Form("BBB_MCstat_%s"        , channel.c_str());
  TString name_BBB_syst     = "BBB_syst";
  n_syst += 2; // BBB_mcstat
  
  double ttB_mcstat = 1. + err_ttB_mcstat;
  double ttB_syst = 1. + err_ttB_syst;
  TString name_ttB_mcstat     = Form("ttB_MCstat_%s"        , channel.c_str());
  TString name_ttB_syst     = "ttB_syst";
  n_syst += 2; // ttB_mcstat
    
  double BJ_mcstat = 1. + err_BJ_mcstat;
  double BJ_syst = 1. + err_BJ_syst;
  TString name_BJ_mcstat     = Form("Fakes_MCstat_%s"        , channel.c_str());
  TString name_BJ_syst     = "Fakes_syst";
  n_syst += 2; // BJ_mcstat
    
  n_bkg = n_BB + n_LLB + n_BBB + n_ttB + n_BJ;
  
  
  // ----- sig uncertainties
  double sig_syst         = 1.10; // dummy 10% from early MC studies
  TString name_sig_syst         = "sig_syst";
  n_syst += 1;

  
  
  // using only MC: take observation == total bkg
  n_data = n_bkg;
  
 
  ofstream ofile;
  ofile.open(cardname);

  ofile <<  "imax 1  number of channels"                                                    << endl;
  ofile <<  "jmax 5  number of backgrounds"                                                 << endl;
  ofile <<  "kmax *"                                                                        << endl;
  ofile <<  "------------"                                                                  << endl;
  ofile <<  Form("bin         %s",channel.c_str())                                          << endl;
  ofile <<  Form("observation %.3f",n_data)                                                 << endl;
  ofile <<  "------------"                                                                  << endl;
  ofile <<  Form("bin             %s   %s   %s   %s   %s   %s",channel.c_str(),channel.c_str(),channel.c_str(),channel.c_str(),channel.c_str(),channel.c_str()) << endl;
  ofile <<  "process          sig       BB        LLB       BBB       ttB       Fakes "                                      << endl; 
  ofile <<  "process           0         1           2         3         4         5"                                      << endl;
  ofile <<  Form("rate            %.3f    %.3f      %.3f      %.3f      %.3f      %.3f",n_sig,n_BB,n_LLB,n_BBB, n_ttB, n_BJ) << endl;
  ofile <<  "------------"                                                                  << endl;
 
  // ---- sig systs
  ofile <<  Form("%s          lnN   %.3f    -      -     -      -      - ",name_sig_syst.Data(),sig_syst)  << endl;
 
  // ---- MC Stat
  ofile <<  Form("%s        lnN    -    %.3f    -    -      -      - ",name_BB_mcstat.Data(),BB_mcstat)  << endl;
  ofile <<  Form("%s        lnN    -    -    %.3f    -      -      - ",name_LLB_mcstat.Data(),LLB_mcstat)  << endl;
  ofile <<  Form("%s        lnN    -    -    -    %.3f      -      - ",name_BBB_mcstat.Data(),BBB_mcstat)  << endl;
  ofile <<  Form("%s        lnN    -    -    -       -    %.3f     - ",name_ttB_mcstat.Data(),ttB_mcstat)  << endl;
  ofile <<  Form("%s        lnN    -    -    -       -      -    %.3f",name_BJ_mcstat.Data(),BJ_mcstat)  << endl;

  // ---- Syst
  ofile <<  Form("%s        lnN    -    %.3f    -    -      -      - ",name_BB_syst.Data(),BB_syst)  << endl;
  ofile <<  Form("%s        lnN    -    -    %.3f    -      -      - ",name_LLB_syst.Data(),LLB_syst)  << endl;
  ofile <<  Form("%s        lnN    -    -    -    %.3f      -      - ",name_BBB_syst.Data(),BBB_syst)  << endl;
  ofile <<  Form("%s        lnN    -    -    -       -    %.3f     - ",name_ttB_syst.Data(),ttB_syst)  << endl;
  ofile <<  Form("%s        lnN    -    -    -       -      -    %.3f",name_BJ_syst.Data(),BJ_syst)  << endl;
  
  ofile.close();

  if (verbose) std::cout << "Wrote card: " << cardname << std::endl;

  //prints a table of background and CR yields, with systematic and statistical errors
  TString tablename = Form("%s/table_%s.txt",output_dir.c_str(),channel.c_str());
//  if (printTable && !FileExists(tablename)) {
//    //calculate the stat error for each background based on poisson interval
//    
//    double lostlep_statUp, lostlep_statDown;
//    
//    double lostlep_syst;
//
//    if (n_mt2bins > 1 && mt2bin >= lostlep_lastbin_hybrid) {
//      lostlep_syst = n_lostlep*pow(pow(1-lostlep_lepeff,2)+pow(1-lostlep_mtcut,2)+pow(1-lostlep_taueff,2)+pow(1-lostlep_btageff,2)+pow(1-lostlep_jec,2)+pow(1-lostlep_renorm,2)+pow(1-lostlep_mcstat,2)+pow(1-lostlep_shape,2),0.5);
//    }
//    else lostlep_syst = n_lostlep*pow(pow(1-lostlep_lepeff,2)+pow(1-lostlep_mtcut,2)+pow(1-lostlep_taueff,2)+pow(1-lostlep_btageff,2)+pow(1-lostlep_jec,2)+pow(1-lostlep_renorm,2)+pow(1-lostlep_mcstat,2),0.5);
//
//    double qcd_syst;
//    if (njets_LOW == 1) {
//      qcd_syst = n_qcd*pow(pow(1-qcd_alphaerr,2),0.5);
//    }
//    else qcd_syst = n_qcd*pow(pow(1-qcd_fjrbsyst,2)+pow(1-qcd_fitstat,2)+pow(1-qcd_fitsyst,2),0.5);
//    
//    //write the table
//    ofstream tablefile;
//    tablefile.open(tablename);
//    tablefile <<  "### bg_name yield statUp statDown systUp systDown" << endl;
//    tablefile << Form("zinv  %.1f  %.1f  %.1f  %.1f  %.1f ",n_zinvDY, zinvDY_statUp, zinvDY_statDown, zinvDY_syst, zinvDY_syst) << endl;
//    tablefile << Form("llep  %.1f  %.1f  %.1f  %.1f  %.1f ",n_lostlep, lostlep_statUp, lostlep_statDown, lostlep_syst, lostlep_syst) << endl;
//    tablefile << Form("qcd  %.1f  %.1f  %.1f  %.1f  %.1f ",n_qcd, qcd_statUp, qcd_statDown, qcd_syst, qcd_syst) << endl;
//    tablefile << Form("data %.0f ", n_data) << endl;
//    tablefile << Form("zinv_nCR %.0f ", n_zinvDY_cr) << endl;
//    tablefile << Form("llep_nCR %.0f ", n_lostlep_cr) << endl;
//    tablefile << Form("qcd_nCR %.0f ", n_qcd_cr) << endl;
//    
//    tablefile.close();
//    
//    if (verbose) std::cout << "Wrote table: " << tablename << std::endl;
//  }//if printTable
  
  return 1;
}

//_______________________________________________________________________________
void cardMaker(string signal = "Decayed_C2N4_Baer_450_LSP_150_200PU", 
               string input_dir = "~/UCSD/Upgrade/Hists/advancedSignal14Nov17/", 
               string output_dir = "./cards/", bool isScan = false, bool doData = false){

  // Benchmark
  TBenchmark *bmark = new TBenchmark();
  bmark->Start("benchmark");

  // ----------------------------------------
  //  samples definition
  // ----------------------------------------

  // set input files
  
  f_BJ = new TFile(Form("%s/Bjall.root",input_dir.c_str()));
  f_TT = new TFile(Form("%s/ttall.root",input_dir.c_str()));
  f_BB = new TFile(Form("%s/BBall.root",input_dir.c_str()));
  f_LLB = new TFile(Form("%s/LLBall.root",input_dir.c_str()));
  f_BBB = new TFile(Form("%s/BBBall.root",input_dir.c_str()));
  f_ttB = new TFile(Form("%s/ttBall.root",input_dir.c_str())); // zgratio from data

  f_sig = new TFile(Form("%s/%s.root",input_dir.c_str(),signal.c_str()));

  if (doData) f_data = new TFile(Form("%s/data_Run2016.root",input_dir.c_str()));

  if( f_BB->IsZombie() || f_LLB->IsZombie() ||  f_BBB->IsZombie() || f_ttB->IsZombie() ) {
    std::cout << "Input file does not exist" << std::endl;
    return;
  }

  // ----------------------------------------
  //  cards definitions
  // ----------------------------------------

  set<pair<int, int> > signal_points;  
  //Loop through list of every directory in the signal file.
  //if directory begins with "sr", excluding "srbase", make cards for it.
  TIter it(f_sig->GetListOfKeys());
  TKey* k;
  string keep = "j2Veto";
  string skip = "srbase"; // Useless
  while ((k = (TKey *)it())) {
    if (strncmp (k->GetTitle(), skip.c_str(), skip.length()) == 0) continue;
    if (strncmp (k->GetTitle(), keep.c_str(), keep.length()) == 0) {//it is a signal region
      string mt2_hist_name = (k->GetTitle());
      mt2_hist_name += "/h_mtminbins";
      TH1D* h_n_mt2bins = (TH1D*) f_sig->Get(TString(mt2_hist_name));
      int n_mt2bins = h_n_mt2bins->GetXaxis()->GetNbins();
      for (int imt2 = 1; imt2 <= n_mt2bins; ++imt2) {//Make a separate card for each MT2 bin.
        if (isScan) {
          int y_binwidth = 25;
          int y_max = 1600;
          if (signal.find("T2cc") != std::string::npos) {
            y_binwidth = 5;
            y_max = 800;
          }
          for (int im1 = 0; im1 <= 2300; im1 += 25) {
            for (int im2 = 0; im2 <= y_max; im2 += y_binwidth) {
              //if (suppressUHmt2bin && TString(k->GetTitle()).Contains("UH") && imt2 == 1) continue;
              int result = printCard(k->GetTitle(), imt2, signal, output_dir, im1, im2);   //MT2 and scan bins with no entries are handled by printCard function.
              if (result > 0) signal_points.insert( make_pair(im1,im2) ); 
            } // scanM2 loop
          } // scanM1 loop
        } // if isScan
        else {
          printCard(k->GetTitle(), imt2, signal, output_dir);   //MT2 bins with no entries are handled by printCard function.
        }
      }
    }
  }
  
  if (isScan) {
    TString filename = Form("%s/points_%s.txt",output_dir.c_str(),signal.c_str());
    ofstream ofile;
    ofile.open(filename);
    cout << "--------------------------------------------" << endl
	 << "- saw nonzero signal entries for the following points: " << endl;
    for (set<pair<int,int> >::iterator it=signal_points.begin(); it!=signal_points.end(); ++it) {
      cout << signal << "_" << (*it).first << "_" << (*it).second << endl;
      ofile << signal << "_" << (*it).first << "_" << (*it).second << endl;
    }
    ofile.close();
  }
  
  bmark->Stop("benchmark");
  cout << endl;
  cout << "------------------------------" << endl;
  cout << "CPU  Time:	" << Form( "%.01f s", bmark->GetCpuTime("benchmark")  ) << endl;
  cout << "Real Time:	" << Form( "%.01f s", bmark->GetRealTime("benchmark") ) << endl;
  cout << endl;
  delete bmark;

}
