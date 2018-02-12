//////////////////////////////////////////////////////////
// Author:      Othmane Rifki
// Contact:     othmane.rifki@cern.ch
// Description: Matches the branches in MiniNtuple
// Date 2016-07-11 07:29:16
//////////////////////////////////////////////////////////



// These are ROOT header files.
#include "TTree.h"
#include "TChain.h"
#include "TBranch.h"
#include "TLeaf.h"

//here are the project-specific files
#include "Analyzer/myevt.h"

void declarestructs(TTree* tree, myevt* evt) {
  TBranch *b;

  if( (b = tree->GetBranch("myevt")) ) {

b->GetLeaf("isMC")->SetAddress(&(evt->isMC));
b->GetLeaf("sumWeight")->SetAddress(&(evt->sumWeight));
b->GetLeaf("sumWeightsq")->SetAddress(&(evt->sumWeightsq));
b->GetLeaf("rawEvents")->SetAddress(&(evt->rawEvents));
   b->GetLeaf("HLT_e24_lhmedium_nod0_ivarloose")->SetAddress(&(evt->HLT_e24_lhmedium_nod0_ivarloose));
   b->GetLeaf("HLT_e24_lhtight_nod0_ivarloose")->SetAddress(&(evt->HLT_e24_lhtight_nod0_ivarloose));
   b->GetLeaf("HLT_e24_lhmedium_nod0_L1EM20VH")->SetAddress(&(evt->HLT_e24_lhmedium_nod0_L1EM20VH));
   b->GetLeaf("HLT_e26_lhtight_iloose")->SetAddress(&(evt->HLT_e26_lhtight_iloose));
   b->GetLeaf("HLT_e26_lhtight_ivarloose")->SetAddress(&(evt->HLT_e26_lhtight_ivarloose));
   b->GetLeaf("HLT_e26_lhtight_nod0_iloose")->SetAddress(&(evt->HLT_e26_lhtight_nod0_iloose));
   b->GetLeaf("HLT_e26_lhtight_nod0_ivarloose")->SetAddress(&(evt->HLT_e26_lhtight_nod0_ivarloose));
   b->GetLeaf("HLT_e60_lhmedium")->SetAddress(&(evt->HLT_e60_lhmedium));
   b->GetLeaf("HLT_e60_lhmedium_nod0")->SetAddress(&(evt->HLT_e60_lhmedium_nod0));
   b->GetLeaf("HLT_e120_lhloose_nod0")->SetAddress(&(evt->HLT_e120_lhloose_nod0));
   b->GetLeaf("HLT_e140_lhloose_nod0")->SetAddress(&(evt->HLT_e140_lhloose_nod0));
   b->GetLeaf("HLT_2e17_lhvloose_nod0")->SetAddress(&(evt->HLT_2e17_lhvloose_nod0));
   b->GetLeaf("HLT_2e15_lhvloose_nod0_L12EM13VH")->SetAddress(&(evt->HLT_2e15_lhvloose_nod0_L12EM13VH));
   b->GetLeaf("HLT_e24_lhmedium_e9_lhmedium")->SetAddress(&(evt->HLT_e24_lhmedium_e9_lhmedium));
   b->GetLeaf("HLT_e24_lhmedium_L1EM20VH")->SetAddress(&(evt->HLT_e24_lhmedium_L1EM20VH));
   b->GetLeaf("HLT_e12_lhvloose_L12EM10VH")->SetAddress(&(evt->HLT_e12_lhvloose_L12EM10VH));
   b->GetLeaf("HLT_e17_lhloose_2e9_lhloose")->SetAddress(&(evt->HLT_e17_lhloose_2e9_lhloose));
   b->GetLeaf("HLT_mu24_ivarmedium")->SetAddress(&(evt->HLT_mu24_ivarmedium));
   b->GetLeaf("HLT_mu24_imedium")->SetAddress(&(evt->HLT_mu24_imedium));
   b->GetLeaf("HLT_mu24_ivarloose")->SetAddress(&(evt->HLT_mu24_ivarloose));
   b->GetLeaf("HLT_mu24_iloose")->SetAddress(&(evt->HLT_mu24_iloose));
   b->GetLeaf("HLT_mu26_ivarmedium")->SetAddress(&(evt->HLT_mu26_ivarmedium));
   b->GetLeaf("HLT_mu26_imedium")->SetAddress(&(evt->HLT_mu26_imedium));
   b->GetLeaf("HLT_mu20_ivarmedium_L1MU15")->SetAddress(&(evt->HLT_mu20_ivarmedium_L1MU15));
   b->GetLeaf("HLT_mu20_imedium_L1MU15")->SetAddress(&(evt->HLT_mu20_imedium_L1MU15));
   b->GetLeaf("HLT_mu20_ivarloose_L1MU15")->SetAddress(&(evt->HLT_mu20_ivarloose_L1MU15));
   b->GetLeaf("HLT_mu20_iloose_L1MU15")->SetAddress(&(evt->HLT_mu20_iloose_L1MU15));
   b->GetLeaf("HLT_mu20_L1MU15")->SetAddress(&(evt->HLT_mu20_L1MU15));
   b->GetLeaf("HLT_mu20_mu8noL1")->SetAddress(&(evt->HLT_mu20_mu8noL1));
   b->GetLeaf("HLT_mu22_mu8noL1")->SetAddress(&(evt->HLT_mu22_mu8noL1));
   b->GetLeaf("HLT_mu20_2mu4noL1")->SetAddress(&(evt->HLT_mu20_2mu4noL1));
   b->GetLeaf("HLT_mu22_2mu4noL1")->SetAddress(&(evt->HLT_mu22_2mu4noL1));
   b->GetLeaf("HLT_mu40")->SetAddress(&(evt->HLT_mu40));
   b->GetLeaf("HLT_mu50")->SetAddress(&(evt->HLT_mu50));
   b->GetLeaf("HLT_2mu10")->SetAddress(&(evt->HLT_2mu10));
   b->GetLeaf("HLT_2mu10_nomucomb")->SetAddress(&(evt->HLT_2mu10_nomucomb));
   b->GetLeaf("HLT_2mu14")->SetAddress(&(evt->HLT_2mu14));
   b->GetLeaf("HLT_2mu14_nomucomb")->SetAddress(&(evt->HLT_2mu14_nomucomb));
   b->GetLeaf("HLT_3mu6")->SetAddress(&(evt->HLT_3mu6));
   b->GetLeaf("HLT_3mu6_msonly")->SetAddress(&(evt->HLT_3mu6_msonly));
   b->GetLeaf("HLT_xe100_L1XE50")->SetAddress(&(evt->HLT_xe100_L1XE50));
   b->GetLeaf("HLT_xe80_mht_L1XE50")->SetAddress(&(evt->HLT_xe80_mht_L1XE50));
   b->GetLeaf("HLT_xe90_mht_L1XE50")->SetAddress(&(evt->HLT_xe90_mht_L1XE50));
   b->GetLeaf("HLT_xe100_mht_L1XE50")->SetAddress(&(evt->HLT_xe100_mht_L1XE50));
   b->GetLeaf("HLT_xe110_mht_L1XE50")->SetAddress(&(evt->HLT_xe110_mht_L1XE50));
   b->GetLeaf("HLT_xe100_tc_em_L1XE50")->SetAddress(&(evt->HLT_xe100_tc_em_L1XE50));
   b->GetLeaf("HLT_xe80_tc_lcw_L1XE50")->SetAddress(&(evt->HLT_xe80_tc_lcw_L1XE50));
   b->GetLeaf("HLT_xe90_tc_lcw_L1XE50")->SetAddress(&(evt->HLT_xe90_tc_lcw_L1XE50));
   b->GetLeaf("HLT_xe80_tc_lcw_wEFMu_L1XE50")->SetAddress(&(evt->HLT_xe80_tc_lcw_wEFMu_L1XE50));
   b->GetLeaf("HLT_e7_lhmedium_mu24")->SetAddress(&(evt->HLT_e7_lhmedium_mu24));
   b->GetLeaf("HLT_e17_lhloose_nod0_mu14")->SetAddress(&(evt->HLT_e17_lhloose_nod0_mu14));
   b->GetLeaf("HLT_e26_lhmedium_nod0_L1EM22VHI_mu8noL1")->SetAddress(&(evt->HLT_e26_lhmedium_nod0_L1EM22VHI_mu8noL1));
   b->GetLeaf("HLT_e24_lhmedium_nod0_L1EM20VHI_mu8noL1")->SetAddress(&(evt->HLT_e24_lhmedium_nod0_L1EM20VHI_mu8noL1));
   b->GetLeaf("HLT_2e12_lhloose_L12EM10VH")->SetAddress(&(evt->HLT_2e12_lhloose_L12EM10VH));
   b->GetLeaf("HLT_e17_lhloose_mu14")->SetAddress(&(evt->HLT_e17_lhloose_mu14));
   b->GetLeaf("HLT_mu18_mu8noL1")->SetAddress(&(evt->HLT_mu18_mu8noL1));
   b->GetLeaf("HLT_xe70")->SetAddress(&(evt->HLT_xe70));
   b->GetLeaf("EventNumber")->SetAddress(&(evt->EventNumber));
   b->GetLeaf("ChannelNumber")->SetAddress(&(evt->ChannelNumber));
   b->GetLeaf("AvgMu")->SetAddress(&(evt->AvgMu));
   b->GetLeaf("EventWeight")->SetAddress(&(evt->EventWeight));
   b->GetLeaf("PRWWeight")->SetAddress(&(evt->PRWWeight));
   b->GetLeaf("PRWrandomRunNumber")->SetAddress(&(evt->PRWrandomRunNumber));
   b->GetLeaf("bcid")->SetAddress(&(evt->bcid));
   b->GetLeaf("LB")->SetAddress(&(evt->LB));
   b->GetLeaf("RunNb")->SetAddress(&(evt->RunNb));
   b->GetLeaf("DetError")->SetAddress(&(evt->DetError));
   b->GetLeaf("NMu")->SetAddress(&(evt->NMu));
   b->GetLeaf("NMuPair")->SetAddress(&(evt->NMuPair));
   b->GetLeaf("Mu_eta")->SetAddress(&(evt->Mu_eta));
   b->GetLeaf("Mu_phi")->SetAddress(&(evt->Mu_phi));
   b->GetLeaf("Mu_pT")->SetAddress(&(evt->Mu_pT));
   b->GetLeaf("Mu_SFw")->SetAddress(&(evt->Mu_SFw));
   b->GetLeaf("Mu_IsoSFw")->SetAddress(&(evt->Mu_IsoSFw));
   b->GetLeaf("Mu_charge")->SetAddress(&(evt->Mu_charge));
   b->GetLeaf("Mu_d0pvtx")->SetAddress(&(evt->Mu_d0pvtx));
   b->GetLeaf("Mu_sigd0")->SetAddress(&(evt->Mu_sigd0));
   b->GetLeaf("Mu_z0sinTheta")->SetAddress(&(evt->Mu_z0sinTheta));
   b->GetLeaf("Mu_isBad")->SetAddress(&(evt->Mu_isBad));
   b->GetLeaf("Mu_passOR")->SetAddress(&(evt->Mu_passOR));
   b->GetLeaf("Mu_isTight")->SetAddress(&(evt->Mu_isTight));
   b->GetLeaf("Mu_isCosmic")->SetAddress(&(evt->Mu_isCosmic));
   b->GetLeaf("Mu_type")->SetAddress(&(evt->Mu_type));
   b->GetLeaf("Mu_origin")->SetAddress(&(evt->Mu_origin));
   b->GetLeaf("Mu_ptcone20")->SetAddress(&(evt->Mu_ptcone20));
   b->GetLeaf("Mu_ptcone30")->SetAddress(&(evt->Mu_ptcone30));
   b->GetLeaf("Mu_ptcone40")->SetAddress(&(evt->Mu_ptcone40));
   b->GetLeaf("Mu_ptvarcone20")->SetAddress(&(evt->Mu_ptvarcone20));
   b->GetLeaf("Mu_ptvarcone30")->SetAddress(&(evt->Mu_ptvarcone30));
   b->GetLeaf("Mu_ptvarcone40")->SetAddress(&(evt->Mu_ptvarcone40));
   b->GetLeaf("Mu_topoetcone20")->SetAddress(&(evt->Mu_topoetcone20));
   b->GetLeaf("Mu_topoetcone30")->SetAddress(&(evt->Mu_topoetcone30));
   b->GetLeaf("Mu_topoetcone40")->SetAddress(&(evt->Mu_topoetcone40));
   b->GetLeaf("Mu_passIsoLooseTO")->SetAddress(&(evt->Mu_passIsoLooseTO));
   b->GetLeaf("Mu_passIsoLoose")->SetAddress(&(evt->Mu_passIsoLoose));
   b->GetLeaf("Mu_passIsoTight")->SetAddress(&(evt->Mu_passIsoTight));
   b->GetLeaf("Mu_passIsoGrad")->SetAddress(&(evt->Mu_passIsoGrad));
   b->GetLeaf("Mu_passIsoGradCustomTight")->SetAddress(&(evt->Mu_passIsoGradCustomTight));
   b->GetLeaf("Mu_passIsoGradCustom")->SetAddress(&(evt->Mu_passIsoGradCustom));
   b->GetLeaf("Mu_passIsoGradLoose")->SetAddress(&(evt->Mu_passIsoGradLoose));
   b->GetLeaf("MuTrigSF_HLT_mu20_iloose_L1MU15_OR_HLT_mu50")->SetAddress(&(evt->MuTrigSF_HLT_mu20_iloose_L1MU15_OR_HLT_mu50));
   b->GetLeaf("Mu_trigMatch_mu26_imedium")->SetAddress(&(evt->Mu_trigMatch_mu26_imedium));
   b->GetLeaf("Mu_trigMatch_mu50")->SetAddress(&(evt->Mu_trigMatch_mu50));
   b->GetLeaf("Mu_trigMatch_mu8noL1")->SetAddress(&(evt->Mu_trigMatch_mu8noL1));
   b->GetLeaf("Mu_trigMatch_mu14")->SetAddress(&(evt->Mu_trigMatch_mu14));
   b->GetLeaf("Mu_trigMatch_mu18")->SetAddress(&(evt->Mu_trigMatch_mu18));
   b->GetLeaf("Mu_trigMatch_mu18_mu8noL1")->SetAddress(&(evt->Mu_trigMatch_mu18_mu8noL1));
   b->GetLeaf("Mu_trigMatch_e17_lhloose_mu14")->SetAddress(&(evt->Mu_trigMatch_e17_lhloose_mu14));
   b->GetLeaf("Mu_trigMatch_e17_lhloose_nod0_mu14")->SetAddress(&(evt->Mu_trigMatch_e17_lhloose_nod0_mu14));
   b->GetLeaf("Mu_trigMatch_mu20_mu8noL1")->SetAddress(&(evt->Mu_trigMatch_mu20_mu8noL1));
   b->GetLeaf("Mu_trigMatch_mu22_mu8noL1")->SetAddress(&(evt->Mu_trigMatch_mu22_mu8noL1));
   b->GetLeaf("Mu_TrigMatch_mu24_iloose")->SetAddress(&(evt->Mu_TrigMatch_mu24_iloose));
   b->GetLeaf("Mu_TrigMatch_mu24_ivarloose")->SetAddress(&(evt->Mu_TrigMatch_mu24_ivarloose));
   b->GetLeaf("Mu_TrigMatch_mu24_iloose_L1MU15")->SetAddress(&(evt->Mu_TrigMatch_mu24_iloose_L1MU15));
   b->GetLeaf("Mu_TrigMatch_mu24_ivarloose_L1MU15")->SetAddress(&(evt->Mu_TrigMatch_mu24_ivarloose_L1MU15));
   b->GetLeaf("Mu_trigMatchPair_mu18_mu8noL1")->SetAddress(&(evt->Mu_trigMatchPair_mu18_mu8noL1));
   b->GetLeaf("Mu_trigMatchPair_mu20_mu8noL1")->SetAddress(&(evt->Mu_trigMatchPair_mu20_mu8noL1));
   b->GetLeaf("Mu_trigMatchPair_mu22_mu8noL1")->SetAddress(&(evt->Mu_trigMatchPair_mu22_mu8noL1));
   b->GetLeaf("NEl")->SetAddress(&(evt->NEl));
   b->GetLeaf("El_eta")->SetAddress(&(evt->El_eta));
   b->GetLeaf("El_etaclus")->SetAddress(&(evt->El_etaclus));
   b->GetLeaf("El_phi")->SetAddress(&(evt->El_phi));
   b->GetLeaf("El_pT")->SetAddress(&(evt->El_pT));
   b->GetLeaf("El_E")->SetAddress(&(evt->El_E));
   b->GetLeaf("El_charge")->SetAddress(&(evt->El_charge));
   b->GetLeaf("El_sigd0")->SetAddress(&(evt->El_sigd0));
   b->GetLeaf("El_z0sinTheta")->SetAddress(&(evt->El_z0sinTheta));
   b->GetLeaf("El_d0pvtx")->SetAddress(&(evt->El_d0pvtx));
   b->GetLeaf("El_passOR")->SetAddress(&(evt->El_passOR));
   b->GetLeaf("El_SFwMediumLH")->SetAddress(&(evt->El_SFwMediumLH));
   b->GetLeaf("El_IsoSFwMediumLH")->SetAddress(&(evt->El_IsoSFwMediumLH));
   b->GetLeaf("El_SFwTightLH")->SetAddress(&(evt->El_SFwTightLH));
   b->GetLeaf("El_SFwLooseAndBLayerLH")->SetAddress(&(evt->El_SFwLooseAndBLayerLH));
   b->GetLeaf("El_SFwTrigMediumLH_e12_lhloose_L1EM10VH")->SetAddress(&(evt->El_SFwTrigMediumLH_e12_lhloose_L1EM10VH));
   b->GetLeaf("El_SFwTrigMediumLH_e17_lhloose")->SetAddress(&(evt->El_SFwTrigMediumLH_e17_lhloose));
   b->GetLeaf("El_SFwTrigMediumLH_single")->SetAddress(&(evt->El_SFwTrigMediumLH_single));
   b->GetLeaf("El_SFwTrigLooseAndBLayerLH_e12_lhloose_L1EM10VH")->SetAddress(&(evt->El_SFwTrigLooseAndBLayerLH_e12_lhloose_L1EM10VH));
   b->GetLeaf("El_isLooseAndBLayerLH")->SetAddress(&(evt->El_isLooseAndBLayerLH));
   b->GetLeaf("El_isMediumLH")->SetAddress(&(evt->El_isMediumLH));
   b->GetLeaf("El_isTightLH")->SetAddress(&(evt->El_isTightLH));
   b->GetLeaf("El_nBLayerHits")->SetAddress(&(evt->El_nBLayerHits));
   b->GetLeaf("El_expectBLayerHit")->SetAddress(&(evt->El_expectBLayerHit));
   b->GetLeaf("El_truthType")->SetAddress(&(evt->El_truthType));
   b->GetLeaf("El_truthOrigin")->SetAddress(&(evt->El_truthOrigin));
   b->GetLeaf("El_bkgTruthType")->SetAddress(&(evt->El_bkgTruthType));
   b->GetLeaf("El_bkgTruthOrigin")->SetAddress(&(evt->El_bkgTruthOrigin));
   b->GetLeaf("El_bkgMotherPdgId")->SetAddress(&(evt->El_bkgMotherPdgId));
   b->GetLeaf("El_firstEgMotherTruthType")->SetAddress(&(evt->El_firstEgMotherTruthType));
   b->GetLeaf("El_firstEgMotherTruthOrigin")->SetAddress(&(evt->El_firstEgMotherTruthOrigin));
   b->GetLeaf("El_firstEgMotherPdgId")->SetAddress(&(evt->El_firstEgMotherPdgId));
   b->GetLeaf("El_chFlip")->SetAddress(&(evt->El_chFlip));
   b->GetLeaf("El_ptcone20")->SetAddress(&(evt->El_ptcone20));
   b->GetLeaf("El_ptcone30")->SetAddress(&(evt->El_ptcone30));
   b->GetLeaf("El_ptcone40")->SetAddress(&(evt->El_ptcone40));
   b->GetLeaf("El_ptvarcone20")->SetAddress(&(evt->El_ptvarcone20));
   b->GetLeaf("El_ptvarcone30")->SetAddress(&(evt->El_ptvarcone30));
   b->GetLeaf("El_ptvarcone40")->SetAddress(&(evt->El_ptvarcone40));
   b->GetLeaf("El_topoetcone20")->SetAddress(&(evt->El_topoetcone20));
   b->GetLeaf("El_topoetcone30")->SetAddress(&(evt->El_topoetcone30));
   b->GetLeaf("El_topoetcone40")->SetAddress(&(evt->El_topoetcone40));
   b->GetLeaf("El_passIsoLooseTO")->SetAddress(&(evt->El_passIsoLooseTO));
   b->GetLeaf("El_passIsoLoose")->SetAddress(&(evt->El_passIsoLoose));
   b->GetLeaf("El_passIsoTight")->SetAddress(&(evt->El_passIsoTight));
   b->GetLeaf("El_passIsoGrad")->SetAddress(&(evt->El_passIsoGrad));
   b->GetLeaf("El_passIsoGradCustomTight")->SetAddress(&(evt->El_passIsoGradCustomTight));
   b->GetLeaf("El_passIsoGradCustom")->SetAddress(&(evt->El_passIsoGradCustom));
   b->GetLeaf("El_passIsoGradLoose")->SetAddress(&(evt->El_passIsoGradLoose));
   b->GetLeaf("El_trigMatch_e12_lhloose_L1EM10VH")->SetAddress(&(evt->El_trigMatch_e12_lhloose_L1EM10VH));
   b->GetLeaf("El_trigMatch_e17_lhloose")->SetAddress(&(evt->El_trigMatch_e17_lhloose));
   b->GetLeaf("El_trigMatch_e60_lhmedium")->SetAddress(&(evt->El_trigMatch_e60_lhmedium));
   b->GetLeaf("El_trigMatch_e24_lhmedium_iloose_L1EM20VH")->SetAddress(&(evt->El_trigMatch_e24_lhmedium_iloose_L1EM20VH));
   b->GetLeaf("El_trigMatch_2e12_lhloose_L12EM10VH")->SetAddress(&(evt->El_trigMatch_2e12_lhloose_L12EM10VH));
   b->GetLeaf("El_trigMatch_2e15_lhloose_L12EM10VH")->SetAddress(&(evt->El_trigMatch_2e15_lhloose_L12EM10VH));
   b->GetLeaf("El_trigMatch_2e15_lhvloose_L12EM13VH")->SetAddress(&(evt->El_trigMatch_2e15_lhvloose_L12EM13VH));
   b->GetLeaf("El_trigMatch_2e15_lhvloose_nod0_L12EM13VH")->SetAddress(&(evt->El_trigMatch_2e15_lhvloose_nod0_L12EM13VH));
   b->GetLeaf("El_trigMatch_2e17_lhvloose_nod0")->SetAddress(&(evt->El_trigMatch_2e17_lhvloose_nod0));
   b->GetLeaf("El_trigMatch_e17_lhloose_mu14")->SetAddress(&(evt->El_trigMatch_e17_lhloose_mu14));
   b->GetLeaf("El_trigMatch_e17_lhloose_nod0_mu14")->SetAddress(&(evt->El_trigMatch_e17_lhloose_nod0_mu14));
   b->GetLeaf("El_TrigMatch_e24_lhmedium_nod0_ivarloose")->SetAddress(&(evt->El_TrigMatch_e24_lhmedium_nod0_ivarloose));
   b->GetLeaf("El_TrigMatch_e24_lhtight_nod0_ivarloose")->SetAddress(&(evt->El_TrigMatch_e24_lhtight_nod0_ivarloose));
   b->GetLeaf("El_TrigMatch_e60_lhmedium_nod0")->SetAddress(&(evt->El_TrigMatch_e60_lhmedium_nod0));
   b->GetLeaf("El_passChargeFlipTaggerBDTmedium")->SetAddress(&(evt->El_passChargeFlipTaggerBDTmedium));
   b->GetLeaf("El_passChargeFlipTaggerBDTloose")->SetAddress(&(evt->El_passChargeFlipTaggerBDTloose));
   b->GetLeaf("El_SFweightCFT")->SetAddress(&(evt->El_SFweightCFT));

   b->GetLeaf("NJet")->SetAddress(&(evt->NJet));
   //   b->GetLeaf("Jet_isSig")->SetAddress(&(evt->Jet_isSig));
   b->GetLeaf("Jet_eta")->SetAddress(&(evt->Jet_eta));
   b->GetLeaf("Jet_phi")->SetAddress(&(evt->Jet_phi));
   b->GetLeaf("Jet_pT")->SetAddress(&(evt->Jet_pT));
   b->GetLeaf("Jet_E")->SetAddress(&(evt->Jet_E));
   b->GetLeaf("Jet_quality")->SetAddress(&(evt->Jet_quality));
   b->GetLeaf("Jet_JVT")->SetAddress(&(evt->Jet_JVT));
   b->GetLeaf("Jet_JVTsf")->SetAddress(&(evt->Jet_JVTsf));
   b->GetLeaf("Jet_MV2c20")->SetAddress(&(evt->Jet_MV2c20));
   b->GetLeaf("Jet_MV2c10")->SetAddress(&(evt->Jet_MV2c10));
   b->GetLeaf("Jet_SFw")->SetAddress(&(evt->Jet_SFw));
   b->GetLeaf("Jet_ConeTruthLabel")->SetAddress(&(evt->Jet_ConeTruthLabel));
   b->GetLeaf("Jet_PartonTruthLabel")->SetAddress(&(evt->Jet_PartonTruthLabel));
   b->GetLeaf("Jet_HadronConeExclTruthLabel")->SetAddress(&(evt->Jet_HadronConeExclTruthLabel));
   b->GetLeaf("Jet_deltaR")->SetAddress(&(evt->Jet_deltaR));
   b->GetLeaf("Jet_nTrk")->SetAddress(&(evt->Jet_nTrk));
   b->GetLeaf("Jet_passOR")->SetAddress(&(evt->Jet_passOR));
   b->GetLeaf("Etmiss_CST_Etx")->SetAddress(&(evt->Etmiss_CST_Etx));
   b->GetLeaf("Etmiss_CST_Ety")->SetAddress(&(evt->Etmiss_CST_Ety));
   b->GetLeaf("Etmiss_CST_Et")->SetAddress(&(evt->Etmiss_CST_Et));
   b->GetLeaf("Etmiss_TST_Etx")->SetAddress(&(evt->Etmiss_TST_Etx));
   b->GetLeaf("Etmiss_TST_Ety")->SetAddress(&(evt->Etmiss_TST_Ety));
   b->GetLeaf("Etmiss_TST_Et")->SetAddress(&(evt->Etmiss_TST_Et));
   b->GetLeaf("Etmiss_TSTterm_Etx")->SetAddress(&(evt->Etmiss_TSTterm_Etx));
   b->GetLeaf("Etmiss_TSTterm_Ety")->SetAddress(&(evt->Etmiss_TSTterm_Ety));
   b->GetLeaf("Etmiss_TSTterm_Et")->SetAddress(&(evt->Etmiss_TSTterm_Et));
   b->GetLeaf("Etmiss_Truth_Etx")->SetAddress(&(evt->Etmiss_Truth_Etx));
   b->GetLeaf("Etmiss_Truth_Ety")->SetAddress(&(evt->Etmiss_Truth_Ety));
   b->GetLeaf("Etmiss_Truth_Et")->SetAddress(&(evt->Etmiss_Truth_Et));
   b->GetLeaf("NTruthJet")->SetAddress(&(evt->NTruthJet));
   b->GetLeaf("TruthJet_eta")->SetAddress(&(evt->TruthJet_eta));
   b->GetLeaf("TruthJet_phi")->SetAddress(&(evt->TruthJet_phi));
   b->GetLeaf("TruthJet_pT")->SetAddress(&(evt->TruthJet_pT));
   b->GetLeaf("TruthJet_E")->SetAddress(&(evt->TruthJet_E));
   b->GetLeaf("TruthJet_ConeTruthLabel")->SetAddress(&(evt->TruthJet_ConeTruthLabel));
   b->GetLeaf("TruthJet_PartonTruthLabel")->SetAddress(&(evt->TruthJet_PartonTruthLabel));
   b->GetLeaf("NTruthL")->SetAddress(&(evt->NTruthL));
   b->GetLeaf("TruthL_eta")->SetAddress(&(evt->TruthL_eta));
   b->GetLeaf("TruthL_phi")->SetAddress(&(evt->TruthL_phi));
   b->GetLeaf("TruthL_pT")->SetAddress(&(evt->TruthL_pT));
   b->GetLeaf("TruthL_id")->SetAddress(&(evt->TruthL_id));
   b->GetLeaf("SUSY_Spart_pdgId1")->SetAddress(&(evt->SUSY_Spart_pdgId1));
   b->GetLeaf("SUSY_Spart_pdgId2")->SetAddress(&(evt->SUSY_Spart_pdgId2));
   b->GetLeaf("SUSY_Gluino_decay1")->SetAddress(&(evt->SUSY_Gluino_decay1));
   b->GetLeaf("SUSY_Gluino_decay2")->SetAddress(&(evt->SUSY_Gluino_decay2));
   b->GetLeaf("GenFiltHT")->SetAddress(&(evt->GenFiltHT));
   b->GetLeaf("GenFiltMET")->SetAddress(&(evt->GenFiltMET));
   b->GetLeaf("PV_z")->SetAddress(&(evt->PV_z));
   b->GetLeaf("Nvtx")->SetAddress(&(evt->Nvtx));
   b->GetLeaf("TruthX1")->SetAddress(&(evt->TruthX1));
   b->GetLeaf("TruthX2")->SetAddress(&(evt->TruthX2));
   b->GetLeaf("TruthQ")->SetAddress(&(evt->TruthQ));
   b->GetLeaf("SherpaNjetWeight")->SetAddress(&(evt->SherpaNjetWeight));
   b->GetLeaf("TruthPDGID1")->SetAddress(&(evt->TruthPDGID1));
   b->GetLeaf("TruthPDGID2")->SetAddress(&(evt->TruthPDGID2));
   b->GetLeaf("extraB")->SetAddress(&(evt->extraB));
   b->GetLeaf("extraC")->SetAddress(&(evt->extraC));
   b->GetLeaf("TriggerDileptonSF")->SetAddress(&(evt->TriggerDileptonSF));

  }
}
