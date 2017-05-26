//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Fri May 26 13:07:37 2017 by ROOT version 6.06/06
// from TTree Delphes/Analysis tree
// found on file: /home/gzevi/C2N4delphes/C2N4full.root
//////////////////////////////////////////////////////////

#ifndef Delphes_h
#define Delphes_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include "TClonesArray.h"
#include "TObject.h"
#include "TLorentzVector.h"
#include "TRefArray.h"
#include "TRef.h"

class Delphes {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.
   static const Int_t kMaxEvent = 1;
   static const Int_t kMaxEventLHEF = 1;
   static const Int_t kMaxWeightLHEF = 1;
   static const Int_t kMaxParticle = 60;
   static const Int_t kMaxVertex = 263;
   static const Int_t kMaxGenJet = 19;
   static const Int_t kMaxGenJetAK8 = 6;
   static const Int_t kMaxGenMissingET = 1;
   static const Int_t kMaxPhoton = 24;
   static const Int_t kMaxElectron = 4;
   static const Int_t kMaxMuonLoose = 3;
   static const Int_t kMaxMuonTight = 3;
   static const Int_t kMaxJet = 177;
   static const Int_t kMaxJetPUPPI = 15;
   static const Int_t kMaxJetAK8 = 33;
   static const Int_t kMaxJetPUPPIAK8 = 5;
   static const Int_t kMaxMissingET = 1;
   static const Int_t kMaxPuppiMissingET = 1;
   static const Int_t kMaxGenPileUpMissingET = 1;
   static const Int_t kMaxScalarHT = 1;

   // Declaration of leaf types
   Int_t           Event_;
   UInt_t          Event_fUniqueID[kMaxEvent];   //[Event_]
   UInt_t          Event_fBits[kMaxEvent];   //[Event_]
   Long64_t        Event_Number[kMaxEvent];   //[Event_]
   Float_t         Event_ReadTime[kMaxEvent];   //[Event_]
   Float_t         Event_ProcTime[kMaxEvent];   //[Event_]
   Int_t           Event_ProcessID[kMaxEvent];   //[Event_]
   Int_t           Event_MPI[kMaxEvent];   //[Event_]
   Float_t         Event_Weight[kMaxEvent];   //[Event_]
   Float_t         Event_Scale[kMaxEvent];   //[Event_]
   Float_t         Event_AlphaQED[kMaxEvent];   //[Event_]
   Float_t         Event_AlphaQCD[kMaxEvent];   //[Event_]
   Int_t           Event_ID1[kMaxEvent];   //[Event_]
   Int_t           Event_ID2[kMaxEvent];   //[Event_]
   Float_t         Event_X1[kMaxEvent];   //[Event_]
   Float_t         Event_X2[kMaxEvent];   //[Event_]
   Float_t         Event_ScalePDF[kMaxEvent];   //[Event_]
   Float_t         Event_PDF1[kMaxEvent];   //[Event_]
   Float_t         Event_PDF2[kMaxEvent];   //[Event_]
   Int_t           Event_size;
   Int_t           EventLHEF_;
   UInt_t          EventLHEF_fUniqueID[kMaxEventLHEF];   //[EventLHEF_]
   UInt_t          EventLHEF_fBits[kMaxEventLHEF];   //[EventLHEF_]
   Long64_t        EventLHEF_Number[kMaxEventLHEF];   //[EventLHEF_]
   Float_t         EventLHEF_ReadTime[kMaxEventLHEF];   //[EventLHEF_]
   Float_t         EventLHEF_ProcTime[kMaxEventLHEF];   //[EventLHEF_]
   Int_t           EventLHEF_ProcessID[kMaxEventLHEF];   //[EventLHEF_]
   Float_t         EventLHEF_Weight[kMaxEventLHEF];   //[EventLHEF_]
   Float_t         EventLHEF_ScalePDF[kMaxEventLHEF];   //[EventLHEF_]
   Float_t         EventLHEF_AlphaQED[kMaxEventLHEF];   //[EventLHEF_]
   Float_t         EventLHEF_AlphaQCD[kMaxEventLHEF];   //[EventLHEF_]
   Int_t           EventLHEF_size;
   Int_t           WeightLHEF_;
   UInt_t          WeightLHEF_fUniqueID[kMaxWeightLHEF];   //[WeightLHEF_]
   UInt_t          WeightLHEF_fBits[kMaxWeightLHEF];   //[WeightLHEF_]
   Int_t           WeightLHEF_ID[kMaxWeightLHEF];   //[WeightLHEF_]
   Float_t         WeightLHEF_Weight[kMaxWeightLHEF];   //[WeightLHEF_]
   Int_t           WeightLHEF_size;
   Int_t           Particle_;
   UInt_t          Particle_fUniqueID[kMaxParticle];   //[Particle_]
   UInt_t          Particle_fBits[kMaxParticle];   //[Particle_]
   Int_t           Particle_PID[kMaxParticle];   //[Particle_]
   Int_t           Particle_Status[kMaxParticle];   //[Particle_]
   Int_t           Particle_IsPU[kMaxParticle];   //[Particle_]
   Int_t           Particle_M1[kMaxParticle];   //[Particle_]
   Int_t           Particle_M2[kMaxParticle];   //[Particle_]
   Int_t           Particle_D1[kMaxParticle];   //[Particle_]
   Int_t           Particle_D2[kMaxParticle];   //[Particle_]
   Int_t           Particle_Charge[kMaxParticle];   //[Particle_]
   Float_t         Particle_Mass[kMaxParticle];   //[Particle_]
   Float_t         Particle_E[kMaxParticle];   //[Particle_]
   Float_t         Particle_Px[kMaxParticle];   //[Particle_]
   Float_t         Particle_Py[kMaxParticle];   //[Particle_]
   Float_t         Particle_Pz[kMaxParticle];   //[Particle_]
   Float_t         Particle_PT[kMaxParticle];   //[Particle_]
   Float_t         Particle_Eta[kMaxParticle];   //[Particle_]
   Float_t         Particle_Phi[kMaxParticle];   //[Particle_]
   Float_t         Particle_Rapidity[kMaxParticle];   //[Particle_]
   Float_t         Particle_T[kMaxParticle];   //[Particle_]
   Float_t         Particle_X[kMaxParticle];   //[Particle_]
   Float_t         Particle_Y[kMaxParticle];   //[Particle_]
   Float_t         Particle_Z[kMaxParticle];   //[Particle_]
   Int_t           Particle_size;
   Int_t           Vertex_;
   UInt_t          Vertex_fUniqueID[kMaxVertex];   //[Vertex_]
   UInt_t          Vertex_fBits[kMaxVertex];   //[Vertex_]
   Float_t         Vertex_T[kMaxVertex];   //[Vertex_]
   Float_t         Vertex_X[kMaxVertex];   //[Vertex_]
   Float_t         Vertex_Y[kMaxVertex];   //[Vertex_]
   Float_t         Vertex_Z[kMaxVertex];   //[Vertex_]
   Int_t           Vertex_size;
   Int_t           GenJet_;
   UInt_t          GenJet_fUniqueID[kMaxGenJet];   //[GenJet_]
   UInt_t          GenJet_fBits[kMaxGenJet];   //[GenJet_]
   Float_t         GenJet_PT[kMaxGenJet];   //[GenJet_]
   Float_t         GenJet_Eta[kMaxGenJet];   //[GenJet_]
   Float_t         GenJet_Phi[kMaxGenJet];   //[GenJet_]
   Float_t         GenJet_T[kMaxGenJet];   //[GenJet_]
   Float_t         GenJet_Mass[kMaxGenJet];   //[GenJet_]
   Float_t         GenJet_DeltaEta[kMaxGenJet];   //[GenJet_]
   Float_t         GenJet_DeltaPhi[kMaxGenJet];   //[GenJet_]
   UInt_t          GenJet_Flavor[kMaxGenJet];   //[GenJet_]
   UInt_t          GenJet_FlavorAlgo[kMaxGenJet];   //[GenJet_]
   UInt_t          GenJet_FlavorPhys[kMaxGenJet];   //[GenJet_]
   UInt_t          GenJet_BTag[kMaxGenJet];   //[GenJet_]
   UInt_t          GenJet_BTagAlgo[kMaxGenJet];   //[GenJet_]
   UInt_t          GenJet_BTagPhys[kMaxGenJet];   //[GenJet_]
   UInt_t          GenJet_TauTag[kMaxGenJet];   //[GenJet_]
   Int_t           GenJet_Charge[kMaxGenJet];   //[GenJet_]
   Float_t         GenJet_EhadOverEem[kMaxGenJet];   //[GenJet_]
   Int_t           GenJet_NCharged[kMaxGenJet];   //[GenJet_]
   Int_t           GenJet_NNeutrals[kMaxGenJet];   //[GenJet_]
   Float_t         GenJet_Beta[kMaxGenJet];   //[GenJet_]
   Float_t         GenJet_BetaStar[kMaxGenJet];   //[GenJet_]
   Float_t         GenJet_MeanSqDeltaR[kMaxGenJet];   //[GenJet_]
   Float_t         GenJet_PTD[kMaxGenJet];   //[GenJet_]
   Float_t         GenJet_FracPt[kMaxGenJet][5];   //[GenJet_]
   Float_t         GenJet_Tau[kMaxGenJet][5];   //[GenJet_]
   TLorentzVector  GenJet_TrimmedP4[5][kMaxGenJet];
   TLorentzVector  GenJet_PrunedP4[5][kMaxGenJet];
   TLorentzVector  GenJet_SoftDroppedP4[5][kMaxGenJet];
   Int_t           GenJet_NSubJetsTrimmed[kMaxGenJet];   //[GenJet_]
   Int_t           GenJet_NSubJetsPruned[kMaxGenJet];   //[GenJet_]
   Int_t           GenJet_NSubJetsSoftDropped[kMaxGenJet];   //[GenJet_]
   TRefArray       GenJet_Constituents[kMaxGenJet];
   TRefArray       GenJet_Particles[kMaxGenJet];
   TLorentzVector  GenJet_Area[kMaxGenJet];
   Int_t           GenJet_size;
   Int_t           GenJetAK8_;
   UInt_t          GenJetAK8_fUniqueID[kMaxGenJetAK8];   //[GenJetAK8_]
   UInt_t          GenJetAK8_fBits[kMaxGenJetAK8];   //[GenJetAK8_]
   Float_t         GenJetAK8_PT[kMaxGenJetAK8];   //[GenJetAK8_]
   Float_t         GenJetAK8_Eta[kMaxGenJetAK8];   //[GenJetAK8_]
   Float_t         GenJetAK8_Phi[kMaxGenJetAK8];   //[GenJetAK8_]
   Float_t         GenJetAK8_T[kMaxGenJetAK8];   //[GenJetAK8_]
   Float_t         GenJetAK8_Mass[kMaxGenJetAK8];   //[GenJetAK8_]
   Float_t         GenJetAK8_DeltaEta[kMaxGenJetAK8];   //[GenJetAK8_]
   Float_t         GenJetAK8_DeltaPhi[kMaxGenJetAK8];   //[GenJetAK8_]
   UInt_t          GenJetAK8_Flavor[kMaxGenJetAK8];   //[GenJetAK8_]
   UInt_t          GenJetAK8_FlavorAlgo[kMaxGenJetAK8];   //[GenJetAK8_]
   UInt_t          GenJetAK8_FlavorPhys[kMaxGenJetAK8];   //[GenJetAK8_]
   UInt_t          GenJetAK8_BTag[kMaxGenJetAK8];   //[GenJetAK8_]
   UInt_t          GenJetAK8_BTagAlgo[kMaxGenJetAK8];   //[GenJetAK8_]
   UInt_t          GenJetAK8_BTagPhys[kMaxGenJetAK8];   //[GenJetAK8_]
   UInt_t          GenJetAK8_TauTag[kMaxGenJetAK8];   //[GenJetAK8_]
   Int_t           GenJetAK8_Charge[kMaxGenJetAK8];   //[GenJetAK8_]
   Float_t         GenJetAK8_EhadOverEem[kMaxGenJetAK8];   //[GenJetAK8_]
   Int_t           GenJetAK8_NCharged[kMaxGenJetAK8];   //[GenJetAK8_]
   Int_t           GenJetAK8_NNeutrals[kMaxGenJetAK8];   //[GenJetAK8_]
   Float_t         GenJetAK8_Beta[kMaxGenJetAK8];   //[GenJetAK8_]
   Float_t         GenJetAK8_BetaStar[kMaxGenJetAK8];   //[GenJetAK8_]
   Float_t         GenJetAK8_MeanSqDeltaR[kMaxGenJetAK8];   //[GenJetAK8_]
   Float_t         GenJetAK8_PTD[kMaxGenJetAK8];   //[GenJetAK8_]
   Float_t         GenJetAK8_FracPt[kMaxGenJetAK8][5];   //[GenJetAK8_]
   Float_t         GenJetAK8_Tau[kMaxGenJetAK8][5];   //[GenJetAK8_]
   TLorentzVector  GenJetAK8_TrimmedP4[5][kMaxGenJetAK8];
   TLorentzVector  GenJetAK8_PrunedP4[5][kMaxGenJetAK8];
   TLorentzVector  GenJetAK8_SoftDroppedP4[5][kMaxGenJetAK8];
   Int_t           GenJetAK8_NSubJetsTrimmed[kMaxGenJetAK8];   //[GenJetAK8_]
   Int_t           GenJetAK8_NSubJetsPruned[kMaxGenJetAK8];   //[GenJetAK8_]
   Int_t           GenJetAK8_NSubJetsSoftDropped[kMaxGenJetAK8];   //[GenJetAK8_]
   TRefArray       GenJetAK8_Constituents[kMaxGenJetAK8];
   TRefArray       GenJetAK8_Particles[kMaxGenJetAK8];
   TLorentzVector  GenJetAK8_Area[kMaxGenJetAK8];
   Int_t           GenJetAK8_size;
   Int_t           GenMissingET_;
   UInt_t          GenMissingET_fUniqueID[kMaxGenMissingET];   //[GenMissingET_]
   UInt_t          GenMissingET_fBits[kMaxGenMissingET];   //[GenMissingET_]
   Float_t         GenMissingET_MET[kMaxGenMissingET];   //[GenMissingET_]
   Float_t         GenMissingET_Eta[kMaxGenMissingET];   //[GenMissingET_]
   Float_t         GenMissingET_Phi[kMaxGenMissingET];   //[GenMissingET_]
   Int_t           GenMissingET_size;
   Int_t           Photon_;
   UInt_t          Photon_fUniqueID[kMaxPhoton];   //[Photon_]
   UInt_t          Photon_fBits[kMaxPhoton];   //[Photon_]
   Float_t         Photon_PT[kMaxPhoton];   //[Photon_]
   Float_t         Photon_Eta[kMaxPhoton];   //[Photon_]
   Float_t         Photon_Phi[kMaxPhoton];   //[Photon_]
   Float_t         Photon_E[kMaxPhoton];   //[Photon_]
   Float_t         Photon_T[kMaxPhoton];   //[Photon_]
   Float_t         Photon_EhadOverEem[kMaxPhoton];   //[Photon_]
   TRefArray       Photon_Particles[kMaxPhoton];
   Float_t         Photon_IsolationVar[kMaxPhoton];   //[Photon_]
   Float_t         Photon_IsolationVarRhoCorr[kMaxPhoton];   //[Photon_]
   Float_t         Photon_SumPtCharged[kMaxPhoton];   //[Photon_]
   Float_t         Photon_SumPtNeutral[kMaxPhoton];   //[Photon_]
   Float_t         Photon_SumPtChargedPU[kMaxPhoton];   //[Photon_]
   Float_t         Photon_SumPt[kMaxPhoton];   //[Photon_]
   Int_t           Photon_size;
   Int_t           Electron_;
   UInt_t          Electron_fUniqueID[kMaxElectron];   //[Electron_]
   UInt_t          Electron_fBits[kMaxElectron];   //[Electron_]
   Float_t         Electron_PT[kMaxElectron];   //[Electron_]
   Float_t         Electron_Eta[kMaxElectron];   //[Electron_]
   Float_t         Electron_Phi[kMaxElectron];   //[Electron_]
   Float_t         Electron_T[kMaxElectron];   //[Electron_]
   Int_t           Electron_Charge[kMaxElectron];   //[Electron_]
   Float_t         Electron_EhadOverEem[kMaxElectron];   //[Electron_]
   TRef            Electron_Particle[kMaxElectron];
   Float_t         Electron_IsolationVar[kMaxElectron];   //[Electron_]
   Float_t         Electron_IsolationVarRhoCorr[kMaxElectron];   //[Electron_]
   Float_t         Electron_SumPtCharged[kMaxElectron];   //[Electron_]
   Float_t         Electron_SumPtNeutral[kMaxElectron];   //[Electron_]
   Float_t         Electron_SumPtChargedPU[kMaxElectron];   //[Electron_]
   Float_t         Electron_SumPt[kMaxElectron];   //[Electron_]
   Int_t           Electron_size;
   Int_t           MuonLoose_;
   UInt_t          MuonLoose_fUniqueID[kMaxMuonLoose];   //[MuonLoose_]
   UInt_t          MuonLoose_fBits[kMaxMuonLoose];   //[MuonLoose_]
   Float_t         MuonLoose_PT[kMaxMuonLoose];   //[MuonLoose_]
   Float_t         MuonLoose_Eta[kMaxMuonLoose];   //[MuonLoose_]
   Float_t         MuonLoose_Phi[kMaxMuonLoose];   //[MuonLoose_]
   Float_t         MuonLoose_T[kMaxMuonLoose];   //[MuonLoose_]
   Int_t           MuonLoose_Charge[kMaxMuonLoose];   //[MuonLoose_]
   TRef            MuonLoose_Particle[kMaxMuonLoose];
   Float_t         MuonLoose_IsolationVar[kMaxMuonLoose];   //[MuonLoose_]
   Float_t         MuonLoose_IsolationVarRhoCorr[kMaxMuonLoose];   //[MuonLoose_]
   Float_t         MuonLoose_SumPtCharged[kMaxMuonLoose];   //[MuonLoose_]
   Float_t         MuonLoose_SumPtNeutral[kMaxMuonLoose];   //[MuonLoose_]
   Float_t         MuonLoose_SumPtChargedPU[kMaxMuonLoose];   //[MuonLoose_]
   Float_t         MuonLoose_SumPt[kMaxMuonLoose];   //[MuonLoose_]
   Int_t           MuonLoose_size;
   Int_t           MuonTight_;
   UInt_t          MuonTight_fUniqueID[kMaxMuonTight];   //[MuonTight_]
   UInt_t          MuonTight_fBits[kMaxMuonTight];   //[MuonTight_]
   Float_t         MuonTight_PT[kMaxMuonTight];   //[MuonTight_]
   Float_t         MuonTight_Eta[kMaxMuonTight];   //[MuonTight_]
   Float_t         MuonTight_Phi[kMaxMuonTight];   //[MuonTight_]
   Float_t         MuonTight_T[kMaxMuonTight];   //[MuonTight_]
   Int_t           MuonTight_Charge[kMaxMuonTight];   //[MuonTight_]
   TRef            MuonTight_Particle[kMaxMuonTight];
   Float_t         MuonTight_IsolationVar[kMaxMuonTight];   //[MuonTight_]
   Float_t         MuonTight_IsolationVarRhoCorr[kMaxMuonTight];   //[MuonTight_]
   Float_t         MuonTight_SumPtCharged[kMaxMuonTight];   //[MuonTight_]
   Float_t         MuonTight_SumPtNeutral[kMaxMuonTight];   //[MuonTight_]
   Float_t         MuonTight_SumPtChargedPU[kMaxMuonTight];   //[MuonTight_]
   Float_t         MuonTight_SumPt[kMaxMuonTight];   //[MuonTight_]
   Int_t           MuonTight_size;
   Int_t           Jet_;
   UInt_t          Jet_fUniqueID[kMaxJet];   //[Jet_]
   UInt_t          Jet_fBits[kMaxJet];   //[Jet_]
   Float_t         Jet_PT[kMaxJet];   //[Jet_]
   Float_t         Jet_Eta[kMaxJet];   //[Jet_]
   Float_t         Jet_Phi[kMaxJet];   //[Jet_]
   Float_t         Jet_T[kMaxJet];   //[Jet_]
   Float_t         Jet_Mass[kMaxJet];   //[Jet_]
   Float_t         Jet_DeltaEta[kMaxJet];   //[Jet_]
   Float_t         Jet_DeltaPhi[kMaxJet];   //[Jet_]
   UInt_t          Jet_Flavor[kMaxJet];   //[Jet_]
   UInt_t          Jet_FlavorAlgo[kMaxJet];   //[Jet_]
   UInt_t          Jet_FlavorPhys[kMaxJet];   //[Jet_]
   UInt_t          Jet_BTag[kMaxJet];   //[Jet_]
   UInt_t          Jet_BTagAlgo[kMaxJet];   //[Jet_]
   UInt_t          Jet_BTagPhys[kMaxJet];   //[Jet_]
   UInt_t          Jet_TauTag[kMaxJet];   //[Jet_]
   Int_t           Jet_Charge[kMaxJet];   //[Jet_]
   Float_t         Jet_EhadOverEem[kMaxJet];   //[Jet_]
   Int_t           Jet_NCharged[kMaxJet];   //[Jet_]
   Int_t           Jet_NNeutrals[kMaxJet];   //[Jet_]
   Float_t         Jet_Beta[kMaxJet];   //[Jet_]
   Float_t         Jet_BetaStar[kMaxJet];   //[Jet_]
   Float_t         Jet_MeanSqDeltaR[kMaxJet];   //[Jet_]
   Float_t         Jet_PTD[kMaxJet];   //[Jet_]
   Float_t         Jet_FracPt[kMaxJet][5];   //[Jet_]
   Float_t         Jet_Tau[kMaxJet][5];   //[Jet_]
   TLorentzVector  Jet_TrimmedP4[5][kMaxJet];
   TLorentzVector  Jet_PrunedP4[5][kMaxJet];
   TLorentzVector  Jet_SoftDroppedP4[5][kMaxJet];
   Int_t           Jet_NSubJetsTrimmed[kMaxJet];   //[Jet_]
   Int_t           Jet_NSubJetsPruned[kMaxJet];   //[Jet_]
   Int_t           Jet_NSubJetsSoftDropped[kMaxJet];   //[Jet_]
   TRefArray       Jet_Constituents[kMaxJet];
   TRefArray       Jet_Particles[kMaxJet];
   TLorentzVector  Jet_Area[kMaxJet];
   Int_t           Jet_size;
   Int_t           JetPUPPI_;
   UInt_t          JetPUPPI_fUniqueID[kMaxJetPUPPI];   //[JetPUPPI_]
   UInt_t          JetPUPPI_fBits[kMaxJetPUPPI];   //[JetPUPPI_]
   Float_t         JetPUPPI_PT[kMaxJetPUPPI];   //[JetPUPPI_]
   Float_t         JetPUPPI_Eta[kMaxJetPUPPI];   //[JetPUPPI_]
   Float_t         JetPUPPI_Phi[kMaxJetPUPPI];   //[JetPUPPI_]
   Float_t         JetPUPPI_T[kMaxJetPUPPI];   //[JetPUPPI_]
   Float_t         JetPUPPI_Mass[kMaxJetPUPPI];   //[JetPUPPI_]
   Float_t         JetPUPPI_DeltaEta[kMaxJetPUPPI];   //[JetPUPPI_]
   Float_t         JetPUPPI_DeltaPhi[kMaxJetPUPPI];   //[JetPUPPI_]
   UInt_t          JetPUPPI_Flavor[kMaxJetPUPPI];   //[JetPUPPI_]
   UInt_t          JetPUPPI_FlavorAlgo[kMaxJetPUPPI];   //[JetPUPPI_]
   UInt_t          JetPUPPI_FlavorPhys[kMaxJetPUPPI];   //[JetPUPPI_]
   UInt_t          JetPUPPI_BTag[kMaxJetPUPPI];   //[JetPUPPI_]
   UInt_t          JetPUPPI_BTagAlgo[kMaxJetPUPPI];   //[JetPUPPI_]
   UInt_t          JetPUPPI_BTagPhys[kMaxJetPUPPI];   //[JetPUPPI_]
   UInt_t          JetPUPPI_TauTag[kMaxJetPUPPI];   //[JetPUPPI_]
   Int_t           JetPUPPI_Charge[kMaxJetPUPPI];   //[JetPUPPI_]
   Float_t         JetPUPPI_EhadOverEem[kMaxJetPUPPI];   //[JetPUPPI_]
   Int_t           JetPUPPI_NCharged[kMaxJetPUPPI];   //[JetPUPPI_]
   Int_t           JetPUPPI_NNeutrals[kMaxJetPUPPI];   //[JetPUPPI_]
   Float_t         JetPUPPI_Beta[kMaxJetPUPPI];   //[JetPUPPI_]
   Float_t         JetPUPPI_BetaStar[kMaxJetPUPPI];   //[JetPUPPI_]
   Float_t         JetPUPPI_MeanSqDeltaR[kMaxJetPUPPI];   //[JetPUPPI_]
   Float_t         JetPUPPI_PTD[kMaxJetPUPPI];   //[JetPUPPI_]
   Float_t         JetPUPPI_FracPt[kMaxJetPUPPI][5];   //[JetPUPPI_]
   Float_t         JetPUPPI_Tau[kMaxJetPUPPI][5];   //[JetPUPPI_]
   TLorentzVector  JetPUPPI_TrimmedP4[5][kMaxJetPUPPI];
   TLorentzVector  JetPUPPI_PrunedP4[5][kMaxJetPUPPI];
   TLorentzVector  JetPUPPI_SoftDroppedP4[5][kMaxJetPUPPI];
   Int_t           JetPUPPI_NSubJetsTrimmed[kMaxJetPUPPI];   //[JetPUPPI_]
   Int_t           JetPUPPI_NSubJetsPruned[kMaxJetPUPPI];   //[JetPUPPI_]
   Int_t           JetPUPPI_NSubJetsSoftDropped[kMaxJetPUPPI];   //[JetPUPPI_]
   TRefArray       JetPUPPI_Constituents[kMaxJetPUPPI];
   TRefArray       JetPUPPI_Particles[kMaxJetPUPPI];
   TLorentzVector  JetPUPPI_Area[kMaxJetPUPPI];
   Int_t           JetPUPPI_size;
   Int_t           JetAK8_;
   UInt_t          JetAK8_fUniqueID[kMaxJetAK8];   //[JetAK8_]
   UInt_t          JetAK8_fBits[kMaxJetAK8];   //[JetAK8_]
   Float_t         JetAK8_PT[kMaxJetAK8];   //[JetAK8_]
   Float_t         JetAK8_Eta[kMaxJetAK8];   //[JetAK8_]
   Float_t         JetAK8_Phi[kMaxJetAK8];   //[JetAK8_]
   Float_t         JetAK8_T[kMaxJetAK8];   //[JetAK8_]
   Float_t         JetAK8_Mass[kMaxJetAK8];   //[JetAK8_]
   Float_t         JetAK8_DeltaEta[kMaxJetAK8];   //[JetAK8_]
   Float_t         JetAK8_DeltaPhi[kMaxJetAK8];   //[JetAK8_]
   UInt_t          JetAK8_Flavor[kMaxJetAK8];   //[JetAK8_]
   UInt_t          JetAK8_FlavorAlgo[kMaxJetAK8];   //[JetAK8_]
   UInt_t          JetAK8_FlavorPhys[kMaxJetAK8];   //[JetAK8_]
   UInt_t          JetAK8_BTag[kMaxJetAK8];   //[JetAK8_]
   UInt_t          JetAK8_BTagAlgo[kMaxJetAK8];   //[JetAK8_]
   UInt_t          JetAK8_BTagPhys[kMaxJetAK8];   //[JetAK8_]
   UInt_t          JetAK8_TauTag[kMaxJetAK8];   //[JetAK8_]
   Int_t           JetAK8_Charge[kMaxJetAK8];   //[JetAK8_]
   Float_t         JetAK8_EhadOverEem[kMaxJetAK8];   //[JetAK8_]
   Int_t           JetAK8_NCharged[kMaxJetAK8];   //[JetAK8_]
   Int_t           JetAK8_NNeutrals[kMaxJetAK8];   //[JetAK8_]
   Float_t         JetAK8_Beta[kMaxJetAK8];   //[JetAK8_]
   Float_t         JetAK8_BetaStar[kMaxJetAK8];   //[JetAK8_]
   Float_t         JetAK8_MeanSqDeltaR[kMaxJetAK8];   //[JetAK8_]
   Float_t         JetAK8_PTD[kMaxJetAK8];   //[JetAK8_]
   Float_t         JetAK8_FracPt[kMaxJetAK8][5];   //[JetAK8_]
   Float_t         JetAK8_Tau[kMaxJetAK8][5];   //[JetAK8_]
   TLorentzVector  JetAK8_TrimmedP4[5][kMaxJetAK8];
   TLorentzVector  JetAK8_PrunedP4[5][kMaxJetAK8];
   TLorentzVector  JetAK8_SoftDroppedP4[5][kMaxJetAK8];
   Int_t           JetAK8_NSubJetsTrimmed[kMaxJetAK8];   //[JetAK8_]
   Int_t           JetAK8_NSubJetsPruned[kMaxJetAK8];   //[JetAK8_]
   Int_t           JetAK8_NSubJetsSoftDropped[kMaxJetAK8];   //[JetAK8_]
   TRefArray       JetAK8_Constituents[kMaxJetAK8];
   TRefArray       JetAK8_Particles[kMaxJetAK8];
   TLorentzVector  JetAK8_Area[kMaxJetAK8];
   Int_t           JetAK8_size;
   Int_t           JetPUPPIAK8_;
   UInt_t          JetPUPPIAK8_fUniqueID[kMaxJetPUPPIAK8];   //[JetPUPPIAK8_]
   UInt_t          JetPUPPIAK8_fBits[kMaxJetPUPPIAK8];   //[JetPUPPIAK8_]
   Float_t         JetPUPPIAK8_PT[kMaxJetPUPPIAK8];   //[JetPUPPIAK8_]
   Float_t         JetPUPPIAK8_Eta[kMaxJetPUPPIAK8];   //[JetPUPPIAK8_]
   Float_t         JetPUPPIAK8_Phi[kMaxJetPUPPIAK8];   //[JetPUPPIAK8_]
   Float_t         JetPUPPIAK8_T[kMaxJetPUPPIAK8];   //[JetPUPPIAK8_]
   Float_t         JetPUPPIAK8_Mass[kMaxJetPUPPIAK8];   //[JetPUPPIAK8_]
   Float_t         JetPUPPIAK8_DeltaEta[kMaxJetPUPPIAK8];   //[JetPUPPIAK8_]
   Float_t         JetPUPPIAK8_DeltaPhi[kMaxJetPUPPIAK8];   //[JetPUPPIAK8_]
   UInt_t          JetPUPPIAK8_Flavor[kMaxJetPUPPIAK8];   //[JetPUPPIAK8_]
   UInt_t          JetPUPPIAK8_FlavorAlgo[kMaxJetPUPPIAK8];   //[JetPUPPIAK8_]
   UInt_t          JetPUPPIAK8_FlavorPhys[kMaxJetPUPPIAK8];   //[JetPUPPIAK8_]
   UInt_t          JetPUPPIAK8_BTag[kMaxJetPUPPIAK8];   //[JetPUPPIAK8_]
   UInt_t          JetPUPPIAK8_BTagAlgo[kMaxJetPUPPIAK8];   //[JetPUPPIAK8_]
   UInt_t          JetPUPPIAK8_BTagPhys[kMaxJetPUPPIAK8];   //[JetPUPPIAK8_]
   UInt_t          JetPUPPIAK8_TauTag[kMaxJetPUPPIAK8];   //[JetPUPPIAK8_]
   Int_t           JetPUPPIAK8_Charge[kMaxJetPUPPIAK8];   //[JetPUPPIAK8_]
   Float_t         JetPUPPIAK8_EhadOverEem[kMaxJetPUPPIAK8];   //[JetPUPPIAK8_]
   Int_t           JetPUPPIAK8_NCharged[kMaxJetPUPPIAK8];   //[JetPUPPIAK8_]
   Int_t           JetPUPPIAK8_NNeutrals[kMaxJetPUPPIAK8];   //[JetPUPPIAK8_]
   Float_t         JetPUPPIAK8_Beta[kMaxJetPUPPIAK8];   //[JetPUPPIAK8_]
   Float_t         JetPUPPIAK8_BetaStar[kMaxJetPUPPIAK8];   //[JetPUPPIAK8_]
   Float_t         JetPUPPIAK8_MeanSqDeltaR[kMaxJetPUPPIAK8];   //[JetPUPPIAK8_]
   Float_t         JetPUPPIAK8_PTD[kMaxJetPUPPIAK8];   //[JetPUPPIAK8_]
   Float_t         JetPUPPIAK8_FracPt[kMaxJetPUPPIAK8][5];   //[JetPUPPIAK8_]
   Float_t         JetPUPPIAK8_Tau[kMaxJetPUPPIAK8][5];   //[JetPUPPIAK8_]
   TLorentzVector  JetPUPPIAK8_TrimmedP4[5][kMaxJetPUPPIAK8];
   TLorentzVector  JetPUPPIAK8_PrunedP4[5][kMaxJetPUPPIAK8];
   TLorentzVector  JetPUPPIAK8_SoftDroppedP4[5][kMaxJetPUPPIAK8];
   Int_t           JetPUPPIAK8_NSubJetsTrimmed[kMaxJetPUPPIAK8];   //[JetPUPPIAK8_]
   Int_t           JetPUPPIAK8_NSubJetsPruned[kMaxJetPUPPIAK8];   //[JetPUPPIAK8_]
   Int_t           JetPUPPIAK8_NSubJetsSoftDropped[kMaxJetPUPPIAK8];   //[JetPUPPIAK8_]
   TRefArray       JetPUPPIAK8_Constituents[kMaxJetPUPPIAK8];
   TRefArray       JetPUPPIAK8_Particles[kMaxJetPUPPIAK8];
   TLorentzVector  JetPUPPIAK8_Area[kMaxJetPUPPIAK8];
   Int_t           JetPUPPIAK8_size;
   Int_t           MissingET_;
   UInt_t          MissingET_fUniqueID[kMaxMissingET];   //[MissingET_]
   UInt_t          MissingET_fBits[kMaxMissingET];   //[MissingET_]
   Float_t         MissingET_MET[kMaxMissingET];   //[MissingET_]
   Float_t         MissingET_Eta[kMaxMissingET];   //[MissingET_]
   Float_t         MissingET_Phi[kMaxMissingET];   //[MissingET_]
   Int_t           MissingET_size;
   Int_t           PuppiMissingET_;
   UInt_t          PuppiMissingET_fUniqueID[kMaxPuppiMissingET];   //[PuppiMissingET_]
   UInt_t          PuppiMissingET_fBits[kMaxPuppiMissingET];   //[PuppiMissingET_]
   Float_t         PuppiMissingET_MET[kMaxPuppiMissingET];   //[PuppiMissingET_]
   Float_t         PuppiMissingET_Eta[kMaxPuppiMissingET];   //[PuppiMissingET_]
   Float_t         PuppiMissingET_Phi[kMaxPuppiMissingET];   //[PuppiMissingET_]
   Int_t           PuppiMissingET_size;
   Int_t           GenPileUpMissingET_;
   UInt_t          GenPileUpMissingET_fUniqueID[kMaxGenPileUpMissingET];   //[GenPileUpMissingET_]
   UInt_t          GenPileUpMissingET_fBits[kMaxGenPileUpMissingET];   //[GenPileUpMissingET_]
   Float_t         GenPileUpMissingET_MET[kMaxGenPileUpMissingET];   //[GenPileUpMissingET_]
   Float_t         GenPileUpMissingET_Eta[kMaxGenPileUpMissingET];   //[GenPileUpMissingET_]
   Float_t         GenPileUpMissingET_Phi[kMaxGenPileUpMissingET];   //[GenPileUpMissingET_]
   Int_t           GenPileUpMissingET_size;
   Int_t           ScalarHT_;
   UInt_t          ScalarHT_fUniqueID[kMaxScalarHT];   //[ScalarHT_]
   UInt_t          ScalarHT_fBits[kMaxScalarHT];   //[ScalarHT_]
   Float_t         ScalarHT_HT[kMaxScalarHT];   //[ScalarHT_]
   Int_t           ScalarHT_size;

   // List of branches
   TBranch        *b_Event_;   //!
   TBranch        *b_Event_fUniqueID;   //!
   TBranch        *b_Event_fBits;   //!
   TBranch        *b_Event_Number;   //!
   TBranch        *b_Event_ReadTime;   //!
   TBranch        *b_Event_ProcTime;   //!
   TBranch        *b_Event_ProcessID;   //!
   TBranch        *b_Event_MPI;   //!
   TBranch        *b_Event_Weight;   //!
   TBranch        *b_Event_Scale;   //!
   TBranch        *b_Event_AlphaQED;   //!
   TBranch        *b_Event_AlphaQCD;   //!
   TBranch        *b_Event_ID1;   //!
   TBranch        *b_Event_ID2;   //!
   TBranch        *b_Event_X1;   //!
   TBranch        *b_Event_X2;   //!
   TBranch        *b_Event_ScalePDF;   //!
   TBranch        *b_Event_PDF1;   //!
   TBranch        *b_Event_PDF2;   //!
   TBranch        *b_Event_size;   //!
   TBranch        *b_EventLHEF_;   //!
   TBranch        *b_EventLHEF_fUniqueID;   //!
   TBranch        *b_EventLHEF_fBits;   //!
   TBranch        *b_EventLHEF_Number;   //!
   TBranch        *b_EventLHEF_ReadTime;   //!
   TBranch        *b_EventLHEF_ProcTime;   //!
   TBranch        *b_EventLHEF_ProcessID;   //!
   TBranch        *b_EventLHEF_Weight;   //!
   TBranch        *b_EventLHEF_ScalePDF;   //!
   TBranch        *b_EventLHEF_AlphaQED;   //!
   TBranch        *b_EventLHEF_AlphaQCD;   //!
   TBranch        *b_EventLHEF_size;   //!
   TBranch        *b_WeightLHEF_;   //!
   TBranch        *b_WeightLHEF_fUniqueID;   //!
   TBranch        *b_WeightLHEF_fBits;   //!
   TBranch        *b_WeightLHEF_ID;   //!
   TBranch        *b_WeightLHEF_Weight;   //!
   TBranch        *b_WeightLHEF_size;   //!
   TBranch        *b_Particle_;   //!
   TBranch        *b_Particle_fUniqueID;   //!
   TBranch        *b_Particle_fBits;   //!
   TBranch        *b_Particle_PID;   //!
   TBranch        *b_Particle_Status;   //!
   TBranch        *b_Particle_IsPU;   //!
   TBranch        *b_Particle_M1;   //!
   TBranch        *b_Particle_M2;   //!
   TBranch        *b_Particle_D1;   //!
   TBranch        *b_Particle_D2;   //!
   TBranch        *b_Particle_Charge;   //!
   TBranch        *b_Particle_Mass;   //!
   TBranch        *b_Particle_E;   //!
   TBranch        *b_Particle_Px;   //!
   TBranch        *b_Particle_Py;   //!
   TBranch        *b_Particle_Pz;   //!
   TBranch        *b_Particle_PT;   //!
   TBranch        *b_Particle_Eta;   //!
   TBranch        *b_Particle_Phi;   //!
   TBranch        *b_Particle_Rapidity;   //!
   TBranch        *b_Particle_T;   //!
   TBranch        *b_Particle_X;   //!
   TBranch        *b_Particle_Y;   //!
   TBranch        *b_Particle_Z;   //!
   TBranch        *b_Particle_size;   //!
   TBranch        *b_Vertex_;   //!
   TBranch        *b_Vertex_fUniqueID;   //!
   TBranch        *b_Vertex_fBits;   //!
   TBranch        *b_Vertex_T;   //!
   TBranch        *b_Vertex_X;   //!
   TBranch        *b_Vertex_Y;   //!
   TBranch        *b_Vertex_Z;   //!
   TBranch        *b_Vertex_size;   //!
   TBranch        *b_GenJet_;   //!
   TBranch        *b_GenJet_fUniqueID;   //!
   TBranch        *b_GenJet_fBits;   //!
   TBranch        *b_GenJet_PT;   //!
   TBranch        *b_GenJet_Eta;   //!
   TBranch        *b_GenJet_Phi;   //!
   TBranch        *b_GenJet_T;   //!
   TBranch        *b_GenJet_Mass;   //!
   TBranch        *b_GenJet_DeltaEta;   //!
   TBranch        *b_GenJet_DeltaPhi;   //!
   TBranch        *b_GenJet_Flavor;   //!
   TBranch        *b_GenJet_FlavorAlgo;   //!
   TBranch        *b_GenJet_FlavorPhys;   //!
   TBranch        *b_GenJet_BTag;   //!
   TBranch        *b_GenJet_BTagAlgo;   //!
   TBranch        *b_GenJet_BTagPhys;   //!
   TBranch        *b_GenJet_TauTag;   //!
   TBranch        *b_GenJet_Charge;   //!
   TBranch        *b_GenJet_EhadOverEem;   //!
   TBranch        *b_GenJet_NCharged;   //!
   TBranch        *b_GenJet_NNeutrals;   //!
   TBranch        *b_GenJet_Beta;   //!
   TBranch        *b_GenJet_BetaStar;   //!
   TBranch        *b_GenJet_MeanSqDeltaR;   //!
   TBranch        *b_GenJet_PTD;   //!
   TBranch        *b_GenJet_FracPt;   //!
   TBranch        *b_GenJet_Tau;   //!
   TBranch        *b_GenJet_TrimmedP4;   //!
   TBranch        *b_GenJet_PrunedP4;   //!
   TBranch        *b_GenJet_SoftDroppedP4;   //!
   TBranch        *b_GenJet_NSubJetsTrimmed;   //!
   TBranch        *b_GenJet_NSubJetsPruned;   //!
   TBranch        *b_GenJet_NSubJetsSoftDropped;   //!
   TBranch        *b_GenJet_Constituents;   //!
   TBranch        *b_GenJet_Particles;   //!
   TBranch        *b_GenJet_Area;   //!
   TBranch        *b_GenJet_size;   //!
   TBranch        *b_GenJetAK8_;   //!
   TBranch        *b_GenJetAK8_fUniqueID;   //!
   TBranch        *b_GenJetAK8_fBits;   //!
   TBranch        *b_GenJetAK8_PT;   //!
   TBranch        *b_GenJetAK8_Eta;   //!
   TBranch        *b_GenJetAK8_Phi;   //!
   TBranch        *b_GenJetAK8_T;   //!
   TBranch        *b_GenJetAK8_Mass;   //!
   TBranch        *b_GenJetAK8_DeltaEta;   //!
   TBranch        *b_GenJetAK8_DeltaPhi;   //!
   TBranch        *b_GenJetAK8_Flavor;   //!
   TBranch        *b_GenJetAK8_FlavorAlgo;   //!
   TBranch        *b_GenJetAK8_FlavorPhys;   //!
   TBranch        *b_GenJetAK8_BTag;   //!
   TBranch        *b_GenJetAK8_BTagAlgo;   //!
   TBranch        *b_GenJetAK8_BTagPhys;   //!
   TBranch        *b_GenJetAK8_TauTag;   //!
   TBranch        *b_GenJetAK8_Charge;   //!
   TBranch        *b_GenJetAK8_EhadOverEem;   //!
   TBranch        *b_GenJetAK8_NCharged;   //!
   TBranch        *b_GenJetAK8_NNeutrals;   //!
   TBranch        *b_GenJetAK8_Beta;   //!
   TBranch        *b_GenJetAK8_BetaStar;   //!
   TBranch        *b_GenJetAK8_MeanSqDeltaR;   //!
   TBranch        *b_GenJetAK8_PTD;   //!
   TBranch        *b_GenJetAK8_FracPt;   //!
   TBranch        *b_GenJetAK8_Tau;   //!
   TBranch        *b_GenJetAK8_TrimmedP4;   //!
   TBranch        *b_GenJetAK8_PrunedP4;   //!
   TBranch        *b_GenJetAK8_SoftDroppedP4;   //!
   TBranch        *b_GenJetAK8_NSubJetsTrimmed;   //!
   TBranch        *b_GenJetAK8_NSubJetsPruned;   //!
   TBranch        *b_GenJetAK8_NSubJetsSoftDropped;   //!
   TBranch        *b_GenJetAK8_Constituents;   //!
   TBranch        *b_GenJetAK8_Particles;   //!
   TBranch        *b_GenJetAK8_Area;   //!
   TBranch        *b_GenJetAK8_size;   //!
   TBranch        *b_GenMissingET_;   //!
   TBranch        *b_GenMissingET_fUniqueID;   //!
   TBranch        *b_GenMissingET_fBits;   //!
   TBranch        *b_GenMissingET_MET;   //!
   TBranch        *b_GenMissingET_Eta;   //!
   TBranch        *b_GenMissingET_Phi;   //!
   TBranch        *b_GenMissingET_size;   //!
   TBranch        *b_Photon_;   //!
   TBranch        *b_Photon_fUniqueID;   //!
   TBranch        *b_Photon_fBits;   //!
   TBranch        *b_Photon_PT;   //!
   TBranch        *b_Photon_Eta;   //!
   TBranch        *b_Photon_Phi;   //!
   TBranch        *b_Photon_E;   //!
   TBranch        *b_Photon_T;   //!
   TBranch        *b_Photon_EhadOverEem;   //!
   TBranch        *b_Photon_Particles;   //!
   TBranch        *b_Photon_IsolationVar;   //!
   TBranch        *b_Photon_IsolationVarRhoCorr;   //!
   TBranch        *b_Photon_SumPtCharged;   //!
   TBranch        *b_Photon_SumPtNeutral;   //!
   TBranch        *b_Photon_SumPtChargedPU;   //!
   TBranch        *b_Photon_SumPt;   //!
   TBranch        *b_Photon_size;   //!
   TBranch        *b_Electron_;   //!
   TBranch        *b_Electron_fUniqueID;   //!
   TBranch        *b_Electron_fBits;   //!
   TBranch        *b_Electron_PT;   //!
   TBranch        *b_Electron_Eta;   //!
   TBranch        *b_Electron_Phi;   //!
   TBranch        *b_Electron_T;   //!
   TBranch        *b_Electron_Charge;   //!
   TBranch        *b_Electron_EhadOverEem;   //!
   TBranch        *b_Electron_Particle;   //!
   TBranch        *b_Electron_IsolationVar;   //!
   TBranch        *b_Electron_IsolationVarRhoCorr;   //!
   TBranch        *b_Electron_SumPtCharged;   //!
   TBranch        *b_Electron_SumPtNeutral;   //!
   TBranch        *b_Electron_SumPtChargedPU;   //!
   TBranch        *b_Electron_SumPt;   //!
   TBranch        *b_Electron_size;   //!
   TBranch        *b_MuonLoose_;   //!
   TBranch        *b_MuonLoose_fUniqueID;   //!
   TBranch        *b_MuonLoose_fBits;   //!
   TBranch        *b_MuonLoose_PT;   //!
   TBranch        *b_MuonLoose_Eta;   //!
   TBranch        *b_MuonLoose_Phi;   //!
   TBranch        *b_MuonLoose_T;   //!
   TBranch        *b_MuonLoose_Charge;   //!
   TBranch        *b_MuonLoose_Particle;   //!
   TBranch        *b_MuonLoose_IsolationVar;   //!
   TBranch        *b_MuonLoose_IsolationVarRhoCorr;   //!
   TBranch        *b_MuonLoose_SumPtCharged;   //!
   TBranch        *b_MuonLoose_SumPtNeutral;   //!
   TBranch        *b_MuonLoose_SumPtChargedPU;   //!
   TBranch        *b_MuonLoose_SumPt;   //!
   TBranch        *b_MuonLoose_size;   //!
   TBranch        *b_MuonTight_;   //!
   TBranch        *b_MuonTight_fUniqueID;   //!
   TBranch        *b_MuonTight_fBits;   //!
   TBranch        *b_MuonTight_PT;   //!
   TBranch        *b_MuonTight_Eta;   //!
   TBranch        *b_MuonTight_Phi;   //!
   TBranch        *b_MuonTight_T;   //!
   TBranch        *b_MuonTight_Charge;   //!
   TBranch        *b_MuonTight_Particle;   //!
   TBranch        *b_MuonTight_IsolationVar;   //!
   TBranch        *b_MuonTight_IsolationVarRhoCorr;   //!
   TBranch        *b_MuonTight_SumPtCharged;   //!
   TBranch        *b_MuonTight_SumPtNeutral;   //!
   TBranch        *b_MuonTight_SumPtChargedPU;   //!
   TBranch        *b_MuonTight_SumPt;   //!
   TBranch        *b_MuonTight_size;   //!
   TBranch        *b_Jet_;   //!
   TBranch        *b_Jet_fUniqueID;   //!
   TBranch        *b_Jet_fBits;   //!
   TBranch        *b_Jet_PT;   //!
   TBranch        *b_Jet_Eta;   //!
   TBranch        *b_Jet_Phi;   //!
   TBranch        *b_Jet_T;   //!
   TBranch        *b_Jet_Mass;   //!
   TBranch        *b_Jet_DeltaEta;   //!
   TBranch        *b_Jet_DeltaPhi;   //!
   TBranch        *b_Jet_Flavor;   //!
   TBranch        *b_Jet_FlavorAlgo;   //!
   TBranch        *b_Jet_FlavorPhys;   //!
   TBranch        *b_Jet_BTag;   //!
   TBranch        *b_Jet_BTagAlgo;   //!
   TBranch        *b_Jet_BTagPhys;   //!
   TBranch        *b_Jet_TauTag;   //!
   TBranch        *b_Jet_Charge;   //!
   TBranch        *b_Jet_EhadOverEem;   //!
   TBranch        *b_Jet_NCharged;   //!
   TBranch        *b_Jet_NNeutrals;   //!
   TBranch        *b_Jet_Beta;   //!
   TBranch        *b_Jet_BetaStar;   //!
   TBranch        *b_Jet_MeanSqDeltaR;   //!
   TBranch        *b_Jet_PTD;   //!
   TBranch        *b_Jet_FracPt;   //!
   TBranch        *b_Jet_Tau;   //!
   TBranch        *b_Jet_TrimmedP4;   //!
   TBranch        *b_Jet_PrunedP4;   //!
   TBranch        *b_Jet_SoftDroppedP4;   //!
   TBranch        *b_Jet_NSubJetsTrimmed;   //!
   TBranch        *b_Jet_NSubJetsPruned;   //!
   TBranch        *b_Jet_NSubJetsSoftDropped;   //!
   TBranch        *b_Jet_Constituents;   //!
   TBranch        *b_Jet_Particles;   //!
   TBranch        *b_Jet_Area;   //!
   TBranch        *b_Jet_size;   //!
   TBranch        *b_JetPUPPI_;   //!
   TBranch        *b_JetPUPPI_fUniqueID;   //!
   TBranch        *b_JetPUPPI_fBits;   //!
   TBranch        *b_JetPUPPI_PT;   //!
   TBranch        *b_JetPUPPI_Eta;   //!
   TBranch        *b_JetPUPPI_Phi;   //!
   TBranch        *b_JetPUPPI_T;   //!
   TBranch        *b_JetPUPPI_Mass;   //!
   TBranch        *b_JetPUPPI_DeltaEta;   //!
   TBranch        *b_JetPUPPI_DeltaPhi;   //!
   TBranch        *b_JetPUPPI_Flavor;   //!
   TBranch        *b_JetPUPPI_FlavorAlgo;   //!
   TBranch        *b_JetPUPPI_FlavorPhys;   //!
   TBranch        *b_JetPUPPI_BTag;   //!
   TBranch        *b_JetPUPPI_BTagAlgo;   //!
   TBranch        *b_JetPUPPI_BTagPhys;   //!
   TBranch        *b_JetPUPPI_TauTag;   //!
   TBranch        *b_JetPUPPI_Charge;   //!
   TBranch        *b_JetPUPPI_EhadOverEem;   //!
   TBranch        *b_JetPUPPI_NCharged;   //!
   TBranch        *b_JetPUPPI_NNeutrals;   //!
   TBranch        *b_JetPUPPI_Beta;   //!
   TBranch        *b_JetPUPPI_BetaStar;   //!
   TBranch        *b_JetPUPPI_MeanSqDeltaR;   //!
   TBranch        *b_JetPUPPI_PTD;   //!
   TBranch        *b_JetPUPPI_FracPt;   //!
   TBranch        *b_JetPUPPI_Tau;   //!
   TBranch        *b_JetPUPPI_TrimmedP4;   //!
   TBranch        *b_JetPUPPI_PrunedP4;   //!
   TBranch        *b_JetPUPPI_SoftDroppedP4;   //!
   TBranch        *b_JetPUPPI_NSubJetsTrimmed;   //!
   TBranch        *b_JetPUPPI_NSubJetsPruned;   //!
   TBranch        *b_JetPUPPI_NSubJetsSoftDropped;   //!
   TBranch        *b_JetPUPPI_Constituents;   //!
   TBranch        *b_JetPUPPI_Particles;   //!
   TBranch        *b_JetPUPPI_Area;   //!
   TBranch        *b_JetPUPPI_size;   //!
   TBranch        *b_JetAK8_;   //!
   TBranch        *b_JetAK8_fUniqueID;   //!
   TBranch        *b_JetAK8_fBits;   //!
   TBranch        *b_JetAK8_PT;   //!
   TBranch        *b_JetAK8_Eta;   //!
   TBranch        *b_JetAK8_Phi;   //!
   TBranch        *b_JetAK8_T;   //!
   TBranch        *b_JetAK8_Mass;   //!
   TBranch        *b_JetAK8_DeltaEta;   //!
   TBranch        *b_JetAK8_DeltaPhi;   //!
   TBranch        *b_JetAK8_Flavor;   //!
   TBranch        *b_JetAK8_FlavorAlgo;   //!
   TBranch        *b_JetAK8_FlavorPhys;   //!
   TBranch        *b_JetAK8_BTag;   //!
   TBranch        *b_JetAK8_BTagAlgo;   //!
   TBranch        *b_JetAK8_BTagPhys;   //!
   TBranch        *b_JetAK8_TauTag;   //!
   TBranch        *b_JetAK8_Charge;   //!
   TBranch        *b_JetAK8_EhadOverEem;   //!
   TBranch        *b_JetAK8_NCharged;   //!
   TBranch        *b_JetAK8_NNeutrals;   //!
   TBranch        *b_JetAK8_Beta;   //!
   TBranch        *b_JetAK8_BetaStar;   //!
   TBranch        *b_JetAK8_MeanSqDeltaR;   //!
   TBranch        *b_JetAK8_PTD;   //!
   TBranch        *b_JetAK8_FracPt;   //!
   TBranch        *b_JetAK8_Tau;   //!
   TBranch        *b_JetAK8_TrimmedP4;   //!
   TBranch        *b_JetAK8_PrunedP4;   //!
   TBranch        *b_JetAK8_SoftDroppedP4;   //!
   TBranch        *b_JetAK8_NSubJetsTrimmed;   //!
   TBranch        *b_JetAK8_NSubJetsPruned;   //!
   TBranch        *b_JetAK8_NSubJetsSoftDropped;   //!
   TBranch        *b_JetAK8_Constituents;   //!
   TBranch        *b_JetAK8_Particles;   //!
   TBranch        *b_JetAK8_Area;   //!
   TBranch        *b_JetAK8_size;   //!
   TBranch        *b_JetPUPPIAK8_;   //!
   TBranch        *b_JetPUPPIAK8_fUniqueID;   //!
   TBranch        *b_JetPUPPIAK8_fBits;   //!
   TBranch        *b_JetPUPPIAK8_PT;   //!
   TBranch        *b_JetPUPPIAK8_Eta;   //!
   TBranch        *b_JetPUPPIAK8_Phi;   //!
   TBranch        *b_JetPUPPIAK8_T;   //!
   TBranch        *b_JetPUPPIAK8_Mass;   //!
   TBranch        *b_JetPUPPIAK8_DeltaEta;   //!
   TBranch        *b_JetPUPPIAK8_DeltaPhi;   //!
   TBranch        *b_JetPUPPIAK8_Flavor;   //!
   TBranch        *b_JetPUPPIAK8_FlavorAlgo;   //!
   TBranch        *b_JetPUPPIAK8_FlavorPhys;   //!
   TBranch        *b_JetPUPPIAK8_BTag;   //!
   TBranch        *b_JetPUPPIAK8_BTagAlgo;   //!
   TBranch        *b_JetPUPPIAK8_BTagPhys;   //!
   TBranch        *b_JetPUPPIAK8_TauTag;   //!
   TBranch        *b_JetPUPPIAK8_Charge;   //!
   TBranch        *b_JetPUPPIAK8_EhadOverEem;   //!
   TBranch        *b_JetPUPPIAK8_NCharged;   //!
   TBranch        *b_JetPUPPIAK8_NNeutrals;   //!
   TBranch        *b_JetPUPPIAK8_Beta;   //!
   TBranch        *b_JetPUPPIAK8_BetaStar;   //!
   TBranch        *b_JetPUPPIAK8_MeanSqDeltaR;   //!
   TBranch        *b_JetPUPPIAK8_PTD;   //!
   TBranch        *b_JetPUPPIAK8_FracPt;   //!
   TBranch        *b_JetPUPPIAK8_Tau;   //!
   TBranch        *b_JetPUPPIAK8_TrimmedP4;   //!
   TBranch        *b_JetPUPPIAK8_PrunedP4;   //!
   TBranch        *b_JetPUPPIAK8_SoftDroppedP4;   //!
   TBranch        *b_JetPUPPIAK8_NSubJetsTrimmed;   //!
   TBranch        *b_JetPUPPIAK8_NSubJetsPruned;   //!
   TBranch        *b_JetPUPPIAK8_NSubJetsSoftDropped;   //!
   TBranch        *b_JetPUPPIAK8_Constituents;   //!
   TBranch        *b_JetPUPPIAK8_Particles;   //!
   TBranch        *b_JetPUPPIAK8_Area;   //!
   TBranch        *b_JetPUPPIAK8_size;   //!
   TBranch        *b_MissingET_;   //!
   TBranch        *b_MissingET_fUniqueID;   //!
   TBranch        *b_MissingET_fBits;   //!
   TBranch        *b_MissingET_MET;   //!
   TBranch        *b_MissingET_Eta;   //!
   TBranch        *b_MissingET_Phi;   //!
   TBranch        *b_MissingET_size;   //!
   TBranch        *b_PuppiMissingET_;   //!
   TBranch        *b_PuppiMissingET_fUniqueID;   //!
   TBranch        *b_PuppiMissingET_fBits;   //!
   TBranch        *b_PuppiMissingET_MET;   //!
   TBranch        *b_PuppiMissingET_Eta;   //!
   TBranch        *b_PuppiMissingET_Phi;   //!
   TBranch        *b_PuppiMissingET_size;   //!
   TBranch        *b_GenPileUpMissingET_;   //!
   TBranch        *b_GenPileUpMissingET_fUniqueID;   //!
   TBranch        *b_GenPileUpMissingET_fBits;   //!
   TBranch        *b_GenPileUpMissingET_MET;   //!
   TBranch        *b_GenPileUpMissingET_Eta;   //!
   TBranch        *b_GenPileUpMissingET_Phi;   //!
   TBranch        *b_GenPileUpMissingET_size;   //!
   TBranch        *b_ScalarHT_;   //!
   TBranch        *b_ScalarHT_fUniqueID;   //!
   TBranch        *b_ScalarHT_fBits;   //!
   TBranch        *b_ScalarHT_HT;   //!
   TBranch        *b_ScalarHT_size;   //!

   Delphes(TTree *tree=0);
   virtual ~Delphes();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef Delphes_cxx
Delphes::Delphes(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("/home/gzevi/C2N4delphes/C2N4full.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("/home/gzevi/C2N4delphes/C2N4full.root");
      }
      f->GetObject("Delphes",tree);

   }
   Init(tree);
}

Delphes::~Delphes()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t Delphes::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t Delphes::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void Delphes::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("Event", &Event_, &b_Event_);
   fChain->SetBranchAddress("Event.fUniqueID", Event_fUniqueID, &b_Event_fUniqueID);
   fChain->SetBranchAddress("Event.fBits", Event_fBits, &b_Event_fBits);
   fChain->SetBranchAddress("Event.Number", Event_Number, &b_Event_Number);
   fChain->SetBranchAddress("Event.ReadTime", Event_ReadTime, &b_Event_ReadTime);
   fChain->SetBranchAddress("Event.ProcTime", Event_ProcTime, &b_Event_ProcTime);
   fChain->SetBranchAddress("Event.ProcessID", Event_ProcessID, &b_Event_ProcessID);
   fChain->SetBranchAddress("Event.MPI", Event_MPI, &b_Event_MPI);
   fChain->SetBranchAddress("Event.Weight", Event_Weight, &b_Event_Weight);
   fChain->SetBranchAddress("Event.Scale", Event_Scale, &b_Event_Scale);
   fChain->SetBranchAddress("Event.AlphaQED", Event_AlphaQED, &b_Event_AlphaQED);
   fChain->SetBranchAddress("Event.AlphaQCD", Event_AlphaQCD, &b_Event_AlphaQCD);
   fChain->SetBranchAddress("Event.ID1", Event_ID1, &b_Event_ID1);
   fChain->SetBranchAddress("Event.ID2", Event_ID2, &b_Event_ID2);
   fChain->SetBranchAddress("Event.X1", Event_X1, &b_Event_X1);
   fChain->SetBranchAddress("Event.X2", Event_X2, &b_Event_X2);
   fChain->SetBranchAddress("Event.ScalePDF", Event_ScalePDF, &b_Event_ScalePDF);
   fChain->SetBranchAddress("Event.PDF1", Event_PDF1, &b_Event_PDF1);
   fChain->SetBranchAddress("Event.PDF2", Event_PDF2, &b_Event_PDF2);
   fChain->SetBranchAddress("Event_size", &Event_size, &b_Event_size);
   fChain->SetBranchAddress("EventLHEF", &EventLHEF_, &b_EventLHEF_);
   fChain->SetBranchAddress("EventLHEF.fUniqueID", EventLHEF_fUniqueID, &b_EventLHEF_fUniqueID);
   fChain->SetBranchAddress("EventLHEF.fBits", EventLHEF_fBits, &b_EventLHEF_fBits);
   fChain->SetBranchAddress("EventLHEF.Number", EventLHEF_Number, &b_EventLHEF_Number);
   fChain->SetBranchAddress("EventLHEF.ReadTime", EventLHEF_ReadTime, &b_EventLHEF_ReadTime);
   fChain->SetBranchAddress("EventLHEF.ProcTime", EventLHEF_ProcTime, &b_EventLHEF_ProcTime);
   fChain->SetBranchAddress("EventLHEF.ProcessID", EventLHEF_ProcessID, &b_EventLHEF_ProcessID);
   fChain->SetBranchAddress("EventLHEF.Weight", EventLHEF_Weight, &b_EventLHEF_Weight);
   fChain->SetBranchAddress("EventLHEF.ScalePDF", EventLHEF_ScalePDF, &b_EventLHEF_ScalePDF);
   fChain->SetBranchAddress("EventLHEF.AlphaQED", EventLHEF_AlphaQED, &b_EventLHEF_AlphaQED);
   fChain->SetBranchAddress("EventLHEF.AlphaQCD", EventLHEF_AlphaQCD, &b_EventLHEF_AlphaQCD);
   fChain->SetBranchAddress("EventLHEF_size", &EventLHEF_size, &b_EventLHEF_size);
   fChain->SetBranchAddress("WeightLHEF", &WeightLHEF_, &b_WeightLHEF_);
   fChain->SetBranchAddress("WeightLHEF.fUniqueID", &WeightLHEF_fUniqueID, &b_WeightLHEF_fUniqueID);
   fChain->SetBranchAddress("WeightLHEF.fBits", &WeightLHEF_fBits, &b_WeightLHEF_fBits);
   fChain->SetBranchAddress("WeightLHEF.ID", &WeightLHEF_ID, &b_WeightLHEF_ID);
   fChain->SetBranchAddress("WeightLHEF.Weight", &WeightLHEF_Weight, &b_WeightLHEF_Weight);
   fChain->SetBranchAddress("WeightLHEF_size", &WeightLHEF_size, &b_WeightLHEF_size);
   fChain->SetBranchAddress("Particle", &Particle_, &b_Particle_);
   fChain->SetBranchAddress("Particle.fUniqueID", Particle_fUniqueID, &b_Particle_fUniqueID);
   fChain->SetBranchAddress("Particle.fBits", Particle_fBits, &b_Particle_fBits);
   fChain->SetBranchAddress("Particle.PID", Particle_PID, &b_Particle_PID);
   fChain->SetBranchAddress("Particle.Status", Particle_Status, &b_Particle_Status);
   fChain->SetBranchAddress("Particle.IsPU", Particle_IsPU, &b_Particle_IsPU);
   fChain->SetBranchAddress("Particle.M1", Particle_M1, &b_Particle_M1);
   fChain->SetBranchAddress("Particle.M2", Particle_M2, &b_Particle_M2);
   fChain->SetBranchAddress("Particle.D1", Particle_D1, &b_Particle_D1);
   fChain->SetBranchAddress("Particle.D2", Particle_D2, &b_Particle_D2);
   fChain->SetBranchAddress("Particle.Charge", Particle_Charge, &b_Particle_Charge);
   fChain->SetBranchAddress("Particle.Mass", Particle_Mass, &b_Particle_Mass);
   fChain->SetBranchAddress("Particle.E", Particle_E, &b_Particle_E);
   fChain->SetBranchAddress("Particle.Px", Particle_Px, &b_Particle_Px);
   fChain->SetBranchAddress("Particle.Py", Particle_Py, &b_Particle_Py);
   fChain->SetBranchAddress("Particle.Pz", Particle_Pz, &b_Particle_Pz);
   fChain->SetBranchAddress("Particle.PT", Particle_PT, &b_Particle_PT);
   fChain->SetBranchAddress("Particle.Eta", Particle_Eta, &b_Particle_Eta);
   fChain->SetBranchAddress("Particle.Phi", Particle_Phi, &b_Particle_Phi);
   fChain->SetBranchAddress("Particle.Rapidity", Particle_Rapidity, &b_Particle_Rapidity);
   fChain->SetBranchAddress("Particle.T", Particle_T, &b_Particle_T);
   fChain->SetBranchAddress("Particle.X", Particle_X, &b_Particle_X);
   fChain->SetBranchAddress("Particle.Y", Particle_Y, &b_Particle_Y);
   fChain->SetBranchAddress("Particle.Z", Particle_Z, &b_Particle_Z);
   fChain->SetBranchAddress("Particle_size", &Particle_size, &b_Particle_size);
   fChain->SetBranchAddress("Vertex", &Vertex_, &b_Vertex_);
   fChain->SetBranchAddress("Vertex.fUniqueID", Vertex_fUniqueID, &b_Vertex_fUniqueID);
   fChain->SetBranchAddress("Vertex.fBits", Vertex_fBits, &b_Vertex_fBits);
   fChain->SetBranchAddress("Vertex.T", Vertex_T, &b_Vertex_T);
   fChain->SetBranchAddress("Vertex.X", Vertex_X, &b_Vertex_X);
   fChain->SetBranchAddress("Vertex.Y", Vertex_Y, &b_Vertex_Y);
   fChain->SetBranchAddress("Vertex.Z", Vertex_Z, &b_Vertex_Z);
   fChain->SetBranchAddress("Vertex_size", &Vertex_size, &b_Vertex_size);
   fChain->SetBranchAddress("GenJet", &GenJet_, &b_GenJet_);
   fChain->SetBranchAddress("GenJet.fUniqueID", GenJet_fUniqueID, &b_GenJet_fUniqueID);
   fChain->SetBranchAddress("GenJet.fBits", GenJet_fBits, &b_GenJet_fBits);
   fChain->SetBranchAddress("GenJet.PT", GenJet_PT, &b_GenJet_PT);
   fChain->SetBranchAddress("GenJet.Eta", GenJet_Eta, &b_GenJet_Eta);
   fChain->SetBranchAddress("GenJet.Phi", GenJet_Phi, &b_GenJet_Phi);
   fChain->SetBranchAddress("GenJet.T", GenJet_T, &b_GenJet_T);
   fChain->SetBranchAddress("GenJet.Mass", GenJet_Mass, &b_GenJet_Mass);
   fChain->SetBranchAddress("GenJet.DeltaEta", GenJet_DeltaEta, &b_GenJet_DeltaEta);
   fChain->SetBranchAddress("GenJet.DeltaPhi", GenJet_DeltaPhi, &b_GenJet_DeltaPhi);
   fChain->SetBranchAddress("GenJet.Flavor", GenJet_Flavor, &b_GenJet_Flavor);
   fChain->SetBranchAddress("GenJet.FlavorAlgo", GenJet_FlavorAlgo, &b_GenJet_FlavorAlgo);
   fChain->SetBranchAddress("GenJet.FlavorPhys", GenJet_FlavorPhys, &b_GenJet_FlavorPhys);
   fChain->SetBranchAddress("GenJet.BTag", GenJet_BTag, &b_GenJet_BTag);
   fChain->SetBranchAddress("GenJet.BTagAlgo", GenJet_BTagAlgo, &b_GenJet_BTagAlgo);
   fChain->SetBranchAddress("GenJet.BTagPhys", GenJet_BTagPhys, &b_GenJet_BTagPhys);
   fChain->SetBranchAddress("GenJet.TauTag", GenJet_TauTag, &b_GenJet_TauTag);
   fChain->SetBranchAddress("GenJet.Charge", GenJet_Charge, &b_GenJet_Charge);
   fChain->SetBranchAddress("GenJet.EhadOverEem", GenJet_EhadOverEem, &b_GenJet_EhadOverEem);
   fChain->SetBranchAddress("GenJet.NCharged", GenJet_NCharged, &b_GenJet_NCharged);
   fChain->SetBranchAddress("GenJet.NNeutrals", GenJet_NNeutrals, &b_GenJet_NNeutrals);
   fChain->SetBranchAddress("GenJet.Beta", GenJet_Beta, &b_GenJet_Beta);
   fChain->SetBranchAddress("GenJet.BetaStar", GenJet_BetaStar, &b_GenJet_BetaStar);
   fChain->SetBranchAddress("GenJet.MeanSqDeltaR", GenJet_MeanSqDeltaR, &b_GenJet_MeanSqDeltaR);
   fChain->SetBranchAddress("GenJet.PTD", GenJet_PTD, &b_GenJet_PTD);
   fChain->SetBranchAddress("GenJet.FracPt[5]", GenJet_FracPt, &b_GenJet_FracPt);
   fChain->SetBranchAddress("GenJet.Tau[5]", GenJet_Tau, &b_GenJet_Tau);
   fChain->SetBranchAddress("GenJet.TrimmedP4[5]", GenJet_TrimmedP4, &b_GenJet_TrimmedP4);
   fChain->SetBranchAddress("GenJet.PrunedP4[5]", GenJet_PrunedP4, &b_GenJet_PrunedP4);
   fChain->SetBranchAddress("GenJet.SoftDroppedP4[5]", GenJet_SoftDroppedP4, &b_GenJet_SoftDroppedP4);
   fChain->SetBranchAddress("GenJet.NSubJetsTrimmed", GenJet_NSubJetsTrimmed, &b_GenJet_NSubJetsTrimmed);
   fChain->SetBranchAddress("GenJet.NSubJetsPruned", GenJet_NSubJetsPruned, &b_GenJet_NSubJetsPruned);
   fChain->SetBranchAddress("GenJet.NSubJetsSoftDropped", GenJet_NSubJetsSoftDropped, &b_GenJet_NSubJetsSoftDropped);
   fChain->SetBranchAddress("GenJet.Constituents", GenJet_Constituents, &b_GenJet_Constituents);
   fChain->SetBranchAddress("GenJet.Particles", GenJet_Particles, &b_GenJet_Particles);
   fChain->SetBranchAddress("GenJet.Area", GenJet_Area, &b_GenJet_Area);
   fChain->SetBranchAddress("GenJet_size", &GenJet_size, &b_GenJet_size);
   fChain->SetBranchAddress("GenJetAK8", &GenJetAK8_, &b_GenJetAK8_);
   fChain->SetBranchAddress("GenJetAK8.fUniqueID", GenJetAK8_fUniqueID, &b_GenJetAK8_fUniqueID);
   fChain->SetBranchAddress("GenJetAK8.fBits", GenJetAK8_fBits, &b_GenJetAK8_fBits);
   fChain->SetBranchAddress("GenJetAK8.PT", GenJetAK8_PT, &b_GenJetAK8_PT);
   fChain->SetBranchAddress("GenJetAK8.Eta", GenJetAK8_Eta, &b_GenJetAK8_Eta);
   fChain->SetBranchAddress("GenJetAK8.Phi", GenJetAK8_Phi, &b_GenJetAK8_Phi);
   fChain->SetBranchAddress("GenJetAK8.T", GenJetAK8_T, &b_GenJetAK8_T);
   fChain->SetBranchAddress("GenJetAK8.Mass", GenJetAK8_Mass, &b_GenJetAK8_Mass);
   fChain->SetBranchAddress("GenJetAK8.DeltaEta", GenJetAK8_DeltaEta, &b_GenJetAK8_DeltaEta);
   fChain->SetBranchAddress("GenJetAK8.DeltaPhi", GenJetAK8_DeltaPhi, &b_GenJetAK8_DeltaPhi);
   fChain->SetBranchAddress("GenJetAK8.Flavor", GenJetAK8_Flavor, &b_GenJetAK8_Flavor);
   fChain->SetBranchAddress("GenJetAK8.FlavorAlgo", GenJetAK8_FlavorAlgo, &b_GenJetAK8_FlavorAlgo);
   fChain->SetBranchAddress("GenJetAK8.FlavorPhys", GenJetAK8_FlavorPhys, &b_GenJetAK8_FlavorPhys);
   fChain->SetBranchAddress("GenJetAK8.BTag", GenJetAK8_BTag, &b_GenJetAK8_BTag);
   fChain->SetBranchAddress("GenJetAK8.BTagAlgo", GenJetAK8_BTagAlgo, &b_GenJetAK8_BTagAlgo);
   fChain->SetBranchAddress("GenJetAK8.BTagPhys", GenJetAK8_BTagPhys, &b_GenJetAK8_BTagPhys);
   fChain->SetBranchAddress("GenJetAK8.TauTag", GenJetAK8_TauTag, &b_GenJetAK8_TauTag);
   fChain->SetBranchAddress("GenJetAK8.Charge", GenJetAK8_Charge, &b_GenJetAK8_Charge);
   fChain->SetBranchAddress("GenJetAK8.EhadOverEem", GenJetAK8_EhadOverEem, &b_GenJetAK8_EhadOverEem);
   fChain->SetBranchAddress("GenJetAK8.NCharged", GenJetAK8_NCharged, &b_GenJetAK8_NCharged);
   fChain->SetBranchAddress("GenJetAK8.NNeutrals", GenJetAK8_NNeutrals, &b_GenJetAK8_NNeutrals);
   fChain->SetBranchAddress("GenJetAK8.Beta", GenJetAK8_Beta, &b_GenJetAK8_Beta);
   fChain->SetBranchAddress("GenJetAK8.BetaStar", GenJetAK8_BetaStar, &b_GenJetAK8_BetaStar);
   fChain->SetBranchAddress("GenJetAK8.MeanSqDeltaR", GenJetAK8_MeanSqDeltaR, &b_GenJetAK8_MeanSqDeltaR);
   fChain->SetBranchAddress("GenJetAK8.PTD", GenJetAK8_PTD, &b_GenJetAK8_PTD);
   fChain->SetBranchAddress("GenJetAK8.FracPt[5]", GenJetAK8_FracPt, &b_GenJetAK8_FracPt);
   fChain->SetBranchAddress("GenJetAK8.Tau[5]", GenJetAK8_Tau, &b_GenJetAK8_Tau);
   fChain->SetBranchAddress("GenJetAK8.TrimmedP4[5]", GenJetAK8_TrimmedP4, &b_GenJetAK8_TrimmedP4);
   fChain->SetBranchAddress("GenJetAK8.PrunedP4[5]", GenJetAK8_PrunedP4, &b_GenJetAK8_PrunedP4);
   fChain->SetBranchAddress("GenJetAK8.SoftDroppedP4[5]", GenJetAK8_SoftDroppedP4, &b_GenJetAK8_SoftDroppedP4);
   fChain->SetBranchAddress("GenJetAK8.NSubJetsTrimmed", GenJetAK8_NSubJetsTrimmed, &b_GenJetAK8_NSubJetsTrimmed);
   fChain->SetBranchAddress("GenJetAK8.NSubJetsPruned", GenJetAK8_NSubJetsPruned, &b_GenJetAK8_NSubJetsPruned);
   fChain->SetBranchAddress("GenJetAK8.NSubJetsSoftDropped", GenJetAK8_NSubJetsSoftDropped, &b_GenJetAK8_NSubJetsSoftDropped);
   fChain->SetBranchAddress("GenJetAK8.Constituents", GenJetAK8_Constituents, &b_GenJetAK8_Constituents);
   fChain->SetBranchAddress("GenJetAK8.Particles", GenJetAK8_Particles, &b_GenJetAK8_Particles);
   fChain->SetBranchAddress("GenJetAK8.Area", GenJetAK8_Area, &b_GenJetAK8_Area);
   fChain->SetBranchAddress("GenJetAK8_size", &GenJetAK8_size, &b_GenJetAK8_size);
   fChain->SetBranchAddress("GenMissingET", &GenMissingET_, &b_GenMissingET_);
   fChain->SetBranchAddress("GenMissingET.fUniqueID", GenMissingET_fUniqueID, &b_GenMissingET_fUniqueID);
   fChain->SetBranchAddress("GenMissingET.fBits", GenMissingET_fBits, &b_GenMissingET_fBits);
   fChain->SetBranchAddress("GenMissingET.MET", GenMissingET_MET, &b_GenMissingET_MET);
   fChain->SetBranchAddress("GenMissingET.Eta", GenMissingET_Eta, &b_GenMissingET_Eta);
   fChain->SetBranchAddress("GenMissingET.Phi", GenMissingET_Phi, &b_GenMissingET_Phi);
   fChain->SetBranchAddress("GenMissingET_size", &GenMissingET_size, &b_GenMissingET_size);
   fChain->SetBranchAddress("Photon", &Photon_, &b_Photon_);
   fChain->SetBranchAddress("Photon.fUniqueID", Photon_fUniqueID, &b_Photon_fUniqueID);
   fChain->SetBranchAddress("Photon.fBits", Photon_fBits, &b_Photon_fBits);
   fChain->SetBranchAddress("Photon.PT", Photon_PT, &b_Photon_PT);
   fChain->SetBranchAddress("Photon.Eta", Photon_Eta, &b_Photon_Eta);
   fChain->SetBranchAddress("Photon.Phi", Photon_Phi, &b_Photon_Phi);
   fChain->SetBranchAddress("Photon.E", Photon_E, &b_Photon_E);
   fChain->SetBranchAddress("Photon.T", Photon_T, &b_Photon_T);
   fChain->SetBranchAddress("Photon.EhadOverEem", Photon_EhadOverEem, &b_Photon_EhadOverEem);
   fChain->SetBranchAddress("Photon.Particles", Photon_Particles, &b_Photon_Particles);
   fChain->SetBranchAddress("Photon.IsolationVar", Photon_IsolationVar, &b_Photon_IsolationVar);
   fChain->SetBranchAddress("Photon.IsolationVarRhoCorr", Photon_IsolationVarRhoCorr, &b_Photon_IsolationVarRhoCorr);
   fChain->SetBranchAddress("Photon.SumPtCharged", Photon_SumPtCharged, &b_Photon_SumPtCharged);
   fChain->SetBranchAddress("Photon.SumPtNeutral", Photon_SumPtNeutral, &b_Photon_SumPtNeutral);
   fChain->SetBranchAddress("Photon.SumPtChargedPU", Photon_SumPtChargedPU, &b_Photon_SumPtChargedPU);
   fChain->SetBranchAddress("Photon.SumPt", Photon_SumPt, &b_Photon_SumPt);
   fChain->SetBranchAddress("Photon_size", &Photon_size, &b_Photon_size);
   fChain->SetBranchAddress("Electron", &Electron_, &b_Electron_);
   fChain->SetBranchAddress("Electron.fUniqueID", Electron_fUniqueID, &b_Electron_fUniqueID);
   fChain->SetBranchAddress("Electron.fBits", Electron_fBits, &b_Electron_fBits);
   fChain->SetBranchAddress("Electron.PT", Electron_PT, &b_Electron_PT);
   fChain->SetBranchAddress("Electron.Eta", Electron_Eta, &b_Electron_Eta);
   fChain->SetBranchAddress("Electron.Phi", Electron_Phi, &b_Electron_Phi);
   fChain->SetBranchAddress("Electron.T", Electron_T, &b_Electron_T);
   fChain->SetBranchAddress("Electron.Charge", Electron_Charge, &b_Electron_Charge);
   fChain->SetBranchAddress("Electron.EhadOverEem", Electron_EhadOverEem, &b_Electron_EhadOverEem);
   fChain->SetBranchAddress("Electron.Particle", Electron_Particle, &b_Electron_Particle);
   fChain->SetBranchAddress("Electron.IsolationVar", Electron_IsolationVar, &b_Electron_IsolationVar);
   fChain->SetBranchAddress("Electron.IsolationVarRhoCorr", Electron_IsolationVarRhoCorr, &b_Electron_IsolationVarRhoCorr);
   fChain->SetBranchAddress("Electron.SumPtCharged", Electron_SumPtCharged, &b_Electron_SumPtCharged);
   fChain->SetBranchAddress("Electron.SumPtNeutral", Electron_SumPtNeutral, &b_Electron_SumPtNeutral);
   fChain->SetBranchAddress("Electron.SumPtChargedPU", Electron_SumPtChargedPU, &b_Electron_SumPtChargedPU);
   fChain->SetBranchAddress("Electron.SumPt", Electron_SumPt, &b_Electron_SumPt);
   fChain->SetBranchAddress("Electron_size", &Electron_size, &b_Electron_size);
   fChain->SetBranchAddress("MuonLoose", &MuonLoose_, &b_MuonLoose_);
   fChain->SetBranchAddress("MuonLoose.fUniqueID", MuonLoose_fUniqueID, &b_MuonLoose_fUniqueID);
   fChain->SetBranchAddress("MuonLoose.fBits", MuonLoose_fBits, &b_MuonLoose_fBits);
   fChain->SetBranchAddress("MuonLoose.PT", MuonLoose_PT, &b_MuonLoose_PT);
   fChain->SetBranchAddress("MuonLoose.Eta", MuonLoose_Eta, &b_MuonLoose_Eta);
   fChain->SetBranchAddress("MuonLoose.Phi", MuonLoose_Phi, &b_MuonLoose_Phi);
   fChain->SetBranchAddress("MuonLoose.T", MuonLoose_T, &b_MuonLoose_T);
   fChain->SetBranchAddress("MuonLoose.Charge", MuonLoose_Charge, &b_MuonLoose_Charge);
   fChain->SetBranchAddress("MuonLoose.Particle", MuonLoose_Particle, &b_MuonLoose_Particle);
   fChain->SetBranchAddress("MuonLoose.IsolationVar", MuonLoose_IsolationVar, &b_MuonLoose_IsolationVar);
   fChain->SetBranchAddress("MuonLoose.IsolationVarRhoCorr", MuonLoose_IsolationVarRhoCorr, &b_MuonLoose_IsolationVarRhoCorr);
   fChain->SetBranchAddress("MuonLoose.SumPtCharged", MuonLoose_SumPtCharged, &b_MuonLoose_SumPtCharged);
   fChain->SetBranchAddress("MuonLoose.SumPtNeutral", MuonLoose_SumPtNeutral, &b_MuonLoose_SumPtNeutral);
   fChain->SetBranchAddress("MuonLoose.SumPtChargedPU", MuonLoose_SumPtChargedPU, &b_MuonLoose_SumPtChargedPU);
   fChain->SetBranchAddress("MuonLoose.SumPt", MuonLoose_SumPt, &b_MuonLoose_SumPt);
   fChain->SetBranchAddress("MuonLoose_size", &MuonLoose_size, &b_MuonLoose_size);
   fChain->SetBranchAddress("MuonTight", &MuonTight_, &b_MuonTight_);
   fChain->SetBranchAddress("MuonTight.fUniqueID", MuonTight_fUniqueID, &b_MuonTight_fUniqueID);
   fChain->SetBranchAddress("MuonTight.fBits", MuonTight_fBits, &b_MuonTight_fBits);
   fChain->SetBranchAddress("MuonTight.PT", MuonTight_PT, &b_MuonTight_PT);
   fChain->SetBranchAddress("MuonTight.Eta", MuonTight_Eta, &b_MuonTight_Eta);
   fChain->SetBranchAddress("MuonTight.Phi", MuonTight_Phi, &b_MuonTight_Phi);
   fChain->SetBranchAddress("MuonTight.T", MuonTight_T, &b_MuonTight_T);
   fChain->SetBranchAddress("MuonTight.Charge", MuonTight_Charge, &b_MuonTight_Charge);
   fChain->SetBranchAddress("MuonTight.Particle", MuonTight_Particle, &b_MuonTight_Particle);
   fChain->SetBranchAddress("MuonTight.IsolationVar", MuonTight_IsolationVar, &b_MuonTight_IsolationVar);
   fChain->SetBranchAddress("MuonTight.IsolationVarRhoCorr", MuonTight_IsolationVarRhoCorr, &b_MuonTight_IsolationVarRhoCorr);
   fChain->SetBranchAddress("MuonTight.SumPtCharged", MuonTight_SumPtCharged, &b_MuonTight_SumPtCharged);
   fChain->SetBranchAddress("MuonTight.SumPtNeutral", MuonTight_SumPtNeutral, &b_MuonTight_SumPtNeutral);
   fChain->SetBranchAddress("MuonTight.SumPtChargedPU", MuonTight_SumPtChargedPU, &b_MuonTight_SumPtChargedPU);
   fChain->SetBranchAddress("MuonTight.SumPt", MuonTight_SumPt, &b_MuonTight_SumPt);
   fChain->SetBranchAddress("MuonTight_size", &MuonTight_size, &b_MuonTight_size);
   fChain->SetBranchAddress("Jet", &Jet_, &b_Jet_);
   fChain->SetBranchAddress("Jet.fUniqueID", Jet_fUniqueID, &b_Jet_fUniqueID);
   fChain->SetBranchAddress("Jet.fBits", Jet_fBits, &b_Jet_fBits);
   fChain->SetBranchAddress("Jet.PT", Jet_PT, &b_Jet_PT);
   fChain->SetBranchAddress("Jet.Eta", Jet_Eta, &b_Jet_Eta);
   fChain->SetBranchAddress("Jet.Phi", Jet_Phi, &b_Jet_Phi);
   fChain->SetBranchAddress("Jet.T", Jet_T, &b_Jet_T);
   fChain->SetBranchAddress("Jet.Mass", Jet_Mass, &b_Jet_Mass);
   fChain->SetBranchAddress("Jet.DeltaEta", Jet_DeltaEta, &b_Jet_DeltaEta);
   fChain->SetBranchAddress("Jet.DeltaPhi", Jet_DeltaPhi, &b_Jet_DeltaPhi);
   fChain->SetBranchAddress("Jet.Flavor", Jet_Flavor, &b_Jet_Flavor);
   fChain->SetBranchAddress("Jet.FlavorAlgo", Jet_FlavorAlgo, &b_Jet_FlavorAlgo);
   fChain->SetBranchAddress("Jet.FlavorPhys", Jet_FlavorPhys, &b_Jet_FlavorPhys);
   fChain->SetBranchAddress("Jet.BTag", Jet_BTag, &b_Jet_BTag);
   fChain->SetBranchAddress("Jet.BTagAlgo", Jet_BTagAlgo, &b_Jet_BTagAlgo);
   fChain->SetBranchAddress("Jet.BTagPhys", Jet_BTagPhys, &b_Jet_BTagPhys);
   fChain->SetBranchAddress("Jet.TauTag", Jet_TauTag, &b_Jet_TauTag);
   fChain->SetBranchAddress("Jet.Charge", Jet_Charge, &b_Jet_Charge);
   fChain->SetBranchAddress("Jet.EhadOverEem", Jet_EhadOverEem, &b_Jet_EhadOverEem);
   fChain->SetBranchAddress("Jet.NCharged", Jet_NCharged, &b_Jet_NCharged);
   fChain->SetBranchAddress("Jet.NNeutrals", Jet_NNeutrals, &b_Jet_NNeutrals);
   fChain->SetBranchAddress("Jet.Beta", Jet_Beta, &b_Jet_Beta);
   fChain->SetBranchAddress("Jet.BetaStar", Jet_BetaStar, &b_Jet_BetaStar);
   fChain->SetBranchAddress("Jet.MeanSqDeltaR", Jet_MeanSqDeltaR, &b_Jet_MeanSqDeltaR);
   fChain->SetBranchAddress("Jet.PTD", Jet_PTD, &b_Jet_PTD);
   fChain->SetBranchAddress("Jet.FracPt[5]", Jet_FracPt, &b_Jet_FracPt);
   fChain->SetBranchAddress("Jet.Tau[5]", Jet_Tau, &b_Jet_Tau);
   fChain->SetBranchAddress("Jet.TrimmedP4[5]", Jet_TrimmedP4, &b_Jet_TrimmedP4);
   fChain->SetBranchAddress("Jet.PrunedP4[5]", Jet_PrunedP4, &b_Jet_PrunedP4);
   fChain->SetBranchAddress("Jet.SoftDroppedP4[5]", Jet_SoftDroppedP4, &b_Jet_SoftDroppedP4);
   fChain->SetBranchAddress("Jet.NSubJetsTrimmed", Jet_NSubJetsTrimmed, &b_Jet_NSubJetsTrimmed);
   fChain->SetBranchAddress("Jet.NSubJetsPruned", Jet_NSubJetsPruned, &b_Jet_NSubJetsPruned);
   fChain->SetBranchAddress("Jet.NSubJetsSoftDropped", Jet_NSubJetsSoftDropped, &b_Jet_NSubJetsSoftDropped);
   fChain->SetBranchAddress("Jet.Constituents", Jet_Constituents, &b_Jet_Constituents);
   fChain->SetBranchAddress("Jet.Particles", Jet_Particles, &b_Jet_Particles);
   fChain->SetBranchAddress("Jet.Area", Jet_Area, &b_Jet_Area);
   fChain->SetBranchAddress("Jet_size", &Jet_size, &b_Jet_size);
   fChain->SetBranchAddress("JetPUPPI", &JetPUPPI_, &b_JetPUPPI_);
   fChain->SetBranchAddress("JetPUPPI.fUniqueID", JetPUPPI_fUniqueID, &b_JetPUPPI_fUniqueID);
   fChain->SetBranchAddress("JetPUPPI.fBits", JetPUPPI_fBits, &b_JetPUPPI_fBits);
   fChain->SetBranchAddress("JetPUPPI.PT", JetPUPPI_PT, &b_JetPUPPI_PT);
   fChain->SetBranchAddress("JetPUPPI.Eta", JetPUPPI_Eta, &b_JetPUPPI_Eta);
   fChain->SetBranchAddress("JetPUPPI.Phi", JetPUPPI_Phi, &b_JetPUPPI_Phi);
   fChain->SetBranchAddress("JetPUPPI.T", JetPUPPI_T, &b_JetPUPPI_T);
   fChain->SetBranchAddress("JetPUPPI.Mass", JetPUPPI_Mass, &b_JetPUPPI_Mass);
   fChain->SetBranchAddress("JetPUPPI.DeltaEta", JetPUPPI_DeltaEta, &b_JetPUPPI_DeltaEta);
   fChain->SetBranchAddress("JetPUPPI.DeltaPhi", JetPUPPI_DeltaPhi, &b_JetPUPPI_DeltaPhi);
   fChain->SetBranchAddress("JetPUPPI.Flavor", JetPUPPI_Flavor, &b_JetPUPPI_Flavor);
   fChain->SetBranchAddress("JetPUPPI.FlavorAlgo", JetPUPPI_FlavorAlgo, &b_JetPUPPI_FlavorAlgo);
   fChain->SetBranchAddress("JetPUPPI.FlavorPhys", JetPUPPI_FlavorPhys, &b_JetPUPPI_FlavorPhys);
   fChain->SetBranchAddress("JetPUPPI.BTag", JetPUPPI_BTag, &b_JetPUPPI_BTag);
   fChain->SetBranchAddress("JetPUPPI.BTagAlgo", JetPUPPI_BTagAlgo, &b_JetPUPPI_BTagAlgo);
   fChain->SetBranchAddress("JetPUPPI.BTagPhys", JetPUPPI_BTagPhys, &b_JetPUPPI_BTagPhys);
   fChain->SetBranchAddress("JetPUPPI.TauTag", JetPUPPI_TauTag, &b_JetPUPPI_TauTag);
   fChain->SetBranchAddress("JetPUPPI.Charge", JetPUPPI_Charge, &b_JetPUPPI_Charge);
   fChain->SetBranchAddress("JetPUPPI.EhadOverEem", JetPUPPI_EhadOverEem, &b_JetPUPPI_EhadOverEem);
   fChain->SetBranchAddress("JetPUPPI.NCharged", JetPUPPI_NCharged, &b_JetPUPPI_NCharged);
   fChain->SetBranchAddress("JetPUPPI.NNeutrals", JetPUPPI_NNeutrals, &b_JetPUPPI_NNeutrals);
   fChain->SetBranchAddress("JetPUPPI.Beta", JetPUPPI_Beta, &b_JetPUPPI_Beta);
   fChain->SetBranchAddress("JetPUPPI.BetaStar", JetPUPPI_BetaStar, &b_JetPUPPI_BetaStar);
   fChain->SetBranchAddress("JetPUPPI.MeanSqDeltaR", JetPUPPI_MeanSqDeltaR, &b_JetPUPPI_MeanSqDeltaR);
   fChain->SetBranchAddress("JetPUPPI.PTD", JetPUPPI_PTD, &b_JetPUPPI_PTD);
   fChain->SetBranchAddress("JetPUPPI.FracPt[5]", JetPUPPI_FracPt, &b_JetPUPPI_FracPt);
   fChain->SetBranchAddress("JetPUPPI.Tau[5]", JetPUPPI_Tau, &b_JetPUPPI_Tau);
   fChain->SetBranchAddress("JetPUPPI.TrimmedP4[5]", JetPUPPI_TrimmedP4, &b_JetPUPPI_TrimmedP4);
   fChain->SetBranchAddress("JetPUPPI.PrunedP4[5]", JetPUPPI_PrunedP4, &b_JetPUPPI_PrunedP4);
   fChain->SetBranchAddress("JetPUPPI.SoftDroppedP4[5]", JetPUPPI_SoftDroppedP4, &b_JetPUPPI_SoftDroppedP4);
   fChain->SetBranchAddress("JetPUPPI.NSubJetsTrimmed", JetPUPPI_NSubJetsTrimmed, &b_JetPUPPI_NSubJetsTrimmed);
   fChain->SetBranchAddress("JetPUPPI.NSubJetsPruned", JetPUPPI_NSubJetsPruned, &b_JetPUPPI_NSubJetsPruned);
   fChain->SetBranchAddress("JetPUPPI.NSubJetsSoftDropped", JetPUPPI_NSubJetsSoftDropped, &b_JetPUPPI_NSubJetsSoftDropped);
   fChain->SetBranchAddress("JetPUPPI.Constituents", JetPUPPI_Constituents, &b_JetPUPPI_Constituents);
   fChain->SetBranchAddress("JetPUPPI.Particles", JetPUPPI_Particles, &b_JetPUPPI_Particles);
   fChain->SetBranchAddress("JetPUPPI.Area", JetPUPPI_Area, &b_JetPUPPI_Area);
   fChain->SetBranchAddress("JetPUPPI_size", &JetPUPPI_size, &b_JetPUPPI_size);
   fChain->SetBranchAddress("JetAK8", &JetAK8_, &b_JetAK8_);
   fChain->SetBranchAddress("JetAK8.fUniqueID", JetAK8_fUniqueID, &b_JetAK8_fUniqueID);
   fChain->SetBranchAddress("JetAK8.fBits", JetAK8_fBits, &b_JetAK8_fBits);
   fChain->SetBranchAddress("JetAK8.PT", JetAK8_PT, &b_JetAK8_PT);
   fChain->SetBranchAddress("JetAK8.Eta", JetAK8_Eta, &b_JetAK8_Eta);
   fChain->SetBranchAddress("JetAK8.Phi", JetAK8_Phi, &b_JetAK8_Phi);
   fChain->SetBranchAddress("JetAK8.T", JetAK8_T, &b_JetAK8_T);
   fChain->SetBranchAddress("JetAK8.Mass", JetAK8_Mass, &b_JetAK8_Mass);
   fChain->SetBranchAddress("JetAK8.DeltaEta", JetAK8_DeltaEta, &b_JetAK8_DeltaEta);
   fChain->SetBranchAddress("JetAK8.DeltaPhi", JetAK8_DeltaPhi, &b_JetAK8_DeltaPhi);
   fChain->SetBranchAddress("JetAK8.Flavor", JetAK8_Flavor, &b_JetAK8_Flavor);
   fChain->SetBranchAddress("JetAK8.FlavorAlgo", JetAK8_FlavorAlgo, &b_JetAK8_FlavorAlgo);
   fChain->SetBranchAddress("JetAK8.FlavorPhys", JetAK8_FlavorPhys, &b_JetAK8_FlavorPhys);
   fChain->SetBranchAddress("JetAK8.BTag", JetAK8_BTag, &b_JetAK8_BTag);
   fChain->SetBranchAddress("JetAK8.BTagAlgo", JetAK8_BTagAlgo, &b_JetAK8_BTagAlgo);
   fChain->SetBranchAddress("JetAK8.BTagPhys", JetAK8_BTagPhys, &b_JetAK8_BTagPhys);
   fChain->SetBranchAddress("JetAK8.TauTag", JetAK8_TauTag, &b_JetAK8_TauTag);
   fChain->SetBranchAddress("JetAK8.Charge", JetAK8_Charge, &b_JetAK8_Charge);
   fChain->SetBranchAddress("JetAK8.EhadOverEem", JetAK8_EhadOverEem, &b_JetAK8_EhadOverEem);
   fChain->SetBranchAddress("JetAK8.NCharged", JetAK8_NCharged, &b_JetAK8_NCharged);
   fChain->SetBranchAddress("JetAK8.NNeutrals", JetAK8_NNeutrals, &b_JetAK8_NNeutrals);
   fChain->SetBranchAddress("JetAK8.Beta", JetAK8_Beta, &b_JetAK8_Beta);
   fChain->SetBranchAddress("JetAK8.BetaStar", JetAK8_BetaStar, &b_JetAK8_BetaStar);
   fChain->SetBranchAddress("JetAK8.MeanSqDeltaR", JetAK8_MeanSqDeltaR, &b_JetAK8_MeanSqDeltaR);
   fChain->SetBranchAddress("JetAK8.PTD", JetAK8_PTD, &b_JetAK8_PTD);
   fChain->SetBranchAddress("JetAK8.FracPt[5]", JetAK8_FracPt, &b_JetAK8_FracPt);
   fChain->SetBranchAddress("JetAK8.Tau[5]", JetAK8_Tau, &b_JetAK8_Tau);
   fChain->SetBranchAddress("JetAK8.TrimmedP4[5]", JetAK8_TrimmedP4, &b_JetAK8_TrimmedP4);
   fChain->SetBranchAddress("JetAK8.PrunedP4[5]", JetAK8_PrunedP4, &b_JetAK8_PrunedP4);
   fChain->SetBranchAddress("JetAK8.SoftDroppedP4[5]", JetAK8_SoftDroppedP4, &b_JetAK8_SoftDroppedP4);
   fChain->SetBranchAddress("JetAK8.NSubJetsTrimmed", JetAK8_NSubJetsTrimmed, &b_JetAK8_NSubJetsTrimmed);
   fChain->SetBranchAddress("JetAK8.NSubJetsPruned", JetAK8_NSubJetsPruned, &b_JetAK8_NSubJetsPruned);
   fChain->SetBranchAddress("JetAK8.NSubJetsSoftDropped", JetAK8_NSubJetsSoftDropped, &b_JetAK8_NSubJetsSoftDropped);
   fChain->SetBranchAddress("JetAK8.Constituents", JetAK8_Constituents, &b_JetAK8_Constituents);
   fChain->SetBranchAddress("JetAK8.Particles", JetAK8_Particles, &b_JetAK8_Particles);
   fChain->SetBranchAddress("JetAK8.Area", JetAK8_Area, &b_JetAK8_Area);
   fChain->SetBranchAddress("JetAK8_size", &JetAK8_size, &b_JetAK8_size);
   fChain->SetBranchAddress("JetPUPPIAK8", &JetPUPPIAK8_, &b_JetPUPPIAK8_);
   fChain->SetBranchAddress("JetPUPPIAK8.fUniqueID", JetPUPPIAK8_fUniqueID, &b_JetPUPPIAK8_fUniqueID);
   fChain->SetBranchAddress("JetPUPPIAK8.fBits", JetPUPPIAK8_fBits, &b_JetPUPPIAK8_fBits);
   fChain->SetBranchAddress("JetPUPPIAK8.PT", JetPUPPIAK8_PT, &b_JetPUPPIAK8_PT);
   fChain->SetBranchAddress("JetPUPPIAK8.Eta", JetPUPPIAK8_Eta, &b_JetPUPPIAK8_Eta);
   fChain->SetBranchAddress("JetPUPPIAK8.Phi", JetPUPPIAK8_Phi, &b_JetPUPPIAK8_Phi);
   fChain->SetBranchAddress("JetPUPPIAK8.T", JetPUPPIAK8_T, &b_JetPUPPIAK8_T);
   fChain->SetBranchAddress("JetPUPPIAK8.Mass", JetPUPPIAK8_Mass, &b_JetPUPPIAK8_Mass);
   fChain->SetBranchAddress("JetPUPPIAK8.DeltaEta", JetPUPPIAK8_DeltaEta, &b_JetPUPPIAK8_DeltaEta);
   fChain->SetBranchAddress("JetPUPPIAK8.DeltaPhi", JetPUPPIAK8_DeltaPhi, &b_JetPUPPIAK8_DeltaPhi);
   fChain->SetBranchAddress("JetPUPPIAK8.Flavor", JetPUPPIAK8_Flavor, &b_JetPUPPIAK8_Flavor);
   fChain->SetBranchAddress("JetPUPPIAK8.FlavorAlgo", JetPUPPIAK8_FlavorAlgo, &b_JetPUPPIAK8_FlavorAlgo);
   fChain->SetBranchAddress("JetPUPPIAK8.FlavorPhys", JetPUPPIAK8_FlavorPhys, &b_JetPUPPIAK8_FlavorPhys);
   fChain->SetBranchAddress("JetPUPPIAK8.BTag", JetPUPPIAK8_BTag, &b_JetPUPPIAK8_BTag);
   fChain->SetBranchAddress("JetPUPPIAK8.BTagAlgo", JetPUPPIAK8_BTagAlgo, &b_JetPUPPIAK8_BTagAlgo);
   fChain->SetBranchAddress("JetPUPPIAK8.BTagPhys", JetPUPPIAK8_BTagPhys, &b_JetPUPPIAK8_BTagPhys);
   fChain->SetBranchAddress("JetPUPPIAK8.TauTag", JetPUPPIAK8_TauTag, &b_JetPUPPIAK8_TauTag);
   fChain->SetBranchAddress("JetPUPPIAK8.Charge", JetPUPPIAK8_Charge, &b_JetPUPPIAK8_Charge);
   fChain->SetBranchAddress("JetPUPPIAK8.EhadOverEem", JetPUPPIAK8_EhadOverEem, &b_JetPUPPIAK8_EhadOverEem);
   fChain->SetBranchAddress("JetPUPPIAK8.NCharged", JetPUPPIAK8_NCharged, &b_JetPUPPIAK8_NCharged);
   fChain->SetBranchAddress("JetPUPPIAK8.NNeutrals", JetPUPPIAK8_NNeutrals, &b_JetPUPPIAK8_NNeutrals);
   fChain->SetBranchAddress("JetPUPPIAK8.Beta", JetPUPPIAK8_Beta, &b_JetPUPPIAK8_Beta);
   fChain->SetBranchAddress("JetPUPPIAK8.BetaStar", JetPUPPIAK8_BetaStar, &b_JetPUPPIAK8_BetaStar);
   fChain->SetBranchAddress("JetPUPPIAK8.MeanSqDeltaR", JetPUPPIAK8_MeanSqDeltaR, &b_JetPUPPIAK8_MeanSqDeltaR);
   fChain->SetBranchAddress("JetPUPPIAK8.PTD", JetPUPPIAK8_PTD, &b_JetPUPPIAK8_PTD);
   fChain->SetBranchAddress("JetPUPPIAK8.FracPt[5]", JetPUPPIAK8_FracPt, &b_JetPUPPIAK8_FracPt);
   fChain->SetBranchAddress("JetPUPPIAK8.Tau[5]", JetPUPPIAK8_Tau, &b_JetPUPPIAK8_Tau);
   fChain->SetBranchAddress("JetPUPPIAK8.TrimmedP4[5]", JetPUPPIAK8_TrimmedP4, &b_JetPUPPIAK8_TrimmedP4);
   fChain->SetBranchAddress("JetPUPPIAK8.PrunedP4[5]", JetPUPPIAK8_PrunedP4, &b_JetPUPPIAK8_PrunedP4);
   fChain->SetBranchAddress("JetPUPPIAK8.SoftDroppedP4[5]", JetPUPPIAK8_SoftDroppedP4, &b_JetPUPPIAK8_SoftDroppedP4);
   fChain->SetBranchAddress("JetPUPPIAK8.NSubJetsTrimmed", JetPUPPIAK8_NSubJetsTrimmed, &b_JetPUPPIAK8_NSubJetsTrimmed);
   fChain->SetBranchAddress("JetPUPPIAK8.NSubJetsPruned", JetPUPPIAK8_NSubJetsPruned, &b_JetPUPPIAK8_NSubJetsPruned);
   fChain->SetBranchAddress("JetPUPPIAK8.NSubJetsSoftDropped", JetPUPPIAK8_NSubJetsSoftDropped, &b_JetPUPPIAK8_NSubJetsSoftDropped);
   fChain->SetBranchAddress("JetPUPPIAK8.Constituents", JetPUPPIAK8_Constituents, &b_JetPUPPIAK8_Constituents);
   fChain->SetBranchAddress("JetPUPPIAK8.Particles", JetPUPPIAK8_Particles, &b_JetPUPPIAK8_Particles);
   fChain->SetBranchAddress("JetPUPPIAK8.Area", JetPUPPIAK8_Area, &b_JetPUPPIAK8_Area);
   fChain->SetBranchAddress("JetPUPPIAK8_size", &JetPUPPIAK8_size, &b_JetPUPPIAK8_size);
   fChain->SetBranchAddress("MissingET", &MissingET_, &b_MissingET_);
   fChain->SetBranchAddress("MissingET.fUniqueID", MissingET_fUniqueID, &b_MissingET_fUniqueID);
   fChain->SetBranchAddress("MissingET.fBits", MissingET_fBits, &b_MissingET_fBits);
   fChain->SetBranchAddress("MissingET.MET", MissingET_MET, &b_MissingET_MET);
   fChain->SetBranchAddress("MissingET.Eta", MissingET_Eta, &b_MissingET_Eta);
   fChain->SetBranchAddress("MissingET.Phi", MissingET_Phi, &b_MissingET_Phi);
   fChain->SetBranchAddress("MissingET_size", &MissingET_size, &b_MissingET_size);
   fChain->SetBranchAddress("PuppiMissingET", &PuppiMissingET_, &b_PuppiMissingET_);
   fChain->SetBranchAddress("PuppiMissingET.fUniqueID", PuppiMissingET_fUniqueID, &b_PuppiMissingET_fUniqueID);
   fChain->SetBranchAddress("PuppiMissingET.fBits", PuppiMissingET_fBits, &b_PuppiMissingET_fBits);
   fChain->SetBranchAddress("PuppiMissingET.MET", PuppiMissingET_MET, &b_PuppiMissingET_MET);
   fChain->SetBranchAddress("PuppiMissingET.Eta", PuppiMissingET_Eta, &b_PuppiMissingET_Eta);
   fChain->SetBranchAddress("PuppiMissingET.Phi", PuppiMissingET_Phi, &b_PuppiMissingET_Phi);
   fChain->SetBranchAddress("PuppiMissingET_size", &PuppiMissingET_size, &b_PuppiMissingET_size);
   fChain->SetBranchAddress("GenPileUpMissingET", &GenPileUpMissingET_, &b_GenPileUpMissingET_);
   fChain->SetBranchAddress("GenPileUpMissingET.fUniqueID", GenPileUpMissingET_fUniqueID, &b_GenPileUpMissingET_fUniqueID);
   fChain->SetBranchAddress("GenPileUpMissingET.fBits", GenPileUpMissingET_fBits, &b_GenPileUpMissingET_fBits);
   fChain->SetBranchAddress("GenPileUpMissingET.MET", GenPileUpMissingET_MET, &b_GenPileUpMissingET_MET);
   fChain->SetBranchAddress("GenPileUpMissingET.Eta", GenPileUpMissingET_Eta, &b_GenPileUpMissingET_Eta);
   fChain->SetBranchAddress("GenPileUpMissingET.Phi", GenPileUpMissingET_Phi, &b_GenPileUpMissingET_Phi);
   fChain->SetBranchAddress("GenPileUpMissingET_size", &GenPileUpMissingET_size, &b_GenPileUpMissingET_size);
   fChain->SetBranchAddress("ScalarHT", &ScalarHT_, &b_ScalarHT_);
   fChain->SetBranchAddress("ScalarHT.fUniqueID", ScalarHT_fUniqueID, &b_ScalarHT_fUniqueID);
   fChain->SetBranchAddress("ScalarHT.fBits", ScalarHT_fBits, &b_ScalarHT_fBits);
   fChain->SetBranchAddress("ScalarHT.HT", ScalarHT_HT, &b_ScalarHT_HT);
   fChain->SetBranchAddress("ScalarHT_size", &ScalarHT_size, &b_ScalarHT_size);
   Notify();
}

Bool_t Delphes::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void Delphes::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t Delphes::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef Delphes_cxx
