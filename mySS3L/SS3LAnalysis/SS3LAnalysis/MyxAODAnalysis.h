#ifndef MyAnalysis_MyxAODAnalysis_H
#define MyAnalysis_MyxAODAnalysis_H

#include <EventLoop/Algorithm.h>

// Infrastructure include(s):
#include "xAODRootAccess/Init.h"
#include "xAODRootAccess/TEvent.h"
#include "xAODRootAccess/TStore.h"

/// OR includes (local includes)
#include "AssociationUtils/OverlapRemovalInit.h"
#include "AssociationUtils/OverlapRemovalDefs.h"

#include <TH1.h>
#include <TTree.h>
//#include "PATInterfaces/SystematicList.h"
//#include "PATInterfaces/SystematicVariation.h"
//#include "PATInterfaces/SystematicRegistry.h"
//#include "PATInterfaces/SystematicCode.h"
//#include "boost/unordered_map.hpp"

#include <map>

// GRL
class GoodRunsListSelectionTool;
namespace CP{
  class PileupReweightingTool;
  class IsolationSelectionTool;
  class MuonSelectionTool;
  class MuonTriggerScaleFactors;
  class IMuonTriggerScaleFactors;
}
using namespace CP;
class JetCleaningTool;

namespace ST{
  class SUSYObjDef_xAOD;
}
using namespace ST;


class AsgElectronLikelihoodTool;

class AsgElectronEfficiencyCorrectionTool;

class AsgElectronChargeIDSelectorTool;

class IAsgElectronEfficiencyCorrectionTool;

class TrigGlobalEfficiencyCorrectionTool;

class ITrigGlobalEfficiencyCorrectionTool;

class MyxAODAnalysis : public EL::Algorithm
{

#ifndef __CINT__
  GoodRunsListSelectionTool *m_grl; //!
  PileupReweightingTool *m_pileupReweightingTool; //!
  SUSYObjDef_xAOD *objTool; //!   
  //   SUSYObjDef_xAOD *objTool_lhmed; //!   
  //   SUSYObjDef_xAOD *objTool_tight; //!   
  //   SUSYObjDef_xAOD *objTool_med; //!   

  ORUtils::ToolBox my_orToolbox; //!

  AsgElectronLikelihoodTool *m_elecSelLikelihood_LhTight; //!

  AsgElectronEfficiencyCorrectionTool* m_electronSF_reco; //!
  AsgElectronEfficiencyCorrectionTool* m_electronSF_LhLoose; //!
  AsgElectronEfficiencyCorrectionTool* m_electronSF_LhTight; //!
  AsgElectronEfficiencyCorrectionTool* m_electronSF_trig_LhLoose; //!
  AsgElectronEfficiencyCorrectionTool* m_electronSF_trig_LhTight; //!
  AsgElectronEfficiencyCorrectionTool* m_electronSF_CFT; //!

  MuonSelectionTool* m_muonSelectionTool; //!

  IsolationSelectionTool *isoLooseTO; //!
  IsolationSelectionTool *isoLoose; //!
  IsolationSelectionTool *isoTight; //!
  IsolationSelectionTool *isoGrad; //!
  IsolationSelectionTool *isoGradLoose; //!
  IsolationSelectionTool *isoGradCustom; //!
  IsolationSelectionTool *isoGradCustomTight; //!

  AsgElectronChargeIDSelectorTool* CFTToolmedium; //!
  AsgElectronChargeIDSelectorTool* CFTToolLoose; //!

  ToolHandleArray<IMuonTriggerScaleFactors> muonTools; //!
  ToolHandleArray<IAsgElectronEfficiencyCorrectionTool> electronEffTools; //! 
  ToolHandleArray<IAsgElectronEfficiencyCorrectionTool> electronSFTools; //!
  TrigGlobalEfficiencyCorrectionTool* myTriggerSFTool; //!

#endif // not __CINT__
 private: 
  unsigned long long EventNumber; //!
  int RunNumber; //!
  /*   std::vector<float> EtaMuons; //! */
  /*   std::vector<float> pTMuons; //! */
  /*   std::vector<float> MassMuons; //! This is here for sanity checks */
  /*   std::vector<float> PhiMuons; //! */
  
  bool isMyOR = false;
  double pT_treshold;

  std::map<const std::string, bool> trig_map;

  // Muon Block
  Int_t   NMu; //!
  std::vector<Double_t> Mu_eta; //!
  std::vector<Double_t> Mu_phi; //!
  std::vector<Double_t> Mu_pT; //!
  std::vector<Int_t>    Mu_charge; //!
  std::vector<Double_t> Mu_SFw; //!
  std::vector<Double_t> Mu_d0pvtx; //!
  std::vector<Double_t> Mu_d0old; //!
  std::vector<Double_t> Mu_d0pvtxerr; //!
  std::vector<Double_t> Mu_sigd0; //!
  std::vector<Double_t> Mu_sigd0old; //!
  std::vector<Double_t> Mu_z0pvtx; //!
  std::vector<bool>     Mu_isSig; //!
  std::vector<bool>     Mu_isBad; //!
  std::vector<bool>     Mu_isTight; //!
  std::vector<bool>     Mu_isCosmic; //!
  std::vector<bool>     Mu_passOR; //!
  std::vector<Int_t>    Mu_type; //! 
  std::vector<Int_t>    Mu_origin; //!
  std::vector<Double_t> Mu_ptcone20; //!
  std::vector<Double_t> Mu_ptcone30; //!
  std::vector<Double_t> Mu_ptcone40; //!
  std::vector<Double_t> Mu_ptvarcone20; //!
  std::vector<Double_t> Mu_ptvarcone30; //!
  std::vector<Double_t> Mu_ptvarcone40; //!
  std::vector<Double_t> Mu_topoetcone20; //!
  std::vector<Double_t> Mu_topoetcone30; //!
  std::vector<Double_t> Mu_topoetcone40; //!
  std::vector<bool>     Mu_passIsoLooseTO; //!
  std::vector<bool>     Mu_passIsoLoose; //!
  std::vector<bool>     Mu_passIsoTight; //!
  std::vector<bool>     Mu_passIsoGrad; //!
  std::vector<bool>     Mu_passIsoGradCustom; //!
  std::vector<bool>     Mu_passIsoGradCustomTight; //!
  std::vector<bool>     Mu_passIsoGradLoose; //!
  std::vector<bool>     Mu_TrigMatch_mu26_ivarmedium; //!
  std::vector<bool>     Mu_TrigMatch_mu20_iloose_L1MU15; //!
  std::vector<bool>     Mu_TrigMatch_mu40; //!
  std::vector<bool>     Mu_TrigMatch_mu50; //!
  std::vector<bool>     Mu_TrigMatch_mu14; //!
  std::vector<bool>     Mu_TrigMatch_mu18; //!
  std::vector<bool>     Mu_TrigMatch_mu8noL1; //!
  std::vector<bool>     Mu_TrigMatch_mu18_mu8noL1; //!
  std::vector<bool>     Mu_TrigMatch_e17_lhloose_mu14; //!
  std::vector<bool>     Mu_TrigMatch_mu20_mu8noL1; //!
  std::vector<bool>     Mu_TrigMatch_mu22_mu8noL1; //!
  std::vector<bool>     Mu_TrigMatch_e17_lhloose_nod0_mu14; //!
  std::vector<bool>     Mu_TrigMatch_mu24_iloose; //!
  std::vector<bool>     Mu_TrigMatch_mu24_ivarloose; //!
  std::vector<bool>     Mu_TrigMatch_mu24_iloose_L1MU15; //!
  std::vector<bool>     Mu_TrigMatch_mu24_ivarloose_L1MU15; //!
  std::vector<std::vector<bool> >     Mu_TrigMatchPair_mu18_mu8noL1; //!
  std::vector<std::vector<bool> >     Mu_TrigMatchPair_mu20_mu8noL1; //!
  std::vector<std::vector<bool> >     Mu_TrigMatchPair_mu22_mu8noL1; //!
  
  std::vector<float>     Mu_TrigSF_MU10; //!
  std::vector<float>     Mu_TrigSF_MU15; //!
  std::vector<float>     Mu_TrigMCeff_MU10; //!
  std::vector<float>     Mu_TrigMCeff_MU15; //!


  //  Float_t   MuTrigSF_2mu14; //!
  Float_t   MuTrigSF_HLT_mu20_iloose_L1MU15_OR_HLT_mu50; //!

  // Electron Block
  Int_t   NEl=0;
  std::vector<Double_t> El_eta; //!
  std::vector<Double_t> El_etaclus; //!
  std::vector<Double_t> El_phi; //!
  std::vector<Double_t> El_pT; //! 
  std::vector<Double_t> El_E; //! 
  std::vector<Int_t>    El_charge; //!
  std::vector<Double_t> El_sigd0; //!  
  std::vector<Double_t> El_sigd0old; //!  
  std::vector<Double_t> El_d0pvtx; //! 
  std::vector<Double_t> El_d0old; //! 
  std::vector<Double_t> El_d0pvtxerr; //! 
  std::vector<Double_t> El_z0pvtx; //! 
  //  std::vector<Double_t> El_SFw; //! 

  std::vector<Double_t> El_SFwMedium; //!
  std::vector<Double_t> El_SFwTight; //!
  std::vector<Double_t> El_SFwMediumLH; //!
  std::vector<Double_t> El_SFwTightLH; //!
  std::vector<Double_t> El_SFwLooseLH; //!

  std::vector<Double_t> El_SFwTrigMedium; //!
  std::vector<Double_t> El_SFwTrigTight; //!
  std::vector<Double_t> El_SFwTrigMediumLH; //!
  std::vector<Double_t> El_SFwTrigMediumLH_e12_lhloose_L1EM10VH; //!
  std::vector<Double_t> El_SFwTrigMediumLH_e17_lhloose; //!
  std::vector<Double_t> El_SFwTrigMediumLH_single; //!
  std::vector<Double_t> El_SFwTrigLooseLH; //!

  std::vector<Double_t> El_SFweightCFT; //! 

  std::vector<bool>     El_isLoose; //!
  std::vector<bool>     El_isMedium; //!
  std::vector<bool>     El_isTight; //!
  std::vector<bool>     El_isLooseLH; //!
  std::vector<bool>     El_isMediumLH; //!
  std::vector<bool>     El_isTightLH; //!
  std::vector<bool>     El_passOR; //!
  std::vector<Int_t>    El_truthType; //! 
  std::vector<Int_t>    El_truthOrigin; //!
  std::vector<Int_t>    El_bkgTruthType; //! 
  std::vector<Int_t>    El_bkgTruthOrigin; //!
  std::vector<Int_t>    El_bkgMotherPdgId; //! 
  std::vector<Int_t>    El_firstEgMotherTruthType; //! 
  std::vector<Int_t>    El_firstEgMotherTruthOrigin; //!
  std::vector<Int_t>    El_firstEgMotherPdgId; //! 
  std::vector<Int_t>    El_chFlip; //!
  std::vector<Int_t>    El_nBLayerHits; //!
  std::vector<Int_t>    El_expectBLayerHit; //!
  std::vector<Double_t> El_ptcone20; //!
  std::vector<Double_t> El_ptcone30; //!
  std::vector<Double_t> El_ptcone40; //!
  std::vector<Double_t> El_ptvarcone20; //!
  std::vector<Double_t> El_ptvarcone30; //!
  std::vector<Double_t> El_ptvarcone40; //!
  std::vector<Double_t> El_topoetcone20; //!
  std::vector<Double_t> El_topoetcone30; //!
  std::vector<Double_t> El_topoetcone40; //!
  std::vector<bool>     El_passIsoLooseTO; //!
  std::vector<bool>     El_passIsoLoose; //!
  std::vector<bool>     El_passIsoTight; //!
  std::vector<bool>     El_passIsoGrad; //!
  std::vector<bool>     El_passIsoGradCustom; //!
  std::vector<bool>     El_passIsoGradCustomTight; //!
  std::vector<bool>     El_passIsoGradLoose; //!
  std::vector<bool>     El_TrigMatch_e12_lhloose_L1EM10VH; //!
  std::vector<bool>     El_TrigMatch_e17_lhloose; //!
  std::vector<bool>     El_TrigMatch_e60_lhmedium; //!
  std::vector<bool>     El_TrigMatch_e24_lhmedium_L1EM20VH; //!
  std::vector<bool>     El_TrigMatch_e24_lhmedium_iloose_L1EM20VH; //!
  std::vector<bool>     El_TrigMatch_e26_lhtight_nod0_ivarloose; //!
  std::vector<bool>     El_TrigMatch_2e12_lhloose_L12EM10VH; //!
  std::vector<bool>     El_TrigMatch_2e15_lhloose_L12EM10VH; //!
  std::vector<bool>     El_TrigMatch_2e15_lhvloose_L12EM13VH; //!
  std::vector<bool>     El_TrigMatch_2e15_lhvloose_nod0_L12EM13VH; //!
  std::vector<bool>     El_TrigMatch_2e17_lhvloose_nod0; //!
  std::vector<bool>     El_TrigMatch_e17_lhloose_mu14; //!
  std::vector<bool>     El_TrigMatch_e17_lhloose_nod0_mu14; //!
  std::vector<bool>     El_TrigMatch_e24_lhmedium_nod0_ivarloose; //!
  std::vector<bool>     El_TrigMatch_e24_lhtight_nod0_ivarloose; //!
  std::vector<bool>     El_TrigMatch_e60_lhmedium_nod0; //!

  std::vector<float>     El_TrigSF_e12_lhloose_L1EM10VH; //!
  std::vector<float>     El_TrigSF_e17_lhloose; //!
  std::vector<float>     El_TrigSF_e60_lhmedium; //!
  std::vector<float>     El_TrigSF_e24_lhmedium_L1EM20VH; //!
  std::vector<float>     El_TrigSF_e24_lhmedium_iloose_L1EM20VH; //!
  std::vector<float>     El_TrigMCeff_e12_lhloose_L1EM10VH; //!
  std::vector<float>     El_TrigMCeff_e17_lhloose; //!
  std::vector<float>     El_TrigMCeff_e60_lhmedium; //!
  std::vector<float>     El_TrigMCeff_e24_lhmedium_L1EM20VH; //!
  std::vector<float>     El_TrigMCeff_e24_lhmedium_iloose_L1EM20VH; //!

  std::vector<float>     El_IsoSFwMediumLH; //!
  std::vector<float>     Mu_IsoSFw; //!

  //  std::vector<bool>     El_passChargeFlipTagger; //!
  std::vector<float>    El_passChargeFlipTaggerBDTmedium; //!  
  std::vector<float>    El_passChargeFlipTaggerBDTloose; //!  

  // JET Block
  Int_t   NJet=0;
  std::vector<bool> Jet_isSig; //!
  std::vector<Double_t> Jet_eta; //!
  std::vector<Double_t> Jet_phi; //!
  std::vector<Double_t> Jet_pT; //!
  std::vector<Double_t> Jet_E; //!
  std::vector<Double_t> Jet_quality; //!
  //  std::vector<Double_t> Jet_JVF; //!
  std::vector<Double_t> Jet_JVT; //!
  std::vector<Double_t> Jet_JVTsf; //!
  std::vector<Double_t> Jet_MV2c20; //!
  std::vector<Double_t> Jet_MV2c10; //!
  std::vector<Double_t> Jet_noMV1; //!
  std::vector<Double_t> Jet_SFw; //!
  std::vector<Int_t> Jet_ConeTruthLabel; //!
  std::vector<Int_t> Jet_PartonTruthLabel; //!
  std::vector<Int_t> Jet_HadronConeExclTruthLabel; //!
  std::vector<Int_t> Jet_isBad; //!
  std::vector<Int_t> Jet_nTrk; //!
  std::vector<bool>  Jet_passOR; //!
  std::vector<Double_t> Jet_deltaR; //!
  
  float totalJVTsf;

  Int_t   NTruthJet=0;
  std::vector<Double_t> TruthJet_eta; //!
  std::vector<Double_t> TruthJet_phi; //!
  std::vector<Double_t> TruthJet_pT; //!
  std::vector<Double_t> TruthJet_E; //!
  std::vector<Int_t>    TruthJet_ConeTruthLabel; //!
  std::vector<Int_t>    TruthJet_PartonTruthLabel; //!
  std::vector<Int_t>    TruthJet_HadronConeExclTruthLabel; //!
  std::vector<Int_t>    TruthJet_ClassHF; //!

  Int_t   NTruthL=0;
  std::vector<Double_t> TruthL_eta   ; //!
  std::vector<Double_t> TruthL_phi   ; //!
  std::vector<Double_t> TruthL_pT    ; //!
  std::vector<Int_t>    TruthL_id    ; //!

  Int_t   NTruthV=0;
  std::vector<Double_t> TruthV_eta   ; //!
  std::vector<Double_t> TruthV_phi   ; //!
  std::vector<Double_t> TruthV_pT    ; //!
  std::vector<Double_t> TruthV_m     ; //!
  std::vector<Int_t>    TruthV_id    ; //!
  std::vector<Int_t>    TruthV_index ; //!

  Int_t   NTruthVch=0;
  std::vector<Double_t> TruthVch_eta   ; //!
  std::vector<Double_t> TruthVch_phi   ; //!
  std::vector<Double_t> TruthVch_pT    ; //!
  std::vector<Int_t>    TruthVch_id    ; //!
  std::vector<Int_t>    TruthVch_index ; //!

  // MET
  Float_t Etmiss_CST_Etx=0.;
  Float_t Etmiss_CST_Ety=0.;
  Float_t Etmiss_CST_Et=0.;

  Float_t Etmiss_TST_Etx=0.;
  Float_t Etmiss_TST_Ety=0.;
  Float_t Etmiss_TST_Et=0.;

  Float_t Etmiss_TSTterm_Etx=0.;
  Float_t Etmiss_TSTterm_Ety=0.;
  Float_t Etmiss_TSTterm_Et=0.;

  Float_t Etmiss_Truth_Etx=0.;
  Float_t Etmiss_Truth_Ety=0.;
  Float_t Etmiss_Truth_Et=0.;

  unsigned long long tEventNumber;
  Int_t tChannelNumber;
  Double_t tAvgMu;
  Int_t bcid;
  Int_t LB;
  Int_t passGRL;
  Int_t RunNb;
  Double_t EventWeight;
  Double_t PRWWeight;
  Int_t PRWrandomRunNumber;
  Double_t TriggerDileptonSF;

  Float_t GenFiltHT ;
  Float_t GenFiltMET ;

  Int_t tDetError;

  Float_t primvertex_x ;
  Float_t primvertex_y ;
  Float_t primvertex_z ;

  Int_t  Nvtx ;

  Int_t pdgid1;
  Int_t pdgid2;
  Int_t gluDecay1;
  Int_t gluDecay2;

  int TruthPDGID1=0.; 
  int TruthPDGID2=0.; 
  int TruthPDFID1=0.; 
  int TruthPDFID2=0.; 
  float TruthX1=0.; 
  float TruthX2=0.; 
  float TruthXF1=0.; 
  float TruthXF2=0.; 
  float TruthQ=0.;

  Float_t SherpaNjetWeight;

  Int_t extraB=0;
  Int_t extraC=0;


  // put your configuration variables here as public variables.
  // that way they can be set directly from CINT and python.
 public:
  int isData;
  int isAtlfast;
  int ismc15c;
  int useLeptonTrigger;
  int doSyst;
  int isDerived;    
  int skipBtag;
  std::string inputDS;
  //  std::vector<CP::SystematicSet> sysList; //!
  
  // variables that don't get filled at submission time should be
  // protected from being send from the submission node to the worker
  // node (done by the //!)
 public:
  TTree *MyTree; //!
  
  float  m_finalSumOfWeights; //!
  float  m_initialSumOfWeights; //!
  float  m_finalNevents; //!
  float  m_initialNevents; //!
  
  TH1D* hEvents; //!
  TH1D* hWeights; //!
  TH1D* hWeightsSquared; //!

  const int nTrig = 58;
  TString nameTrig[58]={ 
	"HLT_e24_lhmedium_nod0_ivarloose",
	"HLT_e24_lhtight_nod0_ivarloose", 
	"HLT_e24_lhmedium_nod0_L1EM20VH",
	"HLT_e26_lhtight_iloose", 	 
	"HLT_e26_lhtight_ivarloose", 	  	  	  	 
	"HLT_e26_lhtight_nod0_iloose", 	  	  	  	 
	"HLT_e26_lhtight_nod0_ivarloose", 
	"HLT_e60_lhmedium", 	  	  	
	"HLT_e60_lhmedium_nod0", 	  	
	"HLT_e120_lhloose_nod0", 	  	
	"HLT_e140_lhloose_nod0", 	  	
	"HLT_2e17_lhvloose_nod0", 	  
	"HLT_2e15_lhvloose_nod0_L12EM13VH",
	"HLT_e24_lhmedium_e9_lhmedium", 
	"HLT_e24_lhmedium_L1EM20VH", 	 
	"HLT_e24_lhmedium_iloose_L1EM20VH", 	 
	"HLT_e12_lhvloose_L12EM10VH",
	"HLT_e17_lhloose_2e9_lhloose", 	  	  	  	 
	"HLT_mu24_ivarmedium", 		 
	"HLT_mu24_imedium", 	  	
	"HLT_mu24_ivarloose", 	  	
	"HLT_mu24_iloose", 	  	  	  	 
	"HLT_mu26_ivarmedium", 
	"HLT_mu20_ivarmedium_L1MU15",
	"HLT_mu20_imedium_L1MU15", 	  	  	  	 
	"HLT_mu20_ivarloose_L1MU15", 	  	  	  	 
	"HLT_mu20_iloose_L1MU15", 	  	  	  	 
	"HLT_mu20_L1MU15",
	"HLT_mu20_mu8noL1", 	  	  	  	 
	"HLT_mu22_mu8noL1", 	  
	"HLT_mu20_2mu4noL1", 	  
	"HLT_mu22_2mu4noL1", 	  
	"HLT_mu40", 	  	  
	"HLT_mu50", 	  	  
	"HLT_2mu10", 	  	  
	"HLT_2mu10_nomucomb",	  	  	  	 
	"HLT_2mu14", 	  	  
	"HLT_2mu14_nomucomb", 	  	  	  	 
	"HLT_3mu6", 	  	  	  	 
	"HLT_3mu6_msonly", 	  	
	"HLT_xe100_L1XE50", 	  	  	  	 
	"HLT_xe80_mht_L1XE50", 	  
	"HLT_xe90_mht_L1XE50",
	"HLT_xe100_mht_L1XE50",
	"HLT_xe100_tc_em_L1XE50", 
	"HLT_xe110_mht_L1XE50",  	  		  	  	  	 
	"HLT_xe80_tc_lcw_L1XE50", 	  
	"HLT_xe90_tc_lcw_L1XE50", 	  
	"HLT_xe80_tc_lcw_wEFMu_L1XE50", 	  	  	  	  
	"HLT_e7_lhmedium_mu24", 	
	"HLT_e7_lhmedium_nod0_mu24", 	
	"HLT_e17_lhloose_nod0_mu14", 
	"HLT_e26_lhmedium_nod0_L1EM22VHI_mu8noL1", 
	"HLT_e24_lhmedium_nod0_L1EM20VHI_mu8noL1",
	"HLT_2e12_lhloose_L12EM10VH",
	"HLT_e17_lhloose_mu14",
	"HLT_mu18_mu8noL1",
	"HLT_xe70"
  };
  xAOD::TEvent *m_event;  //!
  xAOD::TStore store;  //!


  // this is a standard constructor
  MyxAODAnalysis ();

  // these are the functions inherited from Algorithm
  virtual EL::StatusCode setupJob (EL::Job& job);
  virtual EL::StatusCode fileExecute ();
  virtual EL::StatusCode histInitialize ();
  virtual EL::StatusCode changeInput (bool firstFile);
  virtual EL::StatusCode initialize ();
  virtual EL::StatusCode execute ();
  virtual EL::StatusCode postExecute ();
  virtual EL::StatusCode finalize ();
  virtual EL::StatusCode histFinalize ();


  // this is needed to distribute the algorithm to the workers
  ClassDef(MyxAODAnalysis, 1);
};

#endif
