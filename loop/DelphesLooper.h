#ifndef DELPHESLOOPER_h
#define DELPHESLOOPER_h

// ROOT includes
#include "TROOT.h"
#include "TFile.h"
#include "TChain.h"
#include "TTree.h"
#include "TH1.h"
#include "TH2.h"
#include "Math/LorentzVector.h"
#include "TLorentzVector.h"


#include "Delphes.h"

typedef ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > LorentzVector;

struct part {
  TLorentzVector vec;
  int id;
  float mt;
};


class DelphesLooper {
  
 public:
  
//  DelphesLooper();
//  ~DelphesLooper();

  // Work is done here
  void loop(TChain* chain, std::string sample, std::string output_dir, float xsec, int nevt);

  // Other useful functions
  float DeltaR(float eta1, float eta2, float phi1, float phi2);
  float DeltaR(LorentzVector v1, LorentzVector v2); 
  float DeltaPhi(float phi1, float phi2);
  float MT(float pt1, float phi1, float pt2, float phi2);
  void progress( int nEventsTotal, int nEventsChain ); 
  void fillHistos(std::map<std::string, TH1*>& h_1d, const std::string& dirname = "", const std::string& s = "");
  
 private:
  
  TFile * outfile_;
  //Delphes t;
  float evtweight_;

  float HT1p5_;
  float HT2p5_;
  float HT_;
  int njet30barrel_;
  int njet30central_;
  int njet30forward_;
  int njet30_;
  float jet1pt_;
  float jet2pt_;
  int nbjet30_;
  float MT2_;
  float MET_;
  float METphi_;
  float GenMET_;
  float METres_;
  float METdiff_;


  TLorentzVector METvecNoMu1p6_;
  TLorentzVector METvecNoMu2p4_;
  int nlep_;
  int nlepIso_;
  int BBtype_;
  std::string BBstring_;
  float mtmin_;
//  float lep1pt_;
//  float lep1eta_;
//  float lep1phi_;
//  float lep2pt_;
//  float lep2eta_;
//  float lep2phi_;
  std::vector<part> leptons_;
  std::vector<part> leptonsVeto_;


  // One histogram map for every directory, plus a global one (h_1d)
  std::map<std::string, TH1*> h_1d;
  std::map<std::string, TH1*> h_2d;
  std::map<std::string, TH1*> h_1d_base;
  std::map<std::string, TH1*> h_1d_2j;
  std::map<std::string, TH1*> h_1d_WZ;
  std::map<std::string, TH1*> h_1d_ZZ;
  std::map<std::string, TH1*> h_1d_SSWW;
  std::map<std::string, TH1*> h_1d_OSWW;
  std::map<std::string, TH1*> h_1d_WW;
  std::map<std::string, TH1*> h_1d_VH;
  std::map<std::string, TH1*> h_1d_WWW;
  std::map<std::string, TH1*> h_1d_VVZ;
  std::map<std::string, TH1*> h_1d_ttW;
  std::map<std::string, TH1*> h_1d_ttZ;
  std::map<std::string, TH1*> h_1d_lepVeto;
  std::map<std::string, TH1*> h_1d_bVeto;
  std::map<std::string, TH1*> h_1d_j2Veto;
  std::map<std::string, TH1*> h_1d_mt120;
  std::map<std::string, TH1*> h_1d_Zveto;
  std::map<std::string, TH1*> h_1d_other;

  // Efficiency values
  float GetRun2EffMu( float pt, float eta){
    // For SUS-16-039, from https://twiki.cern.ch/twiki/bin/view/CMSPublic/SUSMoriond2017ObjectsEfficiency
    float eff = 0;
    eta = fabs(eta);
    if ( pt < 20) eff = 0;
    else if ( pt < 25 ) {
      if ( eta > 2.4 ) eff = 0;
      else if ( eta < 0.9 ) eff = 0.789;
      else if ( eta < 1.2 ) eff = 0.741;
      else if ( eta < 2.1 ) eff = 0.753;
      else if ( eta < 2.4 ) eff = 0.640;
    }
    else if ( pt < 30 ) {
      if ( eta > 2.4 ) eff = 0;
      else if ( eta < 0.9 ) eff = 0.834;
      else if ( eta < 1.2 ) eff = 0.823;
      else if ( eta < 2.1 ) eff = 0.808;
      else if ( eta < 2.4 ) eff = 0.704;
    }
    else if ( pt < 40 ) {
      if ( eta > 2.4 ) eff = 0;
      else if ( eta < 0.9 ) eff = 0.877;
      else if ( eta < 1.2 ) eff = 0.863;
      else if ( eta < 2.1 ) eff = 0.846;
      else if ( eta < 2.4 ) eff = 0.762;
    }
    else if ( pt < 50 ) {
      if ( eta > 2.4 ) eff = 0;
      else if ( eta < 0.9 ) eff = 0.911;
      else if ( eta < 1.2 ) eff = 0.922;
      else if ( eta < 2.1 ) eff = 0.879;
      else if ( eta < 2.4 ) eff = 0.837;
    }
    else {
      if ( eta > 2.4 ) eff = 0;
      else if ( eta < 0.9 ) eff = 0.924;
      else if ( eta < 1.2 ) eff = 0.924;
      else if ( eta < 2.1 ) eff = 0.913;
      else if ( eta < 2.4 ) eff = 0.857;
    }
    return eff;
  }
  
  float GetRun2EffEl( float pt, float eta){
    // For SUS-16-039, from https://twiki.cern.ch/twiki/bin/view/CMSPublic/SUSMoriond2017ObjectsEfficiency
    float eff = 0;
    eta = fabs(eta);
    if ( pt < 20) eff = 0;
    else if ( pt < 25 ) {
      if ( eta > 2.4        ) eff = 0;
      else if ( eta < 0.8   ) eff = 0.561;
      else if ( eta < 1.442 ) eff = 0.465;
      else if ( eta < 1.556 ) eff = 0.186;
      else if ( eta < 2.0   ) eff = 0.315;
      else if ( eta < 2.5   ) eff = 0.169;
    }
    else if ( pt < 30 ) {
      if ( eta > 2.4        ) eff = 0;
      else if ( eta < 0.8   ) eff = 0.623;
      else if ( eta < 1.442 ) eff = 0.543;
      else if ( eta < 1.556 ) eff = 0.237;
      else if ( eta < 2.0   ) eff = 0.347;
      else if ( eta < 2.5   ) eff = 0.278;
    }
    else if ( pt < 40 ) {
      if ( eta > 2.4        ) eff = 0;
      else if ( eta < 0.8   ) eff = 0.693;
      else if ( eta < 1.442 ) eff = 0.643;
      else if ( eta < 1.556 ) eff = 0.284;
      else if ( eta < 2.0   ) eff = 0.481;
      else if ( eta < 2.5   ) eff = 0.337;
    }
    else if ( pt < 50 ) {
      if ( eta > 2.4        ) eff = 0;
      else if ( eta < 0.8   ) eff = 0.761;
      else if ( eta < 1.442 ) eff = 0.671;
      else if ( eta < 1.556 ) eff = 0.326;
      else if ( eta < 2.0   ) eff = 0.554;
      else if ( eta < 2.5   ) eff = 0.425;
    }
    else {
      if ( eta > 2.4        ) eff = 0;
      else if ( eta < 0.8   ) eff = 0.837;
      else if ( eta < 1.442 ) eff = 0.791;
      else if ( eta < 1.556 ) eff = 0.399;
      else if ( eta < 2.0   ) eff = 0.678;
      else if ( eta < 2.5   ) eff = 0.561;
    }
    return eff;
  }
  
  float GetPhase2EffElTk( float pt, float eta){
    float eff = 0;
    // Copied from https://github.com/delphes/delphes/blob/master/cards/CMS_PhaseII/CMS_PhaseII_200PU_v02.tcl#L287
    eff = (pt <= 0.2) * (0.00) + 
      (abs(eta) <= 1.2) * (pt > 0.2 && pt <= 1.0) * (pt * 0.96) + 
      (abs(eta) <= 1.2) * (pt > 1.0) * (0.97) + 
      (abs(eta) > 1.2 && abs(eta) <= 2.5) * (pt > 0.2 && pt <= 1.0) * (pt*0.85) + 
      (abs(eta) > 1.2 && abs(eta) <= 2.5) * (pt > 1.0 && pt <= 10.0) * (0.82+pt*0.01) + 
      (abs(eta) > 1.2 && abs(eta) <= 2.5) * (pt > 10.0) * (0.90) + 
      (abs(eta) > 2.5 && abs(eta) <= 4.0) * (pt > 0.2 && pt <= 1.0) * (pt*0.8) + 
      (abs(eta) > 2.5 && abs(eta) <= 4.0) * (pt > 1.0 && pt <= 10.0) * (0.8+pt*0.01) + 
      (abs(eta) > 2.5 && abs(eta) <= 4.0) * (pt > 10.0) * (0.85) + 
      (abs(eta) > 4.0) * (0.00);
    return eff;
  }

  float GetPhase2EffMuTk( float pt, float eta){
    float eff = 0;
    // Copied from https://github.com/delphes/delphes/blob/master/cards/CMS_PhaseII/CMS_PhaseII_200PU_v02.tcl#L310
    eff =  (pt <= 0.2) * (0.00) +
      (abs(eta) <= 1.2) * (pt > 0.2 && pt <= 1.0) * (pt * 1.00) + 
      (abs(eta) <= 1.2) * (pt > 1.0) * (1.00) + 
      (abs(eta) > 1.2 && abs(eta) <= 2.8) * (pt > 0.2 && pt <= 1.0) * (pt*1.00) + 
      (abs(eta) > 1.2 && abs(eta) <= 2.8) * (pt > 1.0) * (1.00) + 
      (abs(eta) > 2.8 && abs(eta) <= 4.0) * (pt > 0.2 && pt <= 1.0) * (pt*0.95) + 
      (abs(eta) > 2.8 && abs(eta) <= 4.0) * (pt > 1.0) * (0.95) + 
      (abs(eta) > 4.0) * (0.00);
    //std::cout<<"GetPhase2EffMuTk for pt/eta "<<pt<<"/"<<eta<<": "<<eff<<std::endl;
    return eff;
  }

 float GetPhase2EffElID( float pt, float eta){
    float eff = 0;
    // Copied from https://github.com/delphes/delphes/blob/master/cards/CMS_PhaseII/CMS_PhaseII_200PU_v02.tcl#L1339
    eff = (pt <= 4.0)  * (1.00) + 
      (abs(eta) <= 1.45 ) * (pt >  4.0 && pt <= 6.0)   * (0.50) + 
      (abs(eta) <= 1.45 ) * (pt >  6.0 && pt <= 8.0)   * (0.70) + 
      (abs(eta) <= 1.45 ) * (pt >  8.0 && pt <= 10.0)  * (0.85) + 
      (abs(eta) <= 1.45 ) * (pt > 10.0 && pt <= 30.0)  * (0.94) + 
      (abs(eta) <= 1.45 ) * (pt > 30.0 && pt <= 50.0)  * (0.97) + 
      (abs(eta) <= 1.45 ) * (pt > 50.0 && pt <= 70.0)  * (0.98) + 
      (abs(eta) <= 1.45 ) * (pt > 70.0 )  * (1.0) + 
      (abs(eta) > 1.45  && abs(eta) <= 1.55) * (pt >  4.0 && pt <= 10.0)   * (0.35) + 
      (abs(eta) > 1.45  && abs(eta) <= 1.55) * (pt > 10.0 && pt <= 30.0)   * (0.40) + 
      (abs(eta) > 1.45  && abs(eta) <= 1.55) * (pt > 30.0 && pt <= 70.0)   * (0.45) + 
      (abs(eta) > 1.45  && abs(eta) <= 1.55) * (pt > 70.0 )  * (0.55) + 
      (abs(eta) >= 1.55 && abs(eta) <= 2.0 ) * (pt >  4.0 && pt <= 10.0)  * (0.75) + 
      (abs(eta) >= 1.55 && abs(eta) <= 2.0 ) * (pt > 10.0 && pt <= 30.0)  * (0.85) + 
      (abs(eta) >= 1.55 && abs(eta) <= 2.0 ) * (pt > 30.0 && pt <= 50.0)  * (0.95) + 
      (abs(eta) >= 1.55 && abs(eta) <= 2.0 ) * (pt > 50.0 && pt <= 70.0)  * (0.95) + 
      (abs(eta) >= 1.55 && abs(eta) <= 2.0 ) * (pt > 70.0 )  * (1.0) + 
      (abs(eta) >= 2.0 && abs(eta) <= 2.5 ) * (pt >  4.0 && pt <= 10.0)  * (0.65) + 
      (abs(eta) >= 2.0 && abs(eta) <= 2.5 ) * (pt > 10.0 && pt <= 30.0)  * (0.75) + 
      (abs(eta) >= 2.0 && abs(eta) <= 2.5 ) * (pt > 30.0 && pt <= 50.0)  * (0.90) + 
      (abs(eta) >= 2.0 && abs(eta) <= 2.5 ) * (pt > 50.0 && pt <= 70.0)  * (0.90) + 
      (abs(eta) >= 2.0 && abs(eta) <= 2.5 ) * (pt > 70.0 )  * (0.90) + 
      (abs(eta) > 2.5 && abs(eta) <= 4.0 ) * (pt > 4.0 && pt <= 10.0) * (0.65) + 
      (abs(eta) > 2.5 && abs(eta) <= 4.0 ) * (pt > 10.0 && pt <= 30.0) * (0.75) + 
      (abs(eta) > 2.5 && abs(eta) <= 4.0 ) * (pt > 30.0 && pt <= 50.0) * (0.90) + 
      (abs(eta) > 2.5 && abs(eta) <= 4.0 ) * (pt > 50.0 && pt <= 70.0) * (0.90) + 
      (abs(eta) > 2.5 && abs(eta) <= 4.0 ) * (pt > 70.0 ) * (0.90) + 
      (abs(eta) > 4.0) * (0.00);
    //std::cout<<"GetPhase2EffElID for pt/eta "<<pt<<"/"<<eta<<": "<<eff<<std::endl;

    return eff;
 }
 
 float GetPhase2EffMuID( float pt, float eta){
   float eff = 0;
   // Copied from https://github.com/delphes/delphes/blob/master/cards/CMS_PhaseII/muonTightId.tcl
//    eff =  (pt > 20 && pt < 40) * (abs(eta) > 0 && abs(eta) < 0.2) * 0.965 + 
//                (pt > 20 && pt < 40) * (abs(eta) > 0.2 && abs(eta) < 0.4) * 0.938 +
//                (pt > 20 && pt < 40) * (abs(eta) > 0.4 && abs(eta) < 0.6) * 0.99 +
//                (pt > 20 && pt < 40) * (abs(eta) > 0.6 && abs(eta) < 0.8) * 0.977 +
//                (pt > 20 && pt < 40) * (abs(eta) > 0.8 && abs(eta) < 1) * 0.959 +
//                (pt > 20 && pt < 40) * (abs(eta) > 1 && abs(eta) < 1.2) * 0.976 +
//                (pt > 20 && pt < 40) * (abs(eta) > 1.2 && abs(eta) < 1.4) * 0.984 +
//                (pt > 20 && pt < 40) * (abs(eta) > 1.4 && abs(eta) < 1.6) * 0.981 +
//                (pt > 20 && pt < 40) * (abs(eta) > 1.6 && abs(eta) < 1.8) * 0.978 +
//                (pt > 20 && pt < 40) * (abs(eta) > 1.8 && abs(eta) < 2) * 0.985 +
//                (pt > 20 && pt < 40) * (abs(eta) > 2 && abs(eta) < 2.2) * 0.969 +
//                (pt > 20 && pt < 40) * (abs(eta) > 2.2 && abs(eta) < 2.4) * 0.964 +
//                (pt > 20 && pt < 40) * (abs(eta) > 2.4 && abs(eta) < 2.5) * 0.863 +
//                (pt > 20 && pt < 40) * (abs(eta) > 2.5 && abs(eta) < 2.6) * 0.828 +
//                (pt > 20 && pt < 40) * (abs(eta) > 2.6 && abs(eta) < 2.7) * 0.807 +
//                (pt > 20 && pt < 40) * (abs(eta) > 2.7 && abs(eta) < 2.8) * 0.764 +
//        (pt > 40) * (abs(eta) > 0 && abs(eta) < 0.2) * 0.975 +
//                (pt > 40) * (abs(eta) > 0.2 && abs(eta) < 0.4) * 0.935 +
//                (pt > 40) * (abs(eta) > 0.4 && abs(eta) < 0.6) * 0.991 +
//                (pt > 40) * (abs(eta) > 0.6 && abs(eta) < 0.8) * 0.983 +
//                (pt > 40) * (abs(eta) > 0.8 && abs(eta) < 1) * 0.957 +
//                (pt > 40) * (abs(eta) > 1 && abs(eta) < 1.2) * 0.979 +
//                (pt > 40) * (abs(eta) > 1.2 && abs(eta) < 1.4) * 0.981 +
//                (pt > 40) * (abs(eta) > 1.4 && abs(eta) < 1.6) * 0.983 +
//                (pt > 40) * (abs(eta) > 1.6 && abs(eta) < 1.8) * 0.981 +
//                (pt > 40) * (abs(eta) > 1.8 && abs(eta) < 2) * 0.984 +
//                (pt > 40) * (abs(eta) > 2 && abs(eta) < 2.2) * 0.964 +
//                (pt > 40) * (abs(eta) > 2.2 && abs(eta) < 2.4) * 0.956 +
//                (pt > 40) * (abs(eta) > 2.4 && abs(eta) < 2.5) * 0.855 +
//                (pt > 40) * (abs(eta) > 2.5 && abs(eta) < 2.6) * 0.817 +
//                (pt > 40) * (abs(eta) > 2.6 && abs(eta) < 2.7) * 0.764 +
//                (pt > 40) * (abs(eta) > 2.7 && abs(eta) < 2.8) * 0.752 +
//      (abs(eta) > 2.8) * (0.00);
   // The stuff above doesn't work, it's not cleear why!!
   eff = 0.97;

   //   std::cout<<"GetPhase2EffMuID for pt/eta "<<pt<<"/"<<eta<<": "<<eff<<std::endl;
   return eff;
 }

 float GetPhase2EffMuTotal( float pt, float eta){
   return GetPhase2EffMuID(pt, eta) * GetPhase2EffMuTk(pt, eta);
 }
 float GetPhase2EffElTotal( float pt, float eta){
   return GetPhase2EffElID(pt, eta) * GetPhase2EffElTk(pt, eta);
 }

 float GetPhase2EffTotal( int id, float pt, float eta){
   if ( abs(id) == 11 ) return GetPhase2EffElTotal(pt, eta);
   else if ( abs(id) == 13 ) return GetPhase2EffMuTotal(pt, eta);
   else {
     std::cout<<"Error, GetPhase2EffTotal called with id "<<id<<std::endl;
     return 0;
   }
 }

 float GetRun2Eff( int id, float pt, float eta){
   if ( abs(id) == 11 ) return GetRun2EffEl(pt, eta);
   else if ( abs(id) == 13 ) return GetRun2EffMu(pt, eta);
   else {
     std::cout<<"Error, GetRun2Eff called with id "<<id<<std::endl;
     return 0;
   }
 }


};



#endif
