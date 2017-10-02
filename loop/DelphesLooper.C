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
#include "MT2.h"

// Switches
bool verbose = 0;
bool synchronizemode = 0; // Example: make, then do: ./runLooper /home/gzevi//UpgradeSkims/advanced3Jul17weights/ BB-4p-0-300 output/weights_2Jul17/ 249977 18693008
// Settings
int lumi = 3000; // in fb
float MuonEnd = 2.8; // 1.6, 2.4 or 2.8

//Efficiency bins
const float xbins[6] = {20., 25., 30., 40., 50., 200.};
const float ybinsEl[6] = {0., 0.8, 1.442, 1.556, 2.0, 2.5};
const float ybinsMu[6] = {0., 0.9, 1.2, 2.1, 2.4, 2.8};

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
  cout << "[DelphesLooper::loop] Calling loop with arguments: "<<sample<<", xsec "<<xsec<<", nevt "<<nevt<<endl;
  cout << "[DelphesLooper::loop] Event weight for this sample, "<<sample<<", is "<<xsec_evtweight<<endl;

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

  // Synchronization counters
  int totN = 0, muN = 0, jetN = 0, bjetN = 0, metN=0, htN=0;
  float totW = 0, muW = 0, jetW = 0, bjetW = 0, metW=0, htW=0;

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

      //////////////////////////////////////////////////////////////////////////////////
      //////////// SYNCHRONIZATION MODE, JUST OUTPUT SOME NUMBERS AND RETURN ///////////
      //////////////////////////////////////////////////////////////////////////////////

      if (synchronizemode) {
	totN++; totW+=evtweight_;
	int nmu = 0;
	for ( int i = 0; i < d.MuonTight_ ; ++i) {
	  float pt = d.MuonTight_PT[i];
	  float eta = d.MuonTight_Eta[i];
	  if (pt<20 || fabs(eta)>2.5 ) continue;
	  if (d.MuonTight_IsolationVarRhoCorr[i]/d.MuonTight_PT[i]>0.5 || d.MuonTight_IsolationVarRhoCorr[i] > 5) continue;
	  nmu++;
	}
	if (nmu!=2) continue;
	muN++; muW+=evtweight_;

	int nj = 0, nb = 0;
	for ( int i = 0; i < d.JetPUPPI_ ; ++i) {
	  // Overlap Removal
	  //for ( int j = 0; j < d.MuonTight_ ; ++j) {
	  //  float DR = DeltaR(d.JetPUPPI_Eta[i], d.MuonTight_Eta[j], d.JetPUPPI_Phi[i], d.MuonTight_Phi[j]);
	  //  if (DR<0.4) continue;
	  //}
	  float pt = d.JetPUPPI_PT[i];
	  float eta = d.JetPUPPI_Eta[i];
	  //	  if (pt<30 || fabs(eta)>2.5) continue;
	  if (pt<30) continue;
	  nj++;
	  if (d.JetPUPPI_BTag[i] & (1 << 1)) nb++;
	}
	if (nj<1) continue;
	jetN++; jetW+=evtweight_;
	if (nb>0) continue;
	bjetN++; bjetW+=evtweight_;
	
	if (d.PuppiMissingET_MET[0] <100) continue;
	metN++; metW+=evtweight_;

	if (d.ScalarHT_HT[0] <100) continue;
	htN++; htW+=evtweight_;


	continue; // move on to next event
      }
      //////////////////////////////////////////////////////////////////////////////////
      //////////// END OF SYNCHRONIZATION MODE /////////////////////////////////////////
      //////////////////////////////////////////////////////////////////////////////////


      nlep_=0, nlepIso_=0;
      leptons_.clear();
      leptonsVeto_.clear();
      for ( int i = 0; i < d.MuonLoose_ ; ++i) {
	//cout<<d.MuonLoose_PT[i]<<endl;
	float pt = d.MuonLoose_PT[i];
	float eta = d.MuonLoose_Eta[i];
	plot1D("h_mupt", pt,  evtweight_, h_1d, "pT [GeV]", 40, 0, 400);
	if (pt < 5) continue;
	if (fabs(eta) > MuonEnd) continue; // eta acceptance of veto selection
	plot2D("h_MuIDEffDen", pt, fabs(eta), evtweight_, h_2d, "MuIDEffDen", 5, xbins, 5, ybinsMu);
	//if (eta>0.9891693 && eta<0.9891696) continue; // Hot Spot
	if (d.MuonLoose_IsolationVarRhoCorr[i] >  0.5) continue;
	nlep_++;
	part lep;
	lep.vec.SetPtEtaPhiM(pt,d.MuonLoose_Eta[i],d.MuonLoose_Phi[i],0);
	lep.id = -13 * d.MuonLoose_Charge[i];
	lep.mt = MT(pt, d.MuonLoose_Phi[i], d.PuppiMissingET_MET[0], d.PuppiMissingET_Phi[0]);
	if (d.MuonLoose_IsolationVarRhoCorr[i] > 0.1 || pt < 20  || fabs(eta) > 1.6) { // inverted signal selection
	  leptonsVeto_.push_back(lep);
	}
	else {  // Signal selection
	  nlepIso_++;
	  leptons_.push_back(lep);
	}
	// To plot efficiency, don't cut on eta
	if (d.MuonLoose_IsolationVarRhoCorr[i] < 0.1 && pt > 20  ) { 
	  plot2D("h_MuIDEffNum", pt, fabs(eta), evtweight_, h_2d, "MuIDEffNum", 5, xbins, 5, ybinsMu);
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
	plot2D("h_ElIDEffDen", pt, fabs(eta), evtweight_, h_2d, "ElIDEffDen", 5, xbins, 5, ybinsEl);
	if (d.Electron_IsolationVarRhoCorr[i] >  0.5) continue;
	//if (eta>1.9549165 && eta<1.9549167) continue; // Hot Spot
	//if (eta>-2.566041 && eta<-2.566039) continue; // Hot Spot
	//if (eta>-0.391368 && eta<-0.391366) continue; // Hot Spot
	//if (eta>0.1128721 && eta<0.1128723) continue; // Hot Spot
	nlep_++;
	part lep;
	lep.vec.SetPtEtaPhiM(pt,d.Electron_Eta[i],d.Electron_Phi[i],0);
	lep.id = -11 * d.Electron_Charge[i];
	lep.mt = MT(pt, d.Electron_Phi[i], d.PuppiMissingET_MET[0], d.PuppiMissingET_Phi[0]);
	if (d.Electron_IsolationVarRhoCorr[i] > 0.1 || pt < 20 || fabs(eta) > 1.6) {
	  leptonsVeto_.push_back(lep);
	}
	else {
	  nlepIso_++;
	  leptons_.push_back(lep);
	  plot2D("h_ElIDEffNum", pt, fabs(eta), evtweight_, h_2d, "ElIDEffNum", 5, xbins, 5, ybinsEl);
	}
      }

      if (verbose) cout <<__LINE__ << endl;

      HT1p5_ = 0, HT2p5_ = 0, HT_ = 0, njet30barrel_ = 0, njet30central_ = 0, njet30forward_ = 0, njet30_ = 0, nbjet30_ = 0;
      jet1pt_ = 0, jet2pt_ = 0;
      vector<TLorentzVector> bjets;
      for ( int i = 0; i < d.JetPUPPI_ ; ++i) {
	float pt = d.JetPUPPI_PT[i];
	if (pt>25) {
	  // Overlap Removal
	  bool overlap = false;
	  for ( int j = 0; j < d.Electron_ ; ++j) {
	    float DR = DeltaR(d.JetPUPPI_Eta[i], d.Electron_Eta[j], d.JetPUPPI_Phi[i], d.Electron_Phi[j]);
	    if (DR<0.4) overlap = true;
	  }
	  for ( int j = 0; j < d.MuonLoose_ ; ++j) {
	    float DR = DeltaR(d.JetPUPPI_Eta[i], d.MuonLoose_Eta[j], d.JetPUPPI_Phi[i], d.MuonLoose_Phi[j]);
	    if (DR<0.4) overlap = true;
	  }
	  if (overlap) continue;
	  //cout<<d.JetPUPPI_PT[i]<<endl;
	  plot1D("h_jetpt", pt,  evtweight_, h_1d, "pT [GeV]", 200, 0, 500);
	  plot1D("h_jeteta", d.JetPUPPI_Eta[i],  evtweight_, h_1d, "Eta", 26, -5.2, 5.2);
	  
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
	  if (jet1pt_ == 0) jet1pt_ = pt;
	  else if (jet2pt_ == 0) jet2pt_ = pt;
	  //if (d.JetPUPPI_BTag[i] & (1 << 1)) { // OLD DELPHES SAMPLES
	  if (d.JetPUPPI_BTag[i] ) { // NEW DELPHES SAMPLES
	    nbjet30_++;
	    plot1D("h_bJetEta", d.JetPUPPI_Eta[i],  evtweight_, h_1d, "Eta",  26, -5.2, 5.2);
	    TLorentzVector bjet;
	    bjet.SetPtEtaPhiM(pt,d.JetPUPPI_Eta[i],d.JetPUPPI_Phi[i],0);
	    bjets.push_back(bjet);

	  }
	} //pT>30
	    
      }
            if (verbose) cout <<__LINE__ << endl;

      MET_ = d.PuppiMissingET_MET[0];
      METphi_ = d.PuppiMissingET_Phi[0];
      GenMET_ = d.GenMissingET_MET[0];
      METres_ = GenMET_ > 0 ? (MET_ - GenMET_) / GenMET_ : -999;
      METdiff_ =  (MET_ - GenMET_) ;
      METvecNoMu1p6_.SetPtEtaPhiM(MET_,0,d.PuppiMissingET_Phi[0],0);
      METvecNoMu2p4_.SetPtEtaPhiM(MET_,0,d.PuppiMissingET_Phi[0],0);
	  

      plot1D("h_nlepIso", nlepIso_,  evtweight_, h_1d, "NlepIso",10, -0.5, 9.5);





      // Require dileptons
      if (nlepIso_<2) continue; // CUT //
      // Require same sign for 2 leading isolated leptons
      if (leptons_[0].id * leptons_[1].id < 0) continue; // CUT //



       // Classify MultiBoson backgrounds
      int nWp = 0, nWm = 0, nW = 0, nH = 0, nZ = 0, nTop = 0, nG = 0;
      for ( int i = 0; i < d.Particle_ ; ++i) {
	//cout<<d.Particle_PID[i]<<" "<<d.Particle_Status[i]<<endl;
	if (d.Particle_PID[i]==23  && d.Particle_Status[i]==22) nZ++;
	if (d.Particle_PID[i]==25  && d.Particle_Status[i]==22) nH++;
	if (d.Particle_PID[i]==24  && d.Particle_Status[i]==22) nWp++;
	if (d.Particle_PID[i]==-24 && d.Particle_Status[i]==22) nWm++;
	if (d.Particle_PID[i]==22 && d.Particle_Status[i]==23) nG++;
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
      else if (nG>0) BBtype_ = 9; // VG
      if (nTop==2 ) {
	if (nW==3) BBtype_ = 7; //ttW
	else       BBtype_ = 8; //ttZ
      }
      
      if (BBtype_ == 0 && nW+nZ+nH>1) 
	cout<<"nW="<<nW<<", nZ="<<nZ<<", nTop="<<nTop<<", nH="<<nH<<endl;

      BBstring_ = "";
      if (BBtype_==1)        BBstring_ = "_WWW";
      else if (BBtype_==2)   BBstring_ = "_VVZ";
      else if (BBtype_==3)   BBstring_ = "_VH";
      else if (BBtype_==4)   BBstring_ = "_WW";
      else if (BBtype_==5)   BBstring_ = "_WZ";
      else if (BBtype_==6)   BBstring_ = "_ZZ";
      else if (BBtype_==7)   BBstring_ = "_ttW";
      else if (BBtype_==8)   BBstring_ = "_ttZ"; // maybe could put ttG in here...
      else if (BBtype_==9)   BBstring_ = "_VG";
      else if (BBtype_==0)   BBstring_ = "_other";


      // Check for Z peaks
      int hasOSZ = false;
      bool maybeHasFSRZ = false;
      for ( unsigned int i = 0; i < leptons_.size() ; ++i) {
	for ( unsigned int j = i+1; j < leptons_.size() ; ++j) {
	  TLorentzVector dilep = leptons_[i].vec + leptons_[j].vec;
	  float m = dilep.M();
	  int charge = leptons_[i].id * leptons_[j].id;
	  bool SF = ( abs(leptons_[i].id) ==  abs(leptons_[j].id) );
	  if (!SF) continue;
	  plot1D("h_dilepmass", m,  evtweight_, h_1d, "mLL [GeV]", 60, 0, 150);
	  if (charge > 0)
	    plot1D("h_SSdilepmass", m,  evtweight_, h_1d, "mLL [GeV]", 60, 0, 150);
	  else {
	    if (m < 15 || (m>80 && m<100) ) hasOSZ = true;
	    if (m < 75) maybeHasFSRZ = true;
	    plot1D("h_OSdilepmass", m,  evtweight_, h_1d, "mLL [GeV]", 60, 0, 150);
	    plot1D("h_OSdilepmass"+BBstring_, m,  evtweight_, h_1d, "mLL [GeV]", 60, 0, 150);
	    //cout<<"Making mass from l1: "<<leptons_[i].vec.Pt()<<" and l2: "<<leptons_[j].vec.Pt()<<" : m = "<<m<<endl;
	  }
	}
      }
      for ( unsigned int i = 0; i < leptons_.size() ; ++i) {
	for ( unsigned int j = 0; j < leptonsVeto_.size() ; ++j) {
	  TLorentzVector dilep = leptons_[i].vec + leptonsVeto_[j].vec;
	  float m = dilep.M();
	  int charge = leptons_[i].id * leptonsVeto_[j].id;
	  bool SF = ( abs(leptons_[i].id) ==  abs(leptonsVeto_[j].id) );
	  if (!SF) continue;
	  plot1D("h_lepVetoLepmass", m,  evtweight_, h_1d, "mLL [GeV]", 60, 0, 150);
	  if (charge > 0)
	    plot1D("h_SSlepVetoLepmass", m,  evtweight_, h_1d, "mLL [GeV]", 60, 0, 150);
	  else {
	    if (m < 15 || (m>80 && m<100) ) hasOSZ = true;
	    plot1D("h_OSlepVetoLepmass", m,  evtweight_, h_1d, "mLL [GeV]", 60, 0, 150);
	    plot1D("h_OSlepVetodilepmass"+BBstring_, m,  evtweight_, h_1d, "mLL [GeV]", 60, 0, 150);
	  }
	}
      }
      if (verbose) cout <<__LINE__ << endl;

      if (verbose) cout << evtweight_ <<" "<< HT_ <<" "<< nlep_ <<endl;
      
      // MTmin
      mtmin_ = 999.;
      for ( unsigned int i = 0; i < leptons_.size() ; ++i) {
	if (leptons_[i].mt < mtmin_) mtmin_ = leptons_[i].mt;
      }

      // MT2 of 2 leading leptons (even though these events might have a third lepton at this point)
      LorentzVector lep1LV;
      lep1LV.SetPx( leptons_[0].vec.X()); lep1LV.SetPy( leptons_[0].vec.Y()); lep1LV.SetPz( leptons_[0].vec.Z()); lep1LV.SetE ( leptons_[0].vec.E());
      LorentzVector lep2LV;
      lep2LV.SetPx( leptons_[1].vec.X()); lep2LV.SetPy( leptons_[1].vec.Y()); lep2LV.SetPz( leptons_[1].vec.Z()); lep2LV.SetE ( leptons_[1].vec.E());
      MT2_    = MT2( MET_   , METphi_   , lep1LV, lep2LV, 0.0 );


      // Trilepton Mass
      if (maybeHasFSRZ && leptons_.size()>2 && MET_<50) {
	TLorentzVector dilep = leptons_[0].vec + leptons_[1].vec + leptons_[2].vec;
	float m = dilep.M();
	plot1D("h_trilepmass", m,  evtweight_, h_1d, "mLLL [GeV]", 80, 0, 200);
	plot1D("h_trilepmass"+BBstring_, m,  evtweight_, h_1d, "mLLL [GeV]", 80, 0, 200);
      }
      

      fillHistos(h_1d_base, "Base", ""); // SS dileptons

      if (hasOSZ) continue; // CUT

      // Count reconstructed leptons
      int nmu = 0, nele = 0;
      for ( unsigned int i = 0; i < leptons_.size() ; ++i) {
	if (fabs(leptons_[i].id)==13) nmu++;
	if (fabs(leptons_[i].id)==11) nele++;
      }
      for ( unsigned int i = 0; i < leptonsVeto_.size() ; ++i) {
	if (fabs(leptonsVeto_[i].id)==13) nmu++;
	if (fabs(leptonsVeto_[i].id)==11) nele++;
      }
      int type = nmu>2 ? 1 : nele>2 ? 2 : (nmu==2 && nele==1) ? 3 : (nmu==1 && nele==2) ? 4 : (nmu==2) ? 5 : nele==2 ? 6 : (nmu==1 && nele==1) ? 7 : -1; // mmm=1, eee=2, mme=3, mee=4, mm=5, ee=6, em=7
      if (BBtype_==5) plot1D("h_WZtype_beforeVeto", type,  evtweight_, h_1d, "mmm,eee,mme,mee,mm,ee,em",10, -0.5, 9.5);

      // Count true leptons
      nmu = 0;
      nele = 0;
      for ( int i = 0; i < d.Particle_ ; ++i) {
	if (d.Particle_Status[i]!=1) continue;
	if (fabs(d.Particle_PID[i])==13) nmu++;
	if (fabs(d.Particle_PID[i])==11) nele++;
      }
      int gentype = nmu>2 ? 1 : nele>2 ? 2 : (nmu==2 && nele==1) ? 3 : (nmu==1 && nele==2) ? 4 : (nmu==2) ? 5 : nele==2 ? 6 : (nmu==1 && nele==1) ? 7 : -1; // mmm=1, eee=2, mme=3, mee=4, mm=5, ee=6, em=7
      if (BBtype_==5) plot1D("h_WZgentype_beforeVeto", gentype,  evtweight_, h_1d, "mmm,eee,mme,mee,mm,ee,em",10, -0.5, 9.5);


      //...... Make plots of found/lost leptons before lepton veto for WZ
      if (BBtype_==5 && gentype<=4)        {
	// GenLevel study of WZ events
	for ( int i = 0; i < d.Particle_ ; ++i) {
	  if (d.Particle_Status[i]!=1) continue;
	  if (fabs(d.Particle_PID[i])!=11 && fabs(d.Particle_PID[i])!=13 && fabs(d.Particle_PID[i])!=15 ) continue;
	  float pt = d.Particle_PT[i];
	  float eta = fabs(d.Particle_Eta[i]);
	  //cout<<d.Particle_PID[i]<<" "<<d.Particle_Status[i]<<" "<<d.Particle_PT[i]<<" "<<d.Particle_Eta[i]<<endl;
	  float isel = fabs(d.Particle_PID[i])==11;
	  float ismu = fabs(d.Particle_PID[i])==13;
	  plot1D("hBeforeLepVeto_genLepID", d.Particle_PID[i],  evtweight_, h_1d, "ID", 40, -20, 20);
	  plot1D("hBeforeLepVeto_genLepPT", d.Particle_PT[i],  evtweight_, h_1d, "pT [GeV]", 100, 0, 100);
	  plot1D("hBeforeLepVeto_genLepEta", d.Particle_Eta[i],  evtweight_, h_1d, "Eta",  26, -5.2, 5.2);
	  if (isel) plot1D("hBeforeLepVeto_genLepEtaEl", d.Particle_Eta[i],  evtweight_, h_1d, "Eta",  26, -5.2, 5.2);
	  if (ismu) plot1D("hBeforeLepVeto_genLepEtaMu", d.Particle_Eta[i],  evtweight_, h_1d, "Eta",  26, -5.2, 5.2);
	  if (ismu && pt>5) plot1D("hBeforeLepVeto_genLepEtaMuPt5", d.Particle_Eta[i],  evtweight_, h_1d, "Eta",  26, -5.2, 5.2);
	  if (ismu && pt>5 && type==1) plot1D("hBeforeLepVeto_genLepEtaMuPt5_mmm", d.Particle_Eta[i],  evtweight_, h_1d, "Eta",  26, -5.2, 5.2);
	  if (ismu && pt>5 && type==4) plot1D("hBeforeLepVeto_genLepEtaMuPt5_mee", d.Particle_Eta[i],  evtweight_, h_1d, "Eta",  26, -5.2, 5.2);

	  plot1D("hBeforeLepVeto_genLepPhi", d.Particle_Phi[i],  evtweight_, h_1d, "Phi",  40, -3.2, 3.2);

	  // Efficiency denominator: gen lepton
	  if (isel) plot2D("h_ElFullEffDen", pt, eta, evtweight_, h_2d, "ElFullEffDen", 5, xbins, 5, ybinsEl);
	  if (ismu) plot2D("h_MuFullEffDen", pt, eta, evtweight_, h_2d, "MuFullEffDen", 5, xbins, 5, ybinsMu);

	  // Find the "lost lepton"
	  bool found = false;
	  bool foundTight = false;
	  //cout<<"GenLep "<<d.Particle_PID[i]<<" "<<d.Particle_Status[i]<<" "<<d.Particle_PT[i]<<" "<<d.Particle_Eta[i]<<endl;
	  for ( unsigned int j = 0; j < leptons_.size() ; ++j) {
	    //cout<<"Lep "<<leptons_[j].id<<" "<<leptons_[j].vec.Pt()<<" "<<leptons_[j].vec.Eta()<<endl;
	    if (d.Particle_PID[i] == leptons_[j].id && fabs(d.Particle_PT[i]-leptons_[j].vec.Pt()) < 1 && fabs(d.Particle_Eta[i]-leptons_[j].vec.Eta())<0.1 ) {found = true; foundTight = true;}// Matched!
	  }
	  for ( unsigned int j = 0; j < leptonsVeto_.size() ; ++j) {
	    //cout<<"Lep "<<leptons_[j].id<<" "<<leptons_[j].vec.Pt()<<" "<<leptons_[j].vec.Eta()<<endl;
	    if (d.Particle_PID[i] == leptonsVeto_[j].id && fabs(d.Particle_PT[i]-leptonsVeto_[j].vec.Pt()) < 1 && fabs(d.Particle_Eta[i]-leptonsVeto_[j].vec.Eta())<0.1 ) found = true; // Matched!
	  }
	  if (!found) {
	    plot1D("hBeforeLepVeto_lostLepID", d.Particle_PID[i],  evtweight_, h_1d, "ID", 40, -20, 20);
	    plot1D("hBeforeLepVeto_lostLepPT", d.Particle_PT[i],  evtweight_, h_1d, "pT [GeV]", 100, 0, 100);
	    if (ismu) plot1D("hBeforeLepVeto_lostLepEtaMu", d.Particle_Eta[i],  evtweight_, h_1d, "Eta",  26, -5.2, 5.2);
	    if (ismu && pt>5) plot1D("hBeforeLepVeto_lostLepEtaMuPt5", d.Particle_Eta[i],  evtweight_, h_1d, "Eta",  26, -5.2, 5.2);
	    plot1D("hBeforeLepVeto_lostLepPhi", d.Particle_Phi[i],  evtweight_, h_1d, "Phi",  40, -3.2, 3.2);
	  }
	  else if (found) {
	    if (ismu && pt>5) plot1D("hBeforeLepVeto_foundLepEtaMuPt5", d.Particle_Eta[i],  evtweight_, h_1d, "Eta",  26, -5.2, 5.2);
	    // Efficiency numerator: found
	    if (foundTight) {
	      if (isel) plot2D("h_ElFullEffNum", pt, eta, evtweight_, h_2d, "ElFullEffNum", 5, xbins, 5, ybinsEl);
	      if (ismu) plot2D("h_MuFullEffNum", pt, eta, evtweight_, h_2d, "MuFullEffNum", 5, xbins, 5, ybinsMu);
	    }
	  }

	}
      } //...... End of plots of found/lost leptons before lepton veto for WZ


      fillHistos(h_1d_Zveto, "Zveto", ""); // Veto OS Z
      if (nlep_!=2) continue; // CUT
      fillHistos(h_1d_lepVeto, "lepVeto", ""); // Veto 3rd lepton in general

      if (BBtype_==5) plot1D("h_WZtype_afterVeto", type,  evtweight_, h_1d, "mmm,eee,mme,mee,mm,ee,em",10, -0.5, 9.5);
      if (BBtype_==5) plot1D("h_WZgentype_afterVeto", gentype,  evtweight_, h_1d, "mmm,eee,mme,mee,mm,ee,em",10, -0.5, 9.5);

      //...... Make plots of found/lost leptons after lepton veto for WZ
      if (BBtype_==5 && gentype<=4)        {
	// GenLevel study of WZ events
	//cout<<"WZ event survived lepton veto! Why?"<<endl;
	for ( int i = 0; i < d.Particle_ ; ++i) {
	  if (d.Particle_Status[i]!=1) continue;
	  if (fabs(d.Particle_PID[i])!=11 && fabs(d.Particle_PID[i])!=13 && fabs(d.Particle_PID[i])!=15 ) continue;
	  float pt = d.Particle_PT[i];
	  float eta = d.Particle_Eta[i];
	  TLorentzVector vec;
	  vec.SetPtEtaPhiM(pt,d.Particle_Eta[i],d.Particle_Phi[i],0);

	  //cout<<d.Particle_PID[i]<<" "<<d.Particle_Status[i]<<" "<<d.Particle_PT[i]<<" "<<d.Particle_Eta[i]<<endl;
	  bool isel = fabs(d.Particle_PID[i])==11;
	  bool ismu = fabs(d.Particle_PID[i])==13;
	  bool mmm = ismu && fabs(leptons_[0].id)==13 && fabs(leptons_[1].id)==13;  // mmm only (this only works after the veto since I am implying that there are no leptonsVeto
	  bool mee = ismu && fabs(leptons_[0].id)==11 && fabs(leptons_[1].id)==11;  
	  bool ee = fabs(leptons_[0].id)==11 && fabs(leptons_[1].id)==11;  
	  bool mme = ismu && fabs(leptons_[0].id-leptons_[1].id)==2;

	  
	  plot1D("h_genLepID", d.Particle_PID[i],  evtweight_, h_1d, "ID", 40, -20, 20);
	  plot1D("h_genLepPT", d.Particle_PT[i],  evtweight_, h_1d, "pT [GeV]", 100, 0, 100);
	  plot1D("h_genLepEta", d.Particle_Eta[i],  evtweight_, h_1d, "Eta",  26, -5.2, 5.2);
	  if (isel) plot1D("h_genLepEtaEl", d.Particle_Eta[i],  evtweight_, h_1d, "Eta",  26, -5.2, 5.2);
	  if (ismu) plot1D("h_genLepEtaMu", d.Particle_Eta[i],  evtweight_, h_1d, "Eta",  26, -5.2, 5.2);
	  if (ismu && pt>5) plot1D("h_genLepEtaMuPt5", d.Particle_Eta[i],  evtweight_, h_1d, "Eta",  26, -5.2, 5.2);
	  if (mmm && ismu && pt>5) plot1D("h_genLepEtaMuPt5_mmm", d.Particle_Eta[i],  evtweight_, h_1d, "Eta",  26, -5.2, 5.2);
	  if (mme && ismu && pt>5) plot1D("h_genLepEtaMuPt5_mme", d.Particle_Eta[i],  evtweight_, h_1d, "Eta",  26, -5.2, 5.2);
	  if (ee          && pt>5) plot1D("h_genLepEtaPt5_Xee", d.Particle_Eta[i],  evtweight_, h_1d, "Eta",  26, -5.2, 5.2);
	  if (ee  && ismu && pt>5) plot1D("h_genLepEtaMuPt5_mee", d.Particle_Eta[i],  evtweight_, h_1d, "Eta",  26, -5.2, 5.2);
	  if (ee  && isel && pt>5) plot1D("h_genLepEtaElPt5_eee", d.Particle_Eta[i],  evtweight_, h_1d, "Eta",  26, -5.2, 5.2);

	  plot1D("h_genLepPhi", d.Particle_Phi[i],  evtweight_, h_1d, "Phi",  40, -3.2, 3.2);

	  // Find the "lost lepton"
	  bool found = false;
	  //cout<<"GenLep "<<d.Particle_PID[i]<<" "<<d.Particle_Status[i]<<" "<<d.Particle_PT[i]<<" "<<d.Particle_Eta[i]<<endl;
	  for ( unsigned int j = 0; j < leptons_.size() ; ++j) {
	    //cout<<"Lep "<<leptons_[j].id<<" "<<leptons_[j].vec.Pt()<<" "<<leptons_[j].vec.Eta()<<endl;
	    //	    if (d.Particle_PID[i] == leptons_[j].id && fabs(d.Particle_PT[i]-leptons_[j].vec.Pt()) < 1 && fabs(d.Particle_Eta[i]-leptons_[j].vec.Eta())<0.1 ) found = true; // Matched!
	    if (d.Particle_PID[i] == leptons_[j].id && ROOT::Math::VectorUtil::DeltaR(vec, leptons_[j].vec) <0.1 ) found = true; // Matched!
	  }
	  for ( unsigned int j = 0; j < leptonsVeto_.size() ; ++j) {
	    //cout<<"Lep "<<leptons_[j].id<<" "<<leptons_[j].vec.Pt()<<" "<<leptons_[j].vec.Eta()<<endl;
	    //	    if (d.Particle_PID[i] == leptonsVeto_[j].id && fabs(d.Particle_PT[i]-leptonsVeto_[j].vec.Pt()) < 1 && fabs(d.Particle_Eta[i]-leptonsVeto_[j].vec.Eta())<0.1 ) found = true; // Matched!
	    if (d.Particle_PID[i] == leptonsVeto_[j].id && ROOT::Math::VectorUtil::DeltaR(vec, leptonsVeto_[j].vec) <0.1 ) found = true; // Matched!

	  }

	  TLorentzVector mmvec = fabs(leptons_[0].id)==13 ? leptons_[0].vec + vec : leptons_[1].vec + vec ;
	  float m = mmvec.M();


	  if (!found) {

	    if (mmm  && fabs(eta)< 2.8) {
	      //cout<<"True MET is "<<METvec_.Pt();
	      if ( fabs(eta) > 1.6) METvecNoMu1p6_ = METvecNoMu1p6_ - vec; // subtract "lost" muon from MET if it is out of eta acceptance (assuming it would otherwise have been accepted)
	      if ( fabs(eta) > 2.4) METvecNoMu2p4_ = METvecNoMu2p4_ - vec; 
	      //cout<<", transformed into "<<METvec_.Pt()<<" after subtracting a muon of "<<vec.Pt()<<endl;
	    }
	    
	    //cout<<"Unmatched GenLep "<<d.Particle_PID[i]<<" "<<d.Particle_Status[i]<<" "<<d.Particle_PT[i]<<" "<<d.Particle_Eta[i]<<endl;
	    plot1D("h_lostLepID", d.Particle_PID[i],  evtweight_, h_1d, "ID", 40, -20, 20);
	    plot1D("h_lostLepPT", d.Particle_PT[i],  evtweight_, h_1d, "pT [GeV]", 100, 0, 100);
	    if (ismu) plot1D("h_lostLepEtaMu", d.Particle_Eta[i],  evtweight_, h_1d, "Eta",  26, -5.2, 5.2);
	    if (ismu && pt>5) plot1D("h_lostLepEtaMuPt5", d.Particle_Eta[i],  evtweight_, h_1d, "Eta",  26, -5.2, 5.2);
	    if (mmm && ismu && pt>5) plot1D("h_lostLepAbsEtaMuPt5_mmm", fabs(d.Particle_Eta[i]),  evtweight_, h_1d, "Eta",  13, 0, 5.2);
	    if (mmm && ismu && pt>5) plot1D("h_lostLepEtaMuPt5_mmm", d.Particle_Eta[i],  evtweight_, h_1d, "Eta",  26, -5.2, 5.2);
	    if (mme && ismu && pt>5) plot1D("h_lostLepEtaMuPt5_mme", d.Particle_Eta[i],  evtweight_, h_1d, "Eta",  26, -5.2, 5.2);
	    if (mee && ismu && pt>5) plot1D("h_lostLepEtaMuPt5_mee", d.Particle_Eta[i],  evtweight_, h_1d, "Eta",  26, -5.2, 5.2);
	    plot1D("h_lostLepPhi", d.Particle_Phi[i],  evtweight_, h_1d, "Phi",  40, -3.2, 3.2);


	    if (mme) plot1D("h_lostZdimuonMass", m,  evtweight_, h_1d, "mLL [GeV]", 60, 0, 150);

	  }
	  else if (found) {
	    if (ismu && pt>5) plot1D("h_foundLepEtaMuPt5", d.Particle_Eta[i],  evtweight_, h_1d, "Eta",  26, -5.2, 5.2);
	    if (mmm && ismu && pt>5) plot1D("h_foundLepEtaMuPt5_mmm", d.Particle_Eta[i],  evtweight_, h_1d, "Eta",  26, -5.2, 5.2);
	    if (mme && ismu && pt>5) plot1D("h_foundLepEtaMuPt5_mme", d.Particle_Eta[i],  evtweight_, h_1d, "Eta",  26, -5.2, 5.2);
	    if (mee && ismu && pt>5) plot1D("h_foundLepEtaMuPt5_mee", d.Particle_Eta[i],  evtweight_, h_1d, "Eta",  26, -5.2, 5.2);
	  }

	}
      }  //...... End of plots of found/lost leptons after lepton veto for WZ


      //..... GenLevel study of ttW events to look at gen b-quarks
      if (BBtype_==7)        {
	for ( int i = 0; i < d.Particle_ ; ++i) {
	  if (d.Particle_Status[i]!=71) continue;
	  if (fabs(d.Particle_PID[i])!=5 ) continue;
	  float pt = d.Particle_PT[i];
	  TLorentzVector vec;
	  vec.SetPtEtaPhiM(pt,d.Particle_Eta[i],d.Particle_Phi[i],0);

	  plot1D("hBeforeBVeto_genBPT", d.Particle_PT[i],  evtweight_, h_1d, "pT [GeV]", 100, 0, 100);
	  if(pt>30)plot1D("hBeforeBVeto_genBEta", d.Particle_Eta[i],  evtweight_, h_1d, "Eta",  26, -5.2, 5.2);

	  // Find the "lost lepton"
	  bool found = false;
	  //cout<<"GenLep "<<d.Particle_PID[i]<<" "<<d.Particle_Status[i]<<" "<<d.Particle_PT[i]<<" "<<d.Particle_Eta[i]<<endl;
	  for ( unsigned int j = 0; j < bjets.size() ; ++j) {
	    if ( ROOT::Math::VectorUtil::DeltaR(vec, bjets[j]) <0.1 ) found = true; // Matched!
	  }
	  if (found) {
	    plot1D("hBeforeBVeto_foundBPT", d.Particle_PT[i],  evtweight_, h_1d, "pT [GeV]", 100, 0, 100);
	    if(pt>30)plot1D("hBeforeBVeto_foundBEta", d.Particle_Eta[i],  evtweight_, h_1d, "Eta",  26, -5.2, 5.2);
	  }
	  else {
	    plot1D("hBeforeBVeto_lostBPT", d.Particle_PT[i],  evtweight_, h_1d, "pT [GeV]", 100, 0, 100);
	    if(pt>30)plot1D("hBeforeBVeto_lostBEta", d.Particle_Eta[i],  evtweight_, h_1d, "Eta",  26, -5.2, 5.2);
	  }


	}
      }       //..... End of GenLevel study of ttW events to look at gen b-quarks



      if (nbjet30_>0) continue; // CUT //
      fillHistos(h_1d_bVeto, "bVeto", ""); // Veto b-jets

      if (BBtype_==7)        {
	// GenLevel study of ttW events to look at gen b-quarks
	for ( int i = 0; i < d.Particle_ ; ++i) {
	  if (d.Particle_Status[i]!=71) continue;
	  if (fabs(d.Particle_PID[i])!=5 ) continue;
	  float pt = d.Particle_PT[i];
	  TLorentzVector vec;
	  vec.SetPtEtaPhiM(pt,d.Particle_Eta[i],d.Particle_Phi[i],0);

	  plot1D("hAfterBVeto_genBPT", d.Particle_PT[i],  evtweight_, h_1d, "pT [GeV]", 100, 0, 100);
	  if(pt>30)plot1D("hAfterBVeto_genBEta", d.Particle_Eta[i],  evtweight_, h_1d, "Eta",  26, -5.2, 5.2);

	  // Find the "lost lepton"
	  bool found = false;
	  //cout<<"GenLep "<<d.Particle_PID[i]<<" "<<d.Particle_Status[i]<<" "<<d.Particle_PT[i]<<" "<<d.Particle_Eta[i]<<endl;
	  for ( unsigned int j = 0; j < bjets.size() ; ++j) {
	    if ( ROOT::Math::VectorUtil::DeltaR(vec, bjets[j]) <0.1 ) found = true; // Matched!
	  }
	  if (found) {
	    plot1D("hAfterBVeto_foundBPT", d.Particle_PT[i],  evtweight_, h_1d, "pT [GeV]", 100, 0, 100);
	    if(pt>30)plot1D("hAfterBVeto_foundBEta", d.Particle_Eta[i],  evtweight_, h_1d, "Eta",  26, -5.2, 5.2);
	  }
	  else {
	    plot1D("hAfterBVeto_lostBPT", d.Particle_PT[i],  evtweight_, h_1d, "pT [GeV]", 100, 0, 100);
	    if(pt>30)plot1D("hAfterBVeto_lostBEta", d.Particle_Eta[i],  evtweight_, h_1d, "Eta",  26, -5.2, 5.2);
	  }


	}
      }

      if (njet30_>0) continue; // CUT //
      fillHistos(h_1d_j2Veto, "j2Veto", ""); // Veto 4th jet

      // Analyze some events that make it here:
      if (BBtype_==4) {
	cout<<"WW event passed full selection (no MTmin cut), with MET "<<MET_;
	cout<<". Leptons are "<<leptons_[0].id<<","<<leptons_[0].vec.Pt()<<" and "<<leptons_[1].id<<","<<leptons_[1].vec.Pt()<<endl;
      }

      


      if (mtmin_ < 120) continue; // CUT //
      fillHistos(h_1d_mt120, "mt120", ""); // High MTmin

      cout<<"Event passed full selection, type "<<BBtype_<<", MET "<<MET_;
      cout<<". Leptons are "<<leptons_[0].id<<","<<leptons_[0].vec.Pt()<<" and "<<leptons_[1].id<<","<<leptons_[1].vec.Pt()<<endl;


      
    }// end of event loop


    file->Close();
    delete file;
    //delete tree;
    cout<<"\nFile done"<<endl;

  }//end of  file loop

  if (synchronizemode) {
    cout<<"Unweighted: Total "<<totN<<", 2mu "<<muN<<", 1jet "<<jetN<<", 0bjet "<<bjetN<<", met "<<metN<<", ht "<<htN<<endl;
    cout<<"Weighted: Total "<<totW<<", 2mu "<<muW<<", 1jet "<<jetW<<", 0bjet "<<bjetW<<", met "<<metW<<", ht "<<htW<<endl;
    return;
  }
  
  cout<<"\nWriting file"<<endl;
  savePlotsDir(h_1d, outfile_, "");
  savePlotsDir(h_2d, outfile_, "");
  savePlotsDir(h_1d_base, outfile_, "Base");
  savePlotsDir(h_1d_2j, outfile_, "2Jets");
//  savePlotsDir(h_1d_WZ, outfile_, "WZ");
//  savePlotsDir(h_1d_ZZ, outfile_, "ZZ");
//  savePlotsDir(h_1d_WW, outfile_, "WW");
//  savePlotsDir(h_1d_VH, outfile_, "VH");
//  savePlotsDir(h_1d_WWW, outfile_, "WWW");
//  savePlotsDir(h_1d_VVZ, outfile_, "VVZ");
//  savePlotsDir(h_1d_ttW, outfile_, "ttW");
//  savePlotsDir(h_1d_ttZ, outfile_, "ttZ");
//  savePlotsDir(h_1d_other, outfile_, "other");
  savePlotsDir(h_1d_lepVeto, outfile_, "lepVeto");
  savePlotsDir(h_1d_bVeto, outfile_, "bVeto");
  savePlotsDir(h_1d_j2Veto, outfile_, "j2Veto");
  savePlotsDir(h_1d_Zveto, outfile_, "Zveto");
  savePlotsDir(h_1d_mt120, outfile_, "mt120");
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
  plot1D("h_HTfull"+s+BBstring_, HT_,  evtweight_, h_1d, "HT [GeV]", 200, 0, 2000);
  plot1D("h_njet30barrel"+s, njet30barrel_ ,  evtweight_, h_1d, "N_j barrel", 10, -0.5, 9.5);
  plot1D("h_njet30central"+s, njet30central_ ,  evtweight_, h_1d, "N_j central", 10, -0.5, 9.5);
  plot1D("h_njet30central"+s+BBstring_, njet30central_ ,  evtweight_, h_1d, "N_j central", 10, -0.5, 9.5);
  plot1D("h_njet30forward"+s, njet30forward_ ,  evtweight_, h_1d, "N_j forward", 10, -0.5, 9.5);
  plot1D("h_njet30"+s, njet30_,  evtweight_, h_1d, "N_j", 10, -0.5, 9.5);
  plot1D("h_njet30"+s+BBstring_, njet30_,  evtweight_, h_1d, "N_j", 10, -0.5, 9.5);
  plot1D("h_jet1pt"+s, jet1pt_,  evtweight_, h_1d, "pT(j1) [GeV]", 100, 0, 250);
  plot1D("h_jet2pt"+s, jet2pt_,  evtweight_, h_1d, "pT(j1) [GeV]", 100, 0, 250);
  plot1D("h_jet1pt"+s+BBstring_, jet1pt_,  evtweight_, h_1d, "pT(j1) [GeV]", 100, 0, 250);
  plot1D("h_jet2pt"+s+BBstring_, jet2pt_,  evtweight_, h_1d, "pT(j1) [GeV]", 100, 0, 250);
  plot1D("h_nbjet30"+s, nbjet30_,  evtweight_, h_1d, "N_j", 10, -0.5, 9.5);
  plot1D("h_nbjet30"+s+BBstring_, nbjet30_,  evtweight_, h_1d, "N_j", 10, -0.5, 9.5);
  plot1D("h_BBtype"+s, BBtype_,  evtweight_, h_1d, "BB type [Other, WZ, ZZ, SSWW, OSWW]", 10, -0.5, 9.5);
  plot1D("h_MT2"+s, MT2_,  evtweight_, h_1d, "MT2 [GeV]", 200, 0, 400);
  plot1D("h_MT2"+s+BBstring_, MT2_,  evtweight_, h_1d, "MT2 [GeV]", 200, 0, 400);
  plot1D("h_MET"+s, MET_,  evtweight_, h_1d, "MET [GeV]", 200, 0, 400);
  plot1D("h_MET"+s+BBstring_, MET_,  evtweight_, h_1d, "MET [GeV]", 200, 0, 400);
  plot1D("h_METres"+s, METres_,  evtweight_, h_1d, "(RecoMET - GenMET)/GenMET", 200, -1, 1);
  plot1D("h_METdiff"+s, METdiff_,  evtweight_, h_1d, "(RecoMET - GenMET) [GeV]", 200, -100, 100);
  if (MET_>30) {
    plot1D("h_METgt30res"+s, METres_,  evtweight_, h_1d, "(RecoMET - GenMET)/GenMET", 200, -1, 1);
    plot1D("h_METgt30diff"+s, METdiff_,  evtweight_, h_1d, "(RecoMET - GenMET) [GeV]", 200, -100, 100);
  }
  plot1D("h_nlep"+s, nlep_,  evtweight_, h_1d, "Nlep",10, -0.5, 9.5);
  plot1D("h_nlep"+s+BBstring_, nlep_,  evtweight_, h_1d, "Nlep",10, -0.5, 9.5);
  plot1D("h_nlepIso"+s, nlepIso_,  evtweight_, h_1d, "Nlep(iso)", 10, -0.5, 9.5);
  int nmu = 0, nele = 0;
  for ( unsigned int i = 0; i < leptons_.size() ; ++i) {
    const std::string istring = std::to_string(i);
    plot1D("h_leppt"+istring+s, leptons_[i].vec.Pt(),  evtweight_, h_1d, "Lep pT", 100, 0, 100);
    plot1D("h_lepeta"+istring+s, leptons_[i].vec.Eta(),  evtweight_, h_1d, "Lep eta", 26, -5.2, 5.2);
    if (fabs(leptons_[i].id)==13) plot1D("h_lepetamu"+s, leptons_[i].vec.Eta(),  evtweight_, h_1d, "Lep eta", 26, -5.2, 5.2);
    plot1D("h_lepmt"+istring+s, leptons_[i].mt,  evtweight_, h_1d, "Lep MT", 100, 0, 200);
    if (fabs(leptons_[i].id)==13) nmu++;
    if (fabs(leptons_[i].id)==11) nele++;
  }
  int type = nmu>1 ? 1 : nele>1 ? 3 : (nmu==1 && nele==1) ? 2 : -1; // mm=1, em=2, ee=3
  const std::string stype = type==1 ? "mm" : (type==2 ? "em" : (type==3 ? "ee" : "other"));
  plot1D("h_type"+s, type,  evtweight_, h_1d, "mm,em,ee",6, -2, 4);

  int type2 = nmu>2 ? 1 : nele>2 ? 2 : nmu>1 ? 3 : nele>1 ? 4 : -1; // mmm=1, eee=2, mme=3, mee=4
  plot1D("h_type2"+s, type2,  evtweight_, h_1d, "mmm,eee, mme. mee",7, -2, 5);


  for ( unsigned int i = 0; i < leptonsVeto_.size() ; ++i) {
    if (fabs(leptons_[i].id)==13) {
      plot1D("h_lepetamu"+s, leptonsVeto_[i].vec.Eta(),  evtweight_, h_1d, "Lep eta", 26, -5.2, 5.2);
      plot1D("h_lepetavetomu"+s, leptonsVeto_[i].vec.Eta(),  evtweight_, h_1d, "Lep eta", 26, -5.2, 5.2);
    }
  }


  // Trilepton mass
  if (leptons_.size()>2) {
    TLorentzVector dilep = leptons_[0].vec + leptons_[1].vec + leptons_[2].vec;
    float m = dilep.M();
    plot1D("h_trilepmass"+s, m,  evtweight_, h_1d, "mLLL [GeV]", 80, 0, 200);
    plot1D("h_trilepmass"+s+BBstring_, m,  evtweight_, h_1d, "mLLL [GeV]", 80, 0, 200);
  }


  plot1D("h_mtmin"+s, mtmin_,  evtweight_, h_1d, "MTmin", 150, 0, 300);
  plot1D("h_mtmin"+stype+s, mtmin_,  evtweight_, h_1d, "MTmin", 150, 0, 300);
  plot1D("h_mtmin"+s+BBstring_, mtmin_,  evtweight_, h_1d, "MTmin", 150, 0, 300);


//  // MET Resolution study
//  if ( fabs( METvecNoMu1p6_.Pt() - MET_ ) > 1 ) { // Only plot where it matters: mmm with a muon out of acceptance
//    float MET = METvecNoMu1p6_.Pt();
//    float METres = (MET - GenMET_) / GenMET_;
//    float METdiff =  (MET - GenMET_) ;
//    plot1D("h_LostMuon1p6MET"+s, MET,  evtweight_, h_1d, "MET [GeV]", 200, 0, 400);
//    plot1D("h_LostMuon1p6METres"+s, METres,  evtweight_, h_1d, "(RecoMET - GenMET)/GenMET", 200, -1, 1);
//    plot1D("h_LostMuon1p6METdiff"+s, METdiff,  evtweight_, h_1d, "(RecoMET - GenMET) [GeV]", 200, -100, 100);
//    plot1D("h_LostMuon1p6OrigMET"+s, MET_,  evtweight_, h_1d, "MET [GeV]", 200, 0, 400);
//    plot1D("h_LostMuon1p6OrigMETres"+s, METres_,  evtweight_, h_1d, "(RecoMET - GenMET)/GenMET", 200, -1, 1);
//    plot1D("h_LostMuon1p6OrigMETdiff"+s, METdiff_,  evtweight_, h_1d, "(RecoMET - GenMET) [GeV]", 200, -100, 100);
//  }
//
//  if ( fabs( METvecNoMu2p4_.Pt() - MET_ ) > 1 ) { // Only plot where it matters: mmm with a muon out of acceptance
//    float MET = METvecNoMu2p4_.Pt();
//    float METres = (MET - GenMET_) / GenMET_;
//    float METdiff =  (MET - GenMET_) ;
//    plot1D("h_LostMuon2p4MET"+s, MET,  evtweight_, h_1d, "MET [GeV]", 200, 0, 400);
//    plot1D("h_LostMuon2p4METres"+s, METres,  evtweight_, h_1d, "(RecoMET - GenMET)/GenMET", 200, -1, 1);
//    plot1D("h_LostMuon2p4METdiff"+s, METdiff,  evtweight_, h_1d, "(RecoMET - GenMET) [GeV]", 200, -100, 100);
//    plot1D("h_LostMuon2p4OrigMET"+s, MET_,  evtweight_, h_1d, "MET [GeV]", 200, 0, 400);
//    plot1D("h_LostMuon2p4OrigMETres"+s, METres_,  evtweight_, h_1d, "(RecoMET - GenMET)/GenMET", 200, -1, 1);
//    plot1D("h_LostMuon2p4OrigMETdiff"+s, METdiff_,  evtweight_, h_1d, "(RecoMET - GenMET) [GeV]", 200, -100, 100);
//  }

  return;
}


