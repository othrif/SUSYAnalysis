//////////////////////////////////////////////////////////
// Author:      Othmane Rifki
// Contact:     othmane.rifki@cern.ch
// Description: MiniNtuple from Ximo AnaNtup
// Date 2016-07-11 07:29:16
//////////////////////////////////////////////////////////

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <strstream>
#include <cstring>

#include "TFile.h"
#include "TMath.h"
#include "TTree.h"
#include "TBranch.h"
#include "TLeaf.h"
#include "TRandom.h"
#include <TLorentzVector.h>

#include "MiniNtuple/TMiniNtuple.h"
#include "MiniNtuple/myevt.h"
#include "MiniNtuple/OldNtpBranches.h"
#include "MiniNtuple/JetQuarkLabelD3PD.h"
#include "MiniNtuple/RecoTruthMatch.h"


double weightedSum_events = 0;
double rawEvents = 0;
double weightedSumsq_events = 0;

//__________________________________________________________________________
TMiniNtuple::TMiniNtuple(const std::string& name, ISvcLocator* pSvcLocator) :
  Algorithm(name, pSvcLocator) {

  declareProperty("OutputFileName", ntpName = "output.root");
  declareProperty("InputFileName", inpName);
  declareProperty("Debug", debug = true);
  declareProperty("ApplyLeptonSkim", m_applyLeptonSkim = false);
  declareProperty("MinLeptonPt", m_minLeptonPt = 9000.); //was 13 GeV
}

//_____________________________________________________________________________
TMiniNtuple::~TMiniNtuple() {
}

//_____________________________________________________________________________
StatusCode TMiniNtuple::initialize() {

  StatusCode sc = StatusCode::SUCCESS;

  if (inpName.size() == 0)
	return StatusCode::FAILURE;

  //	t_inpNtuple = new TChain("susy");
  t_inpNtuple = new TChain("AnaNtup");
  std::cout << "Reading: " << inpName.at(0).data() << "\n";
  if (t_inpNtuple->Add(inpName.at(0).data(), 0) == 0) { // the file is empty or it does not contain "AnaNtup" tree
	delete t_inpNtuple;

	t_inpNtuple = new TChain("truth");
	is_truth = true;
	if (t_inpNtuple->Add(inpName.at(0).data(), 0) == 0) {
	  std::cerr
		<< "\nThe given file does not contain a susy or truth tree or is non-existent\n";
	  return StatusCode::FAILURE;
	} else {
	  std::cout << "\nProcessing a TruthD3PD dataset.\n";
	}

  } else {
	is_truth = false;
	std::cout << "\nPrecessing a SUSY_D3PD dataset.\n";
  }

  std::cout << "----- begin job: ---- \n";



  for (unsigned int i = 1; i < inpName.size(); i++) {

	std::cout << "Reading: " << inpName.at(i).data() << "\n";
	if (t_inpNtuple->Add(inpName.at(i).data(), 0) == 0) { // breaks if an empty file is given
	  std::cerr
		<< "\nThe given file does not contain a susy or truth tree or is non-existent\n";
	  return StatusCode::FAILURE;
	}
  }


  long double beforeD = 0.;
  long double afterD = 0.;
  long double beforeDRaw = 0.;
  long double afterDRaw = 0.;
  long double beforeDsq = 0.;
  long double afterDsq = 0.;

  std::cout << "file    originalxAOD    DxAOD    originalxAODsq    DxAODsq" << std::endl;

  for (unsigned int i = 0; i < inpName.size(); i++) {
	std::cout << "file " << i << " ";
	TFile f(inpName.at(i).data(), "READ");

	TH1D* h_events = (TH1D*) f.Get("DerivationStat_Weights");
	if (h_events != NULL) {  
	  std::cout << h_events->GetBinContent(1) << " ";
	  std::cout << h_events->GetBinContent(2) << " ";
	  beforeD += h_events->GetBinContent(1);
	  afterD += h_events->GetBinContent(2);
	}

	TH1D* h_events_sq = (TH1D*) f.Get("DerivationStat_Weights_Squared");
	if (h_events_sq != NULL) {  
	  std::cout << h_events_sq->GetBinContent(1) << " ";
	  std::cout << h_events_sq->GetBinContent(2) << " ";
	  beforeDsq += h_events_sq->GetBinContent(1);
	  afterDsq += h_events_sq->GetBinContent(2);
	}

	TH1D* h_events_raw = (TH1D*) f.Get("DerivationStat_RawEvents");
	if (h_events_raw != NULL) {  
	  std::cout << h_events_raw->GetBinContent(1) << " ";
	  std::cout << h_events_raw->GetBinContent(2) << " ";
	  beforeDRaw += h_events_raw->GetBinContent(1);
	  afterDRaw += h_events_raw->GetBinContent(2);
	}
	
	f.Close();
	
	std::cout << std::endl;
  }

  weightedSum_events = beforeD;
  weightedSumsq_events = beforeDsq;
  rawEvents = beforeDRaw;

  std::cout << "before raw " << beforeDRaw << std::endl;
  std::cout << "after raw " << afterDRaw << std::endl;
  std::cout << "before " << beforeD << std::endl;
  std::cout << "after " << afterD << std::endl;
  std::cout << "before sq " << beforeDsq << std::endl;
  std::cout << "after sq " << afterDsq << std::endl;


  if (debug)
	std::cout << "opening output root file" << std::endl;

  outputRootFile = new TFile(ntpName.data(), "RECREATE");
  //  gDirectory->mkdir("DerivationStat")->cd();
  gDirectory->cd("/");
  m_h_events_raw = new TH1D("h_events_raw", "Raw Events before/after derivation", 2, -0.5, 1.5);
  m_h_events_raw->GetXaxis()->FindBin("original xAOD");
  m_h_events_raw->GetXaxis()->FindBin("DxAOD");
  m_h_events_raw->SetBinContent(1, beforeDRaw);
  m_h_events_raw->SetBinContent(2, afterDRaw);

  m_h_events = new TH1D("h_events", "Events before/after derivation", 2, -0.5, 1.5);
  m_h_events->GetXaxis()->FindBin("original xAOD");
  m_h_events->GetXaxis()->FindBin("DxAOD");
  m_h_events->SetBinContent(1, beforeD);
  m_h_events->SetBinContent(2, afterD);

  m_h_events_sq = new TH1D("h_events_sq", "Events before/after derivation (squared)", 2, -0.5, 1.5);
  m_h_events_sq->GetXaxis()->FindBin("original xAOD");
  m_h_events_sq->GetXaxis()->FindBin("DxAOD");
  m_h_events_sq->SetBinContent(1, beforeDsq);
  m_h_events_sq->SetBinContent(2, afterDsq);

  if (debug)
	std::cout << "booking variables into the tree..." << std::endl;

  //Initialize the new tree:
  evt = new myevt;
  memset(evt, 0, sizeof(myevt));
  t_MiniNtuple = new TTree("MiniNtuple", "a reduced ntuple");
  b = NULL;
  SetNewNtpBranches();
  oldTree = new OldNtpBranches(is_truth);



  return sc;
}

//_____________________________________________________________________________
StatusCode TMiniNtuple::execute() {

  StatusCode sc = StatusCode::SUCCESS;

  std::cout << "----- initializing the main event loop: ---- \n";

  //Here we implement the main event loop
  if (!t_inpNtuple)
	return StatusCode::FAILURE;
  Long64_t treeEntries = (Long64_t) t_inpNtuple->GetEntries();
  //	treeEntries = 100; // temporary
  std::cout << "Expect to process " << treeEntries << " entries" << std::endl;
  if (treeEntries == 0)
	return StatusCode::FAILURE;

  t_inpNtuple->GetEntry(0);
  evt->isMC = oldTree->Init(t_inpNtuple);

  if (evt->isMC)
	std::cout << "Processing MC\n";
  else
	std::cout << "Processing DATA\n";
  
  int treeno = -1;
  for (Long64_t i = 0; i < treeEntries; i++) {

	// only way I can get this to be reliable
	t_inpNtuple->GetEntry(i);

	if (treeno != ((TChain*) t_inpNtuple)->GetTreeNumber()) {
	  evt->isMC = oldTree->Init(t_inpNtuple);
	  t_inpNtuple->GetEntry(i);
	  treeno = ((TChain*) t_inpNtuple)->GetTreeNumber();
	  //SetNewNtpBranches(); //TODO: Do we need this line?
	}


	// initializing ntuple variables
	InitNtpVar(evt);

	//==========================================================================
	// We do all processing here:
	//	std::cout << "Event # " << i << "\n";

	int j, jj;
    if(evt->isMC){
      evt->sumWeight = weightedSum_events;
      evt->sumWeightsq = weightedSumsq_events;
      evt->rawEvents = rawEvents;
      evt->HLT_e24_lhmedium_nod0_ivarloose          = oldTree->HLT_e24_lhmedium_nod0_ivarloose         ;
      evt->HLT_e24_lhtight_nod0_ivarloose           = oldTree->HLT_e24_lhtight_nod0_ivarloose          ;
      evt->HLT_e24_lhmedium_nod0_L1EM20VH           = oldTree->HLT_e24_lhmedium_nod0_L1EM20VH          ;
      evt->HLT_e26_lhtight_iloose                   = oldTree->HLT_e26_lhtight_iloose                  ;
      evt->HLT_e26_lhtight_ivarloose                = oldTree->HLT_e26_lhtight_ivarloose               ;
      evt->HLT_e26_lhtight_nod0_iloose              = oldTree->HLT_e26_lhtight_nod0_iloose             ;
      evt->HLT_e26_lhtight_nod0_ivarloose           = oldTree->HLT_e26_lhtight_nod0_ivarloose          ;
      evt->HLT_e60_lhmedium                         = oldTree->HLT_e60_lhmedium                        ;
      evt->HLT_e60_lhmedium_nod0                    = oldTree->HLT_e60_lhmedium_nod0                   ;
      evt->HLT_e120_lhloose_nod0                    = oldTree->HLT_e120_lhloose_nod0                   ;
      evt->HLT_e140_lhloose_nod0                    = oldTree->HLT_e140_lhloose_nod0                   ;
      evt->HLT_2e17_lhvloose_nod0                   = oldTree->HLT_2e17_lhvloose_nod0                  ;
      evt->HLT_2e15_lhvloose_nod0_L12EM13VH         = oldTree->HLT_2e15_lhvloose_nod0_L12EM13VH        ;
      evt->HLT_e24_lhmedium_e9_lhmedium             = oldTree->HLT_e24_lhmedium_e9_lhmedium            ;
      evt->HLT_e24_lhmedium_L1EM20VH                = oldTree->HLT_e24_lhmedium_L1EM20VH               ;
      evt->HLT_e12_lhvloose_L12EM10VH               = oldTree->HLT_e12_lhvloose_L12EM10VH              ;
      evt->HLT_e17_lhloose_2e9_lhloose              = oldTree->HLT_e17_lhloose_2e9_lhloose             ;
      evt->HLT_mu24_ivarmedium                      = oldTree->HLT_mu24_ivarmedium                     ;
      evt->HLT_mu24_imedium                         = oldTree->HLT_mu24_imedium                        ;
      evt->HLT_mu24_ivarloose                       = oldTree->HLT_mu24_ivarloose                      ;
      evt->HLT_mu24_iloose                          = oldTree->HLT_mu24_iloose                         ;
      evt->HLT_mu26_ivarmedium                      = oldTree->HLT_mu26_ivarmedium                     ;
      evt->HLT_mu26_imedium                         = oldTree->HLT_mu26_imedium                        ;
      evt->HLT_mu20_ivarmedium_L1MU15               = oldTree->HLT_mu20_ivarmedium_L1MU15              ;
      evt->HLT_mu20_imedium_L1MU15                  = oldTree->HLT_mu20_imedium_L1MU15                 ;
      evt->HLT_mu20_ivarloose_L1MU15                = oldTree->HLT_mu20_ivarloose_L1MU15               ;
      evt->HLT_mu20_iloose_L1MU15                   = oldTree->HLT_mu20_iloose_L1MU15                  ;
      evt->HLT_mu20_L1MU15                          = oldTree->HLT_mu20_L1MU15                         ;
      evt->HLT_mu20_mu8noL1                         = oldTree->HLT_mu20_mu8noL1                        ;
      evt->HLT_mu22_mu8noL1                         = oldTree->HLT_mu22_mu8noL1                        ;
      evt->HLT_mu20_2mu4noL1                        = oldTree->HLT_mu20_2mu4noL1                       ;
      evt->HLT_mu22_2mu4noL1                        = oldTree->HLT_mu22_2mu4noL1                       ;
      evt->HLT_mu40                                 = oldTree->HLT_mu40                                ;
      evt->HLT_mu50                                 = oldTree->HLT_mu50                                ;
      evt->HLT_2mu10                                = oldTree->HLT_2mu10                               ;
      evt->HLT_2mu10_nomucomb                       = oldTree->HLT_2mu10_nomucomb                      ;
      evt->HLT_2mu14                                = oldTree->HLT_2mu14                               ;
      evt->HLT_2mu14_nomucomb                       = oldTree->HLT_2mu14_nomucomb                      ;
      evt->HLT_3mu6                                 = oldTree->HLT_3mu6                                ;
      evt->HLT_3mu6_msonly                          = oldTree->HLT_3mu6_msonly                         ;
      evt->HLT_xe100_L1XE50                         = oldTree->HLT_xe100_L1XE50                        ;
      evt->HLT_xe80_mht_L1XE50                      = oldTree->HLT_xe80_mht_L1XE50                     ;
      evt->HLT_xe90_mht_L1XE50                      = oldTree->HLT_xe90_mht_L1XE50                     ;
      evt->HLT_xe100_mht_L1XE50                     = oldTree->HLT_xe100_mht_L1XE50                    ;
      evt->HLT_xe110_pueta_L1XE50                   = oldTree->HLT_xe110_pueta_L1XE50                  ;
      evt->HLT_xe110_pufit_L1XE50                   = oldTree->HLT_xe110_pufit_L1XE50                  ;
      evt->HLT_xe100_tc_em_L1XE50                   = oldTree->HLT_xe100_tc_em_L1XE50                  ;
      evt->HLT_xe80_tc_lcw_L1XE50                   = oldTree->HLT_xe80_tc_lcw_L1XE50                  ;
      evt->HLT_xe90_tc_lcw_L1XE50                   = oldTree->HLT_xe90_tc_lcw_L1XE50                  ;
      evt->HLT_xe80_tc_lcw_wEFMu_L1XE50             = oldTree->HLT_xe80_tc_lcw_wEFMu_L1XE50            ;
      evt->HLT_e7_lhmedium_mu24                     = oldTree->HLT_e7_lhmedium_mu24                    ;
      evt->HLT_e17_lhloose_nod0_mu14                = oldTree->HLT_e17_lhloose_nod0_mu14               ;
      evt->HLT_e26_lhmedium_nod0_L1EM22VHI_mu8noL1  = oldTree->HLT_e26_lhmedium_nod0_L1EM22VHI_mu8noL1 ;
      evt->HLT_e24_lhmedium_nod0_L1EM22VHI_mu8noL1  = oldTree->HLT_e24_lhmedium_nod0_L1EM22VHI_mu8noL1 ;
      evt->HLT_2e12_lhloose_L12EM10VH               = oldTree->HLT_2e12_lhloose_L12EM10VH              ;
      evt->HLT_e17_lhloose_mu14                     = oldTree->HLT_e17_lhloose_mu14                    ;
      evt->HLT_mu18_mu8noL1                         = oldTree->HLT_mu18_mu8noL1                        ;
      evt->HLT_xe70                                 = oldTree->HLT_xe70                                ;
      evt->EventNumber                              = oldTree->EventNumber                             ;
      evt->ChannelNumber                            = oldTree->ChannelNumber                           ;
      evt->AvgMu                                    = oldTree->AvgMu                                   ;
      evt->EventWeight                              = oldTree->EventWeight                             ;
      evt->PRWWeight                                = oldTree->PRWWeight                               ;
      evt->PRWrandomRunNumber                       = oldTree->PRWrandomRunNumber                      ;
      evt->bcid                                     = oldTree->bcid                                    ;
      evt->LB                                       = oldTree->LB                                      ;
      evt->RunNb                                    = oldTree->RunNb                                   ;
      evt->DetError                                 = oldTree->DetError                                ;
      evt->MuTrigSF_HLT_mu20_iloose_L1MU15_OR_HLT_mu50 = oldTree->MuTrigSF_HLT_mu20_iloose_L1MU15_OR_HLT_mu50;
      evt->Etmiss_CST_Etx                           = oldTree->Etmiss_CST_Etx                          ;
      evt->Etmiss_CST_Ety                           = oldTree->Etmiss_CST_Ety                          ;
      evt->Etmiss_CST_Et                            = oldTree->Etmiss_CST_Et                           ;
      evt->Etmiss_TST_Etx                           = oldTree->Etmiss_TST_Etx                          ;
      evt->Etmiss_TST_Ety                           = oldTree->Etmiss_TST_Ety                          ;
      evt->Etmiss_TST_Et                            = oldTree->Etmiss_TST_Et                           ;
      evt->Etmiss_TSTterm_Etx                       = oldTree->Etmiss_TSTterm_Etx                      ;
      evt->Etmiss_TSTterm_Ety                       = oldTree->Etmiss_TSTterm_Ety                      ;
      evt->Etmiss_TSTterm_Et                        = oldTree->Etmiss_TSTterm_Et                       ;
      evt->Etmiss_Truth_Etx                         = oldTree->Etmiss_Truth_Etx                        ;
      evt->Etmiss_Truth_Ety                         = oldTree->Etmiss_Truth_Ety                        ;
      evt->Etmiss_Truth_Et                          = oldTree->Etmiss_Truth_Et                         ;
      evt->NTruthJet                                = oldTree->NTruthJet                               ;
      evt->NTruthL                                  = oldTree->NTruthL                                 ;
      evt->SUSY_Spart_pdgId1                        = oldTree->SUSY_Spart_pdgId1                       ;
      evt->SUSY_Spart_pdgId2                        = oldTree->SUSY_Spart_pdgId2                       ;
      evt->SUSY_Gluino_decay1                       = oldTree->SUSY_Gluino_decay1                      ;
      evt->SUSY_Gluino_decay2                       = oldTree->SUSY_Gluino_decay2                      ;
      evt->GenFiltHT                                = oldTree->GenFiltHT                               ;
      evt->GenFiltMET                               = oldTree->GenFiltMET                              ;
      evt->PV_z                                     = oldTree->PV_z                                    ;
      evt->Nvtx                                     = oldTree->Nvtx                                    ;
      evt->TruthX1                                  = oldTree->TruthX1                                 ;
      evt->TruthX2                                  = oldTree->TruthX2                                 ;
      evt->TruthQ                                   = oldTree->TruthQ                                  ;
      evt->SherpaNjetWeight                         = oldTree->SherpaNjetWeight                        ;
      evt->TruthPDGID1                              = oldTree->TruthPDGID1                             ;
      evt->TruthPDGID2                              = oldTree->TruthPDGID2                             ;


      //electrons
      j = 0;
      for (int i = 0; i < oldTree->NEl; i++) {
		if (j == MAXLEPT) {
		  std::cout << "WARNING: Too many electrons\n";
		  break;
	      }
    evt->El_eta[j] = oldTree->El_eta->at(i);
    evt->El_etaclus[j] = oldTree->El_etaclus->at(i);
    evt->El_phi[j] = oldTree->El_phi->at(i);
    evt->El_pT[j] = oldTree->El_pT->at(i);
    evt->El_E[j] = oldTree->El_E->at(i);
    evt->El_charge[j] = oldTree->El_charge->at(i);
    evt->El_sigd0[j] = oldTree->El_sigd0->at(i);
    evt->El_z0sinTheta[j] = oldTree->El_z0sinTheta->at(i);
    evt->El_d0pvtx[j] = oldTree->El_d0pvtx->at(i);
    evt->El_passOR[j] = oldTree->El_passOR->at(i);
    evt->El_SFwMediumLH[j] = oldTree->El_SFwMediumLH->at(i);
    evt->El_IsoSFwMediumLH[j] = oldTree->El_IsoSFwMediumLH->at(i);
    evt->El_SFwTightLH[j] = oldTree->El_SFwTightLH->at(i);
    evt->El_SFwLooseAndBLayerLH[j] = oldTree->El_SFwLooseAndBLayerLH->at(i);
    evt->El_SFwTrigMediumLH_e12_lhloose_L1EM10VH[j] = oldTree->El_SFwTrigMediumLH_e12_lhloose_L1EM10VH->at(i);
    evt->El_SFwTrigMediumLH_e17_lhloose[j] = oldTree->El_SFwTrigMediumLH_e17_lhloose->at(i);
    evt->El_SFwTrigMediumLH_single[j] = oldTree->El_SFwTrigMediumLH_single->at(i);
    evt->El_SFwTrigLooseAndBLayerLH_e12_lhloose_L1EM10VH[j] = oldTree->El_SFwTrigLooseAndBLayerLH_e12_lhloose_L1EM10VH->at(i);
    evt->El_isLooseAndBLayerLH[j] = oldTree->El_isLooseAndBLayerLH->at(i);
    evt->El_isMediumLH[j] = oldTree->El_isMediumLH->at(i);
    evt->El_isTightLH[j] = oldTree->El_isTightLH->at(i);
    evt->El_nBLayerHits[j] = oldTree->El_nBLayerHits->at(i);
    evt->El_expectBLayerHit[j] = oldTree->El_expectBLayerHit->at(i);
    evt->El_type[j] = oldTree->El_type->at(i);
    evt->El_origin[j] = oldTree->El_origin->at(i);
    evt->El_bkgMotherPdgId[j] = oldTree->El_bkgMotherPdgId->at(i);
    evt->El_bkgOrigin[j] = oldTree->El_bkgOrigin->at(i);
    evt->El_chFlip[j] = oldTree->El_chFlip->at(i);
    evt->El_ptcone20[j] = oldTree->El_ptcone20->at(i);
    evt->El_ptcone30[j] = oldTree->El_ptcone30->at(i);
    evt->El_ptcone40[j] = oldTree->El_ptcone40->at(i);
    evt->El_ptvarcone20[j] = oldTree->El_ptvarcone20->at(i);
    evt->El_ptvarcone30[j] = oldTree->El_ptvarcone30->at(i);
    evt->El_ptvarcone40[j] = oldTree->El_ptvarcone40->at(i);
    evt->El_topoetcone20[j] = oldTree->El_topoetcone20->at(i);
    evt->El_topoetcone30[j] = oldTree->El_topoetcone30->at(i);
    evt->El_topoetcone40[j] = oldTree->El_topoetcone40->at(i);
    evt->El_passIsoLooseTO[j] = oldTree->El_passIsoLooseTO->at(i);
    evt->El_passIsoLoose[j] = oldTree->El_passIsoLoose->at(i);
    evt->El_passIsoTight[j] = oldTree->El_passIsoTight->at(i);
    evt->El_passIsoGrad[j] = oldTree->El_passIsoGrad->at(i);
    evt->El_passIsoGradCustomTight[j] = oldTree->El_passIsoGradCustomTight->at(i);
    evt->El_passIsoGradCustom[j] = oldTree->El_passIsoGradCustom->at(i);
    evt->El_passIsoGradLoose[j] = oldTree->El_passIsoGradLoose->at(i);
    evt->El_trigMatch_e12_lhloose_L1EM10VH[j] = oldTree->El_trigMatch_e12_lhloose_L1EM10VH->at(i);
    evt->El_trigMatch_e17_lhloose[j] = oldTree->El_trigMatch_e17_lhloose->at(i);
    evt->El_trigMatch_e60_lhmedium[j] = oldTree->El_trigMatch_e60_lhmedium->at(i);
    evt->El_trigMatch_e24_lhmedium_iloose_L1EM20VH[j] = oldTree->El_trigMatch_e24_lhmedium_iloose_L1EM20VH->at(i);
    evt->El_trigMatch_2e12_lhloose_L12EM10VH[j] = oldTree->El_trigMatch_2e12_lhloose_L12EM10VH->at(i);
    evt->El_trigMatch_2e15_lhloose_L12EM10VH[j] = oldTree->El_trigMatch_2e15_lhloose_L12EM10VH->at(i);
    evt->El_trigMatch_2e15_lhvloose_L12EM13VH[j] = oldTree->El_trigMatch_2e15_lhvloose_L12EM13VH->at(i);
    evt->El_trigMatch_2e15_lhvloose_nod0_L12EM13VH[j] = oldTree->El_trigMatch_2e15_lhvloose_nod0_L12EM13VH->at(i);
    evt->El_trigMatch_2e17_lhvloose_nod0[j] = oldTree->El_trigMatch_2e17_lhvloose_nod0->at(i);
    evt->El_trigMatch_e17_lhloose_mu14[j] = oldTree->El_trigMatch_e17_lhloose_mu14->at(i);
    evt->El_trigMatch_e17_lhloose_nod0_mu14[j] = oldTree->El_trigMatch_e17_lhloose_nod0_mu14->at(i);
    evt->El_TrigMatch_e24_lhmedium_nod0_ivarloose[j] = oldTree->El_TrigMatch_e24_lhmedium_nod0_ivarloose->at(i);
    evt->El_TrigMatch_e24_lhtight_nod0_ivarloose[j] = oldTree->El_TrigMatch_e24_lhtight_nod0_ivarloose->at(i);
    evt->El_TrigMatch_e60_lhmedium_nod0[j] = oldTree->El_TrigMatch_e60_lhmedium_nod0->at(i);
    j++;
   }
   evt->NEl = j;


	//muons
	j = 0;
	jj = 0;
	for (int i = 0; i < oldTree->NMu; i++) {
	  if (j == MAXLEPT) {
		std::cout << "WARNING: Too many muons\n";
		break;
	  }
    evt->Mu_eta[j] = oldTree->Mu_eta->at(i);
    evt->Mu_phi[j] = oldTree->Mu_phi->at(i);
    evt->Mu_pT[j] = oldTree->Mu_pT->at(i);
    evt->Mu_SFw[j] = oldTree->Mu_SFw->at(i);
    evt->Mu_IsoSFw[j] = oldTree->Mu_IsoSFw->at(i);
    evt->Mu_charge[j] = oldTree->Mu_charge->at(i);
    evt->Mu_d0pvtx[j] = oldTree->Mu_d0pvtx->at(i);
    evt->Mu_sigd0[j] = oldTree->Mu_sigd0->at(i);
    evt->Mu_z0sinTheta[j] = oldTree->Mu_z0sinTheta->at(i);
    evt->Mu_isBad[j] = oldTree->Mu_isBad->at(i);
    evt->Mu_passOR[j] = oldTree->Mu_passOR->at(i);
    evt->Mu_isTight[j] = oldTree->Mu_isTight->at(i);
    evt->Mu_isCosmic[j] = oldTree->Mu_isCosmic->at(i);
    evt->Mu_type[j] = oldTree->Mu_type->at(i);
    evt->Mu_origin[j] = oldTree->Mu_origin->at(i);
    evt->Mu_ptcone20[j] = oldTree->Mu_ptcone20->at(i);
    evt->Mu_ptcone30[j] = oldTree->Mu_ptcone30->at(i);
    evt->Mu_ptcone40[j] = oldTree->Mu_ptcone40->at(i);
    evt->Mu_ptvarcone20[j] = oldTree->Mu_ptvarcone20->at(i);
    evt->Mu_ptvarcone30[j] = oldTree->Mu_ptvarcone30->at(i);
    evt->Mu_ptvarcone40[j] = oldTree->Mu_ptvarcone40->at(i);
    evt->Mu_topoetcone20[j] = oldTree->Mu_topoetcone20->at(i);
    evt->Mu_topoetcone30[j] = oldTree->Mu_topoetcone30->at(i);
    evt->Mu_topoetcone40[j] = oldTree->Mu_topoetcone40->at(i);
    evt->Mu_passIsoLooseTO[j] = oldTree->Mu_passIsoLooseTO->at(i);
    evt->Mu_passIsoLoose[j] = oldTree->Mu_passIsoLoose->at(i);
    evt->Mu_passIsoTight[j] = oldTree->Mu_passIsoTight->at(i);
    evt->Mu_passIsoGrad[j] = oldTree->Mu_passIsoGrad->at(i);
    evt->Mu_passIsoGradCustomTight[j] = oldTree->Mu_passIsoGradCustomTight->at(i);
    evt->Mu_passIsoGradCustom[j] = oldTree->Mu_passIsoGradCustom->at(i);
    evt->Mu_passIsoGradLoose[j] = oldTree->Mu_passIsoGradLoose->at(i);
    evt->Mu_trigMatch_mu26_imedium[j] = oldTree->Mu_trigMatch_mu26_imedium->at(i);
    evt->Mu_trigMatch_mu50[j] = oldTree->Mu_trigMatch_mu50->at(i);
    evt->Mu_trigMatch_mu8noL1[j] = oldTree->Mu_trigMatch_mu8noL1->at(i);
    evt->Mu_trigMatch_mu14[j] = oldTree->Mu_trigMatch_mu14->at(i);
    evt->Mu_trigMatch_mu18[j] = oldTree->Mu_trigMatch_mu18->at(i);
    evt->Mu_trigMatch_mu18_mu8noL1[j] = oldTree->Mu_trigMatch_mu18_mu8noL1->at(i);
    evt->Mu_trigMatch_e17_lhloose_mu14[j] = oldTree->Mu_trigMatch_e17_lhloose_mu14->at(i);
    evt->Mu_trigMatch_e17_lhloose_nod0_mu14[j] = oldTree->Mu_trigMatch_e17_lhloose_nod0_mu14->at(i);
    evt->Mu_trigMatch_mu20_mu8noL1[j] = oldTree->Mu_trigMatch_mu20_mu8noL1->at(i);
    evt->Mu_trigMatch_mu22_mu8noL1[j] = oldTree->Mu_trigMatch_mu22_mu8noL1->at(i);
    evt->Mu_TrigMatch_mu24_iloose[j] = oldTree->Mu_TrigMatch_mu24_iloose->at(i);
    evt->Mu_TrigMatch_mu24_ivarloose[j] = oldTree->Mu_TrigMatch_mu24_ivarloose->at(i);
    evt->Mu_TrigMatch_mu24_iloose_L1MU15[j] = oldTree->Mu_TrigMatch_mu24_iloose_L1MU15->at(i);
    evt->Mu_TrigMatch_mu24_ivarloose_L1MU15[j] = oldTree->Mu_TrigMatch_mu24_ivarloose_L1MU15->at(i);
	for (int ii = 0; ii < oldTree->NMu; ii++) {
	  evt->Mu_trigMatchPair_mu18_mu8noL1[jj] = oldTree->Mu_trigMatchPair_mu18_mu8noL1->at(i).at(ii);
	  evt->Mu_trigMatchPair_mu20_mu8noL1[jj] = oldTree->Mu_trigMatchPair_mu20_mu8noL1->at(i).at(ii);
	  evt->Mu_trigMatchPair_mu22_mu8noL1[jj] = oldTree->Mu_trigMatchPair_mu22_mu8noL1->at(i).at(ii);
	  jj++;
	  }
    j++;
   }
   evt->NMu = j;
   evt->NMuPair = jj;
      //truth leptons
      j = 0;
      for (int i = 0; i < oldTree->NTruthL; i++) {
		if (j == MAXLEPT) {
		  std::cout << "WARNING: Too many leptons\n";
		  break;
	      }
    evt->TruthL_eta[j] = oldTree->TruthL_eta->at(i);
    evt->TruthL_phi[j] = oldTree->TruthL_phi->at(i);
    evt->TruthL_pT[j] = oldTree->TruthL_pT->at(i);
    evt->TruthL_id[j] = oldTree->TruthL_id->at(i);
    j++;
   }
   evt->NTruthL = j;
	//jets
	j = 0;
	for (int i = 0; i < oldTree->NJet; i++) {
	  if (j == MAXJETS) {
		std::cout << "WARNING: Too many jets\n";
		break;
	  }
    evt->Jet_eta[j] = oldTree->Jet_eta->at(i);
    evt->Jet_phi[j] = oldTree->Jet_phi->at(i);
    evt->Jet_pT[j] = oldTree->Jet_pT->at(i);
    evt->Jet_E[j] = oldTree->Jet_E->at(i);
    evt->Jet_quality[j] = oldTree->Jet_quality->at(i);
    evt->Jet_JVT[j] = oldTree->Jet_JVT->at(i);
    evt->Jet_JVTsf[j] = oldTree->Jet_JVTsf->at(i);
    evt->Jet_MV2c20[j] = oldTree->Jet_MV2c20->at(i);
    evt->Jet_MV2c10[j] = oldTree->Jet_MV2c10->at(i);
    evt->Jet_SFw[j] = oldTree->Jet_SFw->at(i);
    evt->Jet_ConeTruthLabel[j] = oldTree->Jet_ConeTruthLabel->at(i);
    evt->Jet_PartonTruthLabel[j] = oldTree->Jet_PartonTruthLabel->at(i);
    evt->Jet_HadronConeExclTruthLabel[j] = oldTree->Jet_HadronConeExclTruthLabel->at(i);
    evt->Jet_deltaR[j] = oldTree->Jet_deltaR->at(i);
    evt->Jet_nTrk[j] = oldTree->Jet_nTrk->at(i);
    evt->Jet_passOR[j] = oldTree->Jet_passOR->at(i);
    j++;
   }
   evt->NJet = j;
	//truth jets
	j = 0;
	for (int i = 0; i < oldTree->NTruthJet; i++) {
	  if (j == MAXJETS) {
		std::cout << "WARNING: Too many jets\n";
		break;
	  }
    evt->TruthJet_eta[j] = oldTree->TruthJet_eta->at(i);
    evt->TruthJet_phi[j] = oldTree->TruthJet_phi->at(i);
    evt->TruthJet_pT[j] = oldTree->TruthJet_pT->at(i);
    evt->TruthJet_E[j] = oldTree->TruthJet_E->at(i);
    evt->TruthJet_ConeTruthLabel[j] = oldTree->TruthJet_ConeTruthLabel->at(i);
    evt->TruthJet_PartonTruthLabel[j] = oldTree->TruthJet_PartonTruthLabel->at(i);
    j++;
   }
   evt->NTruthJet = j;
}else{ 
    evt->sumWeight = -1;
    evt->sumWeightsq = -1;
    evt->rawEvents = -1;
    evt->HLT_e24_lhmedium_nod0_ivarloose          = oldTree->HLT_e24_lhmedium_nod0_ivarloose         ;
    evt->HLT_e24_lhtight_nod0_ivarloose           = oldTree->HLT_e24_lhtight_nod0_ivarloose          ;
    evt->HLT_e24_lhmedium_nod0_L1EM20VH           = oldTree->HLT_e24_lhmedium_nod0_L1EM20VH          ;
    evt->HLT_e26_lhtight_iloose                   = oldTree->HLT_e26_lhtight_iloose                  ;
    evt->HLT_e26_lhtight_ivarloose                = oldTree->HLT_e26_lhtight_ivarloose               ;
    evt->HLT_e26_lhtight_nod0_iloose              = oldTree->HLT_e26_lhtight_nod0_iloose             ;
    evt->HLT_e26_lhtight_nod0_ivarloose           = oldTree->HLT_e26_lhtight_nod0_ivarloose          ;
    evt->HLT_e60_lhmedium                         = oldTree->HLT_e60_lhmedium                        ;
    evt->HLT_e60_lhmedium_nod0                    = oldTree->HLT_e60_lhmedium_nod0                   ;
    evt->HLT_e120_lhloose_nod0                    = oldTree->HLT_e120_lhloose_nod0                   ;
    evt->HLT_e140_lhloose_nod0                    = oldTree->HLT_e140_lhloose_nod0                   ;
    evt->HLT_2e17_lhvloose_nod0                   = oldTree->HLT_2e17_lhvloose_nod0                  ;
    evt->HLT_2e15_lhvloose_nod0_L12EM13VH         = oldTree->HLT_2e15_lhvloose_nod0_L12EM13VH        ;
    evt->HLT_e24_lhmedium_e9_lhmedium             = oldTree->HLT_e24_lhmedium_e9_lhmedium            ;
    evt->HLT_e24_lhmedium_L1EM20VH                = oldTree->HLT_e24_lhmedium_L1EM20VH               ;
    evt->HLT_e12_lhvloose_L12EM10VH               = oldTree->HLT_e12_lhvloose_L12EM10VH              ;
    evt->HLT_e17_lhloose_2e9_lhloose              = oldTree->HLT_e17_lhloose_2e9_lhloose             ;
    evt->HLT_mu24_ivarmedium                      = oldTree->HLT_mu24_ivarmedium                     ;
    evt->HLT_mu24_imedium                         = oldTree->HLT_mu24_imedium                        ;
    evt->HLT_mu24_ivarloose                       = oldTree->HLT_mu24_ivarloose                      ;
    evt->HLT_mu24_iloose                          = oldTree->HLT_mu24_iloose                         ;
    evt->HLT_mu26_ivarmedium                      = oldTree->HLT_mu26_ivarmedium                     ;
    evt->HLT_mu26_imedium                         = oldTree->HLT_mu26_imedium                        ;
    evt->HLT_mu20_ivarmedium_L1MU15               = oldTree->HLT_mu20_ivarmedium_L1MU15              ;
    evt->HLT_mu20_imedium_L1MU15                  = oldTree->HLT_mu20_imedium_L1MU15                 ;
    evt->HLT_mu20_ivarloose_L1MU15                = oldTree->HLT_mu20_ivarloose_L1MU15               ;
    evt->HLT_mu20_iloose_L1MU15                   = oldTree->HLT_mu20_iloose_L1MU15                  ;
    evt->HLT_mu20_L1MU15                          = oldTree->HLT_mu20_L1MU15                         ;
    evt->HLT_mu20_mu8noL1                         = oldTree->HLT_mu20_mu8noL1                        ;
    evt->HLT_mu22_mu8noL1                         = oldTree->HLT_mu22_mu8noL1                        ;
    evt->HLT_mu20_2mu4noL1                        = oldTree->HLT_mu20_2mu4noL1                       ;
    evt->HLT_mu22_2mu4noL1                        = oldTree->HLT_mu22_2mu4noL1                       ;
    evt->HLT_mu40                                 = oldTree->HLT_mu40                                ;
    evt->HLT_mu50                                 = oldTree->HLT_mu50                                ;
    evt->HLT_2mu10                                = oldTree->HLT_2mu10                               ;
    evt->HLT_2mu10_nomucomb                       = oldTree->HLT_2mu10_nomucomb                      ;
    evt->HLT_2mu14                                = oldTree->HLT_2mu14                               ;
    evt->HLT_2mu14_nomucomb                       = oldTree->HLT_2mu14_nomucomb                      ;
    evt->HLT_3mu6                                 = oldTree->HLT_3mu6                                ;
    evt->HLT_3mu6_msonly                          = oldTree->HLT_3mu6_msonly                         ;
    evt->HLT_xe100_L1XE50                         = oldTree->HLT_xe100_L1XE50                        ;
    evt->HLT_xe80_mht_L1XE50                      = oldTree->HLT_xe80_mht_L1XE50                     ;
    evt->HLT_xe90_mht_L1XE50                      = oldTree->HLT_xe90_mht_L1XE50                     ;
    evt->HLT_xe100_mht_L1XE50                     = oldTree->HLT_xe100_mht_L1XE50                    ;
    evt->HLT_xe110_pueta_L1XE50                   = oldTree->HLT_xe110_pueta_L1XE50                  ;
    evt->HLT_xe110_pufit_L1XE50                   = oldTree->HLT_xe110_pufit_L1XE50                  ;
    evt->HLT_xe100_tc_em_L1XE50                   = oldTree->HLT_xe100_tc_em_L1XE50                  ;
    evt->HLT_xe80_tc_lcw_L1XE50                   = oldTree->HLT_xe80_tc_lcw_L1XE50                  ;
    evt->HLT_xe90_tc_lcw_L1XE50                   = oldTree->HLT_xe90_tc_lcw_L1XE50                  ;
    evt->HLT_xe80_tc_lcw_wEFMu_L1XE50             = oldTree->HLT_xe80_tc_lcw_wEFMu_L1XE50            ;
    evt->HLT_e7_lhmedium_mu24                     = oldTree->HLT_e7_lhmedium_mu24                    ;
    evt->HLT_e17_lhloose_nod0_mu14                = oldTree->HLT_e17_lhloose_nod0_mu14               ;
    evt->HLT_e26_lhmedium_nod0_L1EM22VHI_mu8noL1  = oldTree->HLT_e26_lhmedium_nod0_L1EM22VHI_mu8noL1 ;
    evt->HLT_e24_lhmedium_nod0_L1EM22VHI_mu8noL1  = oldTree->HLT_e24_lhmedium_nod0_L1EM22VHI_mu8noL1 ;
    evt->HLT_2e12_lhloose_L12EM10VH               = oldTree->HLT_2e12_lhloose_L12EM10VH              ;
    evt->HLT_e17_lhloose_mu14                     = oldTree->HLT_e17_lhloose_mu14                    ;
    evt->HLT_mu18_mu8noL1                         = oldTree->HLT_mu18_mu8noL1                        ;
    evt->HLT_xe70                                 = oldTree->HLT_xe70                                ;
    evt->EventNumber                              = oldTree->EventNumber                             ;
    evt->ChannelNumber                            = oldTree->ChannelNumber                           ;
    evt->AvgMu                                    = oldTree->AvgMu                                   ;
    evt->EventWeight                              = oldTree->EventWeight                             ;
    evt->PRWWeight                                = oldTree->PRWWeight                               ;
    evt->PRWrandomRunNumber                       = oldTree->PRWrandomRunNumber                      ;
    evt->bcid                                     = oldTree->bcid                                    ;
    evt->LB                                       = oldTree->LB                                      ;
    evt->RunNb                                    = oldTree->RunNb                                   ;
    evt->DetError                                 = oldTree->DetError                                ;
    evt->MuTrigSF_HLT_mu20_iloose_L1MU15_OR_HLT_mu50 = oldTree->MuTrigSF_HLT_mu20_iloose_L1MU15_OR_HLT_mu50;
    evt->Etmiss_CST_Etx                           = oldTree->Etmiss_CST_Etx                          ;
    evt->Etmiss_CST_Ety                           = oldTree->Etmiss_CST_Ety                          ;
    evt->Etmiss_CST_Et                            = oldTree->Etmiss_CST_Et                           ;
    evt->Etmiss_TST_Etx                           = oldTree->Etmiss_TST_Etx                          ;
    evt->Etmiss_TST_Ety                           = oldTree->Etmiss_TST_Ety                          ;
    evt->Etmiss_TST_Et                            = oldTree->Etmiss_TST_Et                           ;
    evt->Etmiss_TSTterm_Etx                       = oldTree->Etmiss_TSTterm_Etx                      ;
    evt->Etmiss_TSTterm_Ety                       = oldTree->Etmiss_TSTterm_Ety                      ;
    evt->Etmiss_TSTterm_Et                        = oldTree->Etmiss_TSTterm_Et                       ;
    evt->Etmiss_Truth_Etx                         = oldTree->Etmiss_Truth_Etx                        ;
    evt->Etmiss_Truth_Ety                         = oldTree->Etmiss_Truth_Ety                        ;
    evt->Etmiss_Truth_Et                          = oldTree->Etmiss_Truth_Et                         ;
    evt->PV_z                                     = oldTree->PV_z                                    ;
    evt->Nvtx                                     = oldTree->Nvtx                                    ;
    evt->TruthX1                                  = oldTree->TruthX1                                 ;
    evt->TruthX2                                  = oldTree->TruthX2                                 ;
    evt->TruthQ                                   = oldTree->TruthQ                                  ;
    evt->SherpaNjetWeight                         = oldTree->SherpaNjetWeight                        ;
    evt->TruthPDGID1                              = oldTree->TruthPDGID1                             ;
    evt->TruthPDGID2                              = oldTree->TruthPDGID2                             ;


	//electrons
	j = 0;
	for (int i = 0; i < oldTree->NEl; i++) {
	  if (j == MAXLEPT) {
		std::cout << "WARNING: Too many electrons\n";
		break;
	  }
    evt->El_eta[j] = oldTree->El_eta->at(i);
    evt->El_etaclus[j] = oldTree->El_etaclus->at(i);
    evt->El_phi[j] = oldTree->El_phi->at(i);
    evt->El_pT[j] = oldTree->El_pT->at(i);
    evt->El_E[j] = oldTree->El_E->at(i);
    evt->El_charge[j] = oldTree->El_charge->at(i);
    evt->El_sigd0[j] = oldTree->El_sigd0->at(i);
    evt->El_z0sinTheta[j] = oldTree->El_z0sinTheta->at(i);
    evt->El_d0pvtx[j] = oldTree->El_d0pvtx->at(i);
    evt->El_passOR[j] = oldTree->El_passOR->at(i);
    evt->El_SFwMediumLH[j] = oldTree->El_SFwMediumLH->at(i);
    evt->El_IsoSFwMediumLH[j] = oldTree->El_IsoSFwMediumLH->at(i);
    evt->El_SFwTightLH[j] = oldTree->El_SFwTightLH->at(i);
    evt->El_SFwLooseAndBLayerLH[j] = oldTree->El_SFwLooseAndBLayerLH->at(i);
    evt->El_SFwTrigMediumLH_e12_lhloose_L1EM10VH[j] = oldTree->El_SFwTrigMediumLH_e12_lhloose_L1EM10VH->at(i);
    evt->El_SFwTrigMediumLH_e17_lhloose[j] = oldTree->El_SFwTrigMediumLH_e17_lhloose->at(i);
    evt->El_SFwTrigMediumLH_single[j] = oldTree->El_SFwTrigMediumLH_single->at(i);
    evt->El_SFwTrigLooseAndBLayerLH_e12_lhloose_L1EM10VH[j] = oldTree->El_SFwTrigLooseAndBLayerLH_e12_lhloose_L1EM10VH->at(i);
    evt->El_isLooseAndBLayerLH[j] = oldTree->El_isLooseAndBLayerLH->at(i);
    evt->El_isMediumLH[j] = oldTree->El_isMediumLH->at(i);
    evt->El_isTightLH[j] = oldTree->El_isTightLH->at(i);
    evt->El_nBLayerHits[j] = oldTree->El_nBLayerHits->at(i);
    evt->El_expectBLayerHit[j] = oldTree->El_expectBLayerHit->at(i);
    evt->El_ptcone20[j] = oldTree->El_ptcone20->at(i);
    evt->El_ptcone30[j] = oldTree->El_ptcone30->at(i);
    evt->El_ptcone40[j] = oldTree->El_ptcone40->at(i);
    evt->El_ptvarcone20[j] = oldTree->El_ptvarcone20->at(i);
    evt->El_ptvarcone30[j] = oldTree->El_ptvarcone30->at(i);
    evt->El_ptvarcone40[j] = oldTree->El_ptvarcone40->at(i);
    evt->El_topoetcone20[j] = oldTree->El_topoetcone20->at(i);
    evt->El_topoetcone30[j] = oldTree->El_topoetcone30->at(i);
    evt->El_topoetcone40[j] = oldTree->El_topoetcone40->at(i);
    evt->El_passIsoLooseTO[j] = oldTree->El_passIsoLooseTO->at(i);
    evt->El_passIsoLoose[j] = oldTree->El_passIsoLoose->at(i);
    evt->El_passIsoTight[j] = oldTree->El_passIsoTight->at(i);
    evt->El_passIsoGrad[j] = oldTree->El_passIsoGrad->at(i);
    evt->El_passIsoGradCustomTight[j] = oldTree->El_passIsoGradCustomTight->at(i);
    evt->El_passIsoGradCustom[j] = oldTree->El_passIsoGradCustom->at(i);
    evt->El_passIsoGradLoose[j] = oldTree->El_passIsoGradLoose->at(i);
    evt->El_trigMatch_e12_lhloose_L1EM10VH[j] = oldTree->El_trigMatch_e12_lhloose_L1EM10VH->at(i);
    evt->El_trigMatch_e17_lhloose[j] = oldTree->El_trigMatch_e17_lhloose->at(i);
    evt->El_trigMatch_e60_lhmedium[j] = oldTree->El_trigMatch_e60_lhmedium->at(i);
    evt->El_trigMatch_e24_lhmedium_iloose_L1EM20VH[j] = oldTree->El_trigMatch_e24_lhmedium_iloose_L1EM20VH->at(i);
    evt->El_trigMatch_2e12_lhloose_L12EM10VH[j] = oldTree->El_trigMatch_2e12_lhloose_L12EM10VH->at(i);
    evt->El_trigMatch_2e15_lhloose_L12EM10VH[j] = oldTree->El_trigMatch_2e15_lhloose_L12EM10VH->at(i);
    evt->El_trigMatch_2e15_lhvloose_L12EM13VH[j] = oldTree->El_trigMatch_2e15_lhvloose_L12EM13VH->at(i);
    evt->El_trigMatch_2e15_lhvloose_nod0_L12EM13VH[j] = oldTree->El_trigMatch_2e15_lhvloose_nod0_L12EM13VH->at(i);
    evt->El_trigMatch_2e17_lhvloose_nod0[j] = oldTree->El_trigMatch_2e17_lhvloose_nod0->at(i);
    evt->El_trigMatch_e17_lhloose_mu14[j] = oldTree->El_trigMatch_e17_lhloose_mu14->at(i);
    evt->El_trigMatch_e17_lhloose_nod0_mu14[j] = oldTree->El_trigMatch_e17_lhloose_nod0_mu14->at(i);
    evt->El_TrigMatch_e24_lhmedium_nod0_ivarloose[j] = oldTree->El_TrigMatch_e24_lhmedium_nod0_ivarloose->at(i);
    evt->El_TrigMatch_e24_lhtight_nod0_ivarloose[j] = oldTree->El_TrigMatch_e24_lhtight_nod0_ivarloose->at(i);
    evt->El_TrigMatch_e60_lhmedium_nod0[j] = oldTree->El_TrigMatch_e60_lhmedium_nod0->at(i);
    j++;
   }
   evt->NEl = j;


	//muons
	j = 0;
	jj = 0;
	for (int i = 0; i < oldTree->NMu; i++) {
	  if (j == MAXLEPT) {
		std::cout << "WARNING: Too many muons\n";
		break;
	  }
    evt->Mu_eta[j] = oldTree->Mu_eta->at(i);
    evt->Mu_phi[j] = oldTree->Mu_phi->at(i);
    evt->Mu_pT[j] = oldTree->Mu_pT->at(i);
    evt->Mu_SFw[j] = oldTree->Mu_SFw->at(i);
    evt->Mu_IsoSFw[j] = oldTree->Mu_IsoSFw->at(i);
    evt->Mu_charge[j] = oldTree->Mu_charge->at(i);
    evt->Mu_d0pvtx[j] = oldTree->Mu_d0pvtx->at(i);
    evt->Mu_sigd0[j] = oldTree->Mu_sigd0->at(i);
    evt->Mu_z0sinTheta[j] = oldTree->Mu_z0sinTheta->at(i);
    evt->Mu_isBad[j] = oldTree->Mu_isBad->at(i);
    evt->Mu_passOR[j] = oldTree->Mu_passOR->at(i);
    evt->Mu_isTight[j] = oldTree->Mu_isTight->at(i);
    evt->Mu_isCosmic[j] = oldTree->Mu_isCosmic->at(i);
    evt->Mu_ptcone20[j] = oldTree->Mu_ptcone20->at(i);
    evt->Mu_ptcone30[j] = oldTree->Mu_ptcone30->at(i);
    evt->Mu_ptcone40[j] = oldTree->Mu_ptcone40->at(i);
    evt->Mu_ptvarcone20[j] = oldTree->Mu_ptvarcone20->at(i);
    evt->Mu_ptvarcone30[j] = oldTree->Mu_ptvarcone30->at(i);
    evt->Mu_ptvarcone40[j] = oldTree->Mu_ptvarcone40->at(i);
    evt->Mu_topoetcone20[j] = oldTree->Mu_topoetcone20->at(i);
    evt->Mu_topoetcone30[j] = oldTree->Mu_topoetcone30->at(i);
    evt->Mu_topoetcone40[j] = oldTree->Mu_topoetcone40->at(i);
    evt->Mu_passIsoLooseTO[j] = oldTree->Mu_passIsoLooseTO->at(i);
    evt->Mu_passIsoLoose[j] = oldTree->Mu_passIsoLoose->at(i);
    evt->Mu_passIsoTight[j] = oldTree->Mu_passIsoTight->at(i);
    evt->Mu_passIsoGrad[j] = oldTree->Mu_passIsoGrad->at(i);
    evt->Mu_passIsoGradCustomTight[j] = oldTree->Mu_passIsoGradCustomTight->at(i);
    evt->Mu_passIsoGradCustom[j] = oldTree->Mu_passIsoGradCustom->at(i);
    evt->Mu_passIsoGradLoose[j] = oldTree->Mu_passIsoGradLoose->at(i);
    evt->Mu_trigMatch_mu26_imedium[j] = oldTree->Mu_trigMatch_mu26_imedium->at(i);
    evt->Mu_trigMatch_mu50[j] = oldTree->Mu_trigMatch_mu50->at(i);
    evt->Mu_trigMatch_mu8noL1[j] = oldTree->Mu_trigMatch_mu8noL1->at(i);
    evt->Mu_trigMatch_mu14[j] = oldTree->Mu_trigMatch_mu14->at(i);
    evt->Mu_trigMatch_mu18[j] = oldTree->Mu_trigMatch_mu18->at(i);
    evt->Mu_trigMatch_mu18_mu8noL1[j] = oldTree->Mu_trigMatch_mu18_mu8noL1->at(i);
    evt->Mu_trigMatch_e17_lhloose_mu14[j] = oldTree->Mu_trigMatch_e17_lhloose_mu14->at(i);
    evt->Mu_trigMatch_e17_lhloose_nod0_mu14[j] = oldTree->Mu_trigMatch_e17_lhloose_nod0_mu14->at(i);
    evt->Mu_trigMatch_mu20_mu8noL1[j] = oldTree->Mu_trigMatch_mu20_mu8noL1->at(i);
    evt->Mu_trigMatch_mu22_mu8noL1[j] = oldTree->Mu_trigMatch_mu22_mu8noL1->at(i);
    evt->Mu_TrigMatch_mu24_iloose[j] = oldTree->Mu_TrigMatch_mu24_iloose->at(i);
    evt->Mu_TrigMatch_mu24_ivarloose[j] = oldTree->Mu_TrigMatch_mu24_ivarloose->at(i);
    evt->Mu_TrigMatch_mu24_iloose_L1MU15[j] = oldTree->Mu_TrigMatch_mu24_iloose_L1MU15->at(i);
    evt->Mu_TrigMatch_mu24_ivarloose_L1MU15[j] = oldTree->Mu_TrigMatch_mu24_ivarloose_L1MU15->at(i);
	for (int ii = 0; ii < oldTree->NMu; ii++) {
	  evt->Mu_trigMatchPair_mu18_mu8noL1[jj] = oldTree->Mu_trigMatchPair_mu18_mu8noL1->at(i).at(ii);
	  evt->Mu_trigMatchPair_mu20_mu8noL1[jj] = oldTree->Mu_trigMatchPair_mu20_mu8noL1->at(i).at(ii);
	  evt->Mu_trigMatchPair_mu22_mu8noL1[jj] = oldTree->Mu_trigMatchPair_mu22_mu8noL1->at(i).at(ii);
	  jj++;
	}
    j++;
   }
   evt->NMu = j;
   evt->NMuPair = jj;
	//jets
	j = 0;
	for (int i = 0; i < oldTree->NJet; i++) {
	  if (j == MAXJETS) {
		std::cout << "WARNING: Too many jets\n";
		break;
	  }
    evt->Jet_eta[j] = oldTree->Jet_eta->at(i);
    evt->Jet_phi[j] = oldTree->Jet_phi->at(i);
    evt->Jet_pT[j] = oldTree->Jet_pT->at(i);
    evt->Jet_E[j] = oldTree->Jet_E->at(i);
    evt->Jet_quality[j] = oldTree->Jet_quality->at(i);
    evt->Jet_JVT[j] = oldTree->Jet_JVT->at(i);
    evt->Jet_JVTsf[j] = oldTree->Jet_JVTsf->at(i);
    evt->Jet_MV2c20[j] = oldTree->Jet_MV2c20->at(i);
    evt->Jet_MV2c10[j] = oldTree->Jet_MV2c10->at(i);
    evt->Jet_SFw[j] = oldTree->Jet_SFw->at(i);
    evt->Jet_nTrk[j] = oldTree->Jet_nTrk->at(i);
    evt->Jet_passOR[j] = oldTree->Jet_passOR->at(i);
    j++;
   }
   evt->NJet = j;
	  }
	//==========================================================================
	if (-1 == t_MiniNtuple->Fill()) { // fill root tree
	  std::cerr
		<< "ERROR: Can not fill the tree for the reduced ntuple.\n";
	  return StatusCode::FAILURE;
	}
  }

  return sc;
}

//_____________________________________________________________________________

StatusCode TMiniNtuple::finalize() {

  StatusCode sc = StatusCode::SUCCESS;

  outputRootFile = t_MiniNtuple->GetCurrentFile(); //just in case we switched to a new file
  outputRootFile->Write(); // close output root file
  outputRootFile->Close(); // close output root file

  delete oldTree;
  delete evt;

  std::cout << "----- end job: ---- \n";

  return sc;
}

//____________________________________________________________________________
void TMiniNtuple::InitNtpVar(myevt *ev) {

  //	ev->el_n = 0;

  return;
}

//_____________________________________________________________________________
float TMiniNtuple::deltaR(float eta1, float phi1, float eta2, float phi2) {

  float deltaR12 = phi1 - phi2;
  if (deltaR12 > TMath::Pi())
	deltaR12 -= 2 * TMath::Pi();
  if (deltaR12 < -TMath::Pi())
	deltaR12 += 2 * TMath::Pi();

  deltaR12 = sqrt(deltaR12 * deltaR12 + (eta1 - eta2) * (eta1 - eta2));
  return deltaR12;
}

