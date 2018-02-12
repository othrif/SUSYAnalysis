//////////////////////////////////////////////////////////
// Author:      Othmane Rifki
// Contact:     othmane.rifki@cern.ch
// Description: Matches the branches in MiniNtuple
// Date 2016-07-11 07:29:16
//////////////////////////////////////////////////////////

#ifndef MYEVT_N_HH_
#define MYEVT_N_HH_

//------------------------------------------------------------------------
//				-= Constants =-
//------------------------------------------------------------------------

const Int_t MAXJETS = 100;
const Int_t MAXLEPT = 25;

//------------------------------------------------------------------------
//				-= Structures =-
//------------------------------------------------------------------------

//This is the format used to store the reduced ntuple
//------------------------------------------------------------------------

struct my_event {

  Bool_t isMC;
  Double_t           sumWeight;
  Double_t           sumWeightsq;
  Double_t           rawEvents;
  Int_t              trigRND;


  //  Declaration of leaf types
  Bool_t	 HLT_e24_lhmedium_nod0_ivarloose;
  Bool_t	 HLT_e24_lhtight_nod0_ivarloose;
  Bool_t	 HLT_e24_lhmedium_nod0_L1EM20VH;
  Bool_t	 HLT_e26_lhtight_iloose;
  Bool_t	 HLT_e26_lhtight_ivarloose;
  Bool_t	 HLT_e26_lhtight_nod0_iloose;
  Bool_t	 HLT_e26_lhtight_nod0_ivarloose;
  Bool_t	 HLT_e60_lhmedium;
  Bool_t	 HLT_e60_lhmedium_nod0;
  Bool_t	 HLT_e120_lhloose_nod0;
  Bool_t	 HLT_e140_lhloose_nod0;
  Bool_t	 HLT_2e17_lhvloose_nod0;
  Bool_t	 HLT_2e15_lhvloose_nod0_L12EM13VH;
  Bool_t	 HLT_e24_lhmedium_e9_lhmedium;
  Bool_t	 HLT_e24_lhmedium_L1EM20VH;
  Bool_t	 HLT_e12_lhvloose_L12EM10VH;
  Bool_t	 HLT_e17_lhloose_2e9_lhloose;
  Bool_t	 HLT_mu24_ivarmedium;
  Bool_t	 HLT_mu24_imedium;
  Bool_t	 HLT_mu24_ivarloose;
  Bool_t	 HLT_mu24_iloose;
  Bool_t	 HLT_mu26_ivarmedium;
  Bool_t	 HLT_mu26_imedium;
  Bool_t	 HLT_mu20_ivarmedium_L1MU15;
  Bool_t	 HLT_mu20_imedium_L1MU15;
  Bool_t	 HLT_mu20_ivarloose_L1MU15;
  Bool_t	 HLT_mu20_iloose_L1MU15;
  Bool_t	 HLT_mu20_L1MU15;
  Bool_t	 HLT_mu20_mu8noL1;
  Bool_t	 HLT_mu22_mu8noL1;
  Bool_t	 HLT_mu20_2mu4noL1;
  Bool_t	 HLT_mu22_2mu4noL1;
  Bool_t	 HLT_mu40;
  Bool_t	 HLT_mu50;
  Bool_t	 HLT_2mu10;
  Bool_t	 HLT_2mu10_nomucomb;
  Bool_t	 HLT_2mu14;
  Bool_t	 HLT_2mu14_nomucomb;
  Bool_t	 HLT_3mu6;
  Bool_t	 HLT_3mu6_msonly;
  Bool_t	 HLT_xe100_L1XE50;
  Bool_t	 HLT_xe80_mht_L1XE50;
  Bool_t	 HLT_xe90_mht_L1XE50;
  Bool_t	 HLT_xe100_mht_L1XE50;
  Bool_t	 HLT_xe110_pueta_L1XE50;
  Bool_t	 HLT_xe110_pufit_L1XE50;
  Bool_t	 HLT_xe100_tc_em_L1XE50;
  Bool_t	 HLT_xe80_tc_lcw_L1XE50;
  Bool_t	 HLT_xe90_tc_lcw_L1XE50;
  Bool_t	 HLT_xe80_tc_lcw_wEFMu_L1XE50;
  Bool_t	 HLT_e7_lhmedium_mu24;
  Bool_t	 HLT_e17_lhloose_nod0_mu14;
  Bool_t	 HLT_e26_lhmedium_nod0_L1EM22VHI_mu8noL1;
  Bool_t	 HLT_e24_lhmedium_nod0_L1EM22VHI_mu8noL1;
  Bool_t	 HLT_2e12_lhloose_L12EM10VH;
  Bool_t	 HLT_e17_lhloose_mu14;
  Bool_t	 HLT_mu18_mu8noL1;
  Bool_t	 HLT_xe70;
  ULong64_t	 EventNumber;
  Int_t	 ChannelNumber;
  Double_t	 AvgMu;
  Double_t	 EventWeight;
  Double_t	 PRWWeight;
  Int_t	 PRWrandomRunNumber;
  Int_t	 bcid;
  Int_t	 LB;
  Int_t	 RunNb;
  Int_t	 DetError;
  Int_t	 NMu;
  Int_t	 NMuPair;
  Double_t	 Mu_eta[MAXLEPT];
  Double_t	 Mu_phi[MAXLEPT];
  Double_t	 Mu_pT[MAXLEPT];
  Double_t	 Mu_SFw[MAXLEPT];
  Float_t	 Mu_IsoSFw[MAXLEPT];
  Int_t	 Mu_charge[MAXLEPT];
  Double_t	 Mu_d0pvtx[MAXLEPT];
  Double_t	 Mu_sigd0[MAXLEPT];
  Double_t	 Mu_z0sinTheta[MAXLEPT];
  Bool_t	 Mu_isBad[MAXLEPT];
  Bool_t	 Mu_passOR[MAXLEPT];
  Bool_t	 Mu_isTight[MAXLEPT];
  Bool_t	 Mu_isCosmic[MAXLEPT];
  Int_t	 Mu_type[MAXLEPT];
  Int_t	 Mu_origin[MAXLEPT];
  Double_t	 Mu_ptcone20[MAXLEPT];
  Double_t	 Mu_ptcone30[MAXLEPT];
  Double_t	 Mu_ptcone40[MAXLEPT];
  Double_t	 Mu_ptvarcone20[MAXLEPT];
  Double_t	 Mu_ptvarcone30[MAXLEPT];
  Double_t	 Mu_ptvarcone40[MAXLEPT];
  Double_t	 Mu_topoetcone20[MAXLEPT];
  Double_t	 Mu_topoetcone30[MAXLEPT];
  Double_t	 Mu_topoetcone40[MAXLEPT];
  Bool_t	 Mu_passIsoLooseTO[MAXLEPT];
  Bool_t	 Mu_passIsoLoose[MAXLEPT];
  Bool_t	 Mu_passIsoTight[MAXLEPT];
  Bool_t	 Mu_passIsoGrad[MAXLEPT];
  Bool_t	 Mu_passIsoGradCustomTight[MAXLEPT];
  Bool_t	 Mu_passIsoGradCustom[MAXLEPT];
  Bool_t	 Mu_passIsoGradLoose[MAXLEPT];
  Float_t	 MuTrigSF_HLT_mu20_iloose_L1MU15_OR_HLT_mu50;
  Bool_t	 Mu_trigMatch_mu26_imedium[MAXLEPT];
  Bool_t	 Mu_trigMatch_mu50[MAXLEPT];
  Bool_t	 Mu_trigMatch_mu8noL1[MAXLEPT];
  Bool_t	 Mu_trigMatch_mu14[MAXLEPT];
  Bool_t	 Mu_trigMatch_mu18[MAXLEPT];
  Bool_t	 Mu_trigMatch_mu18_mu8noL1[MAXLEPT];
  Bool_t	 Mu_trigMatch_e17_lhloose_mu14[MAXLEPT];
  Bool_t	 Mu_trigMatch_e17_lhloose_nod0_mu14[MAXLEPT];
  Bool_t	 Mu_trigMatch_mu20_mu8noL1[MAXLEPT];
  Bool_t	 Mu_trigMatch_mu22_mu8noL1[MAXLEPT];
  Bool_t	 Mu_TrigMatch_mu24_iloose[MAXLEPT];
  Bool_t	 Mu_TrigMatch_mu24_ivarloose[MAXLEPT];
  Bool_t	 Mu_TrigMatch_mu24_iloose_L1MU15[MAXLEPT];
  Bool_t	 Mu_TrigMatch_mu24_ivarloose_L1MU15[MAXLEPT];
  Bool_t	 Mu_trigMatchPair_mu18_mu8noL1[MAXLEPT];
  Bool_t	 Mu_trigMatchPair_mu20_mu8noL1[MAXLEPT];
  Int_t	 NEl;
  Double_t	 El_eta[MAXLEPT];
  Double_t	 El_etaclus[MAXLEPT];
  Double_t	 El_phi[MAXLEPT];
  Double_t	 El_pT[MAXLEPT];
  Double_t	 El_E[MAXLEPT];
  Int_t	 El_charge[MAXLEPT];
  Double_t	 El_sigd0[MAXLEPT];
  Double_t	 El_z0sinTheta[MAXLEPT];
  Double_t	 El_d0pvtx[MAXLEPT];
  Bool_t	 El_passOR[MAXLEPT];
  Double_t	 El_SFwMediumLH[MAXLEPT];
  Float_t	 El_IsoSFwMediumLH[MAXLEPT];
  Double_t	 El_SFwTightLH[MAXLEPT];
  Double_t	 El_SFwLooseAndBLayerLH[MAXLEPT];
  Double_t	 El_SFwTrigMediumLH_e12_lhloose_L1EM10VH[MAXLEPT];
  Double_t	 El_SFwTrigMediumLH_e17_lhloose[MAXLEPT];
  Double_t	 El_SFwTrigMediumLH_single[MAXLEPT];
  Double_t	 El_SFwTrigLooseAndBLayerLH_e12_lhloose_L1EM10VH[MAXLEPT];
  Bool_t	 El_isLooseAndBLayerLH[MAXLEPT];
  Bool_t	 El_isMediumLH[MAXLEPT];
  Bool_t	 El_isTightLH[MAXLEPT];
  Int_t	 El_nBLayerHits[MAXLEPT];
  Int_t	 El_expectBLayerHit[MAXLEPT];
  Int_t	 El_type[MAXLEPT];
  Int_t	 El_origin[MAXLEPT];
  Int_t	 El_bkgMotherPdgId[MAXLEPT];
  Int_t	 El_bkgOrigin[MAXLEPT];
  Int_t	 El_chFlip[MAXLEPT];
  Double_t	 El_ptcone20[MAXLEPT];
  Double_t	 El_ptcone30[MAXLEPT];
  Double_t	 El_ptcone40[MAXLEPT];
  Double_t	 El_ptvarcone20[MAXLEPT];
  Double_t	 El_ptvarcone30[MAXLEPT];
  Double_t	 El_ptvarcone40[MAXLEPT];
  Double_t	 El_topoetcone20[MAXLEPT];
  Double_t	 El_topoetcone30[MAXLEPT];
  Double_t	 El_topoetcone40[MAXLEPT];
  Bool_t	 El_passIsoLooseTO[MAXLEPT];
  Bool_t	 El_passIsoLoose[MAXLEPT];
  Bool_t	 El_passIsoTight[MAXLEPT];
  Bool_t	 El_passIsoGrad[MAXLEPT];
  Bool_t	 El_passIsoGradCustomTight[MAXLEPT];
  Bool_t	 El_passIsoGradCustom[MAXLEPT];
  Bool_t	 El_passIsoGradLoose[MAXLEPT];
  Bool_t	 El_trigMatch_e12_lhloose_L1EM10VH[MAXLEPT];
  Bool_t	 El_trigMatch_e17_lhloose[MAXLEPT];
  Bool_t	 El_trigMatch_e60_lhmedium[MAXLEPT];
  Bool_t	 El_trigMatch_e24_lhmedium_iloose_L1EM20VH[MAXLEPT];
  Bool_t	 El_trigMatch_2e12_lhloose_L12EM10VH[MAXLEPT];
  Bool_t	 El_trigMatch_2e15_lhloose_L12EM10VH[MAXLEPT];
  Bool_t	 El_trigMatch_2e15_lhvloose_L12EM13VH[MAXLEPT];
  Bool_t	 El_trigMatch_2e15_lhvloose_nod0_L12EM13VH[MAXLEPT];
  Bool_t	 El_trigMatch_2e17_lhvloose_nod0[MAXLEPT];
  Bool_t	 El_trigMatch_e17_lhloose_mu14[MAXLEPT];
  Bool_t	 El_trigMatch_e17_lhloose_nod0_mu14[MAXLEPT];
  Bool_t	 El_TrigMatch_e24_lhmedium_nod0_ivarloose[MAXLEPT];
  Bool_t	 El_TrigMatch_e24_lhtight_nod0_ivarloose[MAXLEPT];
  Bool_t	 El_TrigMatch_e60_lhmedium_nod0[MAXLEPT];
  Int_t	 NJet;
  Double_t	 Jet_eta[MAXJETS];
  Double_t	 Jet_phi[MAXJETS];
  Double_t	 Jet_pT[MAXJETS];
  Double_t	 Jet_E[MAXJETS];
  Double_t	 Jet_quality[MAXJETS];
  Double_t	 Jet_JVT[MAXJETS];
  Double_t	 Jet_JVTsf[MAXJETS];
  Double_t	 Jet_MV2c20[MAXJETS];
  Double_t	 Jet_MV2c10[MAXJETS];
  Double_t	 Jet_SFw[MAXJETS];
  Int_t	 Jet_ConeTruthLabel[MAXJETS];
  Int_t	 Jet_PartonTruthLabel[MAXJETS];
  Int_t	 Jet_HadronConeExclTruthLabel[MAXJETS];
  Double_t	 Jet_deltaR[MAXJETS];
  Int_t	 Jet_nTrk[MAXJETS];
  Bool_t	 Jet_passOR[MAXJETS];
  Float_t	 Etmiss_CST_Etx;
  Float_t	 Etmiss_CST_Ety;
  Float_t	 Etmiss_CST_Et;
  Float_t	 Etmiss_TST_Etx;
  Float_t	 Etmiss_TST_Ety;
  Float_t	 Etmiss_TST_Et;
  Float_t	 Etmiss_TSTterm_Etx;
  Float_t	 Etmiss_TSTterm_Ety;
  Float_t	 Etmiss_TSTterm_Et;
  Float_t	 Etmiss_Truth_Etx;
  Float_t	 Etmiss_Truth_Ety;
  Float_t	 Etmiss_Truth_Et;
  Int_t	 NTruthJet;
  Double_t	 TruthJet_eta[MAXJETS];
  Double_t	 TruthJet_phi[MAXJETS];
  Double_t	 TruthJet_pT[MAXJETS];
  Double_t	 TruthJet_E[MAXJETS];
  Int_t	 TruthJet_ConeTruthLabel[MAXJETS];
  Int_t	 TruthJet_PartonTruthLabel[MAXJETS];
  Int_t	 NTruthL;
  Double_t	 TruthL_eta[MAXLEPT];
  Double_t	 TruthL_phi[MAXLEPT];
  Double_t	 TruthL_pT[MAXLEPT];
  Int_t	 TruthL_id[MAXLEPT];
  Int_t	 SUSY_Spart_pdgId1;
  Int_t	 SUSY_Spart_pdgId2;
  Int_t	 SUSY_Gluino_decay1;
  Int_t	 SUSY_Gluino_decay2;
  Float_t	 GenFiltHT;
  Float_t	 GenFiltMET;
  Float_t	 PV_z;
  Int_t	 Nvtx;
  Float_t	 TruthX1;
  Float_t	 TruthX2;
  Float_t	 TruthQ;
  Float_t	 SherpaNjetWeight;
  Int_t	 TruthPDGID1;
  Int_t	 TruthPDGID2;
};

typedef struct my_event myevt;

// defines the lepton collection in the event
struct lepton_info {
  int num_leptons; 
  int num_leptons_baseline; 

  int index[2 * MAXLEPT];
  Double_t pT[2 * MAXLEPT]; 
  Double_t phi[2 * MAXLEPT]; 
  Double_t eta[2 * MAXLEPT]; 
  Double_t E[2 * MAXLEPT]; 
  Double_t m[2 * MAXLEPT]; 
  bool is_electron[2 * MAXLEPT];
  Double_t SFw[2 * MAXLEPT];
  float charge[2 * MAXLEPT];

  bool has_ee;
  bool has_em;
  bool has_mm;
  bool has_ss;

  bool has_Z;
  bool has_Z_SS;  
  bool has_Z_OS;
  bool has_Z_OS_SR3L3b;
  bool has_Z_lll;
  double MZ;
  double lowest_M;
  double m_ll[MAXLEPT]; // 0->12, 1->13, 2->23 or 2->14...
  int ind1;
  int ind2;
  int ind1_Mll;
  int ind2_Mll;

  bool is_fake_HF[2 * MAXLEPT];
  bool is_fake_LF[2 * MAXLEPT];
  bool is_chmisid[2 * MAXLEPT];

};
typedef struct lepton_info my_leptons;

// refers to individual lepton and not the collection 
struct short_lep {
  bool is_electron;
  double pT;
  int ind;
};

// defines the jet collection in the event
struct jet_info{
  int num_jets;
  int index[MAXJETS];
  Double_t pT[MAXJETS]; 
  Double_t phi[MAXJETS]; 
  Double_t eta[MAXJETS]; 
  Double_t E[MAXJETS]; 
  Double_t MV2c20[MAXJETS];
};
typedef struct jet_info my_jets;

// refers to individual jet and not the collection 
struct short_jet {
  double pt;
  int ind;
};
typedef struct short_jet srtJt;


struct duplicate {
  Double_t genFiltHT;
  Double_t genFiltMET;
  Int_t runNb;
  Int_t eventNumber;
}; 


#endif /* MYEVT_N_HH_ */



