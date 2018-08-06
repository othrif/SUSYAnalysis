/* To run, type
 *  make plotter
 *  ./plotter <tagname> <rootfiles>
 *
 *  e.g. ./plotter bhmu0d /cdf1a/UCntuple/bhmu0d/bhel*.root
 *
 */
long int nGenerated;
// These are standard C++ header files.
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <string>
#include <strstream>
#include <map>
#include <set>
#include <vector>

// These are ROOT header files.
#include "TChain.h"
#include "TTree.h"
#include "TFile.h"
#include "TH1.h"
#include "TH2.h"
#include "TMath.h"
#include "TVector3.h"
#include "TProfile.h"
#include "TROOT.h"
#include "TStopwatch.h"
#include "TRandom2.h"
#include "TLorentzVector.h"

//here are the project-specific files
#include "myevt.h"
#include "my_objects.h" //Muon selection Muon_IdHitReq updated, Jet isCleanMet updated
#include "GoodRunsLists/TGoodRunsList.h" //GoodRunLists trunk rev 514175
#include "GoodRunsLists/TGoodRunsListReader.h" //GoodRunLists trunk rev 514175
#include "JetUncertainties/JESUncertaintyProvider.h" //JetUncertainty-00-06-00-04
#include "JetUncertainties/MultijetJESUncertaintyProvider.h" //JetUncertainty-00-06-00-04
#include "JetResolution/JERProvider.h" //JetResolution-01-00-01
#include "ApplyJetCalibration/ApplyJetCalibration.h" //ApplyJetCalibration-00-02-07
#include "MuonEfficiencyCorrections/AnalysisMuonConfigurableScaleFactors.h" //MuonEfficiencyCorrections-02-01-04
#include "MuonMomentumCorrections/SmearingClass.h" //MuonMomentumCorrections-00-07-00
#include "MissingETUtility/METUtility.h" //MissingETUtility-01-01-01
#include "egammaAnalysisUtils/egammaSFclass.h" //egammaAnalysisUtils-00-03-45
#include "egammaAnalysisUtils/EnergyRescalerUpgrade.h" //egammaAnalysisUtils-00-03-45
#include "PileupReweighting/TPileupReweighting.h" //PileupReweighting-00-02-06
#include "egammaAnalysisUtils/IsEMPlusPlusDefs.h" //egammaAnalysisUtils-00-03-45
#include "egammaEvent/egammaPIDdefs.h" //egammaEvent-03-06-37
#include "BTagCalib.h"
void declarestructs(TTree* tree, myevt* evt);

//------------------------------------------------------------------------
//				-= Main loop =-
//------------------------------------------------------------------------
int main_loop(TChain* oldtree, char* ftag) {

	std::cout << " ------- " << ftag << " ------- " << std::endl;

	Root::TGoodRunsListReader foo;
	foo.AddXMLFile("data12_8TeV.periodAllYear_DetStatus-v61-pro14-02_DQDefects-00-01-00_PHYS_StandardGRL_All_Good.xml"); //GRL
	foo.Interpret();
	Root::TGoodRunsList grl = foo.GetMergedGoodRunsList();

	//Root::TPileupReweighting* m_pileupTool_test = new Root::TPileupReweighting("test");
	//m_pileupTool_test->UsePeriodConfig("MC12a");
	//m_pileupTool_test->Initialize();

	//Pileup Treatment in MC
	Root::TPileupReweighting* m_pileupTool = new Root::TPileupReweighting("Jimmy");
	m_pileupTool->SetDataScaleFactors(1.0 / 1.09);
	m_pileupTool->AddConfigFile("mc12a_defaults.prw.root");
	//"/users/cz36/testarea/17.0.4/PhysicsAnalysis/AnalysisCommon/PileupReweighting/share/mc12a_defaults.prw.root");
	m_pileupTool->AddLumiCalcFile("ilumicalc_histograms_None_200842-215643.root");
	m_pileupTool->SetUnrepresentedDataAction(2);
	m_pileupTool->Initialize();

	//Pileup Treatment in MC
	Root::TPileupReweighting* m_pileupTool_up = new Root::TPileupReweighting("Jimmy");
	//m_pileupTool_up->MergeMCRunNumbers(185649,185761);
	m_pileupTool_up->SetDataScaleFactors(1.1 / 1.09);
	m_pileupTool_up->AddConfigFile("mc12a_defaults.prw.root");
	//"/users/cz36/testarea/17.0.4/PhysicsAnalysis/AnalysisCommon/PileupReweighting/share/mc12a_defaults.prw.root");
	m_pileupTool_up->AddLumiCalcFile("ilumicalc_histograms_None_200842-215643.root");
	m_pileupTool_up->SetUnrepresentedDataAction(2);
	m_pileupTool_up->Initialize();

	//Pileup Treatment in MC
	Root::TPileupReweighting* m_pileupTool_dn = new Root::TPileupReweighting("Jimmy");
	//m_pileupTool_dn->MergeMCRunNumbers(185649,185761);
	m_pileupTool_dn->SetDataScaleFactors(0.9 / 1.09);
	m_pileupTool_dn->AddConfigFile("mc12a_defaults.prw.root");
	//"/users/cz36/testarea/17.0.4/PhysicsAnalysis/AnalysisCommon/PileupReweighting/share/mc12a_defaults.prw.root");
	m_pileupTool_dn->AddLumiCalcFile("ilumicalc_histograms_None_200842-215643.root");
	m_pileupTool_dn->SetUnrepresentedDataAction(2);
	m_pileupTool_dn->Initialize();

	//Initialization of the Met Utility Tool
	METUtility* _metUtility = new METUtility();
	// Turn on (off) the relevant MET terms
	// RefEle, RefGamma, RefTau, RefJet, RefMuon, MuonTotal, SoftTerms
	_metUtility->defineMissingET(true, true, false, true, false, true, true);
	_metUtility->setIsMuid(false);

	//Muon Efficiency
	Analysis::AnalysisMuonConfigurableScaleFactors StacoCBSCF("/users/cz36/testarea/17.0.4/PhysicsAnalysis/MuonID/MuonIDAnalysis/MuonEfficiencyCorrections/share/",
			"STACO_CB_plus_ST_2012_SF.txt", "MeV", Analysis::AnalysisMuonConfigurableScaleFactors::AverageOverRuns);
	StacoCBSCF.Initialise();

	TRandom2 *rndm = new TRandom2();

	// JES uncertainties
	MultijetJESUncertaintyProvider myJES_04("JES_2012/Moriond2013/MultijetJES_2012.config", //edited config file refers to MJESUncertainty_Preliminary.root and ./analysisPlots/UnknownFlavourComp.root
			"JES_2012/Moriond2013/InsituJES2012_14NP.config", //refers to JESUncertainty2012_FirstData.root
			"AntiKt4LCTopo", "MC12a", "/users/cz36/testarea/17.0.4/Reconstruction/Jet/JetUncertainties/share/");
	//https://twiki.cern.ch/twiki/bin/viewauth/AtlasProtected/JetUncertainties2012
	//myJES_04.includeFlavorComposition(false);
	//myJES_04.init();

	MultijetJESUncertaintyProvider myJES_04_AFII("JES_2012/Moriond2013/MultijetJES_2012.config", //edited config file refers to MJESUncertainty_Preliminary.root and ./analysisPlots/UnknownFlavourComp.root
			"JES_2012/Moriond2013/InsituJES2012_14NP.config", //refers to JESUncertainty2012_FirstData.root
			"AntiKt4LCTopo", "AFII", "/users/cz36/testarea/17.0.4/Reconstruction/Jet/JetUncertainties/share/");

	// Jet Energy Calibration
	JetCalibrationTool *myEtaJES = NULL;
	JetCalibrationTool *myEtaJES_DATA = new JetCalibrationTool("AntiKt4LCTopo",
			"/users/cz36/testarea/17.0.4/Reconstruction/Jet/ApplyJetCalibration/data/CalibrationConfigs/JES_Full2012dataset_Preliminary_Jan13.config", true);
	JetCalibrationTool *myEtaJES_MC = new JetCalibrationTool("AntiKt4LCTopo",
			"/users/cz36/testarea/17.0.4/Reconstruction/Jet/ApplyJetCalibration/data/CalibrationConfigs/JES_Full2012dataset_Preliminary_Jan13.config", false);
	JetCalibrationTool *myEtaJES_MC_AFII = new JetCalibrationTool("AntiKt4LCTopo",
			"/users/cz36/testarea/17.0.4/Reconstruction/Jet/ApplyJetCalibration/data/CalibrationConfigs/JES_Full2012dataset_Preliminary_AFII_Jan13.config", false);

	//Energy Rescaling for electron and muon
	egRescaler::EnergyRescalerUpgrade eRescale;
	//eRescale.useDefaultCalibConstants("2012"); //OLD
	eRescale.Init("/users/cz36/testarea/17.0.4/Reconstruction/egamma/egammaAnalysis/egammaAnalysisUtils/share/EnergyRescalerData.root", "2012", "es2010");

	//JER provider
	JERProvider myJER("AntiKt4LCTopoJES", "Truth", "JERProviderPlots_2012.root");
	myJER.init();
	myJER.useGeV(true);

	//Muon Momentum Correction / Smearing
	MuonSmear::SmearingClass mcp_smear("Data12", "staco", "q_pT", "Rel17.2Repro", "/users/cz36/testarea/17.0.4/PhysicsAnalysis/MuonID/MuonIDAnalysis/MuonMomentumCorrections/share/");
	//mcp_smear.UseScale(1);
	//mcp_smear.UseImprovedCombine();

	//Optional: enable advanced (charge-dependent) muon scale corrections that result in better data/MC agreement
	// NOT AVAILABLE FOR 2012 DATA CORRECTIONS
	//mcp_smear.RestrictCurvatureCorrections(2.5);
	//mcp_smear.FillScales("KC");

	BTagCalib* m_bTagCalib = new BTagCalib(string("MV1"), "data/BTagCalibration.env", "data/", string("0_7892"), false, 0.7892);

	//! initialize
	DileptonTriggerTool* _dileptonTriggerTool;
	char* envval;
	envval = getenv("triggerReweighterFileNameE");
	TString triggerReweighterFileNameE = "DileptonTriggerSFe.root";
	if (envval != NULL) {
		triggerReweighterFileNameE = TString(envval);
	}
	envval = getenv("triggerReweighterFileNameM");
	TString triggerReweighterFileNameM = "DileptonTriggerSFm.root";
	if (envval != NULL) {
		triggerReweighterFileNameM = TString(envval);
	}
	envval = getenv("triggerReweighterFileNameSR");
	TString triggerReweighterFileNameSR = "METTriggerSF.root";
	if (envval != NULL) {
		triggerReweighterFileNameSR = TString(envval);
	}

	map < TString, pair<TString, TString> > *Trigger[3];
	Trigger[0] = new map<TString, pair<TString, TString> >();
	Trigger[0]->insert(map<TString, pair<TString, TString> >::value_type("DileptonFirst", std::pair<TString, TString>(triggerReweighterFileNameE, "EF_e12Tvh_loose1")));
	Trigger[0]->insert(map<TString, pair<TString, TString> >::value_type("DileptonSecond", std::pair<TString, TString>(triggerReweighterFileNameE, "EF_e12Tvh_loose1")));
	Trigger[0]->insert(map<TString, pair<TString, TString> >::value_type("SingleLeptonElectron", std::pair<TString, TString>(triggerReweighterFileNameE, "EF_e60_medium1")));
	Trigger[0]->insert(map<TString, pair<TString, TString> >::value_type("MET", std::pair<TString, TString>(triggerReweighterFileNameSR, "EF_xe80_tclcw_loose")));
	Trigger[1] = new map<TString, pair<TString, TString> >();
	Trigger[1]->insert(map<TString, pair<TString, TString> >::value_type("DileptonFirst", std::pair<TString, TString>(triggerReweighterFileNameM, "EF_mu18_tight")));
	Trigger[1]->insert(map<TString, pair<TString, TString> >::value_type("DileptonSecond", std::pair<TString, TString>(triggerReweighterFileNameM, "EF_mu8_EFFS")));
	Trigger[1]->insert(map<TString, pair<TString, TString> >::value_type("SingleLeptonMuon", std::pair<TString, TString>(triggerReweighterFileNameM, "EF_mu36_tight")));
	Trigger[1]->insert(map<TString, pair<TString, TString> >::value_type("MET", std::pair<TString, TString>(triggerReweighterFileNameSR, "EF_xe80_tclcw_loose")));
	Trigger[2] = new map<TString, pair<TString, TString> >();
	Trigger[2]->insert(map<TString, pair<TString, TString> >::value_type("DileptonFirst", std::pair<TString, TString>(triggerReweighterFileNameE, "EF_e12Tvh_medium1")));
	Trigger[2]->insert(map<TString, pair<TString, TString> >::value_type("DileptonSecond", std::pair<TString, TString>(triggerReweighterFileNameM, "EF_mu8_EFFS")));
	Trigger[2]->insert(map<TString, pair<TString, TString> >::value_type("SingleLeptonElectron", std::pair<TString, TString>(triggerReweighterFileNameE, "EF_e60_medium1")));
	Trigger[2]->insert(map<TString, pair<TString, TString> >::value_type("SingleLeptonMuon", std::pair<TString, TString>(triggerReweighterFileNameM, "EF_mu36_tight")));
	Trigger[2]->insert(map<TString, pair<TString, TString> >::value_type("MET", std::pair<TString, TString>(triggerReweighterFileNameSR, "EF_xe80_tclcw_loose")));

	_dileptonTriggerTool = new DileptonTriggerTool(Trigger);

	myevt evt;
	TStopwatch st;
	std::map<unsigned int, std::set<unsigned int> > evtmap;

	//-----------------------------------------------------------------------

	char fname[500];
	sprintf(fname, "./results/%s_plots.root", ftag);
	TFile file(fname, "RECREATE");

	//-----------------------------------------------------------------------
	// Signal Regions
	bool PRE;      // basic selection common to all 
	bool SR3L3B;  // 3L, ll OSSF, MET>50, |mll-mZ|>10,  |mlll-mZ|>10, >=3bJETS  
	bool SR3b;     // SS/3L, >=3bJETS, >=5JETS, meff>350
	bool SR3b3L;
	bool SR0b;     // SS, =0bJETS, >=3JETS, MET>150, meff>400
	bool SR1b;     // SS, >=1bJETS, >=3JETS, MET>150, mT>100, meff>700, veto SR3b
	bool SR3Llow;  // 3L, >=4JETS, 50<MET<150, Z veto, veto SR3b 
	bool SR3Lhigh; // 3L, >=4JETS, MET>150, veto SR3b, meff>400
	// counts
	long int count_PRE=0;
	long int count_SR3L3B=0;
	long int count_SR3b3L=0;
	long int count_SR3b=0;
	long int count_SR0b=0;
	long int count_SR1b=0;
	long int count_SR3Llow=0;
	long int count_SR3Lhigh=0;
	//-----------------------------------------------------------------------
	// SS
	//number of events processed
	TH1D *num_of_evts_SS = new TH1D("num_of_evts_SS", "num_of_evts", 1, 0, 1);

	//Missing pt
	TH1D *met_SS = new TH1D("met_SS", "MET; MET [GeV]; entries", 20, 0, 200.);
	met_SS->Sumw2();

	//m effective
	TH1D *meff_SS = new TH1D("meff_SS", "Meff; Meff [GeV]; entries", 25, 0, 1000.);
	meff_SS->Sumw2();

	//transverse mass
	TH1D *mT_SS = new TH1D("mT_SS", "mT; mT [GeV]; entries", 25, 0, 1000.);
	mT_SS->Sumw2();

	//dilepton mass
	TH1D *mll_SS = new TH1D("mll_SS", "mll; mll [GeV]; entries", 100, 0, 200.);
	mll_SS->Sumw2();

	//trilepton mass
	TH1D *m3l_SS = new TH1D("m3l_SS", "m3l; m3l [GeV]; entries", 100, 0, 500.);
	m3l_SS->Sumw2();

	//number of jets
	TH1D *num_jets_SS = new TH1D("num_jets_SS", "num_jets; NJETS; entries", 11, -0.5, 10.5);
	num_jets_SS->Sumw2();

	//number of bjets
	TH1D *num_bjets_SS = new TH1D("num_bjets_SS", "num_bjets; NBJETS; entries", 11, -0.5, 10.5);
	num_bjets_SS->Sumw2();

	//number of ee
	TH1D *num_ee_SS = new TH1D("num_ee_SS", "num_ee; NEE; entries", 11, -0.5, 10.5);
	num_ee_SS->Sumw2();

	//number of em
	TH1D *num_em_SS = new TH1D("num_em_SS", "num_em; NEM; entries", 11, -0.5, 10.5);
	num_em_SS->Sumw2();

	//number of mm
	TH1D *num_mm_SS = new TH1D("num_mm_SS", "num_mm; NMM; entries", 11, -0.5, 10.5);
	num_mm_SS->Sumw2();

	//number of leps
	TH1D *num_leps_SS = new TH1D("num_leps", "num_leps; NLEPS; entries", 11, -0.5, 10.5);
	num_leps_SS->Sumw2();

	//-----------------------------------------------------------------------

	// 3L
	//number of events processed
	TH1D *num_of_evts_3L = new TH1D("num_of_evts_3L", "num_of_evts", 1, 0, 1);

	//Missing pt
	TH1D *met_3L = new TH1D("met_3L", "MET; MET [GeV]; entries", 20, 0, 200.);
	met_3L->Sumw2();

	//m effective
	TH1D *meff_3L = new TH1D("meff_3L", "Meff; Meff [GeV]; entries", 25, 0, 1000.);
	meff_3L->Sumw2();

	//transverse mass
	TH1D *mT_3L = new TH1D("mT_3L", "mT; mT [GeV]; entries", 25, 0, 1000.);
	mT_3L->Sumw2();

	//dilepton mass
	TH1D *mll_3L = new TH1D("mll_3L", "mll; mll [GeV]; entries", 100, 0, 200.);
	mll_3L->Sumw2();

	//trilepton mass
	TH1D *m3l_3L = new TH1D("m3l_3L", "m3l; m3l [GeV]; entries", 100, 0, 500.);
	m3l_3L->Sumw2();

	//number of jets
	TH1D *num_jets_3L = new TH1D("num_jets_3L", "num_jets; NJETS; entries", 11, -0.5, 10.5);
	num_jets_3L->Sumw2();

	//number of bjets
	TH1D *num_bjets_3L = new TH1D("num_bjets_3L", "num_bjets; NBJETS; entries", 11, -0.5, 10.5);
	num_bjets_3L->Sumw2();

	//number of leps
	TH1D *num_leps_3L = new TH1D("num_leps", "num_leps; NLEPS; entries", 11, -0.5, 10.5);
	num_leps_3L->Sumw2();

	//-----------------------------------------------------------------------
	// SS/3L
	//number of events processed
	TH1D *num_of_evts = new TH1D("num_of_evts", "num_of_evts", 1, 0, 1);

	//number of leps
	TH1D *num_leps = new TH1D("num_leps", "num_leps; NLEPS; entries", 11, -0.5, 10.5);
	num_leps->Sumw2();

	//Missing pt
	TH1D *met = new TH1D("met", "MET; MET [GeV]; entries", 20, 0, 200.);
	met->Sumw2();

	//m effective
	TH1D *mEFF = new TH1D("meff", "Meff; Meff [GeV]; entries", 25, 0, 1000.);
	mEFF->Sumw2();

	//transverse mass
	TH1D *mT = new TH1D("mT", "mT; mT [GeV]; entries", 25, 0, 1000.);
	mT->Sumw2();

	//dilepton mass
	TH1D *mll = new TH1D("mll", "mll; mll [GeV]; entries", 100, 0, 200.);
	mll->Sumw2();

	//trilepton mass
	TH1D *m3l = new TH1D("m3l", "m3l; m3l [GeV]; entries", 100, 0, 500.);
	m3l->Sumw2();

	//number of jets
	TH1D *num_jets = new TH1D("num_jets", "num_jets; NJETS; entries", 11, -0.5, 10.5);
	num_jets->Sumw2();

	//number of bjets
	TH1D *num_bjets = new TH1D("num_bjets", "num_bjets; NBJETS; entries", 11, -0.5, 10.5);
	num_bjets->Sumw2();


	//-----------------------------------------------------------------------

	//-----------------------------------------------------------------------
	// vertex information
	TH1D *num_vtx = new TH1D("num_vtx", "num_vtx;# prim. vtx.;entries", 40, 0, 40);
	num_vtx->Sumw2();

	//-----------------------------------------------------------------------
	// averageIntPerXing
	TH1D *averageIntPerXing = new TH1D("averageIntPerXing", "averageIntPerXing;averageIntPerXing;entries", 40, 0, 40);
	averageIntPerXing->Sumw2();

	//-----------------------------------------------------------------------
	// cut optimization
	TH1D* cut_flow = new TH1D("cut_flow", "cut_flow for the baseline W->munu selection", 100, 0, 100);
	cut_flow->Sumw2();

	TH1D* cut_flow_ee_ss = new TH1D("cut_flow_ee_ss", "cut_flow for ee_ss selection", 40, 0, 40);
	cut_flow_ee_ss->Sumw2();

	TH1D* cut_flow_em_ss = new TH1D("cut_flow_em_ss", "cut_flow for em_ss selection", 40, 0, 40);
	cut_flow_em_ss->Sumw2();

	TH1D* cut_flow_mm_ss = new TH1D("cut_flow_mm_ss", "cut_flow for mm_ss selection", 40, 0, 40);
	cut_flow_mm_ss->Sumw2();

	TH1D* deltaR_e_mu = new TH1D("deltaR_e_mu", "#DeltaR(e,mu);#DeltaR(e,mu);entries", 50, 0, 5);
	deltaR_e_mu->Sumw2();

	TH1D* deltaR_e_e = new TH1D("deltaR_e_e", "#DeltaR(e,e);#DeltaR(e,e);entries", 50, 0, 5);
	deltaR_e_e->Sumw2();

	TH1D* deltaR_mu_mu = new TH1D("deltaR_mu_mu", "#DeltaR(#mu,#mu);#DeltaR(#mu,#mu);entries", 50, 0, 5);
	deltaR_mu_mu->Sumw2();

	TH2D* em_overlap_map = new TH2D("em_overlap_map", "em_overlap_map;#eta(#mu);#phi(#mu)", 20, -2.5, 2.5, 20, -3.1416, 3.1416);
	em_overlap_map->Sumw2();

	TH1D* deltaR_e_jet = new TH1D("deltaR_e_jet", "deltaR_e_jet", 50, 0, 5);
	deltaR_e_jet->Sumw2();

	TH1D* deltaR_mu_jet = new TH1D("deltaR_mu_jet", "deltaR_mu_jet", 50, 0, 5);
	deltaR_mu_jet->Sumw2();

	//mZ distribution for the cut-flow
	TH1D *MZ = new TH1D("MZ", "MZ", 100, 0, 200);
	MZ->Sumw2();

	TH1D *lowest_M = new TH1D("lowest_M", "lowest_M;lowest M(l+l-) [GeV];entries", 100, 0, 200);
	lowest_M->Sumw2();

	//TEST: mZ distribution for the cut-flow
	TH1D *my_MZ_1 = new TH1D("my_MZ_1", "MZ(e+e-);M(e+e-) [GeV];Events", 100, 0, 200);
	my_MZ_1->Sumw2();

	TH1D *my_MZ_2 = new TH1D("my_MZ_2", "MZ(e+e+);M(e+e+) [GeV];Events", 100, 0, 200);
	my_MZ_2->Sumw2();

	TH1D *my_MZ_3 = new TH1D("my_MZ_3", "MZ(e-e-);M(e-e-) [GeV];Events", 100, 0, 200);
	my_MZ_3->Sumw2();

	TH1D *mu_MZ = new TH1D("mu_MZ", "MZ(#mu#mu);M(#mu+#mu-) [GeV];Events", 100, 0, 200);
	mu_MZ->Sumw2();

	TH1D *emu_M = new TH1D("emu_M", "M(e#mu);M(e#mu) [GeV];Events", 450, 100, 1000);
	emu_M->Sumw2();

	//dZ test for Larry
	TH2D *mu_dZ_eta = new TH2D("mu_dZ_eta", "dZ(#mu-vtx) vs #eta;dz(#mu);#eta", 100, -5, 5, 100, -2.5, 2.5);
	mu_dZ_eta->Sumw2();

	TH2D* vtx_x_vs_y = new TH2D("vtx_x_vs_y", "vtx_x_vs_y;x [mm];y [mm]", 40, -5, 5, 40, -5, 5);
	vtx_x_vs_y->Sumw2();

	// --- correction to the NLO cross-section
	TH1D* phase_space = new TH1D("phase_space", "mass threshold;fail/pass;entries", 2, -0.5, 1.5);
	phase_space->Sumw2();

	//TEST 
	TH1D *M_mumu = new TH1D("M_mumu", "M(#mu#mu);M(#mu+#mu-) [GeV];Events", 80, 40, 120);
	M_mumu->Sumw2();

	//MET test
	TH2D *my_MET = new TH2D("my_MET", "MET;MET(D3PD) [GeV];MET(recalculated) [GeV]", 100, 0, 100, 100, 0, 100);
	my_MET->Sumw2();
	/*
	//-----------------------------------------------------------------------
	BookHistos_SystSet("zero_0b");
	BookHistos_SystSet("one_0b");
	BookHistos_SystSet("two_0b");
	BookHistos_SystSet("three_0b");
	//-----------------------------------------------------------------------
	BookHistos_SystSet("zero_1b");
	BookHistos_SystSet("one_1b");
	BookHistos_SystSet("two_1b");
	BookHistos_SystSet("three_1b");
	//-----------------------------------------------------------------------
	BookHistos_SystSet("full_3b");
	BookHistos_SystSet("full_2l0b");
	BookHistos_SystSet("full_2l1b");
	BookHistos_SystSet("full_3llm");
	BookHistos_SystSet("full_3lhm");
	//-----------------------------------------------------------------------
	*/
	st.Reset();
	unsigned long int n_bytes = 0;
	unsigned long int file_size = 0;

	if (!oldtree)
		return 1;

	Long64_t tree_Entries = (Long64_t) oldtree->GetEntries();
	std::cout << "Expect to process " << tree_Entries << " entries.\n";
	if (tree_Entries == 0)
		return 1;

	oldtree->GetEntry(0);
	declarestructs(oldtree->GetTree(), &evt);
	int treeno = ((TChain*) oldtree)->GetTreeNumber();
	file_size = ((TChain*) oldtree)->GetFile()->GetSize();
	TString filename = oldtree->GetFile()->GetName();
	std::cout << "file: " << filename << "\n";

	//ATLAS Fast check
	bool isATLFAST = false;
	if (filename.Index("_a") > 0 || filename.Index("LF") > 0) { //filename has _a???? in it: made using atlas-fast
		isATLFAST = true;
		std::cout << "Using ATLAS FAST configuration" << std::endl;
	}

	//Sherpa check
	bool isSherpa = false;
	if (filename.Index("herpa") > 0) { //
		isSherpa = true;
		std::cout << "Sherpa!" << std::endl;
	}

	st.Start();

	float packed_rate, unpacked_rate, real_time;
	bool unique;

	//-----------------------------------------------------------------------
	// Main Loop
	for (Long64_t entr_ind = 0; entr_ind < tree_Entries; entr_ind++) {

		n_bytes += oldtree->GetEntry(entr_ind);

		if (treeno != ((TChain*) oldtree)->GetTreeNumber()) {
			declarestructs(oldtree->GetTree(), &evt);
			oldtree->GetEntry(entr_ind);
			treeno = ((TChain*) oldtree)->GetTreeNumber();

			// I/O performance benchmark.
			st.Stop();
			real_time = st.RealTime();
			st.Start(true);

			if (real_time > 0) {
				packed_rate = n_bytes / (1024. * 1024. * real_time);
				unpacked_rate = file_size / (1024. * 1024. * real_time);
				n_bytes = 0;

				std::cout << "entry: " << entr_ind << ",\t time to process: " << real_time << " sec.\n";
				std::cout << "avg. unpacked rate : " << packed_rate << " MB/sec\n";
				std::cout << "avg. packed rate   : " << unpacked_rate << " MB/sec\n\n";
			}

			filename = oldtree->GetFile()->GetName();
			std::cout << "file: " << filename << "\n";
			file_size = oldtree->GetFile()->GetSize();
			// End of the I/O benchmark

			//ATLAS Fast check
			isATLFAST = false;
			if (filename.Index("_a") > 0 || filename.Index("LF") > 0) { //filename has _a???? in it: made using atlas-fast
				isATLFAST = true;
				std::cout << "\nUsing ATLAS FAST configuration" << std::endl;
			}

			//Sherpa check
			isSherpa = false;
			if (filename.Index("herpa") > 0) { //
			  isSherpa = true;
			  std::cout << "Sherpa!" << std::endl;
			}

		}

		//m_pileupTool_test->Fill(evt.runNumber,evt.mc_channel_number,evt.weight,evt.averageIntPerXing); //117800
		//-------------------------------------------------------------------------------------------
		//GRL selection
		//-------------------------------------------------------------------------------------------
		bool muo_GRL = true;
		if (!evt.isMC) {
			muo_GRL = grl.HasRunLumiBlock(evt.runNumber, evt.lumiBlock);
		}

		if (!muo_GRL)
			continue;

		// we test if the event is unique (in data)
		if (!evt.isMC) {
			unique = (evtmap[evt.runNumber].insert(evt.eventNumber)).second;
			if (!unique) {
				std::cout << "\nWarning: duplicate event.\n";
				continue;
			}
		}

		// initiating the JES calibration tool
		if (myEtaJES == NULL) {
			if (evt.isMC)
				if (!isATLFAST)
					myEtaJES = myEtaJES_MC;
				else
					myEtaJES = myEtaJES_MC_AFII;
			else
				myEtaJES = myEtaJES_DATA;
		}

		//-------------------------------------------------------------------
		// Generic event selection
		//-------------------------------------------------------------------

		//int data_period = muonTrigger(&evt, rndm->Rndm()); //OLD
		//bool mu_trig = (data_period > 0); // collection of muon triggers //OLD
		//bool mu_trig = true; //UNTIL TRIGGERS FIXED //OLD

		//Single lepton and two lepton triggers
		//Bool_t mu_trig = evt.EF_e24vhi_medium1 || evt.EF_e60_medium1 || evt.EF_mu24i_tight || evt.EF_mu36_tight || evt.EF_2e12Tvh_loose1 || evt.EF_2mu13 || evt.EF_mu18_tight_mu8_EFFS || evt.EF_e12Tvh_medium1_mu10 || evt.EF_e24vhi_loose1_mu8 || evt.EF_e24vh_medium1_e7_medium1 || evt.EF_e12Tvh_medium1_mu8 || evt.EF_mu18_tight_e7_medium1;
		//Bool_t mu_trig = evt.EF_2e12Tvh_loose1 || evt.EF_2mu13; //2Triggers
		//Bool_t mu_trig = evt.EF_2e12Tvh_loose1 || evt.EF_2mu13 || evt.EF_mu18_tight_mu8_EFFS || evt.EF_e12Tvh_medium1_mu10 || evt.EF_e12Tvh_medium1_mu8 || evt.EF_mu18_tight_e7_medium1 ; //6Triggers
		//bool mu_trig = evt.EF_xe80T_tclcw_loose || evt.EF_xe80_tclcw_loose || evt.EF_2e12Tvh_loose1 || evt.EF_e60_medium1 || evt.EF_mu18_tight_mu8_EFFS || evt.EF_mu36_tight || evt.EF_e12Tvh_medium1_mu8;

		int n_prim_vtx = 0;
		int n_prim_vtx_JES = 0; //# of primary vertecies for the JES calculation

		for (int i = 0; i < evt.vxp_n; i++) {
			if (evt.vxp_vertNtrk[i] >= 5) //this is a good vertex
				n_prim_vtx++;

			if (evt.vxp_vertNtrk[i] >= 2)
				n_prim_vtx_JES++;
		}

		calJet AntiKt4LCTopo_D3PD; //needed for MET calculations
		memcpy(&AntiKt4LCTopo_D3PD, &evt.AntiKt4LCTopo, sizeof(calJet));

		// Now we fix JES variables ---------------------------------------------------------------------
		for (int jeti = 0; jeti < evt.AntiKt4LCTopo.n; jeti++) {
			// Calibrate the jet!
			TLorentzVector jet = myEtaJES->ApplyJetAreaOffsetEtaJES(evt.AntiKt4LCTopo.constscale_E[jeti], evt.AntiKt4LCTopo.constscale_eta[jeti], evt.AntiKt4LCTopo.constscale_phi[jeti],
					evt.AntiKt4LCTopo.constscale_m[jeti], evt.AntiKt4LCTopo.ActiveAreaPx[jeti], evt.AntiKt4LCTopo.ActiveAreaPy[jeti], evt.AntiKt4LCTopo.ActiveAreaPz[jeti],
					evt.AntiKt4LCTopo.ActiveAreaE[jeti], evt.Eventshape_rhoKt4LC, evt.averageIntPerXing, n_prim_vtx_JES);

			evt.AntiKt4LCTopo.E[jeti] = jet.E();
			evt.AntiKt4LCTopo.pt[jeti] = jet.Pt();
			evt.AntiKt4LCTopo.phi[jeti] = jet.Phi();
			evt.AntiKt4LCTopo.eta[jeti] = jet.Eta();
			evt.AntiKt4LCTopo.m[jeti] = jet.M();
			evt.AntiKt4LCTopo.px[jeti] = jet.Px();
			evt.AntiKt4LCTopo.py[jeti] = jet.Py();
			evt.AntiKt4LCTopo.pz[jeti] = jet.Pz();
		}

		//---------------------------------------------------------------------------
		// Now we correct energies of electrons
		for (int i = 0; i < evt.el_n; i++) {

			double el_pt;
			if ((evt.el_nSCTHits[i] + evt.el_nPixHits[i]) < 4) {
				el_pt = evt.el_cl_E[i] / cosh(evt.el_cl_eta[i]);
			} else {
				el_pt = evt.el_cl_E[i] / cosh(evt.el_tracketa[i]);
			}

			el_pt *= smear_An_ElectronPt(&evt, i, &eRescale);
			el_pt *= scale_An_ElectronPt(&evt, i, &eRescale, isATLFAST);
			evt.el_pt[i] = el_pt;

		}

		//---------------------------------------------------------------------------
		//electrons for the electron-jet overlap
		my_leptons elec_4jetOverlap;
		elec_4jetOverlap.num_leptons = 0;
		elec_4jetOverlap.delta_met_x = 0;
		elec_4jetOverlap.delta_met_y = 0;

		// Now we count # of electrons
		for (int i = 0; i < evt.el_n; i++) {
			if (is_preselection_electron_nonIso(&evt, i, evt.el_pt[i])) {
				elec_4jetOverlap.pt[elec_4jetOverlap.num_leptons] = evt.el_pt[i];
				elec_4jetOverlap.index[elec_4jetOverlap.num_leptons] = i;
				elec_4jetOverlap.is_electron[elec_4jetOverlap.num_leptons] = true;
				elec_4jetOverlap.charge[elec_4jetOverlap.num_leptons] = evt.el_charge[i];
				elec_4jetOverlap.num_leptons++;
			}
		}

		//---------------------------------------------------------------------------
		//lepton variables for mis-pT cleaning
		my_leptons lep_met;
		lep_met.num_leptons = 0;
		lep_met.delta_met_x = 0;
		lep_met.delta_met_y = 0;

		//lepton variables for event selection
		my_leptons lep;
		lep.num_leptons = 0;
		lep.delta_met_x = 0;
		lep.delta_met_y = 0;

		// Now we count # of 18 GeV Muons
		for (int i = 0; i < evt.mu_staco_n; i++) {
			float corr_muon_pt = smear_A_MuonPt(&evt, i, &mcp_smear);

			if (is_preselection_muon_noIso(&evt, i, corr_muon_pt)) {
				lep_met.pt[lep_met.num_leptons] = corr_muon_pt;
				lep_met.index[lep_met.num_leptons] = i;
				lep_met.is_electron[lep_met.num_leptons] = false;
				lep_met.charge[lep_met.num_leptons] = evt.mu_staco_charge[i];
				lep_met.num_leptons++;

				if (is_tight_muon(&evt, i, corr_muon_pt, &elec_4jetOverlap, n_prim_vtx)) {
					lep.pt[lep.num_leptons] = corr_muon_pt;
					lep.index[lep.num_leptons] = i;
					lep.is_electron[lep.num_leptons] = false;
					lep.charge[lep.num_leptons] = evt.mu_staco_charge[i];
					lep.num_leptons++;
				}

			}
		}

		// Now we count # of electrons
		for (int i = 0; i < evt.el_n; i++) {

			double el_pt = evt.el_pt[i];

			if (is_preselection_electron_4met(&evt, i, el_pt)) {
				lep_met.pt[lep_met.num_leptons] = el_pt;
				lep_met.index[lep_met.num_leptons] = i;
				lep_met.is_electron[lep_met.num_leptons] = true;
				lep_met.charge[lep_met.num_leptons] = evt.el_charge[i];
				lep_met.num_leptons++;
			}

			if (is_tight_electron(&evt, i, el_pt, &elec_4jetOverlap, n_prim_vtx)) {
				lep.pt[lep.num_leptons] = el_pt;
				lep.index[lep.num_leptons] = i;
				lep.is_electron[lep.num_leptons] = true;
				lep.charge[lep.num_leptons] = evt.el_charge[i];
				lep.num_leptons++;
			}
		}

		//---------------------------------------------------------------------------
		//Scaling of the electron energy in data and MC
		//scaleElectronPt(&evt, &lep, &eRescale, isATLFAST); //Now it is done within the pre-selection loop
		//scaleElectronPt(&evt, &lep_met, &eRescale, isATLFAST); //Now it is done within the pre-selection loop

		//Smear momenta of electrons in simulations
		//smearElectronPt(&evt, &lep, &eRescale); //Now The smearing is done within the pre-selection loop
		//smearElectronPt(&evt, &lep_met, &eRescale); //Now The smearing is done within the pre-selection loop

		//Smearing of muon pt:
		//smearMuonPt(&evt, &lep, &mcp_smear); //Now The smearing is done within the pre-selection loop
		//smearMuonPt(&evt, &lep_met, &mcp_smear); //Now The smearing is done within the pre-selection loop

		//We need to sort the leptons in pt
		sortLeptons(&lep);
		//we need to re-calculate the number of 20 GeV leptons after scaling and smearing of their momenta.
		calcNum20GeVleptons(&lep, &evt, &lep_met, &elec_4jetOverlap);
		//We need to recalculate charge
		calcChargeLeptons(&lep, &evt);
		//We need to find if there is a Z-boson
		containsZ(&lep, &evt);

		//We need to sort the leptons in pt
		sortLeptons(&lep_met);
		//we need to re-calculate the number of 20 GeV leptons after scaling and smearing of their momenta.
		calcNum20GeVleptons(&lep_met, &evt, &lep_met, &elec_4jetOverlap);
		//We need to recalculate charge
		calcChargeLeptons(&lep_met, &evt);
		//We need to find if there is a Z-boson
		containsZ(&lep_met, &evt);

		//Re-calculate missing-pT
		//if (lep_met.num_leptons > 1 || evt.isMC) //disabled for the cut-flow
		{ //optimization
			TVector2 newMet = getMET(&evt, &evt.AntiKt4LCTopo, &AntiKt4LCTopo_D3PD, &lep_met, SystErr::NONE, _metUtility);
			my_MET->Fill(sqrt(evt.MET_Egamma10NoTau_RefFinal_etx * evt.MET_Egamma10NoTau_RefFinal_etx + evt.MET_Egamma10NoTau_RefFinal_ety * evt.MET_Egamma10NoTau_RefFinal_ety) / 1000.0,
					sqrt(newMet.X() * newMet.X() + newMet.Y() * newMet.Y()) / 1000.0, evt.weight);
			evt.MET_Egamma10NoTau_RefFinal_etx = newMet.X();
			evt.MET_Egamma10NoTau_RefFinal_ety = newMet.Y();
			//evt.MRF_Pt = newMet.Mod(); = sqrt( MRF_Px * MRF_Px + MRF_Py * MRF_Py);
		}

		//std::cout << "\n Old mis-pX: " << evt.MET_Simplified20_RefFinal_etx << ", new mis-pX: " << newMet.X();
		//std::cout << "\n Old mis-pY: " << evt.MET_Simplified20_RefFinal_ety << ", new mis-pY: " << newMet.Y();
		//std::cout << "\n new mis-Pt: " << newMet.Mod();

		//========================================================================
		// ee cut-flow
		//========================================================================

		if (muo_GRL) {
			cut_flow_ee_ss->Fill(0.1, evt.weight);

			if (evt.larError != 2) { //LAr Error
				cut_flow_ee_ss->Fill(1.1, evt.weight);

				if (evt.tileError != 2) { //Tile Error
					cut_flow_ee_ss->Fill(2.1, evt.weight);

					if ((evt.coreFlags & 0x40000) == 0) { //4: core flags
						cut_flow_ee_ss->Fill(3.1, evt.weight);

						if (evt.vxp_vertNtrk[0] > 4 && evt.vxp_n > 0) { // The primary vertex has 5 or more tracks
							cut_flow_ee_ss->Fill(4.1, evt.weight);

							if (NoBadMuon(&evt, &lep_met, &elec_4jetOverlap)) {
								cut_flow_ee_ss->Fill(5.1, evt.weight); //6:

								if (HEC_Veto(&(evt.AntiKt4LCTopo), &evt)) { // HEC Veto
									cut_flow_ee_ss->Fill(6.1, evt.weight);

									if (isCleanMet(&(evt.AntiKt4LCTopo), &evt, &elec_4jetOverlap)) { //jet cleaning
										cut_flow_ee_ss->Fill(7.1, evt.weight);

										if (NoCosmicMuon(&evt, &lep_met, &elec_4jetOverlap)) {
											cut_flow_ee_ss->Fill(8.1, evt.weight);

											int n_10GeV_Presel_Lept = 0;

											for (int i = 0; i < lep_met.num_leptons; i++)
											  if (!lep_met.lept_overlap[i]) {
													if (lep_met.is_electron[i]) {
														if (is_preselection_electron(&evt, lep_met.index[i], lep_met.pt[i], &elec_4jetOverlap))
															n_10GeV_Presel_Lept++;
													} else {
														if (is_preselection_muon(&evt, lep_met.index[i], lep_met.pt[i], &elec_4jetOverlap))
															n_10GeV_Presel_Lept++;
													}
												}

											if (n_10GeV_Presel_Lept > 1) { // >1lep > 10 GeV
												cut_flow_ee_ss->Fill(9.1, evt.weight);

												int n_15GeV_Presel_Lept = 0;

												for (int i = 0; i < lep_met.num_leptons; i++)
													if (lep_met.pt[i] > LeptPt && !lep_met.lept_overlap[i]) {
														if (lep_met.is_electron[i]) {
															if (is_preselection_electron(&evt, lep_met.index[i], lep_met.pt[i], &elec_4jetOverlap))
																n_15GeV_Presel_Lept++;
														} else {
															if (is_preselection_muon(&evt, lep_met.index[i], lep_met.pt[i], &elec_4jetOverlap))
																n_15GeV_Presel_Lept++;
														}
													}

												if (n_15GeV_Presel_Lept > 1) { // >1lep > 15 GeV
													cut_flow_ee_ss->Fill(10.1, evt.weight);

													if (lep.num_20GeV_leptons_noverlap > 1) { //>1 tight lepton
														cut_flow_ee_ss->Fill(11.1, evt.weight);

														if (SetChannelAlternate(&lep, &evt)) { // setChannelAlternate (20,15,15)
															cut_flow_ee_ss->Fill(12.1, evt.weight);

															/*if (is_ee(&lep, &evt)) { //is_ee
																cut_flow_ee_ss->Fill(13.1, evt.weight);
																
															
																														
																double triggerWeight;
																if (trigger_ee(&lep, &evt, _dileptonTriggerTool, triggerWeight)) { //Trigger weight
																	cut_flow_ee_ss->Fill(14.1, evt.weight);
															
															*/														if (dilepton_mass(&lep, &evt) > 12000.) {
															  //	cut_flow_ee_ss->Fill(15.1, evt.weight);

																		//--------------------------------------------------------------------------------------------*/

																		//effective mass
																		float meff = 0;
																		for (int i = 0; i < lep.num_leptons; i++) {
																		  if (lep.pt[i] > LeptPt && !lep.lept_overlap[i]) {
																		    meff += lep.pt[i];
																		  }
																		}

																		//miss-Et variables
																		float mis_Ex = lep.delta_met_x + evt.MET_Egamma10NoTau_RefFinal_etx;
																		float mis_Ey = lep.delta_met_y + evt.MET_Egamma10NoTau_RefFinal_ety;
																		float my_MET_pT = sqrt(mis_Ex * mis_Ex + mis_Ey * mis_Ey);

																		meff += my_MET_pT;

																		//Now we can count jets
																		int n_jets = 0;
																		calJet *jet = &(evt.AntiKt4LCTopo);

																		for (int i = 0; i < jet->n; i++)
																			if (jet->pt[i] > 50000. && fabs(jet->eta[i]) < 2.8) {

																				bool dR_excl = false;
																				float dR;
																				//We exclude all electrons and muons from the jet collection
																				for (int k = 0; k < elec_4jetOverlap.num_leptons && !dR_excl; k++) {

																					if ((evt.el_nSCTHits[elec_4jetOverlap.index[k]] + evt.el_nPixHits[elec_4jetOverlap.index[k]]) < 4) {
																						dR = DeltaR(evt.el_cl_eta[elec_4jetOverlap.index[k]], evt.el_cl_phi[elec_4jetOverlap.index[k]], evt.AntiKt4LCTopo.eta[i],
																								evt.AntiKt4LCTopo.phi[i]);
																					} else {
																						dR = DeltaR(evt.el_tracketa[elec_4jetOverlap.index[k]], evt.el_trackphi[elec_4jetOverlap.index[k]], evt.AntiKt4LCTopo.eta[i],
																								evt.AntiKt4LCTopo.phi[i]);
																					}

																					dR_excl |= (dR <= 0.2);
																				}

																				if (!dR_excl) {
																					n_jets++;
																					meff += jet->pt[i];
																				}
																			}

																		//Now we can count bjets
																		int n_bjets = 0;

																		for (int i = 0; i < jet->n; i++)
																			if (jet->pt[i] > 20000. && fabs(jet->eta[i]) < 2.5 && jet->flavor_weight_MV1[i] > 0.7892) {

																				bool dR_excl = false;
																				float dR;
																				//We exclude all electrons and muons from the jet collection
																				for (int k = 0; k < elec_4jetOverlap.num_leptons && !dR_excl; k++) {

																					if ((evt.el_nSCTHits[elec_4jetOverlap.index[k]] + evt.el_nPixHits[elec_4jetOverlap.index[k]]) < 4) {
																						dR = DeltaR(evt.el_cl_eta[elec_4jetOverlap.index[k]], evt.el_cl_phi[elec_4jetOverlap.index[k]], evt.AntiKt4LCTopo.eta[i],
																								evt.AntiKt4LCTopo.phi[i]);
																					} else {
																						dR = DeltaR(evt.el_tracketa[elec_4jetOverlap.index[k]], evt.el_trackphi[elec_4jetOverlap.index[k]], evt.AntiKt4LCTopo.eta[i],
																								evt.AntiKt4LCTopo.phi[i]);
																					}

																					dR_excl |= (dR <= 0.2);
																				}

																				if (!dR_excl) {
																					n_bjets++; //TODO: are b-jets counted in m_eff?
																																			}
																			}
										 




				if((lep.num_20GeV_leptons_noverlap == 2 && fabs(lep.total_charge) > 1.) || lep.num_20GeV_leptons_noverlap >= 3){

						 // Signal Regions
						 // SS/3L Analysis-----------------------------------------------
						 // PRE: basic selection common to all 
						 // SR3b3l: 3L, >=3bJETS, <=5JETS OR meff<350
						 // SR3b: SS/3L, >=3bJETS, >=5JETS, meff>350
						 // SR0b: SS, =0bJETS, >=3JETS, MET>150, meff>400
						 // SR1b: SS, >=1bJETS, >=3JETS, MET>150, mT>100, meff>700, veto SR3b
						 // SR3Llow: 3L, >=4JETS, 50<MET<150, Z veto, veto SR3b 
						 // SR3Lhigh: 3L, >=4JETS, MET>150, veto SR3b, meff>400

														
				  num_leps->Fill(lep.num_20GeV_leptons_noverlap, evt.weight);


						   if(lep.num_20GeV_leptons_noverlap >= 3){
						     num_of_evts_3L->Fill(.1, evt.weight);
						     met_3L->Fill(my_MET_pT/1000., evt.weight);
						     meff_3L->Fill(meff/1000., evt.weight);
						     mT_3L->Fill(transverse_mass(&lep, &evt)/1000., evt.weight);
						     mll_3L->Fill(dilepton_mass(&lep, &evt), evt.weight);
						     num_jets_3L->Fill(n_jets, evt.weight);
						     num_bjets_3L->Fill(n_bjets, evt.weight);
						   }
						   else if(lep.num_20GeV_leptons_noverlap == 2){
						     num_of_evts_SS->Fill(.1, evt.weight);
						     met_SS->Fill(my_MET_pT/1000., evt.weight);
						     meff_SS->Fill(meff/1000., evt.weight);
						     mT_SS->Fill(transverse_mass(&lep, &evt)/1000., evt.weight);
						     mll_SS->Fill(dilepton_mass(&lep, &evt), evt.weight);
						     num_jets_SS->Fill(n_jets, evt.weight);
						     num_bjets_SS->Fill(n_bjets, evt.weight);
						     if(lep.is_electron[0] &&  lep.is_electron[1])
						       num_ee_SS->Fill(lep.num_20GeV_leptons_noverlap, evt.weight);
						     if(!lep.is_electron[0] &&  !lep.is_electron[1])
						       num_mm_SS->Fill(lep.num_20GeV_leptons_noverlap, evt.weight);
						     if( (lep.is_electron[0] &&  !lep.is_electron[1]) || (!lep.is_electron[0] &&  lep.is_electron[1]))
						       num_em_SS->Fill(lep.num_20GeV_leptons_noverlap, evt.weight);
						   }

						   num_of_evts->Fill(.1, evt.weight);
						   met->Fill(my_MET_pT/1000., evt.weight);
						   mEFF->Fill(meff/1000., evt.weight);
						   mT->Fill(transverse_mass(&lep, &evt)/1000., evt.weight);
						   mll->Fill(dilepton_mass(&lep, &evt), evt.weight);
						   num_jets->Fill(n_jets, evt.weight);
						   num_bjets->Fill(n_bjets, evt.weight);



				  PRE=true;
				  count_PRE++;
				  SR3b3L = (lep.num_20GeV_leptons_noverlap >= 3 && n_bjets >= 3 && my_MET_pT > 50000. && (meff < 350000. || n_jets <= 5) );
				  if(SR3b3L)
				    count_SR3b3L++;
				  SR3b = (meff > 350000. && n_jets >= 5 && n_bjets >= 3);
				  if(SR3b)
				    count_SR3b++;			
				  SR0b = (lep.num_20GeV_leptons_noverlap == 2  && n_jets >= 3 && n_bjets == 0 && my_MET_pT > 150000. && transverse_mass(&lep, &evt) > 100000. &&  meff > 400000. );
				  if(SR0b)
				    count_SR0b++;
				  SR1b= (lep.num_20GeV_leptons_noverlap == 2 && n_jets >= 3 && n_bjets >=1 && my_MET_pT > 150000. && transverse_mass(&lep, &evt) > 100000. && !SR3b && meff > 700000.);
				  if(SR1b)
				    count_SR1b++;
				  SR3Llow=(lep.num_20GeV_leptons_noverlap >= 3 && n_jets >= 4 && my_MET_pT > 50000. && my_MET_pT < 150000. && !lep.has_Z && !SR3b && meff > 400000.);
				  if(SR3Llow)
				    count_SR3Llow++;				  
				  SR3Lhigh=(lep.num_20GeV_leptons_noverlap >= 3 && n_jets >= 4 && my_MET_pT > 150000. && !SR3b && meff > 400000.);
				  if(SR3Lhigh)
				    count_SR3Lhigh++;








														if (dilepton_mass(&lep, &evt) > 12000.) {
														  cut_flow_ee_ss->Fill(13.1, evt.weight);      
														  if(n_jets>=4){
														    cut_flow_ee_ss->Fill(14.1,evt.weight);
														    if (is_ee(&lep, &evt)) { //is_ee
														      cut_flow_ee_ss->Fill(15.1, evt.weight);
														    if(my_MET_pT>150000.)
														      cut_flow_ee_ss->Fill(16.1,evt.weight);
														    }}}}}	} // setChannelAlternate (20,15,15)
														       	} // >1 tight leptons
												} // >1lep > 15 GeV
											} // >1 lept > 10 GeV
										} // Cosmic muon
									} // Jet Cleaning
								} // HEC veto
							} //Bad muons
						} // Primary vertex has 5 or more tracks
					} //core flags
				} //Tile Error
			} //LAR error
		}
			//---------------------------------------------------------------------------
	} // End of the main loop


std::cout << "\nDESCRIPTION\n";
std::cout << filename(83,16) << std::endl;
std::cout << "PRE: basic selection common to all \t" << count_PRE << std::endl;
std::cout << "SR3b3L: 3L, >=3bJETS, MET>50, <=5JETS OR meff<350 \t" << count_SR3b3L << std::endl;
std::cout << "SR3b: SS/3L, >=3bJETS, >=5JETS, meff>350 \t" << count_SR3b << std::endl;
std::cout << "SR1b: SS, >=1bJETS, >=3JETS, MET>150, mT>100, meff>700, veto SR3b \t" << count_SR1b << std::endl;
std::cout << "SR0b: SS, =0bJETS, >=3JETS, MET>150, meff>400 \t" << count_SR0b << std::endl;
std::cout << "SR3Llow: 3L, >=4JETS, 50<MET<150, Z veto, veto SR3b \t" << count_SR3Llow << std::endl;
std::cout << "SR3Lhigh: 3L, >=4JETS, MET>150, veto SR3b, meff>400 \t" << count_SR3Lhigh << std::endl;

std::cout << "PRE NORM";
std::cout << std::endl << filename(83,16) << "   Xsection: " << Get_CrossSection(&filename) << " nb" << std::endl;
 std::cout << "PRE " << count_PRE << std::endl;
 std::cout << "3b3L " << count_SR3b3L << std::endl;
 std::cout << "3b " << count_SR3b << std::endl;
 std::cout << "1b " << count_SR1b << std::endl;
 std::cout << "0b " << count_SR0b << std::endl;
 std::cout << "3Llow " << count_SR3Llow << std::endl;
 std::cout << "3Lhigh " << count_SR3Lhigh << std::endl;
std::cout << std::endl;

std::cout << "POST NORM 8TeV 20 1/fb \n";
std::cout << filename(83,16)  << "   Xsection: " << Get_CrossSection(&filename) << " nb" << std::endl;
std::cout  << "PRE "<< count_PRE*20*Get_CrossSection(&filename)*1.e6/80000. << std::endl;
std::cout  << "3b3L "<< count_SR3b3L*20*Get_CrossSection(&filename)*1.e6/80000. << std::endl;
std::cout  << "3b "<< count_SR3b*20*Get_CrossSection(&filename)*1.e6/80000. << std::endl;
std::cout << "1b "<< count_SR1b*20*Get_CrossSection(&filename)*1.e6/80000. << std::endl;
std::cout  << "0b "<< count_SR0b*20*Get_CrossSection(&filename)*1.e6/80000. << std::endl;
std::cout << "3Llow " << count_SR3Llow*20*Get_CrossSection(&filename)*1.e6/80000. << std::endl;
std::cout<< "3Lhigh " << count_SR3Lhigh*20*Get_CrossSection(&filename)*1.e6/80000. << std::endl;
std::cout << std::endl;

std::cout << "POST NORM 13TeV 3 1/fb \n";
std::cout << filename(83,16)  << "   Xsection: " << Get_CrossSection_13(&filename) << " fb" << std::endl;
std::cout << "PRE "<< count_PRE*3*Get_CrossSection_13(&filename)*1.e3/80000. << std::endl;
std::cout  << "3b3L "<< count_SR3b3L*3*Get_CrossSection_13(&filename)*1.e3/80000. << std::endl;
std::cout << "3b " << count_SR3b*3*Get_CrossSection_13(&filename)*1.e3/80000. << std::endl;
std::cout  << "1b "<< count_SR0b*3*Get_CrossSection_13(&filename)*1.e3/80000. << std::endl;
std::cout << "0b "<< count_SR1b*3*Get_CrossSection_13(&filename)*1.e3/80000. << std::endl;
std::cout << "3Llow "<< count_SR3Llow*3*Get_CrossSection_13(&filename)*1.e3/80000. << std::endl;
std::cout << "3Lhigh "<< count_SR3Lhigh*3*Get_CrossSection_13(&filename)*1.e3/80000. << std::endl;
std::cout << std::endl;

	st.Stop();
	real_time = st.RealTime();

	if (real_time > 0) {
		packed_rate = n_bytes / (1024. * 1024. * real_time);
		unpacked_rate = file_size / (1024. * 1024. * real_time);
		n_bytes = 0;
		std::cout << "entry: " << tree_Entries << ",\t time to process: " << real_time << " sec.\n";
		std::cout << "avg. unpacked rate : " << packed_rate << " MB/sec\n";
		std::cout << "avg. packed rate   : " << unpacked_rate << " MB/sec\n\n";
	}
	std::cout << "\n";

	file.Write();

//m_pileupTool_test->WriteToFile();

	return 0;
}

//-----------------------------------------------------------------------
int main(int argc, char **argv) {

	TChain tc("MiniNtuple");

	if (argc < 3) {
		std::cout << "Usage: " << argv[0] << " data-tag /my_folder/file-list.root\n";
		return 1;
	}

	long int unskimmed = 0;
	long int skimmed = 0;

	for (int i = 2; i < argc; i++) {

		//Here we extract the number of events before skimming on GRID

		TFile f(argv[i], "READ");
		TH1D* h_events = (TH1D*) f.Get("MiniMon/h_events");
		if (h_events != NULL) {
			unskimmed += h_events->GetBinContent(1);
			skimmed += h_events->GetBinContent(2);
		}
		f.Close();

		//-----------------------------

		tc.Add(argv[i]);
	}

	std::cout << "\nNumber of events before GRID skimming: " << unskimmed << "\n";
	std::cout << "\nNumber of events after GRID skimming: " << skimmed << "\n";

	return main_loop(&tc, argv[1]);
}
