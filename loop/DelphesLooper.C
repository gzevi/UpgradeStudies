#include "DelphesLooper.h"

// C++
#include <iostream>
#include <vector>
#include <set>
#include <cmath>
#include <sstream>
#include <stdexcept>

// ROOT
#include "TDirectory.h"
#include "TTreeCache.h"
#include "Math/VectorUtil.h"
#include "TVector2.h"
#include "TBenchmark.h"
#include "TMath.h"
#include "TF1.h"

//#include "Plotting/PlotUtilities.h"
#include "PlotUtilities.h"

// Switches
bool verbose = 0;

// Settings
int lumi = 300; // in fb


void DelphesLooper::progress( int nEventsTotal, int nEventsChain ){
  int period = 1000;
  if(nEventsTotal%1000 == 0) {
    if (isatty(1)) {
      if( ( nEventsChain - nEventsTotal ) > period ){
        float frac = (float)nEventsTotal/(nEventsChain*0.01);
        printf("\015\033[32m ---> \033[1m\033[31m%4.1f%%"
               "\033[0m\033[32m <---\033[0m\015", frac);
        fflush(stdout);
      }
      else {
        printf("\015\033[32m ---> \033[1m\033[31m%4.1f%%"
               "\033[0m\033[32m <---\033[0m\015", 100.);
        cout << endl;
      }
    }
  }
}

float DelphesLooper::DeltaR(float eta1, float eta2, float phi1, float phi2){
  float dEta = eta1 - eta2;
  float dPhi = DeltaPhi(phi1, phi2);
  return TMath::Sqrt(dEta*dEta + dPhi*dPhi);
}

float DelphesLooper::DeltaR(LorentzVector v1, LorentzVector v2){
  return DeltaR(v1.eta(), v2.eta(), v1.phi(), v2.phi()); 
}

float DelphesLooper::DeltaPhi(float phi1, float phi2){
  float dPhi = phi1 - phi2;
  while (dPhi  >  TMath::Pi()) dPhi -= 2*TMath::Pi();
  while (dPhi <= -TMath::Pi()) dPhi += 2*TMath::Pi();
  return fabs(dPhi);
}

float DelphesLooper::MT(float pt1, float phi1, float pt2, float phi2){
  return sqrt( 2 * pt1 * pt2 * ( 1 - cos( phi1 - phi2 ) ) );
}



//Main function
void DelphesLooper::loop(TChain* chain, std::string sample, std::string output_dir, float xsec, int nevt){

  //  evtweight_ = lumi*xsec*1000./nevt; //xsec in fb
  float xsec_evtweight = lumi*xsec*1./nevt; //xsec in pb
  cout << "[DelphesLooper::loop] Event weight for this sample, "<<sample<<", is "<<evtweight_<<endl;

  //Set up loop over chain
  unsigned int nEventsDone = 0;
  unsigned int nEventsToDo = chain->GetEntries();
  TObjArray *listOfFiles = chain->GetListOfFiles();
  TIter fileIter(listOfFiles);
  TFile *currentFile = 0;
  std::map<std::string, TH1*> h_1d;

  gROOT->cd();
  TString output_name = Form("%s/%s.root",output_dir.c_str(),sample.c_str());
  cout << "[DelphesLooper::loop] creating output file: " << output_name << endl;

  outfile_ = new TFile(output_name.Data(),"RECREATE") ; 
  if (verbose) cout <<__LINE__ << endl;

  // File Loop
  while ( (currentFile = (TFile*)fileIter.Next()) ) { 
    if (verbose) cout <<__LINE__ << endl;

    // Get File Content
    if(nEventsDone >= nEventsToDo) continue;
    TFile *file = new TFile( currentFile->GetTitle() );
    TString filename(currentFile->GetTitle());
    if (verbose) cout << "file name is " << file->GetName() << endl;

    TTree *tree = (TTree*)file->Get("Delphes");
    Delphes d(tree); // Create an instance of the delphes class and connect it to this tree
    if (verbose) cout <<__LINE__ << endl;

    // Loop over Events in current file
    unsigned int nEventsTree = tree->GetEntriesFast();
    if (verbose) cout <<__LINE__ << endl;

    for(unsigned int evt = 0; evt < nEventsTree; evt++){  // Real loop over all events
    //for(unsigned int evt = 0; evt < 10; evt++){  // For Testing
      if (verbose) cout <<__LINE__ << endl;

      // Get Event Content
      if(nEventsDone >= nEventsToDo) continue;  
      if (verbose) cout <<__LINE__ << endl; 
      d.GetEntry(evt);
      nEventsDone++;
      if (verbose) cout <<__LINE__ << endl;

      //Debug mode
     
      // Progress
      progress(nEventsDone, nEventsToDo);

      evtweight_ = xsec_evtweight;
      if (d.Event_Weight[0] > 0.01 && d.Event_Weight[0] < 100) {
	evtweight_ *= d.Event_Weight[0];
      }
      else cout<<"Strange event weight: "<< d.Event_Weight[0] << endl;

      nlep_=0, nlepIso_=0;
      leptons_.clear();
      leptonsVeto_.clear();
      for ( int i = 0; i < d.MuonTight_ ; ++i) {
	//cout<<d.MuonTight_PT[i]<<endl;
	float pt = d.MuonTight_PT[i];
	float eta = d.MuonTight_Eta[i];
	plot1D("h_mupt", pt,  evtweight_, h_1d, "pT [GeV]", 40, 0, 400);
	if (pt < 5) continue;
	//if (eta>0.9891693 && eta<0.9891696) continue; // Hot Spot
	nlep_++;
	part lep;
	lep.vec.SetPtEtaPhiM(pt,d.MuonTight_Eta[i],d.MuonTight_Phi[i],0);
	lep.id = -13 * d.MuonTight_Charge[i];
	lep.mt = MT(pt, d.MuonTight_Phi[i], d.PuppiMissingET_MET[0], d.PuppiMissingET_Phi[0]);
	if (d.MuonTight_IsolationVarRhoCorr[i]/pt > 0.1 || pt < 20) {
	  leptonsVeto_.push_back(lep);
	}
	else {
	  nlepIso_++;
	  leptons_.push_back(lep);
	}
      }
      if (verbose) cout <<__LINE__ << endl;

      //      cout<<"About to loop over "<<d.Electron_<<" electrons. Alternative counter is "<<d.Electron_size<<endl; 

      for ( int i = 0; i < d.Electron_ ; ++i) {
	//cout<<d.Electron_PT[i]<<endl;
	float pt = d.Electron_PT[i];
	float eta = d.Electron_Eta[i];
	//plot1D("h_elpt", pt,  evtweight_, h_1d, "pT [GeV]", 40, 0, 400);
	if (pt < 5) continue;
	//if (eta>1.9549165 && eta<1.9549167) continue; // Hot Spot
	//if (eta>-2.566041 && eta<-2.566039) continue; // Hot Spot
	//if (eta>-0.391368 && eta<-0.391366) continue; // Hot Spot
	//if (eta>0.1128721 && eta<0.1128723) continue; // Hot Spot
	nlep_++;
	part lep;
	lep.vec.SetPtEtaPhiM(pt,d.Electron_Eta[i],d.Electron_Phi[i],0);
	lep.id = -11 * d.Electron_Charge[i];
	lep.mt = MT(pt, d.Electron_Phi[i], d.PuppiMissingET_MET[0], d.PuppiMissingET_Phi[0]);
	if (d.Electron_IsolationVarRhoCorr[i]/pt > 0.1 || pt < 20) {
	  leptonsVeto_.push_back(lep);
	}
	else {
	  nlepIso_++;
	  leptons_.push_back(lep);
	}
      }

      if (verbose) cout <<__LINE__ << endl;

      HT1p5_ = 0, HT2p5_ = 0, HT_ = 0, njet30barrel_ = 0, njet30central_ = 0, njet30forward_ = 0, njet30_ = 0, nbjet30_ = 0;
      for ( int i = 0; i < d.JetPUPPI_ ; ++i) {
	// Overlap Removal
	for ( int j = 0; j < d.Electron_ ; ++j) {
	  float DR = DeltaR(d.JetPUPPI_Eta[i], d.Electron_Eta[j], d.JetPUPPI_Phi[i], d.Electron_Phi[j]);
	  if (DR<0.4) continue;
	}
	for ( int j = 0; j < d.MuonTight_ ; ++j) {
	  float DR = DeltaR(d.JetPUPPI_Eta[i], d.MuonTight_Eta[j], d.JetPUPPI_Phi[i], d.MuonTight_Phi[j]);
	  if (DR<0.4) continue;
	}
	//cout<<d.JetPUPPI_PT[i]<<endl;
	float pt = d.JetPUPPI_PT[i];
	plot1D("h_jetpt", pt,  evtweight_, h_1d, "pT [GeV]", 200, 0, 500);
	if (pt>30) {
	  plot1D("h_jeteta", d.JetPUPPI_Eta[i],  evtweight_, h_1d, "pT [GeV]", 100, -5, 5);

	  if (fabs(d.JetPUPPI_Eta[i]) < 2.5 ) {
	    HT2p5_ += pt;
	    njet30central_++;
	    if (fabs(d.JetPUPPI_Eta[i]) < 1.5 ) {
	      HT1p5_ += pt;
	      njet30barrel_++;
	    }
	  }
	  else njet30forward_++;
	  HT_ += pt;
	  njet30_++;
	  if (d.JetPUPPI_BTag[i] & (1 << 1)) nbjet30_++;
	}
	    
      }
            if (verbose) cout <<__LINE__ << endl;

      MET_ = d.PuppiMissingET_MET[0];

      plot1D("h_nlepIso", nlepIso_,  evtweight_, h_1d, "NlepIso",10, -0.5, 9.5);


      // Require dileptons
      if (nlepIso_<2) continue;
      // Require same sign for 2 leading isolated leptons
      if (leptons_[0].id * leptons_[1].id < 0) continue;
      // Check for Z peaks
      int hasOSZ = false;
      for ( unsigned int i = 0; i < leptons_.size() ; ++i) {
	for ( unsigned int j = i+1; j < leptons_.size() ; ++j) {
	  TLorentzVector dilep = leptons_[i].vec + leptons_[j].vec;
	  float m = dilep.M();
	  int charge = leptons_[i].id * leptons_[j].id;
	  plot1D("h_dilepmass", m,  evtweight_, h_1d, "mLL [GeV]", 60, 0, 150);
	  if (charge > 0)
	    plot1D("h_SSdilepmass", m,  evtweight_, h_1d, "mLL [GeV]", 60, 0, 150);
	  else {
	    if (m < 15 || (m>80 && m<100) ) hasOSZ = true;
	    plot1D("h_OSdilepmass", m,  evtweight_, h_1d, "mLL [GeV]", 60, 0, 150);
	  }

	}
      }
      for ( unsigned int i = 0; i < leptons_.size() ; ++i) {
	for ( unsigned int j = 0; j < leptonsVeto_.size() ; ++j) {
	  TLorentzVector dilep = leptons_[i].vec + leptonsVeto_[j].vec;
	  float m = dilep.M();
	  int charge = leptons_[i].id * leptonsVeto_[j].id;
	  plot1D("h_lepVetoLepmass", m,  evtweight_, h_1d, "mLL [GeV]", 60, 0, 150);
	  if (charge > 0)
	    plot1D("h_SSlepVetoLepmass", m,  evtweight_, h_1d, "mLL [GeV]", 60, 0, 150);
	  else {
	    if (m < 15 || (m>80 && m<100) ) hasOSZ = true;
	    plot1D("h_OSlepVetoLepmass", m,  evtweight_, h_1d, "mLL [GeV]", 60, 0, 150);
	  }
	}
      }
      if (verbose) cout <<__LINE__ << endl;

       // Classify MultiBoson backgrounds
      int nWp = 0, nWm = 0, nW = 0, nH = 0, nZ = 0, nTop = 0;
      for ( int i = 0; i < d.Particle_ ; ++i) {
	//cout<<d.Particle_PID[i]<<" "<<d.Particle_Status[i]<<endl;
	if (d.Particle_PID[i]==23  && d.Particle_Status[i]==22) nZ++;
	if (d.Particle_PID[i]==25  && d.Particle_Status[i]==22) nH++;
	if (d.Particle_PID[i]==24  && d.Particle_Status[i]==22) nWp++;
	if (d.Particle_PID[i]==-24 && d.Particle_Status[i]==22) nWm++;
	if (fabs(d.Particle_PID[i])==6 && d.Particle_Status[i]==22) nTop++;
      }
      nW = nWp + nWm;
      


      // WWW, WWZ/WZZ/ZZZ = VVZ, VH, WW, WZ, ZZ, ttW, ttZ

      BBtype_ = 0;
      if (nW==3)  BBtype_ = 1; //WWW
      else if (nW+nZ==3) BBtype_ = 2; //VVZ
      else if (nH>0)   BBtype_ = 3; //VH
      else if (nW==2)  BBtype_ = 4; //WW
      else if (nW==1 && nZ==1)  BBtype_ = 5; //WZ
      else if (nZ==2)  BBtype_ = 6; //ZZ
      if (nTop==2 ) {
	if (nW==3) BBtype_ = 7;
	else       BBtype_ = 8;
      }
      
      if (BBtype_ == 0 && nW+nZ+nH>1) 
	cout<<"nW="<<nW<<", nZ="<<nZ<<", nTop="<<nTop<<", nH="<<nH<<endl;


      if (verbose) cout << evtweight_ <<" "<< HT_ <<" "<< nlep_ <<endl;

      // Make plots before lepton veto
      if (BBtype_==5)        {
	// GenLevel study of WZ events
	for ( int i = 0; i < d.Particle_ ; ++i) {
	  if (d.Particle_Status[i]!=1) continue;
	  if (fabs(d.Particle_PID[i])!=11 && fabs(d.Particle_PID[i])!=13 && fabs(d.Particle_PID[i])!=15 ) continue;
	  float pt = d.Particle_PT[i];
	  //cout<<d.Particle_PID[i]<<" "<<d.Particle_Status[i]<<" "<<d.Particle_PT[i]<<" "<<d.Particle_Eta[i]<<endl;
	  float isel = fabs(d.Particle_PID[i])==11;
	  float ismu = fabs(d.Particle_PID[i])==13;
	  plot1D("hBeforeLepVeto_genLepID", d.Particle_PID[i],  evtweight_, h_1d, "ID", 40, -20, 20);
	  plot1D("hBeforeLepVeto_genLepPT", d.Particle_PT[i],  evtweight_, h_1d, "pT [GeV]", 100, 0, 100);
	  plot1D("hBeforeLepVeto_genLepEta", d.Particle_Eta[i],  evtweight_, h_1d, "Eta",  40, -5, 5);
	  if (isel) plot1D("hBeforeLepVeto_genLepEtaEl", d.Particle_Eta[i],  evtweight_, h_1d, "Eta",  40, -5, 5);
	  if (ismu) plot1D("hBeforeLepVeto_genLepEtaMu", d.Particle_Eta[i],  evtweight_, h_1d, "Eta",  40, -5, 5);
	  if (ismu && pt>5) plot1D("hBeforeLepVeto_genLepEtaMuPt5", d.Particle_Eta[i],  evtweight_, h_1d, "Eta",  40, -5, 5);
	  plot1D("hBeforeLepVeto_genLepPhi", d.Particle_Phi[i],  evtweight_, h_1d, "Phi",  40, -3.2, 3.2);

	  // Find the "lost lepton"
	  bool found = false;
	  //cout<<"GenLep "<<d.Particle_PID[i]<<" "<<d.Particle_Status[i]<<" "<<d.Particle_PT[i]<<" "<<d.Particle_Eta[i]<<endl;
	  for ( unsigned int j = 0; j < leptons_.size() ; ++j) {
	    //cout<<"Lep "<<leptons_[j].id<<" "<<leptons_[j].vec.Pt()<<" "<<leptons_[j].vec.Eta()<<endl;
	    if (d.Particle_PID[i] == leptons_[j].id && fabs(d.Particle_PT[i]-leptons_[j].vec.Pt()) < 1 && fabs(d.Particle_Eta[i]-leptons_[j].vec.Eta())<0.1 ) found = true; // Matched!
	  }
	  for ( unsigned int j = 0; j < leptonsVeto_.size() ; ++j) {
	    //cout<<"Lep "<<leptons_[j].id<<" "<<leptons_[j].vec.Pt()<<" "<<leptons_[j].vec.Eta()<<endl;
	    if (d.Particle_PID[i] == leptonsVeto_[j].id && fabs(d.Particle_PT[i]-leptonsVeto_[j].vec.Pt()) < 1 && fabs(d.Particle_Eta[i]-leptonsVeto_[j].vec.Eta())<0.1 ) found = true; // Matched!
	  }
	  if (!found) {
	    plot1D("hBeforeLepVeto_lostLepID", d.Particle_PID[i],  evtweight_, h_1d, "ID", 40, -20, 20);
	    plot1D("hBeforeLepVeto_lostLepPT", d.Particle_PT[i],  evtweight_, h_1d, "pT [GeV]", 100, 0, 100);
	    if (ismu) plot1D("hBeforeLepVeto_lostLepEtaMu", d.Particle_Eta[i],  evtweight_, h_1d, "Eta",  40, -5, 5);
	    if (ismu && pt>5) plot1D("hBeforeLepVeto_lostLepEtaMuPt5", d.Particle_Eta[i],  evtweight_, h_1d, "Eta",  40, -5, 5);
	    plot1D("hBeforeLepVeto_lostLepPhi", d.Particle_Phi[i],  evtweight_, h_1d, "Phi",  40, -3.2, 3.2);
	  }
	  else if (found) {
	    if (ismu && pt>5) plot1D("hBeforeLepVeto_foundLepEtaMuPt5", d.Particle_Eta[i],  evtweight_, h_1d, "Eta",  40, -5, 5);
	  }

	}
      }

      fillHistos(h_1d_base, "Base", ""); // SS dileptons
      if (hasOSZ) continue;
      fillHistos(h_1d_Zveto, "Zveto", ""); // Veto OS Z
      if (nlep_!=2) continue;
      fillHistos(h_1d_lepVeto, "lepVeto", ""); // Veto 3rd lepton in general
      if (nbjet30_>0) continue;
      fillHistos(h_1d_bVeto, "bVeto", ""); // Veto b-jets
      if (njet30_>3) continue;
      fillHistos(h_1d_j4Veto, "j4Veto", ""); // Veto 4th jet

      if (njet30_>2)  fillHistos(h_1d_2j, "2Jets", ""); // Now fill histos with some cuts

     
      // Full plots for each diboson category
      if (BBtype_==5)        {
	fillHistos(h_1d_WZ, "WZ", ""); 
	// GenLevel study of WZ events
	//cout<<"WZ event survived lepton veto! Why?"<<endl;
	for ( int i = 0; i < d.Particle_ ; ++i) {
	  if (d.Particle_Status[i]!=1) continue;
	  if (fabs(d.Particle_PID[i])!=11 && fabs(d.Particle_PID[i])!=13 && fabs(d.Particle_PID[i])!=15 ) continue;
	  float pt = d.Particle_PT[i];
	  //cout<<d.Particle_PID[i]<<" "<<d.Particle_Status[i]<<" "<<d.Particle_PT[i]<<" "<<d.Particle_Eta[i]<<endl;
	  float isel = fabs(d.Particle_PID[i])==11;
	  float ismu = fabs(d.Particle_PID[i])==13;
	  plot1D("h_genLepID", d.Particle_PID[i],  evtweight_, h_1d, "ID", 40, -20, 20);
	  plot1D("h_genLepPT", d.Particle_PT[i],  evtweight_, h_1d, "pT [GeV]", 100, 0, 100);
	  plot1D("h_genLepEta", d.Particle_Eta[i],  evtweight_, h_1d, "Eta",  40, -5, 5);
	  if (isel) plot1D("h_genLepEtaEl", d.Particle_Eta[i],  evtweight_, h_1d, "Eta",  40, -5, 5);
	  if (ismu) plot1D("h_genLepEtaMu", d.Particle_Eta[i],  evtweight_, h_1d, "Eta",  40, -5, 5);
	  if (ismu && pt>5) plot1D("h_genLepEtaMuPt5", d.Particle_Eta[i],  evtweight_, h_1d, "Eta",  40, -5, 5);
	  plot1D("h_genLepPhi", d.Particle_Phi[i],  evtweight_, h_1d, "Phi",  40, -3.2, 3.2);

	  // Find the "lost lepton"
	  bool found = false;
	  //cout<<"GenLep "<<d.Particle_PID[i]<<" "<<d.Particle_Status[i]<<" "<<d.Particle_PT[i]<<" "<<d.Particle_Eta[i]<<endl;
	  for ( unsigned int j = 0; j < leptons_.size() ; ++j) {
	    //cout<<"Lep "<<leptons_[j].id<<" "<<leptons_[j].vec.Pt()<<" "<<leptons_[j].vec.Eta()<<endl;
	    if (d.Particle_PID[i] == leptons_[j].id && fabs(d.Particle_PT[i]-leptons_[j].vec.Pt()) < 1 && fabs(d.Particle_Eta[i]-leptons_[j].vec.Eta())<0.1 ) found = true; // Matched!
	  }
	  for ( unsigned int j = 0; j < leptonsVeto_.size() ; ++j) {
	    //cout<<"Lep "<<leptons_[j].id<<" "<<leptons_[j].vec.Pt()<<" "<<leptons_[j].vec.Eta()<<endl;
	    if (d.Particle_PID[i] == leptonsVeto_[j].id && fabs(d.Particle_PT[i]-leptonsVeto_[j].vec.Pt()) < 1 && fabs(d.Particle_Eta[i]-leptonsVeto_[j].vec.Eta())<0.1 ) found = true; // Matched!
	  }
	  if (!found) {
	    //cout<<"Unmatched GenLep "<<d.Particle_PID[i]<<" "<<d.Particle_Status[i]<<" "<<d.Particle_PT[i]<<" "<<d.Particle_Eta[i]<<endl;
	    plot1D("h_lostLepID", d.Particle_PID[i],  evtweight_, h_1d, "ID", 40, -20, 20);
	    plot1D("h_lostLepPT", d.Particle_PT[i],  evtweight_, h_1d, "oT [GeV]", 100, 0, 100);
	    if (ismu) plot1D("h_lostLepEtaMu", d.Particle_Eta[i],  evtweight_, h_1d, "Eta",  40, -5, 5);
	    if (ismu && pt>5) plot1D("h_lostLepEtaMuPt5", d.Particle_Eta[i],  evtweight_, h_1d, "Eta",  40, -5, 5);
	    plot1D("h_lostLepPhi", d.Particle_Phi[i],  evtweight_, h_1d, "Phi",  40, -3.2, 3.2);
	  }
	  else if (found) {
	    if (ismu && pt>5) plot1D("h_foundLepEtaMuPt5", d.Particle_Eta[i],  evtweight_, h_1d, "Eta",  40, -5, 5);
	  }

	}
      }
      else if (BBtype_==1)   fillHistos(h_1d_WWW, "WWW", "");
      else if (BBtype_==2)   fillHistos(h_1d_VVZ, "VVZ", "");
      else if (BBtype_==3)   fillHistos(h_1d_VH, "VH", ""); // from BBB sample
      else if (BBtype_==4)   fillHistos(h_1d_WW, "WW", "");
//      else if (BBtype_==3)   fillHistos(h_1d_SSWW, "SSWW", "");
//      else if (BBtype_==4)   fillHistos(h_1d_OSWW, "OSWW", "");
      else if (BBtype_==6)   fillHistos(h_1d_ZZ, "ZZ", ""); 
      else if (BBtype_==7)   fillHistos(h_1d_ttW, "ttW", "");
      else if (BBtype_==8)   fillHistos(h_1d_ttZ, "ttZ", "");
      else if (BBtype_==0)   fillHistos(h_1d_other, "other", "");
      
      //      if (mtmin < 120) continue;


      
    }// end of event loop
    
    file->Close();
    delete file;
    //delete tree;
    cout<<"\nFile done"<<endl;

  }//end of  file loop
  
  cout<<"\nWriting file"<<endl;
  savePlotsDir(h_1d, outfile_, "");
  savePlotsDir(h_1d_base, outfile_, "Base");
  savePlotsDir(h_1d_2j, outfile_, "2Jets");
  savePlotsDir(h_1d_WZ, outfile_, "WZ");
  savePlotsDir(h_1d_ZZ, outfile_, "ZZ");
  savePlotsDir(h_1d_WW, outfile_, "WW");
  savePlotsDir(h_1d_VH, outfile_, "VH");
  savePlotsDir(h_1d_WWW, outfile_, "WWW");
  savePlotsDir(h_1d_VVZ, outfile_, "VVZ");
  savePlotsDir(h_1d_ttW, outfile_, "ttW");
  savePlotsDir(h_1d_ttZ, outfile_, "ttZ");
  savePlotsDir(h_1d_other, outfile_, "other");
  savePlotsDir(h_1d_lepVeto, outfile_, "lepVeto");
  savePlotsDir(h_1d_bVeto, outfile_, "bVeto");
  savePlotsDir(h_1d_j4Veto, outfile_, "j4Veto");
  savePlotsDir(h_1d_Zveto, outfile_, "Zveto");
  outfile_->Write();
  outfile_->Close();
  delete outfile_;
  
  return;  
  
}

void DelphesLooper::fillHistos(std::map<std::string, TH1*>& h_1d, const std::string& dirname, const std::string& s){
  TDirectory * dir = (TDirectory*)outfile_->Get(dirname.c_str());
  if (dir == 0) {
    dir = outfile_->mkdir(dirname.c_str());
  } 
  dir->cd();

  plot1D("h_HT1p5"+s, HT1p5_,  evtweight_, h_1d, "HT barrel [GeV]", 200, 0, 2000);
  plot1D("h_HT2p5"+s, HT2p5_,  evtweight_, h_1d, "HT central [GeV]", 200, 0, 2000);
  plot1D("h_HTfull"+s, HT_,  evtweight_, h_1d, "HT [GeV]", 200, 0, 2000);
  plot1D("h_njet30barrel"+s, njet30barrel_ ,  evtweight_, h_1d, "N_j barrel", 10, -0.5, 9.5);
  plot1D("h_njet30central"+s, njet30central_ ,  evtweight_, h_1d, "N_j central", 10, -0.5, 9.5);
  plot1D("h_njet30forward"+s, njet30forward_ ,  evtweight_, h_1d, "N_j forward", 10, -0.5, 9.5);
  plot1D("h_njet30"+s, njet30_,  evtweight_, h_1d, "N_j", 10, -0.5, 9.5);
  plot1D("h_nbjet30"+s, nbjet30_,  evtweight_, h_1d, "N_j", 10, -0.5, 9.5);
  plot1D("h_BBtype"+s, BBtype_,  evtweight_, h_1d, "BB type [Other, WZ, ZZ, SSWW, OSWW]", 10, -0.5, 9.5);
  plot1D("h_MET"+s, MET_,  evtweight_, h_1d, "pT [GeV]", 200, 0, 2000);
  plot1D("h_nlep"+s, nlep_,  evtweight_, h_1d, "Nlep",10, -0.5, 9.5);
  plot1D("h_nlepIso"+s, nlepIso_,  evtweight_, h_1d, "Nlep(iso)", 10, -0.5, 9.5);
  float mtmin = 999.;
  int nmu = 0, nele = 0;
  for ( unsigned int i = 0; i < leptons_.size() ; ++i) {
    const std::string istring = std::to_string(i);
    plot1D("h_leppt"+istring+s, leptons_[i].vec.Pt(),  evtweight_, h_1d, "Lep pT", 100, 0, 100);
    plot1D("h_lepeta"+istring+s, leptons_[i].vec.Eta(),  evtweight_, h_1d, "Lep eta", 40, -5, 5);
    if (fabs(leptons_[i].id)==13) plot1D("h_lepetamu"+s, leptons_[i].vec.Eta(),  evtweight_, h_1d, "Lep eta", 40, -5, 5);
    plot1D("h_lepmt"+istring+s, leptons_[i].mt,  evtweight_, h_1d, "Lep MT", 100, 0, 200);
    if (leptons_[i].mt < mtmin) mtmin = leptons_[i].mt;
    if (fabs(leptons_[i].id)==13) nmu++;
    if (fabs(leptons_[i].id)==11) nele++;
  }
  int type = nmu>1 ? 1 : nele>1 ? 3 : (nmu==1 && nele==1) ? 2 : -1; // mm=1, em=2, ee=3
  const std::string stype = type==1 ? "mm" : (type==2 ? "em" : (type==3 ? "ee" : "other"));
  plot1D("h_type"+s, type,  evtweight_, h_1d, "mm,em,ee",6, -2, 4);


  for ( unsigned int i = 0; i < leptonsVeto_.size() ; ++i) {
    if (fabs(leptons_[i].id)==13) plot1D("h_lepetamu"+s, leptonsVeto_[i].vec.Eta(),  evtweight_, h_1d, "Lep eta", 40, -5, 5);
  }


  plot1D("h_mtmin"+s, mtmin,  evtweight_, h_1d, "MTmin", 150, 0, 300);
  plot1D("h_mtmin"+stype+s, mtmin,  evtweight_, h_1d, "MTmin", 150, 0, 300);


  return;
}


