#include "TFile.h"
#include "TChain.h"
#include "TH1.h"
#include "TH2.h"
#include "TLegend.h"
#include "TString.h"
#include "TCanvas.h"
#include "TCut.h"
#include "TEfficiency.h"
#include "tdrstyle_SUSY.C"



void makeOverlay( TChain* t_full, TChain* t_fast, TString var_full, TString var_fast, TCut cut_full, TCut cut_fast, int nbins, float min, float max, TString xaxis, TString yaxis, TString saveas) {
  
  TH1D* h_pt_full = new TH1D("h_pt_full",";"+xaxis,nbins,min,max);
  TH1D* h_pt_fast = (TH1D*) h_pt_full->Clone("h_pt_fast");
  TCanvas* c = new TCanvas("c","c");
  c->SetGrid(1,1);
  c->cd();
  
  t_full->Draw(var_full+">>h_pt_full",cut_full);
  t_fast->Draw(var_fast+">>h_pt_fast",cut_fast);
  
  float ymax = h_pt_full->GetMaximum()*1.3;
  if (h_pt_fast->GetMaximum()*1.3 > h_pt_full->GetMaximum()*1.3) ymax = h_pt_fast->GetMaximum()*1.3;

  TH2F* h_axis = new TH2F("h_axis",";"+xaxis+";"+yaxis,nbins,min,max,20,0,ymax);
  h_axis->Draw();
  
  h_pt_full->SetLineColor(kBlue);
  h_pt_full->SetMarkerColor(kBlue);

  h_pt_fast->Draw("pe same");
  h_pt_full->Draw("pe same");
  
  TLegend* leg = new TLegend(0.65,0.3,0.96,0.5);
  leg->AddEntry(h_pt_fast,"Delphes","pe");
  leg->AddEntry(h_pt_full,"Fullsim","pe");
  leg->Draw("same");
  
  c->SaveAs(saveas+".pdf");
  c->Close();
  h_pt_full->Delete();
  h_pt_fast->Delete();
  
}


void compareKinematics () {

  setTDRStyle();

  TH1::SetDefaultSumw2();

  TChain *t_full = new TChain("Events");
  t_full->Add("/home/gzevi/VBF_HToZZTo4L_M125_14TeV_200PU/CMS4/merged_ntuple_1.root");
  t_full->SetBranchStatus("*",1);
  TChain *t_delphes = new TChain("Delphes");
  t_delphes->Add("/home/gzevi/VBF_HToZZTo4L_M125_14TeV_200PU/DelphesSkims/VBF_HToZZTo4L_M125_14TeV.root");

  TCut sieieEB = "els_sigmaIEtaIEta_full5x5[0]<0.009996";
  TCut hoeEB   = "els_hOverE[0]<0.253";
  TCut detaEB  = "fabs(els_dEtaIn[0] - els_etaSC[0] + els_scSeedEta[0])  <0.00311";
  TCut dphiEB  = "els_dPhiIn[0]<0.103";
  TCut eOpEB   = "abs((1./els_ecalEnergy[0]) - (els_eOverPIn[0]/els_ecalEnergy[0]))<0.134";
  TCut IsoEB  = "els_pfChargedHadronIso/els_p4.pt()<0.05";

  TCut sieieEE = "els_sigmaIEtaIEta_full5x5[0]<0.0298";
  TCut hoeEE   = "els_hOverE[0]<0.0878";
  TCut detaEE  = "fabs(els_dEtaIn[0] - els_etaSC[0] + els_scSeedEta[0])  <0.00609";
  TCut dphiEE  = "els_dPhiIn[0]<0.103";
  TCut eOpEE   = "abs((1./els_ecalEnergy[0]) - (els_eOverPIn[0]/els_ecalEnergy[0]))<0.13";
  TCut IsoEE  = IsoEB;

  TCut IDEB = sieieEB+hoeEB+detaEB+dphiEB+eOpEB+IsoEB;
  TCut IDEE = sieieEE+hoeEE+detaEE+dphiEE+eOpEE+IsoEE;

  TString elePtDelphes = "Electron.PT";
  TString elePtFull = "els_p4.pt()";
  TCut eleIsoDelphes = "Electron.IsolationVarRhoCorr/Electron.PT<0.1";
  TCut eleIsoFull = IsoEB;
   
  //void makeOverlay( TChain* t_full, TChain* t_fast, TString var_full, TString var_fast, TCut cut_full, TCut cut_fast, int nbins, float min, float max, TString xaxis, TString yaxis, TString saveas) {
  makeOverlay(t_full, t_delphes, elePtFull, elePtDelphes, eleIsoFull, eleIsoDelphes, 50, 0,100, "Electron PT", "Events", "ElePT");


  TString jetPtDelphes = "JetPUPPI.PT";
  TString jetPtFull = "pfjets_puppi_p4.pt()";
  TCut jetCutDelphes = "JetPUPPI.PT>30";
  TCut jetCutFull = "pfjets_puppi_p4.pt()>30";

  makeOverlay(t_full, t_delphes, jetPtFull, jetPtDelphes, jetCutFull, jetCutDelphes, 100, 0,500, "Jet PT", "Events", "JetPT");

  TString jetEtaDelphes = "JetPUPPI.Eta";
  TString jetEtaFull = "pfjets_puppi_p4.eta()";

  makeOverlay(t_full, t_delphes, jetEtaFull, jetEtaDelphes, jetCutFull, jetCutDelphes, 100, -5,5, "Jet Eta", "Events", "JetEta");


  TString muPtDelphes = "MuonTight.PT";
  TString muPtFull = "mus_p4.pt()";
  TCut muIsoDelphes = "MuonTight.IsolationVarRhoCorr/MuonTight.PT<0.1";
  TCut muIsoFull = "mus_isoR03_pf_ChargedHadronPt/mus_p4.pt()<0.05";
   
  //void makeOverlay( TChain* t_full, TChain* t_fast, TString var_full, TString var_fast, TCut cut_full, TCut cut_fast, int nbins, float min, float max, TString xaxis, TString yaxis, TString saveas) {
  makeOverlay(t_full, t_delphes, muPtFull, muPtDelphes, muIsoFull, muIsoDelphes, 50, 0,100, "Muon PT", "Events", "MuPT");


}

