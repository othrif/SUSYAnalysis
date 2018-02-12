/*****************************************************************************/
/*                                                                           */
/* File Name        : analyze.cxx                                            */
/*                                                                           */
/* Author           : Othmane Rifki			                                 */
/* Email            : othmane.rifki@cern.ch			                         */
/*                                                                           */
/* Description      : Applies Object Definition and Selection for SS/3L      */
/*                    Runs over MiniNtuple                                   */
/*                    Produces histograms for SR/VR/CRs                      */
/*                    To run: analyze <foldername> <filename> <rootfiles>    */
/*                    e.g. analzye testfolder data data/DAOD_SUSY2*.root     */
/*                                                                           */
/*                                                                           */
/***** C 2016 ****************************************************************/


//here are the project-specific files
#include "Analyzer/my_objects.h"
#include "Root/my_objects.cxx"
#include "Analyzer/DileptonTriggerWeight.h"
#include "Root/DileptonTriggerWeight.cxx"
#include "GoodRunsLists/TGoodRunsListReader.h"
#include "GoodRunsLists/GoodRunsListSelectionTool.h"
#include "PileupReweighting/PileupReweightingTool.h"
#include "xAODEventInfo/EventInfo.h"
#include "xAODEventInfo/EventInfoContainer.h"
#include "xAODEventInfo/EventInfoAuxContainer.h"
#include "SUSYTools/SUSYCrossSection.h"
#include "CPAnalysisExamples/errorcheck.h"
//#include "LHAPDF/PDFSet.h"
//#include "LHAPDF/Reweighting.h"
//#include "LHAPDF/LHAPDF.h"
#include "FakeObjectTools/TwoLepSSFakeBkg.h"

// PILEUP REWEIGHTING
// The application's name:
const char* APP_NAME = "Monstres tronats";

//------------------------------------------------------------------------
//				-= General Declarations =-
//------------------------------------------------------------------------

//#define luminosity 36470.16 
#define luminosity 36074.56
// lumi 2016 new:  32861.6 +- 4.5%
// lumi 2015: 3212.96 +- 2.1%
// lumi 2015+2016: 36074.56 +- 4.1%
// lumi 2016 old: 33257.2 +- 4.5%

bool GG = false;           // Gluino mediated processes
bool BB = false;           // sbottom mediated processes
bool strong = false;       // strong production for NUHM2
bool applyOR = true;
bool cutflow = false;      // to activate cutflow

bool useTTbarHT = false;    // only HT or MET is true, not both
bool useTTbarMET = false;

bool noXsection = true;

bool debugme = false;

bool old_OR_strategy = false;

void declarestructs(TTree* tree, myevt* evt);

//------------------------------------------------------------------------
//				-= Main loop =-
//------------------------------------------------------------------------
int main_loop(TChain* oldtree, char* name, char* ftag) {
  
  std::cout << " \n------- " << ftag << " ------- " << std::endl;
  
  myevt evt;
  std::map<unsigned int, std::set<ULong64_t> > evtmap;

  //-----------------------------------------------------------------------

  if (!oldtree)
	return 1;
	
  Long64_t tree_Entries = (Long64_t) oldtree->GetEntries();
  if (tree_Entries == 0)
	return 1;

  oldtree->GetEntry(0);
  declarestructs(oldtree->GetTree(), &evt);
  int treeno = ((TChain*) oldtree)->GetTreeNumber();
  TString filename = oldtree->GetFile()->GetName();
  TString oldfilename = oldtree->GetFile()->GetName();
  int numtrees = ((TChain*) oldtree)->GetNtrees();
  //  std::cout << "file: " << filename << ", number of trees: " << numtrees << "\n";
  std::cout << "Expect to process " << tree_Entries << " entries in " << numtrees << " file(s).\n";

  //  std::cout << "file: " << filename << ", treeno: " << treeno << "\n";

  // Check the filename to select processes contributing to charge flip
  //  bool isCFSource = false;
  //  if(filename.Index("_ttbar_") > 0 || filename.Index("_Zee") > 0 ||  filename.Index("_Zmumu") > 0 ||  filename.Index("_Ztautau") > 0  || filename.Index("_llvv.") > 0 ){
  //	isCFSource = true;
  //	std::cout << "source of charge flip sample!!" << std::endl;
  //  }

  // For signal cross sections
  if(filename.Index("_GG_") > 0 )
    GG = true;
  if(filename.Index("_BB_") > 0 )
    BB = true;
  if(filename.Index("strong") > 0 )
    strong = true;
  if(filename.Index("_GG_2stepWZ") > 0 )
    GG = false;

  /*
  // PileupReweighing
  CP::PileupReweightingTool* m_Pileup;

  m_Pileup  = new CP::PileupReweightingTool("Pileup");
  std::vector<std::string> confFiles;
  std::vector<std::string> lcalcFiles;
  */
  oldtree->GetEntry(0);
  /*
  std::cout << "MC15c sample" << std::endl;
  //  confFiles.push_back("/cvmfs/atlas.cern.ch/repo/sw/database/GroupData/dev/SUSYTools/merged_prw_mc15c.root");
  confFiles.push_back("/cvmfs/atlas.cern.ch/repo/sw/database/GroupData/dev/SUSYTools/merged_prw_mc15c_latest.root");
  //  confFiles.push_back("/cvmfs/atlas.cern.ch/repo/sw/database/GroupData/dev/SUSYTools/merged_prw_mc15c_signal_latest.root");
  lcalcFiles.push_back("/afs/cern.ch/work/o/othrif/workarea/myFramework/Analyzer/data/ilumicalc_histograms_None_276262-284484.root");
  lcalcFiles.push_back("/afs/cern.ch/work/o/othrif/workarea/myFramework/Analyzer/data/ilumicalc_histograms_None_297730-311481_OflLumi-13TeV-005.root");

  CHECK(m_Pileup->setProperty( "ConfigFiles", confFiles) );
  //  CHECK(m_Pileup->setProperty( "DefaultChannel",410000) ); 
  CHECK(m_Pileup->setProperty( "LumiCalcFiles", lcalcFiles) );

  CHECK(m_Pileup->setProperty( "DataScaleFactor", 1.0/1.09) );
  CHECK(m_Pileup->setProperty( "DataScaleFactorUP", 1.0/1.0) );
  CHECK(m_Pileup->setProperty( "DataScaleFactorDOWN", 1.0/1.18) );

  CHECK(m_Pileup->initialize());
  */

  // Dummy EventInfo object to manipulate later
  xAOD::EventInfo* eventInfo;
  xAOD::EventInfoContainer* eInfos;

  eInfos = new xAOD::EventInfoContainer();
  eInfos->setStore(new xAOD::EventInfoAuxContainer());
  eInfos->push_back(new xAOD::EventInfo());
  eventInfo = eInfos->at(0);

  // GoodRunsLists
  GoodRunsListSelectionTool *m_grl;
  m_grl = new GoodRunsListSelectionTool("GoodRunsListSelectionTool");
  std::vector<std::string> myvals;
  myvals.push_back("/afs/cern.ch/work/o/othrif/workarea/myFramework/Analyzer/data/data15_13TeV.periodAllYear_DetStatus-v79-repro20-02_DQDefects-00-02-02_PHYS_StandardGRL_All_Good_25ns.xml");
  //  myvals.push_back("/afs/cern.ch/work/o/othrif/workarea/myFramework/Analyzer/data/data16_13TeV.periodAllYear_DetStatus-v83-pro20-15_DQDefects-00-02-04_PHYS_StandardGRL_All_Good_25ns.xml");
  myvals.push_back("/afs/cern.ch/work/o/othrif/workarea/myFramework/Analyzer/data/data16_13TeV.periodAllYear_DetStatus-v88-pro20-21_DQDefects-00-02-04_PHYS_StandardGRL_All_Good_25ns.xml");
  CHECK( m_grl->setProperty( "GoodRunsListVec", myvals) );
  CHECK( m_grl->setProperty("PassThrough", false) );
  CHECK( m_grl->initialize() );
  
  // Cross Sections
  SUSY::CrossSectionDB myXsection("/afs/cern.ch/work/o/othrif/workarea/myFramework/Analyzer/data/mc15_13TeV/");

  // Dilepton trigger weight
  DileptonTriggerWeight dtwTool;

  // create folder
  char fpath[512];
  sprintf(fpath, "/afs/cern.ch/work/o/othrif/workarea/results");
  int res = mkdir(fpath, 0700);
  if ( res == -1) {
	std::cout << "WARNING: Folder " << fpath  << " already exists!" << std::endl;
  }

  sprintf(fpath, "/afs/cern.ch/work/o/othrif/workarea/results/v52");
  res = mkdir(fpath, 0700);
  if ( res == -1) {
	std::cout << "WARNING: Folder " << fpath  << " already exists!" << std::endl;
  }

  sprintf(fpath, "/afs/cern.ch/work/o/othrif/workarea/results/v52/%s", name);
  res = mkdir(fpath, 0700);
  if ( res == -1) {
	std::cout << "WARNING: Folder " << fpath  << " already exists!" << std::endl;
  }

  // logs
  char lpath[512];
  sprintf(lpath, "/afs/cern.ch/work/o/othrif/workarea/results/v52/%s/logs", name);
  int res_log = mkdir(lpath, 0700);
  if ( res_log == -1) {
	std::cout << "WARNING: Folder " << lpath  << " already exists!" << std::endl;
  }
  
  // output file
  char fname[512];
  sprintf(fname, "/afs/cern.ch/work/o/othrif/workarea/results/v52/%s/%s.root", name,ftag);
  TFile file(fname, "RECREATE");

  // Save log file
  char logfile[512];
  sprintf(logfile,"/afs/cern.ch/work/o/othrif/workarea/results/v52/%s/logs/%s.log", name,ftag);
  FILE *fp;
  fp=fopen(logfile, "w+");
  if(!fp)
	std::cout << "ERROR: Cannot write to log file!" << std::endl;

  sprintf(logfile,"/afs/cern.ch/work/o/othrif/workarea/results/v52/%s/logs/%s_debug.log", name,ftag);
  FILE *fpd;
  fpd=fopen(logfile, "w+");
  if(!fpd)
	std::cout << "ERROR: Cannot write to debug log file!" << std::endl;

  sprintf(logfile,"/afs/cern.ch/work/o/othrif/workarea/results/v52/%s/logs/yields_per_file.log", name);
  FILE *fpy;
  fpy=fopen(logfile, "a+");
  if(!fpy)
	std::cout << "ERROR: Cannot write to debug log file!" << std::endl;

  // SS/3L
  //-----------------------------------------------------------------------                                                                 
  // General information
  //-----------------------------------------------------------------------

  // vertex information
  TH1D *num_vtx_noPRW = new TH1D("num_vtx_noPRW", "num_vtx_noPRW;# prim. vtx.;entries", 40, 0, 40);
  num_vtx_noPRW->Sumw2();
  TH1D *num_vtx_PRW = new TH1D("num_vtx_PRW", "num_vtx_PRW;# prim. vtx.;entries", 40, 0, 40);
  num_vtx_PRW->Sumw2();
  
  // averageIntPerXing                                                                                             
  TH1D *averageIntPerXing_noPRW = new TH1D("averageIntPerXing_noPRW", "averageIntPerXing_noPRW;averageIntPerXing;entries", 40, 0, 40);
  averageIntPerXing_noPRW->Sumw2();
  TH1D *averageIntPerXing_PRW = new TH1D("averageIntPerXing_PRW", "averageIntPerXing_PRW;averageIntPerXing;entries", 40, 0, 40);
  averageIntPerXing_PRW->Sumw2();  
  TH1D *averageIntPerXing_PRW_SS3L = new TH1D("averageIntPerXing_PRW_SS3L", "averageIntPerXing_PRW_SS3L;averageIntPerXing;entries", 40, 0, 40);
  averageIntPerXing_PRW_SS3L->Sumw2();
  
  //number of leptons
  TH1D *num_of_leptons_noPRW  = new TH1D("num_of_leptons_noPRW", "num_of_leptons_noPRW;N_{lep};Events", 11, -0.5, 10.5);
  num_of_leptons_noPRW->Sumw2();
  TH1D *num_of_leptons_PRW = new TH1D("num_of_leptons_PRW", "num_of_leptons_PRW;N_{lep}; Events", 11, -0.5, 10.5);
  num_of_leptons_PRW->Sumw2();
  
  //number of jets
  TH1D *num_of_jets_noPRW  = new TH1D("num_of_jets_noPRW", "num_of_jets_noPRW ;N_{jet}; Events", 21, -0.5, 20.5);
  num_of_jets_noPRW->Sumw2();
  TH1D *num_of_jets_PRW = new TH1D("num_of_jets_PRW", "num_of_jets_PRW;N_{jet}; Events", 21, -0.5, 20.5);
  num_of_jets_PRW->Sumw2();

  // b-tagging weight
  TH1D *btag_weight_noPRW  = new TH1D("btag_weight_noPRW", "btag_weight_noPRW  MV2c20;btag_weight MV2c20;entries", 30, -1.5, 1.5);
  btag_weight_noPRW->Sumw2();  
  TH1D *btag_weight_PRW = new TH1D("btag_weight_PRW", "btag_weight_PRW MV2c20;btag_weight MV2c20;entries", 30, -1.5, 1.5);
  btag_weight_PRW->Sumw2();  

  // Total Event weight
  TH1D *event_weight_noXsec  = new TH1D("event_weight_noXsec", "event_weight_noXsec ;Total Event Weight (NoXsec);entries", 300, 0, 1.5);
  event_weight_noXsec->Sumw2();  
 
  // Correlations
  TH2D *btagwgh_mu_noPRW =  new TH2D("btagwgh_mu_noPRW", "btag_weight vs. #mu_noPRW;averageIntPerXing;btag_weight MV2c20;entries", 40, 0, 40, 30, -1.5, 1.5);
  btagwgh_mu_noPRW->Sumw2();

  TH2D *evtwgh_mu_noXsec =  new TH2D("evtwgh_mu_noXsec", "event_weight vs. #mu_noXsec;averageIntPerXing;Total Event Weight (NoXsec);entries", 40, 0, 40, 300, 0, 1.5);
  evtwgh_mu_noXsec->Sumw2();

  TH2D *btagwgh_mu_PRW =  new TH2D("btagwgh_mu_PRW", "btag_weight vs. #mu_PRW;averageIntPerXing;btag_weight MV2c20;entries", 40, 0, 40, 30, -1.5, 1.5);
  btagwgh_mu_PRW->Sumw2();

  TH2D *ttbarClass =  new TH2D("ttbarClass", "b jet truth vs. Event class;Event Class;b jet truth;entries", 3, 0, 3, 2, 0, 2);
  ttbarClass->Sumw2();

  TH2D *ttbarClass_SS3L =  new TH2D("ttbarClass_SS3L", "b jet truth vs. Event class;Event Class;b jet truth;entries", 3, 0, 3, 2, 0, 2);
  ttbarClass_SS3L->Sumw2();

  TH2D *ttbarClass_OS =  new TH2D("ttbarClass_OS", "b jet truth vs. Event class;Event Class;b jet truth;entries", 3, 0, 3, 2, 0, 2);
  ttbarClass_OS->Sumw2();


  // Cutflow                                                                                                                          
  //-----------------------------------------------------------------------
  TH1D* cut_flow = new TH1D("cut_flow", "cut_flow for the baseline selection", 100, 0, 100);
  cut_flow->Sumw2();
  
  TH1D* cut_flow_ee_ss = new TH1D("cut_flow_ee_ss", "cut_flow for ee_ss selection", 40, 0, 40);
  cut_flow_ee_ss->Sumw2();
  
  TH1D* cut_flow_em_ss = new TH1D("cut_flow_em_ss", "cut_flow for em_ss selection", 40, 0, 40);
  cut_flow_em_ss->Sumw2();
	
  TH1D* cut_flow_mm_ss = new TH1D("cut_flow_mm_ss", "cut_flow for mm_ss selection", 40, 0, 40);
  cut_flow_mm_ss->Sumw2();

  TH1D* weight_flow = new TH1D("weight_flow", "weight for ss/3l selection", 8, 0, 8);
  weight_flow->Sumw2();

  // Checks                                                                                                                          
  //-----------------------------------------------------------------------
  TH1D* hscaled = new TH1D("hscaled", "Sanity Checks", 10, 0, 10);
  hscaled->Sumw2();

  hscaled->GetXaxis()->FindBin("All");
  hscaled->GetXaxis()->FindBin("SS ee+e#mu+#mu#mu");
  hscaled->GetXaxis()->FindBin("SS ee");
  hscaled->GetXaxis()->FindBin("SS e#mu");
  hscaled->GetXaxis()->FindBin("SS #mu#mu");
  hscaled->GetXaxis()->FindBin("OS ee+e#mu+#mu#mu");
  hscaled->GetXaxis()->FindBin("OS ee");
  hscaled->GetXaxis()->FindBin("OS e#mu");
  hscaled->GetXaxis()->FindBin("OS #mu#mu");

  TH1D* hraw = (TH1D*)hscaled->Clone("hraw");
  hraw->Sumw2();

  // Composition:

  TH1D* composition_3lss = new TH1D("composition_3lss", "Background Composition;;Events", 9, 0, 9);
  composition_3lss->Sumw2();

  composition_3lss->GetXaxis()->FindBin("All");
  composition_3lss->GetXaxis()->FindBin("All Prompt");
  composition_3lss->GetXaxis()->FindBin("2 Prompt & 1 Fake");
  composition_3lss->GetXaxis()->FindBin("2 Prompt & 1 MisId");
  composition_3lss->GetXaxis()->FindBin("1 Prompt & 1 Fake & 1 MisId");
  composition_3lss->GetXaxis()->FindBin("1 Prompt & 2 Fake & 0 MisId");
  composition_3lss->GetXaxis()->FindBin("1 Prompt & 0 Fake & 2 MisId");
  composition_3lss->GetXaxis()->FindBin("All fakes or charge flips");
  composition_3lss->GetXaxis()->FindBin("Rest");


  // SR
  //-----------------------------------------------------------------------
  TH1D* signal_region = new TH1D("signal_region", "Signal Regions;;Events", 25, 0, 25);
  signal_region->Sumw2();

  signal_region->GetXaxis()->FindBin("All");
  signal_region->GetXaxis()->FindBin("VRttW");
  signal_region->GetXaxis()->FindBin("VRttZ");
  signal_region->GetXaxis()->FindBin("VRWW");
  signal_region->GetXaxis()->FindBin("VRWZ4j");
  signal_region->GetXaxis()->FindBin("VRWZ5j");
  signal_region->GetXaxis()->FindBin("Rpc2L0bH");
  signal_region->GetXaxis()->FindBin("Rpc2L0bS");
  signal_region->GetXaxis()->FindBin("Rpc2L1bH");
  signal_region->GetXaxis()->FindBin("Rpc2L1bS");
  signal_region->GetXaxis()->FindBin("Rpc2L2bH");
  signal_region->GetXaxis()->FindBin("Rpc2L2bS");
  signal_region->GetXaxis()->FindBin("Rpc2Lsoft1b");
  signal_region->GetXaxis()->FindBin("Rpc2Lsoft2b");
  signal_region->GetXaxis()->FindBin("Rpc3L0bH");
  signal_region->GetXaxis()->FindBin("Rpc3L0bS");
  signal_region->GetXaxis()->FindBin("Rpc3LSS1b");
  signal_region->GetXaxis()->FindBin("Rpc3L1bH");
  signal_region->GetXaxis()->FindBin("Rpc3L1bS");
  signal_region->GetXaxis()->FindBin("Rpv2L0b");
  signal_region->GetXaxis()->FindBin("Rpv2L1bH");
  signal_region->GetXaxis()->FindBin("Rpv2L1bM");
  signal_region->GetXaxis()->FindBin("Rpv2L1bS");
  signal_region->GetXaxis()->FindBin("Rpv2L2bH");
  signal_region->GetXaxis()->FindBin("Rpv2L2bS");




  // SR N-1 plots
  //-----------------------------------------------------------------------
  /*  TH1D *SR3LmMET  = new TH1D("MET_SR3LmMET_SS3L", "mEt (N-1);E_{T}^{miss}  (N-1) [GeV];Events / 25 GeV", 7, 50, 225);
  SR3LmMET->Sumw2();
 
  TH1D *SR0bmMET  = new TH1D("MET_SR0bmMET_SS3L", "mEt (N-1);E_{T}^{miss}  (N-1) [GeV];Events / 25 GeV", 5, 50, 175);
  SR0bmMET->Sumw2();
 
  TH1D *SR1bmMET  = new TH1D("MET_SR1bmMET_SS3L", "mEt (N-1);E_{T}^{miss}  (N-1) [GeV];Events / 25 GeV", 5, 50, 175);
  SR1bmMET->Sumw2();
 
  TH1D *SR3bmMET  = new TH1D("MET_SR3bmMET_SS3L", "mEt (N-1);E_{T}^{miss}  (N-1) [GeV];Events / 25 GeV", 5, 50, 175);
  SR3bmMET->Sumw2();
 
    TH1D *SRrpv0bmMeff  = new TH1D("Meff_SRrpv0bmMeff_SS3L", "effective mass (N-1); m_{eff}  (N-1) [GeV] ;Events / 100 GeV", 5, 600, 1600);
  SRrpv0bmMeff->Sumw2();
 
  TH1D *SRrpv1bmMeff  = new TH1D("Meff_SRrpv1bmMeff_SS3L", "effective mass (N-1); m_{eff}  (N-1) [GeV] ;Events / 100 GeV", 7, 600, 2000);
  SRrpv1bmMeff->Sumw2();
 
  TH1D *SRrpv3bmMeff  = new TH1D("Meff_SRrpv3bmMeff_SS3L", "effective mass (N-1); m_{eff}  (N-1) [GeV] ;Events / 100 GeV", 7, 600, 1300);
  SRrpv3bmMeff->Sumw2();*/

  // Initialize variables
  //-----------------------------------------------------------------------

  // Signal regions
  int count_ALL = 0;
  int count_SR3L0b1 = 0;
  int count_SR3L0b2 = 0;
  int count_SR3L1b1 = 0;
  int count_SR3L1b2 = 0;
  int count_SR0b1 = 0;
  int count_SR0b2 = 0;
  int count_SR1b1 = 0;
  int count_SR1b2 = 0;
  int count_SR1b_3LSS = 0;
  int count_SR3b1 = 0;
  int count_SR3b2 = 0;
  int count_SRlow = 0;
  int count_SRhigh = 0;
  int count_SR1b_DD_low = 0;
  int count_SR1b_DD_high = 0;
  int count_SR3b_DD = 0;
  int count_SR1b_GG = 0;
  int count_SRRPV0b = 0;
  int count_SRRPV3b = 0;
  int count_Rpc2L2bS = 0;
  int count_Rpc2L2bH = 0;
  int count_Rpv2L2bS = 0;
  int count_Rpv2L2bH = 0;
  // Validation regions
  int count_VRWW = 0;
  int count_VRWZ4j = 0;
  int count_VRWZ5j = 0;
  int count_VRttW = 0;
  int count_VRttZ = 0;

  // Count OS vs. SS in Z window
  float num_OS=0.;                                                                                                     
  float num_SS=0.;   

  // other
  double pileupwgh=1.0;

  // Book histograms to be filled later
  //-----------------------------------------------------------------------
  if(!cutflow)
	{
	  //	  BookHistos_Channel(ftag, "OS");
	  BookHistos_Channel(ftag, "SS3L");
	  //  BookHistos_Channel(ftag, "SS3L_noZ");
	  //	BookHistos_Channel(ftag, "SS");
	  //  BookHistos_Channel(ftag, "3L");
	}

  bool unique;
  
  // Fake and charge flip backgrounds
  //-----------------------------------------------------------------------
  TwoLepSSFakeBkg stdMxmTool;
  stdMxmTool.UseSplitErrBySource_OStoSS(true);

  int raw=0, processed=0;
  float scaled=0, Xsect=0, sumWeight=0;
  bool newtree=false;
  // Main event loop
  //-----------------------------------------------------------------------
  for (Long64_t entr_ind = 0; entr_ind < tree_Entries; entr_ind++) {
	oldtree->GetEntry(entr_ind);	  
	if (treeno != ((TChain*) oldtree)->GetTreeNumber()) {
	  declarestructs(oldtree->GetTree(), &evt);
	  oldtree->GetEntry(entr_ind);
	  treeno = ((TChain*) oldtree)->GetTreeNumber();
	  filename = oldtree->GetFile()->GetName();
	  newtree=true;
	}

	// Extend ttbar samples using HT samples
	// HT Sliced samples: 407009 || 407010 || 407011 
	if(!useTTbarHT && (evt.ChannelNumber == 407009 || evt.ChannelNumber == 407010 || evt.ChannelNumber == 407011 ))
	  continue;

	if( useTTbarHT && evt.ChannelNumber == 410000 && evt.GenFiltHT > 600000 )
	  continue;
	
	// Extend ttbar samples using MET samples
	// ChannelNumber: 407012
	if(!useTTbarMET && evt.ChannelNumber == 407012)
	  continue;

	if(useTTbarMET && evt.ChannelNumber == 410000 && evt.GenFiltMET > 200000 )
	  continue;	
	
	// Sanity checks
	num_vtx_noPRW->Fill(evt.Nvtx, evt.EventWeight);  
	averageIntPerXing_noPRW->Fill(evt.AvgMu, evt.EventWeight);  
	num_of_leptons_noPRW->Fill(evt.NEl + evt.NMu, evt.EventWeight);  
	num_of_jets_noPRW->Fill(evt.NJet, evt.EventWeight);  
	for (int ijet=0; ijet<evt.NJet; ijet++){
	  btag_weight_noPRW->Fill(evt.Jet_MV2c20[ijet], evt.EventWeight);
	  btagwgh_mu_noPRW->Fill(evt.AvgMu, evt.Jet_MV2c20[ijet], evt.EventWeight);
	}
	eventInfo->setEventNumber(evt.EventNumber);
	eventInfo->setRunNumber(evt.RunNb);
	eventInfo->setLumiBlock(evt.LB);	

	if(evt.isMC){
	  
	  // Put the ntuple variables into EventInfo
	  eventInfo->setMCChannelNumber(evt.ChannelNumber);
	  eventInfo->setEventTypeBitmask( xAOD::EventInfo::IS_SIMULATION );
	  eventInfo->setAverageInteractionsPerCrossing(evt.AvgMu);
	  vector<float> w;
	  w.clear();
	  w.push_back(evt.EventWeight);
	  eventInfo->setMCEventWeights( w );
	  /*
	  // Pileup reweighting
	  pileupwgh = 1.0;
	  // nominal case
	  CP::SystematicSet defaultSet;
	  CHECK(m_Pileup->applySystematicVariation(defaultSet) );
	  // produces a decoration in Eventinfo
	  CHECK(m_Pileup->apply(*eventInfo,false) ); 
	  
	  // example to retrieve decoration:
	  pileupwgh = eventInfo->auxdata< float >( "PileupWeight" );
	  */
	  pileupwgh = evt.PRWWeight;
	  double tmpEventWeight = evt.EventWeight;
	  // apply prw
	  evt.EventWeight *= pileupwgh;

	  num_vtx_PRW->Fill(evt.Nvtx, pileupwgh);  
	  averageIntPerXing_PRW->Fill(evt.AvgMu, pileupwgh);  
	  num_of_leptons_PRW->Fill(evt.NEl + evt.NMu, pileupwgh);  
	  num_of_jets_PRW->Fill(evt.NJet, pileupwgh);  
	  for (int ijet=0; ijet<evt.NJet; ijet++){
		btag_weight_PRW->Fill(evt.Jet_MV2c20[ijet], pileupwgh);
		btagwgh_mu_PRW->Fill(evt.AvgMu, evt.Jet_MV2c20[ijet], evt.EventWeight);
	  }

	  evt.EventWeight = tmpEventWeight;
	}
	
	//========================================================================
	// General Selection
	//========================================================================

	/*	if(evt.EventNumber == 179 || evt.EventNumber == 365 || evt.EventNumber == 1044 || evt.EventNumber == 1383 ){
	  for (int eli = 0; eli < evt.NEl ; eli++)
		std::cout << "evtNr=" << evt.EventNumber << ", El_pt=" << evt.El_pT[eli] << ", SFweightCFT=" << evt.El_SFweightCFT[eli] << std::endl;
		}*/
	// Analyzer
	//-----------------------------------------------------------------------
	cut_flow->Fill(0.1, 1.0);//evt.EventWeight);  
	if(!newtree)
	  processed+=1;

	// good run lists
	bool muo_GRL = true;
	if (!evt.isMC) {
	  muo_GRL = m_grl->passRunLB(eventInfo->runNumber(), eventInfo->lumiBlock()); //(my_grl.HasRunLumiBlock(evt.RunNb, evt.LB));
	}                                                                                                           	  

	if (!muo_GRL )
	  continue;
	cut_flow->Fill(1.1, 1.0);//evt.EventWeight);

	// we test if the event is unique (in data)
	if (!evt.isMC) {
	  unique = (evtmap[evt.RunNb].insert(evt.EventNumber)).second;
	  if (!unique) {
		std::cout << "\nWarning: duplicate event in RunNb=" << evt.RunNb << std::endl;
		continue;
	  }
	}
	
	// primary vertex
	bool goodPV = (evt.PV_z > -999);
	if(!goodPV)
	  continue;
	cut_flow->Fill(2.1,1.0);//evt.EventWeight);

	// trigger
	bool trigger = true; 
	int RunNum=1; 
	//	int RunNum2=1; 
	if(evt.isMC){
	  //	  RunNum = m_Pileup->getRandomRunNumber( *eventInfo , true); 
	  //	  RunNum2 = eventInfo->auxdata<unsigned int>("RandomRunNumber");
	  	  RunNum = evt.PRWrandomRunNumber;
	}
	else
	  RunNum = evt.RunNb;
	evt.trigRND = RunNum;	

	if(RunNum > 290000){
	  // 2016 strategy
	  if(evt.Etmiss_TST_Et <= 250000)
		trigger = ( evt.HLT_2e17_lhvloose_nod0 || evt.HLT_e17_lhloose_nod0_mu14 || evt.HLT_mu22_mu8noL1 );
	  else if(evt.Etmiss_TST_Et > 250000)
		trigger = ( evt.HLT_2e17_lhvloose_nod0 || evt.HLT_e17_lhloose_nod0_mu14 || evt.HLT_mu22_mu8noL1 || evt.HLT_xe100_mht_L1XE50 || evt.HLT_xe110_mht_L1XE50);
	}
	else {
	  // 2015 strategy	
	  if(evt.Etmiss_TST_Et <= 250000)
		trigger = (evt.HLT_2e12_lhloose_L12EM10VH || evt.HLT_mu18_mu8noL1 || evt.HLT_e17_lhloose_mu14 );
	  else if(evt.Etmiss_TST_Et > 250000)
		trigger = (evt.HLT_2e12_lhloose_L12EM10VH || evt.HLT_mu18_mu8noL1 || evt.HLT_e17_lhloose_mu14 || evt.HLT_xe70);
	}

	//	if(evt.EventNumber == 105615 || evt.EventNumber == 110015 || evt.EventNumber == 169557 || evt.EventNumber == 156255 ){
	/*	if(evt.EventNumber == ){
	  //	  debug_printall(&evt);

	  std::cout << "just before trigger ..." << ", EventNb=" << evt.EventNumber << ", RunNb=" << RunNum << ", MET=" << evt.Etmiss_TST_Et/1000. << std::endl;
	  std::cout << "2016 Config" << 
		", HLT_2e17_lhvloose_nod0 " <<  evt.HLT_2e17_lhvloose_nod0 << 
		", HLT_e17_lhloose_nod0_mu14 " << evt.HLT_e17_lhloose_nod0_mu14 << 
		", HLT_mu22_mu8noL1 " << evt.HLT_mu22_mu8noL1 << 
		", HLT_xe100_mht_L1XE50 " << evt.HLT_xe100_mht_L1XE50 << 
		", HLT_xe110_mht_L1XE50 " << evt.HLT_xe110_mht_L1XE50 << 
		std::endl;

	  std::cout << "2015 Config" << 
		", HLT_2e12_lhloose_L12EM10VH " <<  evt.HLT_2e12_lhloose_L12EM10VH << 
		", HLT_mu18_mu8noL1 " <<  evt.HLT_mu18_mu8noL1 << 
		", HLT_e17_lhloose_mu14 " << evt.HLT_e17_lhloose_mu14 << 
		", HLT_xe70 " << evt.HLT_xe70 << 
		std::endl;
		}*/

	if(!trigger)
	  continue;
	cut_flow->Fill(3.1,1.0);//evt.EventWeight);
	
	//	std::cout << "trigger " << evt.EventNumber << std::endl;
	//	if(evt.PRWWeight != pileupwgh)
	//	  std::cout << "PRWrandomRunNumber=" << evt.PRWrandomRunNumber << ", RunNum=" << RunNum << " // PRWWeight=" << evt.PRWWeight << ", pileup=" << pileupwgh << std::endl;
	//   	if(evt.PRWrandomRunNumber != RunNum)
	//	  std::cout << "PRWrandomRunNumber=" << evt.PRWrandomRunNumber << ", RunNum=" << RunNum << " // PRWWeight=" << evt.PRWWeight << ", pileup=" << pileupwgh << std::endl;
	
	
	// global flags
	bool global = (evt.DetError == 1);

	if(global)
	  continue;
	cut_flow->Fill(4.1,1.0);//evt.EventWeight);

	// muon cleaning
	bool nobadmuon = true;
	for (int mui = 0; mui < evt.NMu; mui++)
	  if(is_baseline_muon(&evt, mui))
		nobadmuon &= !evt.Mu_isBad[mui];

	if(!nobadmuon)
	  continue;
	cut_flow->Fill(5.1,1.0);//evt.EventWeight);
	

	// Overlap removal
	//-----------------------------------------------------------------------
	my_jets jet;
	my_leptons lep_baseline;
	if(old_OR_strategy){
	  // OLD STRATEGY

	// check jet OR
	jet.num_jets = 0;
	for (int jetk = 0; jetk < evt.NJet; jetk++) 	
	  if( (is_baseline_jet(&evt, jetk)  && evt.Jet_passOR[jetk]) || !applyOR){
		jet.index[jet.num_jets] = jetk;
		jet.E[jet.num_jets] =  evt.Jet_E[jetk];
		jet.pT[jet.num_jets] =  evt.Jet_pT[jetk];
		jet.eta[jet.num_jets] =  evt.Jet_eta[jetk];
		jet.phi[jet.num_jets] =  evt.Jet_phi[jetk];
		jet.MV2c20[jet.num_jets] = evt.Jet_MV2c20[jetk];
		jet.num_jets++;
	  }

	if(cutflow){
	  if(jet.num_jets < 1)
		continue;
	  cut_flow->Fill(6.1,1.0);//evt.EventWeight);
	}

	// check el and mu OR
	lep_baseline.num_leptons = 0;
	for (int eli = 0; eli < evt.NEl ; eli++)
	  if( (is_baseline_electron(&evt, eli) && evt.El_passOR[eli]) || !applyOR)
		{
		  lep_baseline.index[lep_baseline.num_leptons] = eli;
		  lep_baseline.m[lep_baseline.num_leptons] = electron_mass;
		  lep_baseline.E[lep_baseline.num_leptons] = evt.El_E[eli];
		  lep_baseline.pT[lep_baseline.num_leptons] = evt.El_pT[eli];
		  lep_baseline.phi[lep_baseline.num_leptons] = evt.El_phi[eli];
		  lep_baseline.eta[lep_baseline.num_leptons] = evt.El_eta[eli];
		  lep_baseline.SFw[lep_baseline.num_leptons] = evt.El_SFwTightLH[eli];
		  lep_baseline.is_electron[lep_baseline.num_leptons] = true;
		  lep_baseline.charge[lep_baseline.num_leptons] = evt.El_charge[eli];
		  lep_baseline.num_leptons++;
		}

	//rm muon overlapping with electron
	for (int mui = 0; mui < evt.NMu ; mui++)
	  if( (is_baseline_muon(&evt, mui) && evt.Mu_passOR[mui]) || !applyOR)
		{
		  lep_baseline.index[lep_baseline.num_leptons] = mui;
		  lep_baseline.m[lep_baseline.num_leptons] = muon_mass;
		  lep_baseline.pT[lep_baseline.num_leptons] = evt.Mu_pT[mui];
		  lep_baseline.phi[lep_baseline.num_leptons] = evt.Mu_phi[mui];
		  lep_baseline.eta[lep_baseline.num_leptons] =  evt.Mu_eta[mui];
		  lep_baseline.SFw[lep_baseline.num_leptons] = evt.Mu_SFw[mui];
		  lep_baseline.is_electron[lep_baseline.num_leptons] = false;
		  lep_baseline.charge[lep_baseline.num_leptons] = evt.Mu_charge[mui];
		  lep_baseline.num_leptons++;
		}
	} else {

	  // NEW STRATEGY
	// check jet OR
	jet.num_jets = 0;
	for (int jetk = 0; jetk < evt.NJet; jetk++) 	
	  if( (is_baseline_jet(&evt, jetk)  && evt.Jet_passOR[jetk]) || !applyOR){
		jet.index[jet.num_jets] = jetk;
		jet.E[jet.num_jets] =  evt.Jet_E[jetk];
		jet.pT[jet.num_jets] =  evt.Jet_pT[jetk];
		jet.eta[jet.num_jets] =  evt.Jet_eta[jetk];
		jet.phi[jet.num_jets] =  evt.Jet_phi[jetk];
		jet.MV2c20[jet.num_jets] = evt.Jet_MV2c20[jetk];
		jet.num_jets++;
	  }

	if(cutflow){
	  if(jet.num_jets < 1)
		continue;
	  cut_flow->Fill(6.1,1.0);//evt.EventWeight);
	}
	  
	  my_leptons elec_4Overlap;
	  elec_4Overlap.num_leptons = 0;
	  for (int eli = 0; eli < evt.NEl; eli++) 
		if( (is_baseline_electron(&evt, eli) && evt.El_passOR[eli]) || !applyOR)
		  {
			elec_4Overlap.index[elec_4Overlap.num_leptons] = eli;
			elec_4Overlap.m[elec_4Overlap.num_leptons] = electron_mass;
			elec_4Overlap.E[elec_4Overlap.num_leptons] = evt.El_E[eli];
			elec_4Overlap.pT[elec_4Overlap.num_leptons] = evt.El_pT[eli];
			elec_4Overlap.phi[elec_4Overlap.num_leptons] = evt.El_phi[eli];
			elec_4Overlap.eta[elec_4Overlap.num_leptons] = evt.El_eta[eli];
			elec_4Overlap.SFw[elec_4Overlap.num_leptons] = evt.El_SFwTightLH[eli];
			elec_4Overlap.is_electron[elec_4Overlap.num_leptons] = true;
			elec_4Overlap.charge[elec_4Overlap.num_leptons] = evt.El_charge[eli];
			elec_4Overlap.num_leptons++;
		  }
	  
	  lep_baseline.num_leptons = 0;
	  for (int eli = 0; eli < elec_4Overlap.num_leptons ; eli++)
		if( (!electron_overlapsdR_jet(&evt, elec_4Overlap.index[eli], &jet)) ||  !applyOR )
		  {
			lep_baseline.index[lep_baseline.num_leptons] = elec_4Overlap.index[eli];
			lep_baseline.m[lep_baseline.num_leptons] = electron_mass;
			lep_baseline.E[lep_baseline.num_leptons] = elec_4Overlap.E[eli];
			lep_baseline.pT[lep_baseline.num_leptons] = elec_4Overlap.pT[eli];
			lep_baseline.phi[lep_baseline.num_leptons] = elec_4Overlap.phi[eli];
			lep_baseline.eta[lep_baseline.num_leptons] = elec_4Overlap.eta[eli];
			lep_baseline.SFw[lep_baseline.num_leptons] = elec_4Overlap.SFw[eli];
			lep_baseline.is_electron[lep_baseline.num_leptons] = true;
			lep_baseline.charge[lep_baseline.num_leptons] = elec_4Overlap.charge[eli];
			lep_baseline.num_leptons++;
		  }

	  my_leptons muon_4Overlap;
	  muon_4Overlap.num_leptons = 0;
	  for (int mui = 0; mui < evt.NMu; mui++) 
		if( (is_baseline_muon(&evt, mui) && evt.Mu_passOR[mui]) || !applyOR )
		  {
			muon_4Overlap.index[muon_4Overlap.num_leptons] = mui;
			muon_4Overlap.m[muon_4Overlap.num_leptons] = muon_mass;
			muon_4Overlap.pT[muon_4Overlap.num_leptons] = evt.Mu_pT[mui];
			muon_4Overlap.phi[muon_4Overlap.num_leptons] = evt.Mu_phi[mui];
			muon_4Overlap.eta[muon_4Overlap.num_leptons] = evt.Mu_eta[mui];
			muon_4Overlap.SFw[muon_4Overlap.num_leptons] = evt.Mu_SFw[mui];
			muon_4Overlap.is_electron[muon_4Overlap.num_leptons] = false;
			muon_4Overlap.charge[muon_4Overlap.num_leptons] = evt.Mu_charge[mui];
			muon_4Overlap.num_leptons++;
		  }
 
	  for (int mui = 0; mui < muon_4Overlap.num_leptons ; mui++)
		if( (!muon_overlapsdR_jet(&evt, muon_4Overlap.index[mui], &jet)) ||  !applyOR )
		  {
			lep_baseline.index[lep_baseline.num_leptons] = muon_4Overlap.index[mui];
			lep_baseline.m[lep_baseline.num_leptons] = muon_mass;
			lep_baseline.pT[lep_baseline.num_leptons] = muon_4Overlap.pT[mui];
			lep_baseline.phi[lep_baseline.num_leptons] = muon_4Overlap.phi[mui];
			lep_baseline.eta[lep_baseline.num_leptons] = muon_4Overlap.eta[mui];
			lep_baseline.SFw[lep_baseline.num_leptons] = muon_4Overlap.SFw[mui];
			lep_baseline.is_electron[lep_baseline.num_leptons] = false;
			lep_baseline.charge[lep_baseline.num_leptons] = muon_4Overlap.charge[mui];
			lep_baseline.num_leptons++;
		  }

	}
	// End Overlap Removal

 

	// jet cleaning; check all eta
	bool nobadjet = true;
	for (int jetk = 0; jetk < jet.num_jets; jetk++)
	  nobadjet &= (evt.Jet_quality[jet.index[jetk]] == 0);
	
	if(!nobadjet )
	  continue;

	cut_flow->Fill(7.1,1.0);//evt.EventWeight);

	my_jets jet_signal;
	jet_signal.num_jets = 0;
	for (int jeti = 0; jeti < jet.num_jets; jeti++)
	  if(is_signal_jet(&evt, jet.index[jeti]))
		{
		  jet_signal.index[jet_signal.num_jets] = jet.index[jeti];
		  jet_signal.E[jet_signal.num_jets] =  jet.E[jeti];
		  jet_signal.pT[jet_signal.num_jets] =  jet.pT[jeti];
		  jet_signal.eta[jet_signal.num_jets] =  jet.eta[jeti];
		  jet_signal.phi[jet_signal.num_jets] =  jet.phi[jeti];
		  jet_signal.MV2c20[jet_signal.num_jets] = jet.MV2c20[jeti];
		  jet_signal.num_jets++;
		}

	my_jets bjet_signal;
	bjet_signal.num_jets = 0;
	for (int jeti = 0; jeti < jet.num_jets; jeti++)
	  if(is_signal_bjet(&evt, jet.index[jeti])){
		bjet_signal.index[bjet_signal.num_jets] = jet.index[jeti];
		bjet_signal.E[bjet_signal.num_jets] =  jet.E[jeti];
		bjet_signal.pT[bjet_signal.num_jets] =  jet.pT[jeti];
		bjet_signal.eta[bjet_signal.num_jets] =  jet.eta[jeti];
		bjet_signal.phi[bjet_signal.num_jets] =  jet.phi[jeti];
		bjet_signal.MV2c20[bjet_signal.num_jets] = jet.MV2c20[jeti];
		bjet_signal.num_jets++;
	  }

	int n_jets_50 = 0;
	for (int jeti = 0; jeti < jet_signal.num_jets; jeti++)
	  if(jet_signal.pT[jeti]>50000)
		n_jets_50++;

	int n_jets_25 = 0;
	for (int jeti = 0; jeti < jet_signal.num_jets; jeti++)
	  if(jet_signal.pT[jeti]>25000)
		n_jets_25++;

	int n_jets_30 = 0;
	for (int jeti = 0; jeti < jet_signal.num_jets; jeti++)
	  if(jet_signal.pT[jeti]>30000)
		n_jets_30++;

	int n_jets_35 = 0;
	for (int jeti = 0; jeti < jet_signal.num_jets; jeti++)
	  if(jet_signal.pT[jeti]>35000)
		n_jets_35++;

	int n_jets_40 = 0;
	for (int jeti = 0; jeti < jet_signal.num_jets; jeti++)
	  if(jet_signal.pT[jeti]>40000)
		n_jets_40++;
	
	int n_bjets = bjet_signal.num_jets;
	
	if(cutflow){
	  if(jet_signal.num_jets <1)
		continue;
	}

	cut_flow->Fill(8.1,1.0);//evt.EventWeight);

	//sort leptons
	sortLeptons(&lep_baseline);
  
	// cosmic veto
	bool nocosmicveto = NoCosmicMuon(&evt, &lep_baseline);
	if(!nocosmicveto)
	  continue;
	cut_flow->Fill(9.1,1.0);//evt.EventWeight);	


	// >=2 baseline leptons
	if( (lep_baseline.num_leptons) <2)
	  continue;
	cut_flow->Fill(10.1,1.0);//evt.EventWeight);


	my_leptons lep_signal;
	lep_signal.num_leptons = 0;	
	for (int lepi = 0; lepi < lep_baseline.num_leptons; lepi++)
	  if(((is_signal_electron(&evt, lep_baseline.index[lepi]) && lep_baseline.is_electron[lepi]) || (is_signal_muon(&evt, lep_baseline.index[lepi]) && !lep_baseline.is_electron[lepi])))
		{
		  lep_signal.index[lep_signal.num_leptons] = lep_baseline.index[lepi];
		  lep_signal.m[lep_signal.num_leptons] = lep_baseline.m[lepi];
		  if(lep_baseline.is_electron[lepi])
			lep_signal.E[lep_signal.num_leptons] = lep_baseline.E[lepi];
		  lep_signal.pT[lep_signal.num_leptons] = lep_baseline.pT[lepi];
		  lep_signal.phi[lep_signal.num_leptons] = lep_baseline.phi[lepi];
		  lep_signal.eta[lep_signal.num_leptons] = lep_baseline.eta[lepi];
		  lep_signal.SFw[lep_signal.num_leptons] = lep_baseline.SFw[lepi];
		  lep_signal.is_electron[lep_signal.num_leptons] = lep_baseline.is_electron[lepi];
		  lep_signal.charge[lep_signal.num_leptons] = lep_baseline.charge[lepi];
		  lep_signal.num_leptons++;
		}
	lep_signal.num_leptons_baseline = lep_baseline.num_leptons;
	  
	int num20GeVLept = 0;
	for (int lepi = 0; lepi < lep_signal.num_leptons; lepi++)
	  if(lep_signal.pT[lepi] > LeptPt){
		num20GeVLept++;
	  }

	int num10GeVLept = 0;
	for (int lepi = 0; lepi < lep_signal.num_leptons; lepi++)
	  if(lep_signal.pT[lepi] > 10000){
		num10GeVLept++;
	  }

	int numLept = 0;
	for (int lepi = 0; lepi < lep_signal.num_leptons; lepi++)
	  {
		numLept++;
	  }

	//	if(numLept < 2) // 10GeV
	//continue;

	if(num20GeVLept < 2)
	  continue;

	if(cutflow){	
	// >=2 signal leptons with pT > 20 GeV
	  //	if(num10GeVLept < 2)
	  //	  continue;
	if(num20GeVLept < 2)
	  continue;
	cut_flow->Fill(11.1,1.0);//evt.EventWeight);
	}

	//sort jets
	sortJets(&jet_signal);
	sortJets(&bjet_signal);

	// classify jets
	//	classify_jets(&evt, &jet_signal);
	//	for (int jeti = 0; jeti < bjet_signal.num_jets; jeti++){
	//	  bjet_signal.is_btype_jet[jeti] = false;
	//	}
	//	for (int jeti = 0; jeti < bjet_signal.num_jets; jeti++){
	//	  std::cout << "before jet" << jeti << ", " << bjet_signal.is_btype_jet[jeti] << std::endl;
	//	}
	classify_jets(&evt, &bjet_signal);
	//	for (int jeti = 0; jeti < bjet_signal.num_jets; jeti++){
	//	  std::cout << "after jet" << jeti << ", " << bjet_signal.is_btype_jet[jeti] << std::endl;
	//	}
	//	std::cout << std::endl;

	// Event contains Z
	containsZ(&evt, &lep_signal);
	dilepton_mass_comb(&evt, &lep_signal);

	// Separate events into ee em mm
	SetChannelSeparation(&lep_signal);

	// Determine fake and charge flipped leptons
	classify_leptons(&evt, &lep_signal);

	//	classify_leptons_custom(&evt, &lep_signal);
	//	if(isCFSource){
	//	classify_leptons_custom(&evt, &lep_signal);
	//	}


	// Trigger matching
	if(!cutflow){
	  if(!checkTriggerMatching(&evt, &lep_signal))
		continue;
	}

	// same sign
	if(cutflow){
	  if(!lep_signal.has_ss)
		continue;
	}
	cut_flow->Fill(12.1,1.0);//evt.EventWeight);	
	
	/*	if(checkTriggerMatching(&evt, &lep_signal))
		std::cout << evt.EventNumber << std::endl;*/

	//miss-Et variables
	float mis_Ex = evt.Etmiss_TST_Etx;
	float mis_Ey = evt.Etmiss_TST_Ety;
	float met = sqrt(mis_Ex * mis_Ex + mis_Ey * mis_Ey);
  
	// General Selection  -- ends here
	// At this stage i have signal leptons, jets, and bjets, met
	//-----------------------------------------------------------------------
	
	//-----------------------------------------------------------------------	
	// Analyzer
	//-----------------------------------------------------------------------		
	if(lep_signal.has_ss){
	  // ee cut-flow 
	  if(lep_signal.has_ee){
		cut_flow_ee_ss->Fill(0.1,1.0);//evt.EventWeight);
		// Trigger matching
		if(checkTriggerMatching(&evt, &lep_signal)){
		  cut_flow_ee_ss->Fill(1.1,1.0);//evt.EventWeight);
		  if(bjet_signal.num_jets>0){
			cut_flow_ee_ss->Fill(2.1,1.0);//evt.EventWeight);
			if(n_jets_50>3){
			  cut_flow_ee_ss->Fill(3.1,1.0);//evt.EventWeight);
			  if(met>125000){
				cut_flow_ee_ss->Fill(4.1,1.0);//evt.EventWeight);
			  }
			}
		  }
		}
	  }
	}
	
	// em cut-flow 
	if(lep_signal.has_em){
	  cut_flow_em_ss->Fill(0.1,1.0);//evt.EventWeight);
	  // Trigger matching
	  if(checkTriggerMatching(&evt, &lep_signal)){
		//		std::cout << evt.EventNumber << std::endl;
		cut_flow_em_ss->Fill(1.1,1.0);//evt.EventWeight);
		if(bjet_signal.num_jets>0){
		  cut_flow_em_ss->Fill(2.1,1.0);//evt.EventWeight);
		  if(n_jets_50>3){
			cut_flow_em_ss->Fill(3.1,1.0);//evt.EventWeight);
			if(met>125000){
			  cut_flow_em_ss->Fill(4.1,1.0);//evt.EventWeight);
			}
		  }
		}
	  }
	}
	  
	// mm cut-flow 
	if(lep_signal.has_mm){
	  cut_flow_mm_ss->Fill(0.1,1.0);//evt.EventWeight);
	  // Trigger matching
	  if(checkTriggerMatching(&evt, &lep_signal)){
		//		std::cout << evt.EventNumber << std::endl;
		cut_flow_mm_ss->Fill(1.1,1.0);//evt.EventWeight);
		if(bjet_signal.num_jets>0){
		  cut_flow_mm_ss->Fill(2.1,1.0);//evt.EventWeight);
		  if(n_jets_50>3){
			cut_flow_mm_ss->Fill(3.1,1.0);//evt.EventWeight);			 
			//met>150
			if(met>125000){
			  cut_flow_mm_ss->Fill(4.1,1.0);//evt.EventWeight);
			}
		  }
		}
	  }
	}

	/*	debug_jet(&evt, &jet_signal);
	for (int jeti = 0; jeti < jet_signal.num_jets; jeti++)
	  {
		std::cout << "jet" << jeti << ", pt=" << jet_signal.pT[jeti] << ", Jet_partonTruthLabel=" << evt.Jet_PartonTruthLabel[jet_signal.index[jeti]] << ", Jet_ConeTruthLabel=" << evt.Jet_ConeTruthLabel[jet_signal.index[jeti]] << ", Jet_HadronConeExclTruthLabel=" << evt.Jet_HadronConeExclTruthLabel[jet_signal.index[jeti]]<< std::endl;
	  }

	for (int ijet=0; ijet<evt.NJet; ijet++){
	  std::cout << "truth jet" << ijet << ", pt=" <<  evt.Jet_pT[ijet] << ", TruthJet_ConeTruthLabel=" << evt.TruthJet_ConeTruthLabel[ijet] << ", TruthJet_PartonTruthLabel=" << evt.TruthJet_PartonTruthLabel[ijet] << std::endl;
	  }
	*/

	/*
	if(evt.EventNumber == 4019390311 ||evt.EventNumber == 917547813 ||evt.EventNumber == 400536526 || evt.EventNumber == 5212515109)
	  {	
		std::cout << "EventNumber=" << evt.EventNumber << std::endl;  
		debug_SR_VR(&evt, &lep_signal, &jet_signal, &bjet_signal, fp, false);
		}*/
	

	//-----------------------------------------------------------------------	
	//-----------------------------------------------------------------------	
	// SS/3L
	//-----------------------------------------------------------------------		
	//-----------------------------------------------------------------------	
  
	bool is_SR =  false;
	bool is_SR_veto =  false;
	bool is_VR = false;

	//effective mass and HT
	//-----------------------------------------------------------------------
	double meff = 0;
	double ht = 0;
	double sum_bjet_pt = 0;	
	double sum_jet_pt = 0;	
	double sum_lep_pt = 0;	

	// leptons pt
	for (int i = 0; i < lep_signal.num_leptons; i++) {
	  meff += lep_signal.pT[i];
	  sum_lep_pt += lep_signal.pT[i];
	}
	
	// jets pt
	for (int i = 0; i < jet_signal.num_jets; i++) {
	  meff += jet_signal.pT[i];
	  sum_jet_pt += jet_signal.pT[i];
	}

	// b-jets pt
	for (int i = 0; i < bjet_signal.num_jets; i++) {
	  sum_bjet_pt += bjet_signal.pT[i];
	}

	ht = meff;
	
	if(ht){} // suppress warning unused ht

	meff += met;

 // calculate deltaR lep, jet:
  double deltaR_lep_jet[2] = { 5., 5.};
  double  dR = 10.;
  for (int jeti = 0; jeti < jet_signal.num_jets; jeti++)
    if(jet_signal.pT[jeti]>25000)
	  if(lep_signal.num_leptons >1)
		for (int lepj = 0; lepj < 2; lepj++) {
		  dR = DeltaR(jet_signal.eta[jeti], jet_signal.phi[jeti], lep_signal.eta[lepj], lep_signal.phi[lepj]);
		  if (dR < deltaR_lep_jet[lepj])
			deltaR_lep_jet[lepj] = dR;
		}

 // calculate deltaR lep, lep:
  double deltaR_lep_lep = 5.;
  double  dRl = 10.;
  for (int lepi = 0; lepi < lep_signal.num_leptons; lepi++)
		for (int lepj = lepi+1; lepj < lep_signal.num_leptons; lepj++) {
		  dRl = DeltaR(lep_signal.eta[lepi], lep_signal.phi[lepi], lep_signal.eta[lepj], lep_signal.phi[lepj]);
		  if (dRl < deltaR_lep_lep)
			deltaR_lep_lep = dRl;
		}

	bool el_eta137=true;
	for (int lepi = 0; lepi < 2; lepi++)
	  if(lep_signal.is_electron[lepi])
		el_eta137 &= fabs(lep_signal.eta[lepi])<1.37;
	  
	int count_Ncharge = 0;
	for (int lepi = 0; lepi < lep_signal.num_leptons; lepi++)
	  if(lep_signal.charge[lepi]<0)
		count_Ncharge++;
	

	// variables: n_jets, n_bjets, meff, met

	//  Signal regions
	//-----------------------------------------------------------------------	

	//	if(evt.isMC) {

	bool SR3L0b1 = (num20GeVLept >= 2 && lep_signal.has_ss && numLept >= 3 && n_bjets == 0 && n_jets_40 >= 4 && met > 200000  && meff > 600000 );
	if(SR3L0b1){
	  is_SR = true; is_SR_veto = true;
	  fprintf(fp,"SR3L0b1 ");
	  count_SR3L0b1++;			
		signal_region->Fill(15.1,evt.EventWeight);
	}

	count_ALL++;

	signal_region->Fill(0.1,evt.EventWeight);

	bool SR3L0b2 = (num20GeVLept >= 2 && lep_signal.has_ss && numLept >= 3 && n_bjets == 0 && n_jets_40 >= 4 && met > 200000 && meff > 1600000);
	if(SR3L0b2){
		is_SR = true; is_SR_veto = true;
		fprintf(fp,"SR3L0b2 ");
		count_SR3L0b2++;			
		signal_region->Fill(14.1,evt.EventWeight);
	}  

	  bool SR3L1b1 = (num20GeVLept >= 2 && lep_signal.has_ss && numLept >= 3 && n_bjets >= 1 && n_jets_40 >= 4 && met > 200000  && meff > 600000 );
	  if(SR3L1b1){
		is_SR = true; is_SR_veto = true;
		fprintf(fp,"SR3L1b1 ");
		count_SR3L1b1++;			
		signal_region->Fill(18.1,evt.EventWeight);
	  }  

	  bool SR3L1b2 = (num20GeVLept >= 2 && lep_signal.has_ss && numLept >= 3 && n_bjets >= 1 && n_jets_40 >= 4 && met > 200000 && meff > 1600000);
	  if(SR3L1b2){
		is_SR = true; is_SR_veto = true;
		fprintf(fp,"SR3L1b2 ");
		count_SR3L1b2++;	
		signal_region->Fill(17.1,evt.EventWeight);		
	  }  

	  bool SR0b1 = (num20GeVLept >= 2 && lep_signal.has_ss && n_bjets == 0 && n_jets_25 >= 6  && met > 150000 && met/meff > 0.25);
	  if(SR0b1){
		is_SR = true; is_SR_veto = true;
		fprintf(fp,"SR0b1 ");
		count_SR0b1++;			
		signal_region->Fill(7.1,evt.EventWeight);
	  }  

	  bool SR0b2 = (num20GeVLept >= 2 && lep_signal.has_ss && n_bjets == 0 && n_jets_40 >= 6  && met > 250000 && meff > 900000 );
	  if(SR0b2){
		is_SR = true; is_SR_veto = true;
		fprintf(fp,"SR0b2 ");
		count_SR0b2++;		
		signal_region->Fill(6.1,evt.EventWeight);	
	  }  

	  bool SR1b1 = (num20GeVLept >= 2 && lep_signal.has_ss && n_bjets >= 1 && n_jets_25 >= 6  && met > 0 && meff > 600000 && met/meff > 0.25 );
	  if(SR1b1){
		is_SR = true; is_SR_veto = true;
		fprintf(fp,"SR1b1 ");
		count_SR1b1++;		
		signal_region->Fill(9.1,evt.EventWeight);	
	  }  

	  bool SR1b2 = (num20GeVLept >= 2 && lep_signal.has_ss && n_bjets >= 1 && n_jets_25 >= 6  && met > 250000 && meff > 0 && met/meff > 0.2 );
	  if(SR1b2){
		is_SR = true; is_SR_veto = true;
		fprintf(fp,"SR1b2 ");
		count_SR1b2++;		
		signal_region->Fill(8.1,evt.EventWeight);	
	  }  

	  bool SR3b1 = (num20GeVLept >= 2 && lep_signal.has_ss && n_bjets >= 3 && n_jets_25 >= 6 && met > 150000 && meff > 0 && met/meff > 0.2);
	  if(SR3b1){
		//		is_SR = true; is_SR_veto = true;
		fprintf(fp,"SR3b1 ");
		count_SR3b1++;			
	  }

	  bool SR3b2 = (num20GeVLept >= 2 && lep_signal.has_ss && n_bjets >= 3 && n_jets_25 >= 6 && met > 250000 && meff > 1200000 && met/meff > 0);
	  if(SR3b2){
		//		is_SR = true; is_SR_veto = true;
		fprintf(fp,"SR3b2 ");
		count_SR3b2++;			
	  }


	  /*	  if(evt.EventNumber == 2984910099)
		{
		  debug_objects(&evt, &lep_baseline, &jet_signal, fp, false); 
		  debug_SR_VR(&evt, &lep_signal, &jet_signal, &bjet_signal, fp, false);
		  }*/

	  bool SRlow = (lep_signal.has_ss && 20000 < lep_signal.pT[0] &&  lep_signal.pT[0] < 100000 && 10000 < lep_signal.pT[1]  &&   n_bjets >= 2 && n_jets_25 >= 6 && met > 200000 && meff > 600000 && met/meff > 0.25);
	  if(SRlow){
		is_SR = true; is_SR_veto = true;
		//		std::cout << "SRlow " << evt.EventNumber << std::endl;
		fprintf(fp,"SRlow ");
		count_SRlow++;			
		signal_region->Fill(13.1,evt.EventWeight);
	  }

	  bool SRhigh = (lep_signal.has_ss && 20000 < lep_signal.pT[0] &&  lep_signal.pT[0] < 100000 && 10000 < lep_signal.pT[1] &&  n_bjets >= 1 && n_jets_25 >= 6 && met > 100000 && meff > 0 && met/meff > 0.3);
	  if(SRhigh){
		is_SR = true; is_SR_veto = true;
		//		std::cout << "SRhigh " << evt.EventNumber << std::endl;
		fprintf(fp,"SRhigh ");
		count_SRhigh++;		
		signal_region->Fill(12.1,evt.EventWeight);	
	  }

	  bool SR1b_3LSS = (num20GeVLept >= 2 && lep_signal.has_ss && lep_signal.has_3lss && n_bjets >= 1 && !lep_signal.has_Z_SS_ee);
	  if(SR1b_3LSS){
		//		is_SR = true; is_SR_veto = true;
		fprintf(fp,"SR1b_3LSS ");
		count_SR1b_3LSS++;			
		signal_region->Fill(16.1,evt.EventWeight);
	  }

	  //	  bool SR1b_DD_low = (lep_signal.has_ss && n_bjets >= 1 && n_jets_50 >= 4  && met > 0 && meff > 1200000 && count_Ncharge >= 2);
	  bool SR1b_DD_low = (num20GeVLept >= 2 && lep_signal.has_ss && n_bjets >= 1 && n_jets_50 >= 4  && met > 0 && meff > 1200000 );
	  if(SR1b_DD_low){
		is_SR_veto = true;
		if(count_Ncharge >= 2){
		is_SR = true; 
		fprintf(fp,"SR1b_DD_low ");
		count_SR1b_DD_low++;			
		signal_region->Fill(22.1,evt.EventWeight);
		}
	  }

	  //	  bool SR1b_DD_high = (lep_signal.has_ss && n_bjets >= 1 && n_jets_50 >= 4  && met > 0 && meff > 1800000 && count_Ncharge >= 2);
	  bool SR1b_DD_high = (num20GeVLept >= 2 && lep_signal.has_ss && n_bjets >= 1 && n_jets_50 >= 4  && met > 0 && meff > 1800000 );
	  if(SR1b_DD_high){
		is_SR_veto = true;
		if( count_Ncharge >= 2 ){
		  is_SR = true;
		  fprintf(fp,"SR1b_DD_high ");
		  count_SR1b_DD_high++;
		  signal_region->Fill(21.1,evt.EventWeight);			
		}
	  }

	  //	  bool SR3b_DD = (lep_signal.has_ss && n_bjets >= 3 && n_jets_50 >= 3  && met > 0 && meff > 1200000 && count_Ncharge >= 2);
	  bool SR3b_DD = (num20GeVLept >= 2 && lep_signal.has_ss && n_bjets >= 3 && n_jets_50 >= 3  && met > 0 && meff > 1200000 );
	  if(SR3b_DD){
		//		is_SR_veto = true;
		if(count_Ncharge >= 2){
		  //		  is_SR = true; 
		  fprintf(fp,"SR3b_DD ");
		  count_SR3b_DD++;	
		}
	  }

	  bool SR1b_GG = (num20GeVLept >= 2 && lep_signal.has_ss && n_bjets >= 1 && n_jets_50 >= 6  && met > 0 && meff > 2200000);
	  if(SR1b_GG){
		is_SR = true; is_SR_veto = true;
		fprintf(fp,"SR1b_GG ");
		count_SR1b_GG++;	
		signal_region->Fill(20.1,evt.EventWeight);				
	  }


	  //	  bool SRRPV0b = (lep_signal.has_ss && numLept == 2 && n_bjets == 0 && n_jets_40 >= 6  && ht > 1500000 && !lep_signal.has_Z_OS );
	  bool SRRPV0b = (num20GeVLept >= 2 && lep_signal.has_ss && numLept == 2 && n_bjets == 0 && n_jets_40 >= 6  && meff > 1800000 );
	  if(SRRPV0b){
		is_SR_veto = true;
		if(  !lep_signal.has_Z_SS_ee ){
		is_SR = true;
		fprintf(fp,"SRRPV0b ");
		count_SRRPV0b++;	
		signal_region->Fill(19.1,evt.EventWeight);			
		}	
	  }

	  //	  bool SRRPV3b = (lep_signal.has_ss && n_bjets >= 3 && n_jets_40 >= 6  && ht > 1500000 && !lep_signal.has_Z_OS );
	  bool SRRPV3b = (num20GeVLept >= 2 &&  lep_signal.has_ss && n_bjets >= 3 && n_jets_40 >= 6  && meff > 1800000 );
	  if(SRRPV3b){
		//		is_SR_veto = true;
		if(  !lep_signal.has_Z_SS_ee ){ 
		  //		  is_SR = true; 
		fprintf(fp,"SRRPV3b ");
		count_SRRPV3b++;		
		}	
	  }

	  bool Rpc2L2bS = (num20GeVLept >= 2 && lep_signal.has_ss && n_bjets >= 2 && n_jets_25 >= 6 && met > 200000 && meff > 600000 && met/meff > 0.25);
	  if(Rpc2L2bS){
		is_SR = true; is_SR_veto = true;
		fprintf(fp,"Rpc2L2bS ");
		count_Rpc2L2bS++;			
		signal_region->Fill(11.1,evt.EventWeight);		
	  }

	  bool Rpc2L2bH = (num20GeVLept >= 2 && lep_signal.has_ss && n_bjets >= 2 && n_jets_25 >= 6 && met > 0 && meff > 1800000 && met/meff > 0.15);
	  if(Rpc2L2bH){
		is_SR = true; is_SR_veto = true;	
		  fprintf(fp,"Rpc2L2bH ");
		  count_Rpc2L2bH++;	
		  signal_region->Fill(10.1,evt.EventWeight);				
		}
	  
	  bool Rpv2L2bS = (num20GeVLept >= 2 && lep_signal.has_ss && n_bjets >= 2 && n_jets_50 >= 3 && meff > 1200000);
	  if(Rpv2L2bS){
		is_SR_veto = true;
		if(count_Ncharge >= 2){
		  is_SR = true;
		  fprintf(fp,"Rpv2L2bS ");
		  count_Rpv2L2bS++;		
		  signal_region->Fill(24.1,evt.EventWeight);			
		}
	  }

	  bool Rpv2L2bH = (num20GeVLept >= 2 && lep_signal.has_ss && n_bjets >= 2 && n_jets_40 >= 6 && meff > 2000000 );
	  if(Rpv2L2bH){
		is_SR_veto = true;
			if(  !lep_signal.has_Z_SS_ee ){ 
		  is_SR = true;
		  fprintf(fp,"Rpv2L2bH ");
		  count_Rpv2L2bH++;		
		  signal_region->Fill(23.1,evt.EventWeight);			
		}
	  }
 
	  if(is_SR)
		fprintf(fp,"-> runNr = %d, evNr = %llu, ", evt.RunNb, evt.EventNumber);

	  //	}
  
	// N-1 regions
	bool SR3L0b1mMET = (lep_signal.has_ss && numLept >= 3 && n_bjets == 0 && n_jets_40 >= 4 && meff > 600000 );
	if(SR3L0b1mMET){
	  fprintf(fpd,"SR3L0b1mMET -> * evNr = %llu, RunNb = %d, met = %.2f\n", evt.EventNumber,evt.RunNb,met/1000.);
	}

	bool SR3L0b2mMET = (lep_signal.has_ss && numLept >= 3 && n_bjets == 0 && n_jets_40 >= 4 && meff > 1600000);
	if(SR3L0b2mMET){
	  fprintf(fpd,"SR3L0b2mMET -> * evNr = %llu, RunNb = %d, met = %.2f\n", evt.EventNumber,evt.RunNb,met/1000.);
	}

	bool SR3L1b1mMET = (lep_signal.has_ss && numLept >= 3 && n_bjets >= 1 && n_jets_40 >= 4 && meff > 600000 );
	if(SR3L1b1mMET){
	  fprintf(fpd,"SR3L1b1mMET -> * evNr = %llu, RunNb = %d, met = %.2f\n", evt.EventNumber,evt.RunNb,met/1000.);
	}

	bool SR3L1b2mMET = (lep_signal.has_ss && numLept >= 3 && n_bjets >= 1 && n_jets_40 >= 4 && meff > 1600000);
	if(SR3L1b2mMET){
	  fprintf(fpd,"SR3L1b2mMET -> * evNr = %llu, RunNb = %d, met = %.2f\n", evt.EventNumber,evt.RunNb,met/1000.);
	}

	bool SR0b1mMET = (lep_signal.has_ss && n_bjets == 0 && n_jets_25 >= 6  && met/meff > 0.25);
	if(SR0b1mMET){
	  fprintf(fpd,"SR0b1mMET -> * evNr = %llu, RunNb = %d, met = %.2f\n", evt.EventNumber,evt.RunNb,met/1000.);
	}
  
	bool SR0b2mMET = (lep_signal.has_ss && n_bjets == 0 && n_jets_40 >= 6  && meff > 900000 );
	if(SR0b2mMET){
	  fprintf(fpd,"SR0b2mMET -> * evNr = %llu, RunNb = %d, met = %.2f\n", evt.EventNumber,evt.RunNb,met/1000.);
	}

	bool SR1b2mMET = (lep_signal.has_ss && n_bjets >= 1 && n_jets_25 >= 6  && meff > 0 && met/meff > 0.2 );
	if(SR1b2mMET){
	  fprintf(fpd,"SR1b2mMET -> * evNr = %llu, RunNb = %d, met = %.2f\n", evt.EventNumber,evt.RunNb,met/1000.);
	}
  
	bool SR3b1mMET = (lep_signal.has_ss && n_bjets >= 3 && n_jets_25 >= 6 && meff > 0 && met/meff > 0.2);
	if(SR3b1mMET){
	  fprintf(fpd,"SR3b1mMET -> * evNr = %llu, RunNb = %d, met = %.2f\n", evt.EventNumber,evt.RunNb,met/1000.);
	}

	bool SR3b2mMET = (lep_signal.has_ss && n_bjets >= 3 && n_jets_25 >= 6 && meff > 1200000 && met/meff > 0);
	if(SR3b2mMET){
	  fprintf(fpd,"SR3b2mMET -> * evNr = %llu, RunNb = %d, met = %.2f\n", evt.EventNumber,evt.RunNb,met/1000.);
	}

	bool SRlowmMET = (lep_signal.has_ss && 20000 < lep_signal.pT[0] &&  lep_signal.pT[0] < 100000 && 10000 < lep_signal.pT[1]  &&   n_bjets >= 2 && n_jets_25 >= 6 && meff > 600000 && met/meff > 0.25);
	if(SRlowmMET){
	  fprintf(fpd,"SRlow -> * evNr = %llu, RunNb = %d, met = %.2f\n", evt.EventNumber,evt.RunNb,met/1000.);
	}

	bool SRhighmMET = (lep_signal.has_ss && 20000 < lep_signal.pT[0] &&  lep_signal.pT[0] < 100000 && 10000 < lep_signal.pT[1] &&  n_bjets >= 1 && n_jets_25 >= 6 && meff > 0 && met/meff > 0.3);
	if(SRhighmMET){
	  fprintf(fpd,"SRhigh -> * evNr = %llu, RunNb = %d, met = %.2f\n", evt.EventNumber,evt.RunNb,met/1000.);
	}
	
	bool SRRPV0bmMeff = (num20GeVLept >= 2 && lep_signal.has_ss && numLept == 2 && n_bjets == 0 && n_jets_40 >= 6  && meff > 200000 && meff < 1800000 
						 &&  !lep_signal.has_Z_SS_ee);
	if(SRRPV0bmMeff){
	  fprintf(fpd,"SRRPV0bmMeff -> * evNr = %llu, RunNb = %d, meff = %.2f\n", evt.EventNumber,evt.RunNb,meff/1000.);
	  //	  printf("SRRPV0bmMeff -> * evNr = %llu, RunNb = %d, meff = %.2f\n", evt.EventNumber,evt.RunNb,meff/1000.);
	}
	
  

	// validation regions


	bool VRWW =  ( num20GeVLept >= 2 &&  lep_signal.has_ss && numLept == 2 && lep_baseline.num_leptons ==2 && n_bjets == 0  && n_jets_50 >= 2 && met > 55000 && meff > 650000 && lep_signal.pT[1] > 30000 
				   && (!lep_signal.has_Z || lep_signal.has_em || lep_signal.has_mm) && deltaR_lep_lep > 1.3 && deltaR_lep_jet[0] > 0.7 && deltaR_lep_jet[1] > 0.7 && !is_SR_veto );
	if(VRWW){
	  is_VR = true;
	  count_VRWW++;
	  fprintf(fp,"VRWW -> runNr = %d, evNr = %llu, ", evt.RunNb, evt.EventNumber);
	  signal_region->Fill(3.1,evt.EventWeight);		
	}
	
	bool VRWZ4j = ( num20GeVLept >= 2 &&  lep_signal.has_ss && numLept == 3  && lep_signal.num_leptons_baseline == 3 && n_bjets == 0 && n_jets_25 >= 4 && meff > 450000 && met/sum_lep_pt < 0.7 && !is_SR_veto );
	if(VRWZ4j){
	  is_VR = true;
	  count_VRWZ4j++;
	  fprintf(fp,"VRWZ4j -> runNr = %d, evNr = %llu, ", evt.RunNb, evt.EventNumber);
	  signal_region->Fill(4.1,evt.EventWeight);		
	}

	bool VRWZ5j = ( num20GeVLept >= 2 &&  lep_signal.has_ss && numLept == 3  && lep_signal.num_leptons_baseline == 3 && n_bjets == 0 && n_jets_25 >= 5 && meff > 450000 && met/sum_lep_pt < 0.7 && !is_SR_veto );
	if(VRWZ5j){
	  is_VR = true;
	  count_VRWZ5j++;
	  fprintf(fp,"VRWZ5j -> runNr = %d, evNr = %llu, ", evt.RunNb, evt.EventNumber);
	  signal_region->Fill(5.1,evt.EventWeight);		
	}
	
	bool VRttW = ( num20GeVLept >= 2 &&  lep_signal.has_ss && numLept == 2  && lep_baseline.num_leptons ==2 && n_bjets >= 1 && ((n_jets_40 >= 4 && (lep_signal.has_ee || lep_signal.has_em)) || (n_jets_25 >= 3 && lep_signal.has_mm)) && met > 45000 && meff > 550000 && lep_signal.pT[1] > 40000 && sum_bjet_pt / sum_jet_pt > 0.25  && !is_SR_veto );
	if(VRttW){
	  is_VR = true;
	  count_VRttW++;
	  fprintf(fp,"VRttW -> runNr = %d, evNr = %llu, ", evt.RunNb, evt.EventNumber);
	  signal_region->Fill(1.1,evt.EventWeight);		
	}
	
	//	if(evt.EventNumber == 4019390311)
	//	  std::cout <<  "is SR veto=" << is_SR_veto << std::endl;

	bool VRttZ = ( num20GeVLept >= 2 &&  lep_signal.has_ss && numLept >= 3 && n_bjets >= 1 && n_jets_35 >= 3 && meff > 450000 &&  lep_signal.has_Z_OS && !is_SR_veto );
	if(VRttZ){
	  is_VR = true;
	  count_VRttZ++;
	  fprintf(fp,"VRttZ -> runNr = %d, evNr = %llu, ", evt.RunNb, evt.EventNumber);
	  signal_region->Fill(2.1,evt.EventWeight);		
	}

	if( (is_SR || is_VR) && !evt.isMC)
	  fprintf(fp,"\n");

	// blind data for SR
	/*	if( is_SR && !evt.isMC)
		continue;*/
	
	//	if(!is_SR_veto &&  lep_signal.has_ss && n_jets_40 >= 2 && met > 50000 && n_bjets >= 1)
	//	  std::cout << "CR1b " << evt.RunNb << " " << evt.EventNumber << std::endl;

	//if(evt.EventNumber == 1000791561 || evt.EventNumber == 1986787007 || evt.EventNumber == 2932567041 || evt.EventNumber == 933421418 )
	// debug_SR_VR(&evt, &lep_signal, &jet_signal, &bjet_signal, fp, false);
	  

	//========================================================================
	// Main part of the analysis
	//========================================================================
	//	is_SR = true;	fprintf(fp,"-> runNr = %d, evNr = %llu, ", evt.RunNb, evt.EventNumber);
	if( (is_SR || is_VR) && evt.isMC){
	  fprintf(fp,"\t Weights: init = %f, ", evt.EventWeight);
	}

	//	if(lep_signal.has_em)
	//	  debugme=true;

	if(debugme){
	  fprintf(fpd,"* evNr = %llu\n", evt.EventNumber);
	  fprintf(fpd,"  EventWeight = %f", evt.EventWeight);
	}
	// Apply pileupwgh
	evt.EventWeight *= pileupwgh;

	// re-weighting
	if(evt.isMC){

	  // already applied prw
	if( (is_SR || is_VR) && evt.isMC)
		fprintf(fp," puW = %f, ", pileupwgh);

	  if(debugme)
		fprintf(fpd,"  PileUpWeigh = %f, ", pileupwgh);


	  // Cross sections
	  double weightXsection = 1.;
	  double XsecXeff = myXsection.xsectTimesEff(evt.ChannelNumber);	  

	  if( !GG && !BB && !strong )
		XsecXeff = myXsection.xsectTimesEff(evt.ChannelNumber);  
	  else if(GG)
		XsecXeff = myXsection.xsectTimesEff(evt.ChannelNumber,2);  
	  else if(BB)
		XsecXeff = myXsection.xsectTimesEff(evt.ChannelNumber,51);  
	  else if(strong){ // NUHM2
		XsecXeff = myXsection.xsectTimesEff(evt.ChannelNumber,2);  
	  }
	  if(XsecXeff>0)
		weightXsection = (luminosity*XsecXeff/evt.sumWeight);
	  else{
		weightXsection = -999.0;
		if(noXsection){
		  cout << "================0 weight=============" << std::endl;
		  std::cout << evt.ChannelNumber << " " <<  XsecXeff << " " << weightXsection << std::endl;
		  cout << "=====================================" << std::endl;
		  noXsection = false;
		}
	  }
	
	  static int lastChanNum = -99999;
	  if(lastChanNum != evt.ChannelNumber){
		std::cout << "ChannelNum " << evt.ChannelNumber << ", XsecXeff " << XsecXeff  << ", sumWeight " << evt.sumWeight << ", luminosity " << luminosity << ", weight " << weightXsection << ", FullSim " << is_FullSim(&evt) << std::endl;
		lastChanNum = evt.ChannelNumber;
	  }

	  evt.EventWeight *= weightXsection;
	  if(!newtree){
		Xsect=XsecXeff; 
		sumWeight=evt.sumWeight;
	  }
	if( (is_SR || is_VR) && evt.isMC)
		fprintf(fp," XsecW = %f (chNr = %d, XsecXeff = %f, sumWeight = %f, lumi = %f), ", weightXsection,  evt.ChannelNumber, XsecXeff, 
				evt.sumWeight, luminosity);
	  
	  double lepW = 1.;
	  double elW  = 1.;
	  double muW  = 1.;
	  
	  // lepton scale factors
	  for (int lepi = 0; lepi < lep_signal.num_leptons; lepi++)
		{
		  if(lep_signal.is_electron[lepi]) // electron scale factor
			{
			  if(evt.El_isMediumLH[lep_signal.index[lepi]]){
				//				if(is_SR || is_VR)
				//				  fprintf(fp," elW %d  pt = %f SF= %f IsoSF= %f", lepi, lep_signal.pT[lepi], evt.El_SFwMediumLH[lep_signal.index[lepi]], evt.El_IsoSFwMediumLH[lep_signal.index[lepi]],);

				float SFweightCFT = evt.El_SFweightCFT[lep_signal.index[lepi]];
				if(lep_signal.pT[lepi]<15000)
				  SFweightCFT =1.0;
				elW *= evt.El_SFwMediumLH[lep_signal.index[lepi]]*evt.El_IsoSFwMediumLH[lep_signal.index[lepi]]*SFweightCFT;
			  }
			  else
				elW *= 1.;
			  	if( (is_SR || is_VR) && evt.isMC)
				fprintf(fp," elW %d  pt = %f SF= %f IsoSF= %f ChargeFlipBDT medium=%f/loose=%f", lepi, lep_signal.pT[lepi], evt.El_SFwMediumLH[lep_signal.index[lepi]], evt.El_IsoSFwMediumLH[lep_signal.index[lepi]], evt.El_passChargeFlipTaggerBDTmedium[lep_signal.index[lepi]], evt.El_passChargeFlipTaggerBDTloose[lep_signal.index[lepi]]);

			  //			  if(evt.El_isMediumLH[lep_signal.index[lepi]]){
			  	if( (is_SR || is_VR) && evt.isMC)
				fprintf(fp," CFTweight=%f", evt.El_SFweightCFT[lep_signal.index[lepi]]);
			  //			  }
			} else {// muon scale factor
				if( (is_SR || is_VR) && evt.isMC)
			  fprintf(fp," muW %d pt = %f SF= %f IsoSF= %f, ", lepi,lep_signal.pT[lepi], evt.Mu_SFw[lep_signal.index[lepi]],evt.Mu_IsoSFw[lep_signal.index[lepi]]);
			muW *= evt.Mu_SFw[lep_signal.index[lepi]]*evt.Mu_IsoSFw[lep_signal.index[lepi]];	  
		  }
		}
	  
	  lepW = elW * muW;
	  evt.EventWeight *= lepW;

	  if( (is_SR || is_VR) && evt.isMC){
		fprintf(fp," elW FINAL= %f, ", elW);
		fprintf(fp," muW FINAL= %f, ", muW);
	  }

	  if(debugme){
		fprintf(fpd," WeightEventselSF= %f, ", elW);
		fprintf(fpd," WeightEventsmuSF= %f, ", muW);
	  }

	  double jetW = 1.;
	  double jetjvt = 1.;
	  for (int jeti = 0; jeti < jet_signal.num_jets; jeti++) 
		if(fabs(jet_signal.eta[jeti])<2.5){
		  jetW *= evt.Jet_SFw[jet_signal.index[jeti]]*evt.Jet_JVTsf[jet_signal.index[jeti]];
		  jetjvt *= evt.Jet_JVTsf[jet_signal.index[jeti]];
		}

	  evt.EventWeight *= jetW;

	  if( (is_SR || is_VR) && evt.isMC)
		fprintf(fp," jetW = %f, ", jetW);

		double dtW = 1;
	  bool passMET = false;
	  if( RunNum > 290000 && met>250000 && (evt.HLT_xe100_mht_L1XE50 || evt.HLT_xe110_mht_L1XE50)) passMET = true;
	  if( RunNum <= 290000 && met>250000 && evt.HLT_xe70) passMET = true;
	  bool failMET =  ( (RunNum <= 290000 && (met < 250000 || !evt.HLT_xe70))  || (RunNum > 290000 && (met < 250000 || (!evt.HLT_xe100_mht_L1XE50 && !evt.HLT_xe110_mht_L1XE50)))  );

	  if( failMET )
		{
		  if(passMET)
			std::cout << "Problem with MET selection for DileptonTriggerWeight in RunNum=" << RunNum << ", with met=" << met << std::endl;

		  /*
		  // lepton scale factors
		  for (int lepi = 0; lepi < lep_signal.num_leptons; lepi++)
			{
			  if(lep_signal.is_electron[lepi]) // electron scale factor
				dtwTool.AddElectron(lep_signal.pT[lepi],lep_signal.eta[lepi],RunNum, is_FullSim(&evt));
			  else // muon scale factor
				dtwTool.AddMuon(lep_signal.pT[lepi],lep_signal.eta[lepi],lep_signal.phi[lepi], RunNum);
			}

		  double uncertainty;
		  dtW = dtwTool.GetScaleFactor(uncertainty);
		  */
		  dtW = evt.TriggerDileptonSF; //dtwTool.GetScaleFactor(uncertainty);
		  //		  std::cout << evt.TriggerDileptonSF << std::endl;
		} else 
		dtW = 1.;

	  evt.EventWeight *= dtW;
	  
	  if( (is_SR || is_VR) && evt.isMC)
		fprintf(fp," dileptrigW = %f, ", dtW);	

	  if(debugme)
		fprintf(fpd," WeightEvents_trigger_dilep = %f, ", dtW);	


	  if(debugme)
		fprintf(fpd," WeightEventsJVT = %f\n", jetjvt);

	  // Z+jets 2.2 Weights
	  //	  if(  363364 < evt.ChannelNumber && evt.ChannelNumber < 363411 /*&& !isnan(evt.SherpaNjetWeight) */)
	  //		evt.EventWeight *= evt.SherpaNjetWeight;
		
	  if( (is_SR || is_VR) && evt.isMC)
		fprintf(fp," totalW = %f\n", evt.EventWeight);

	  if( (is_SR || is_VR) && evt.isMC)
		debug_SR_VR(&evt, &lep_signal, &jet_signal, &bjet_signal, fp, true);

	  event_weight_noXsec->Fill(evt.EventWeight/weightXsection,evt.EventWeight);
	  evtwgh_mu_noXsec->Fill(evt.AvgMu, evt.EventWeight/weightXsection,evt.EventWeight);
	}

	//-----------------------------------------------------------------------	
	if(cutflow)
	  if(lep_signal.has_ss){
		// ee cut-flow 
		if(lep_signal.has_ee){
		  weight_flow->Fill(0.1,evt.EventWeight);
		// Trigger matching
		if(checkTriggerMatching(&evt, &lep_signal))
		  weight_flow->Fill(1.1,evt.EventWeight);
		}
		if(lep_signal.has_em){
		  weight_flow->Fill(2.1,evt.EventWeight);
		  // Trigger matching
		  if(checkTriggerMatching(&evt, &lep_signal))
			weight_flow->Fill(3.1,evt.EventWeight);
		}
		if(lep_signal.has_mm){
		  weight_flow->Fill(4.1,evt.EventWeight);
		  // Trigger matching
		  if(checkTriggerMatching(&evt, &lep_signal))
			weight_flow->Fill(5.1,evt.EventWeight);
		}
	  }
	
	int ind_extraB = -1;
	int ind_extraC = -1;
	int ind_extraNone = -1;

	int index_realb = -1;
	int index_fakeb = -1;
	double yval = -1.;

	for (int jeti = 0; jeti < bjet_signal.num_jets; jeti++)
      if(!bjet_signal.is_btype_jet[jeti] )
		{
		  index_fakeb = jeti;
		  break;
		}

	if (index_fakeb >= 0) 
	  yval = 1;
	else
	  yval = 0;

	if(n_bjets >= 3){
	  // extraB extraC extraNone
	  // R F

  if (evt.extraB) 	  
		ttbarClass->Fill(0.,yval,evt.EventWeight);
	  else if (evt.extraC)
		ttbarClass->Fill(1.,yval,evt.EventWeight);
	  else 
		ttbarClass->Fill(2.,yval,evt.EventWeight);

	  if(lep_signal.has_os){
	  if (evt.extraB) 	  
		ttbarClass_OS->Fill(0.,yval,evt.EventWeight);
	  else if (evt.extraC)
		ttbarClass_OS->Fill(1.,yval,evt.EventWeight);
	  else 
		ttbarClass_OS->Fill(2.,yval,evt.EventWeight);
	  }

	  if(lep_signal.has_ss){
	  if (evt.extraB) 	  
		ttbarClass_SS3L->Fill(0.,yval,evt.EventWeight);
	  else if (evt.extraC)
		ttbarClass_SS3L->Fill(1.,yval,evt.EventWeight);
	  else 
		ttbarClass_SS3L->Fill(2.,yval,evt.EventWeight);
	  }

	}


	// Central value
	//-----------------------------------------------------------------------	
	if(!cutflow ){

	  // For Powheg samples Mll>60GeV
	  //	  if(dilepton_mass(&evt, &lep_signal) < 60000 && lep_signal.is_electron[lep_signal.ind1_Mll]==lep_signal.is_electron[lep_signal.ind2_Mll] ) continue;   
	  //	  if(dilepton_mass_ss(&evt, &lep_signal) < 60000  ) continue;   
	  
	  //	  if(lep_signal.has_os /*&& dilepton_mass_lead(&evt,&lep_signal)>12000*/)
	  //		FillHistos_Regions(ftag, "OS", &evt, &lep_signal, &jet_signal, &bjet_signal);
	  
	  /*
	  // Charge flip stuff
	  if(!lep_signal.has_ss && numLept == 2){
	  static double unc_misid[256];
	  static double chargeFlipWgtUp[256];
	  double sign = 1.;
	  double chargeFlipWgt = 0.;

	  if(lep_signal.has_ee){
	  int i0 = 0, i1 = 1;
	  chargeFlipWgt = sign*stdMxmTool.GetWeight_OStoSS_ElEl(lep_signal.eta[i0],lep_signal.pT[i0]*0.001,true, lep_signal.eta[i1],lep_signal.pT[i1]*0.001,true, unc_misid);
	  }
	  else if (lep_signal.has_em){
	  int i0 = (lep_signal.is_electron[0]?0:1);
	  chargeFlipWgt = sign*stdMxmTool.GetWeight_OStoSS_ElMu(lep_signal.eta[i0],lep_signal.pT[i0]*0.001,true, unc_misid);
	  }

	  std::cout << "chargeFlipWgt = " << chargeFlipWgt << ", Num of uncertainties: " << TwoLepSSFakeBkg::nErrorSources_OStoSS << std::endl;
	  double unc_misid_error = 0.0;
	  for(int k=0;k<TwoLepSSFakeBkg::nErrorSources_OStoSS;++k)
	  {
	  chargeFlipWgtUp[k] = chargeFlipWgt + unc_misid[k];
	  unc_misid_error = unc_misid[k]*unc_misid[k];
	  if(unc_misid[k] != 0)
	  std::cout << k << " --> " << unc_misid[k] << std::endl;
	  }
	  unc_misid_error = sqrt(unc_misid_error);
	  }*/

	  if(lep_signal.has_ss /*&& dilepton_mass(&evt, &lep_signal) > 60000*/){
		FillHistos_Regions(ftag, "SS3L", &evt, &lep_signal, &jet_signal, &bjet_signal);	
	  }

	  //	  if(evt.ChannelNumber == 361106 || evt.ChannelNumber == 361107 || evt.ChannelNumber == 361108)
	  //	   	if(dilepton_mass(&evt, &lep_signal) < 60000 && lep_signal.is_electron[lep_signal.ind1_Mll]==lep_signal.is_electron[lep_signal.ind2_Mll] ) continue; 
	  
	  //	  if(lep_signal.has_ss && numLept == 2){
	  //	   	FillHistos_Regions(ftag, "SS", &evt, &lep_signal, &jet_signal, &bjet_signal);	
	  //	  }
	  
	  //	if(lep_signal.has_ss && !lep_signal.has_Z)
	  //	  FillHistos_Regions(ftag, "SS3L_noZ", &evt, &lep_signal, &jet_signal, &bjet_signal);	

	  //	  if(lep_signal.has_ss && num20GeVLept == 2)
	  //		FillHistos_Regions(ftag, "SS", &evt, &lep_signal, &jet_signal, &bjet_signal);
	
	  //	  if(lep_signal.num_leptons > 2)
	  //		FillHistos_Regions(ftag, "3L", &evt, &lep_signal, &jet_signal, &bjet_signal);
	  
	  //	if(lep_signal.has_ss){
	  //	  FillHistos_Regions(ftag, "noPRW_SS3L", &evt, &lep_signal, &jet_signal, &bjet_signal);	
	  //	  evt.EventWeight *= pileupwgh;
	  //	  FillHistos_Regions(ftag, "PRW_SS3L", &evt, &lep_signal, &jet_signal, &bjet_signal);	
	  //	  averageIntPerXing_PRW_SS3L->Fill(evt.AvgMu, evt.EventWeight);
	  //	}
  
	  if(lep_signal.has_Z && lep_signal.num_leptons == 2){
		if(!lep_signal.has_ss){                                                                                                                  
		  num_OS+=evt.EventWeight;
		} else 
		  num_SS+=evt.EventWeight;
	  }
	}

	/*	  static int lastChanNum_log = lastChanNum;
		  if(lastChanNum_log != evt.ChannelNumber){
		  std::cout << "ChannelNum " << evt.ChannelNumber << ", lastchan " << lastChanNum <<  ", XsecXeff " << XsecXeff  << ", sumWeight " << evt.sumWeight << ", luminosity " << luminosity << ", weight " << weightXsection << std::endl;
		  lastChanNum_log = evt.ChannelNumber;
		  }*/


	if(newtree){
	  std::cout << treeno-1 << " " << oldfilename << ": scaled=" << scaled << "  raw=" << raw << "  Xsect=" << Xsect << "  sumWeight=" << sumWeight << "  processed=" << processed << "  luminosity " << luminosity << "\n";
	  printf("%d %s: scaled=%.2f  raw=%.0f  XsectXeff=%.2f  sumWeight=%.0f  processed=%d  luminosity=%.2f\n", treeno-1, oldfilename.Data(), hscaled->GetBinContent(1), hraw->GetBinContent(1), Xsect, sumWeight, processed, luminosity);
	  fprintf(fpy,"%d ALL %s: scaled=%.2f  raw=%.0f  XsectXeff=%.2f  sumWeight=%.0f \n", treeno-1, oldfilename.Data(), hscaled->GetBinContent(1), hraw->GetBinContent(1), Xsect, sumWeight);
	  fprintf(fpy,"%d SS %s: scaled=%.2f  raw=%.0f  XsectXeff=%.2f  sumWeight=%.0f \n", treeno-1, oldfilename.Data(), hscaled->GetBinContent(2), hraw->GetBinContent(2), Xsect, sumWeight);
	  fprintf(fpy,"%d SSee %s: scaled=%.2f  raw=%.0f  XsectXeff=%.2f  sumWeight=%.0f \n", treeno-1, oldfilename.Data(), hscaled->GetBinContent(3), hraw->GetBinContent(3), Xsect, sumWeight);
	  fprintf(fpy,"%d SSem %s: scaled=%.2f  raw=%.0f  XsectXeff=%.2f  sumWeight=%.0f \n", treeno-1, oldfilename.Data(), hscaled->GetBinContent(4), hraw->GetBinContent(4), Xsect, sumWeight);
	  fprintf(fpy,"%d SSmm %s: scaled=%.2f  raw=%.0f  XsectXeff=%.2f  sumWeight=%.0f \n", treeno-1, oldfilename.Data(), hscaled->GetBinContent(5), hraw->GetBinContent(5), Xsect, sumWeight);
	  fprintf(fpy,"%d OS %s: scaled=%.2f  raw=%.0f  XsectXeff=%.2f  sumWeight=%.0f \n", treeno-1, oldfilename.Data(), hscaled->GetBinContent(6), hraw->GetBinContent(6), Xsect, sumWeight);
	  fprintf(fpy,"%d OSee %s: scaled=%.2f  raw=%.0f  XsectXeff=%.2f  sumWeight=%.0f \n", treeno-1, oldfilename.Data(), hscaled->GetBinContent(7), hraw->GetBinContent(7), Xsect, sumWeight);
	  fprintf(fpy,"%d OSem %s: scaled=%.2f  raw=%.0f  XsectXeff=%.2f  sumWeight=%.0f \n", treeno-1, oldfilename.Data(), hscaled->GetBinContent(8), hraw->GetBinContent(8), Xsect, sumWeight);
	  fprintf(fpy,"%d OSmm %s: scaled=%.2f  raw=%.0f  XsectXeff=%.2f  sumWeight=%.0f \n", treeno-1, oldfilename.Data(), hscaled->GetBinContent(9), hraw->GetBinContent(9), Xsect, sumWeight);

	  raw=0; scaled=0; Xsect=0;sumWeight=0;processed=2;
	  hraw->Reset();
	  hscaled->Reset();
	  newtree=false;
	  oldfilename = filename;
	}

	raw += 1;
	scaled += evt.EventWeight;
  
	hraw->Fill(0.1, 1.0);
	hscaled->Fill(0.1, evt.EventWeight);

	if(lep_signal.has_ss){
	  hraw->Fill(1.1, 1.0);
	  hscaled->Fill(1.1, evt.EventWeight);

	  if(lep_signal.has_ee){
		hraw->Fill(2.1, 1.0);
		hscaled->Fill(2.1, evt.EventWeight);
	  }
	  else if(lep_signal.has_em){
		hraw->Fill(3.1, 1.0);
		hscaled->Fill(3.1, evt.EventWeight);
	  }
	  else if(lep_signal.has_mm){
		hraw->Fill(4.1, 1.0);
		hscaled->Fill(4.1, evt.EventWeight);
	  }
	  else 
		std::cout << "This is a problem!" << std::endl;
	} else if (lep_signal.has_os /*&& dilepton_mass_lead(&evt,&lep_signal)>12000*/){

	  hraw->Fill(5.1, 1.0);
	  hscaled->Fill(5.1, evt.EventWeight);

	  if(lep_signal.has_os_ee){
		hraw->Fill(6.1, 1.0);
		hscaled->Fill(6.1, evt.EventWeight);
	  }
	  else if(lep_signal.has_os_em){
		hraw->Fill(7.1, 1.0);
		hscaled->Fill(7.1, evt.EventWeight);
	  }
	  else if(lep_signal.has_os_mm){
		hraw->Fill(8.1, 1.0);
		hscaled->Fill(8.1, evt.EventWeight);
		//	  std::cout << evt.EventNumber << std::endl;
	  }
	}



  } // End of event loop

  printf("%d %s: scaled=%.2f  raw=%.0f  XsectXeff=%.2f  sumWeight=%.0f  processed=%d  luminosity=%.2f\n", treeno, oldfilename.Data(), hscaled->GetBinContent(1), hraw->GetBinContent(1), Xsect, sumWeight, processed, luminosity);
  fprintf(fpy,"%d ALL %s: scaled=%.2f  raw=%.0f  XsectXeff=%.2f  sumWeight=%.0f \n", treeno, oldfilename.Data(), hscaled->GetBinContent(1), hraw->GetBinContent(1), Xsect, sumWeight);
  fprintf(fpy,"%d SS %s: scaled=%.2f  raw=%.0f  XsectXeff=%.2f  sumWeight=%.0f \n", treeno, oldfilename.Data(), hscaled->GetBinContent(2), hraw->GetBinContent(2), Xsect, sumWeight);
  fprintf(fpy,"%d SSee %s: scaled=%.2f  raw=%.0f  XsectXeff=%.2f  sumWeight=%.0f \n", treeno, oldfilename.Data(), hscaled->GetBinContent(3), hraw->GetBinContent(3), Xsect, sumWeight);
  fprintf(fpy,"%d SSem %s: scaled=%.2f  raw=%.0f  XsectXeff=%.2f  sumWeight=%.0f \n", treeno, oldfilename.Data(), hscaled->GetBinContent(4), hraw->GetBinContent(4), Xsect, sumWeight);
  fprintf(fpy,"%d SSmm %s: scaled=%.2f  raw=%.0f  XsectXeff=%.2f  sumWeight=%.0f \n", treeno, oldfilename.Data(), hscaled->GetBinContent(5), hraw->GetBinContent(5), Xsect, sumWeight);
  fprintf(fpy,"%d OS %s: scaled=%.2f  raw=%.0f  XsectXeff=%.2f  sumWeight=%.0f \n", treeno, oldfilename.Data(), hscaled->GetBinContent(6), hraw->GetBinContent(6), Xsect, sumWeight);
  fprintf(fpy,"%d OSee %s: scaled=%.2f  raw=%.0f  XsectXeff=%.2f  sumWeight=%.0f \n", treeno, oldfilename.Data(), hscaled->GetBinContent(7), hraw->GetBinContent(7), Xsect, sumWeight);
  fprintf(fpy,"%d OSem %s: scaled=%.2f  raw=%.0f  XsectXeff=%.2f  sumWeight=%.0f \n", treeno, oldfilename.Data(), hscaled->GetBinContent(8), hraw->GetBinContent(8), Xsect, sumWeight);
  fprintf(fpy,"%d OSmm %s: scaled=%.2f  raw=%.0f  XsectXeff=%.2f  sumWeight=%.0f \n", treeno, oldfilename.Data(), hscaled->GetBinContent(9), hraw->GetBinContent(9), Xsect, sumWeight);


  if(cutflow){    
	// print cutflow
	//-----------------------------------------------------------------------  
	std::cout << "**********" << std::endl;
	std::cout << "Analyzer:" << std::endl;
	std::cout << setprecision(10) << std::endl;
	std::cout << setw(40) << left << cut_name[0]  << " = " << setw(15) << cut_flow->GetBinContent(1) << std::endl;
	std::cout << setw(40) << left << cut_name[1]  << " = " << setw(15) << cut_flow->GetBinContent(2) << std::endl;
	std::cout << setw(40) << left << cut_name[2]  << " = " << setw(15) << cut_flow->GetBinContent(3) << std::endl;
	std::cout << setw(40) << left << cut_name[3]  << " = " << setw(15) << cut_flow->GetBinContent(4) << std::endl;
	std::cout << setw(40) << left << cut_name[4]  << " = " << setw(15) << cut_flow->GetBinContent(5) << std::endl;
	std::cout << setw(40) << left << cut_name[5]  << " = " << setw(15) << cut_flow->GetBinContent(6) << std::endl;
	std::cout << setw(40) << left << cut_name[6]  << " = " << setw(15) << cut_flow->GetBinContent(7) << std::endl;
	std::cout << setw(40) << left << cut_name[7]  << " = " << setw(15) << cut_flow->GetBinContent(8) << std::endl;
	std::cout << setw(40) << left << cut_name[8]  << " = " << setw(15) << cut_flow->GetBinContent(9) << std::endl;
	std::cout << setw(40) << left << cut_name[9]  << " = " << setw(15) << cut_flow->GetBinContent(10) << std::endl;
	std::cout << setw(40) << left << cut_name[10]  << " = " << setw(15) << cut_flow->GetBinContent(11) << std::endl;
	std::cout << setw(40) << left << cut_name[11]  << " = " << setw(15) << cut_flow->GetBinContent(12) << std::endl;
	std::cout << setw(40) << left << cut_name[12]  << " = " << setw(15) << cut_flow->GetBinContent(13) << std::endl;
 
  
	// El-El channel                                                                                                                                          
	std::cout << "**********" << std::endl;
	std::cout << "Channel e-e:" << std::endl;
	std::cout << setw(40) << left << cut_name[13]  << " = " << setw(15) << cut_flow_ee_ss->GetBinContent(1) << std::endl;
	//	std::cout << setw(40) << left << cut_name[23]  << " weight = " << setw(15) << weight_flow->GetBinContent(1) << std::endl;
	std::cout << setw(40) << left << cut_name[14]  << " = " << setw(15) << cut_flow_ee_ss->GetBinContent(2) << std::endl;
	//	std::cout << setw(40) << left << cut_name[23]  << " weight = " << setw(15) << weight_flow->GetBinContent(2) << std::endl;
	std::cout << setw(40) << left << cut_name[15]  << " = " << setw(15) << cut_flow_ee_ss->GetBinContent(3) << std::endl;
	std::cout << setw(40) << left << cut_name[16]  << " = " << setw(15) << cut_flow_ee_ss->GetBinContent(4) << std::endl;
	std::cout << setw(40) << left << cut_name[17]  << " = " << setw(15) << cut_flow_ee_ss->GetBinContent(5) << std::endl;

	// El-Mu channel                                                                                                                                          
	std::cout << "**********" << std::endl;
	std::cout << "Channel e-m:" << std::endl;
	std::cout << setw(40) << left << cut_name[18]  << " = " << setw(15) << cut_flow_em_ss->GetBinContent(1) << std::endl;
	//	std::cout << setw(40) << left << cut_name[23]  << " weight = " << setw(15) << weight_flow->GetBinContent(3) << std::endl;
	std::cout << setw(40) << left << cut_name[19]  << " = " << setw(15) << cut_flow_em_ss->GetBinContent(2) << std::endl;
	//	std::cout << setw(40) << left << cut_name[23]  << " weight = " << setw(15) << weight_flow->GetBinContent(4) << std::endl;
	std::cout << setw(40) << left << cut_name[20]  << " = " << setw(15) << cut_flow_em_ss->GetBinContent(3) << std::endl;
	std::cout << setw(40) << left << cut_name[21]  << " = " << setw(15) << cut_flow_em_ss->GetBinContent(4) << std::endl;
	std::cout << setw(40) << left << cut_name[22]  << " = " << setw(15) << cut_flow_em_ss->GetBinContent(5) << std::endl;

	// Mu-Mu channel                                                                                                                                          
	std::cout << "**********" << std::endl;
	std::cout << "Channel m-m:" << std::endl;
	std::cout << setw(40) << left << cut_name[23]  << " = " << setw(15) << cut_flow_mm_ss->GetBinContent(1) << std::endl;
	//	std::cout << setw(40) << left << cut_name[23]  << " weight = " << setw(15) << weight_flow->GetBinContent(5) << std::endl;
	std::cout << setw(40) << left << cut_name[24]  << " = " << setw(15) << cut_flow_mm_ss->GetBinContent(2) << std::endl;
	//	std::cout << setw(40) << left << cut_name[23]  << " weight = " << setw(15) << weight_flow->GetBinContent(6) << std::endl;
	std::cout << setw(40) << left << cut_name[25]  << " = " << setw(15) << cut_flow_mm_ss->GetBinContent(3) << std::endl;
	std::cout << setw(40) << left << cut_name[26]  << " = " << setw(15) << cut_flow_mm_ss->GetBinContent(4) << std::endl;
	std::cout << setw(40) << left << cut_name[27]  << " = " << setw(15) << cut_flow_mm_ss->GetBinContent(5) << std::endl;
  
	std::cout << "**********" << std::endl;

	std::cout << "\n\n";
	std::cout << "Num OS: " <<  num_OS  << std::endl;
	std::cout << "Num SS: " <<  num_SS  << std::endl;
	if(num_OS!=0)
	  std::cout << "SS/OS: " <<  num_SS/num_OS  << std::endl;
  }
  //  else if(evt.isMC)
  else
	{

	  std::cout << setw(40) << left << "SR3L0b1"  << " = " << setw(15) << count_SR3L0b1  << std::endl;
	  std::cout << setw(40) << left << "SR3L0b2"  << " = " << setw(15) << count_SR3L0b2  << std::endl;
	  std::cout << setw(40) << left << "SR3L1b1"  << " = " << setw(15) << count_SR3L1b1  << std::endl;
	  std::cout << setw(40) << left << "SR3L1b2"  << " = " << setw(15) << count_SR3L1b2  << std::endl;
	  std::cout << setw(40) << left << "SR0b1"  << " = " << setw(15) << count_SR0b1 << std::endl;
	  std::cout << setw(40) << left << "SR0b2"  << " = " << setw(15) << count_SR0b2 << std::endl;
	  std::cout << setw(40) << left << "SR1b1"  << " = " << setw(15) << count_SR1b1 << std::endl;
	  std::cout << setw(40) << left << "SR1b2"  << " = " << setw(15) << count_SR1b2 << std::endl;
	  std::cout << setw(40) << left << "SR3b1"  << " = " << setw(15) << count_SR3b1 << std::endl;
	  std::cout << setw(40) << left << "SR3b2"  << " = " << setw(15) << count_SR3b2 << std::endl;
	  std::cout << setw(40) << left << "SRlow"  << " = " << setw(15) << count_SRlow << std::endl;
	  std::cout << setw(40) << left << "SRhigh"  << " = " << setw(15) << count_SRhigh << std::endl;
	  std::cout << setw(40) << left << "SR1b_3LSS"  << " = " << setw(15) << count_SR1b_3LSS << std::endl;
	  std::cout << setw(40) << left << "SR1b_DD_low"  << " = " << setw(15) << count_SR1b_DD_low << std::endl;
	  std::cout << setw(40) << left << "SR1b_DD_high"  << " = " << setw(15) << count_SR1b_DD_high << std::endl;
	  std::cout << setw(40) << left << "SR3b_DD"  << " = " << setw(15) << count_SR3b_DD << std::endl;
	  std::cout << setw(40) << left << "SR1b_GG"  << " = " << setw(15) << count_SR1b_GG << std::endl;
	  std::cout << setw(40) << left << "SRRPV0b"  << " = " << setw(15) << count_SRRPV0b << std::endl;
	  std::cout << setw(40) << left << "SRRPV3b"  << " = " << setw(15) << count_SRRPV3b << std::endl;
	  std::cout << setw(40) << left << "Rpc2L2bS"  << " = " << setw(15) << count_Rpc2L2bS << std::endl;
	  std::cout << setw(40) << left << "Rpc2L2bH"  << " = " << setw(15) << count_Rpc2L2bH << std::endl;
	  std::cout << setw(40) << left << "Rpv2L2bS"  << " = " << setw(15) << count_Rpv2L2bS << std::endl;
	  std::cout << setw(40) << left << "Rpv2L2bH"  << " = " << setw(15) << count_Rpv2L2bH << std::endl;

	  std::cout << setw(40) << left << "VRWW"  << " = " << setw(15) << count_VRWW  << std::endl;
	  std::cout << setw(40) << left << "VRWZ4j"  << " = " << setw(15) << count_VRWZ4j  << std::endl;
	  std::cout << setw(40) << left << "VRWZ5j"  << " = " << setw(15) << count_VRWZ5j  << std::endl;
	  std::cout << setw(40) << left << "VRttW" << " = " << setw(15) << count_VRttW << std::endl;
	  std::cout << setw(40) << left << "VRttZ" << " = " << setw(15) << count_VRttZ << std::endl;

	}

  file.Write();
  fclose(fp);
  fclose(fpy);
  fclose(fpd);


  return 0;
}

//-----------------------------------------------------------------------
int main(int argc, char **argv) {

  TChain tc("MiniNtuple");

  // show usage
  if (argc < 3) {
	std::cout << "Usage: " << argv[0] << " foldername filename /my_folder/file-list.root\n";
	return 1;
  }

  for (int i = 3; i < argc; i++) {
	tc.Add(argv[i]);
  }

  return main_loop(&tc, argv[1], argv[2]);
}

// Debugging statements

// std::cout << evt.EventNumber << std::endl;
// if(evt.EventNumber == -1 || evt.EventNumber == -1 || evt.EventNumber == -1)
// debug_printall(&evt);
// debug_lept(&evt, &lep_baseline);
// debug_jet(&evt, &jet);
// debug_objects(&evt, &lep_baseline, &jet_signal, fp, true);
// debug_SR_VR(&evt, &lep_signal, &jet_signal, &bjet_signal, fp, true);

/*	if( evt.EventNumber == 1051409 ){
	std::cout << "just before trigger ..." << std::endl;
	std::cout << "RunNb=" << RunNum << 
	", MET " << evt.Etmiss_TST_Et << 
	", HLT_2e17_lhvloose_nod0 " <<  evt.HLT_2e17_lhvloose_nod0 << 
	", HLT_e17_lhloose_nod0_mu14 " << evt.HLT_e17_lhloose_nod0_mu14 << 
	", HLT_mu20_mu8noL1 " << evt.HLT_mu20_mu8noL1 << 
	", HLT_xe80_tc_lcw_L1XE50 " << evt.HLT_xe80_tc_lcw_L1XE50 << 
	std::endl;

	std::cout << "2015 Config" << 
	", MET " << evt.Etmiss_TST_Et << 
	", HLT_2e12_lhloose_L12EM10VH " <<  evt.HLT_2e12_lhloose_L12EM10VH << 
	", HLT_mu18_mu8noL1 " <<  evt.HLT_mu18_mu8noL1 << 
	", HLT_e17_lhloose_mu14 " << evt.HLT_e17_lhloose_mu14 << 
	", HLT_xe70 " << evt.HLT_xe70 << 
	std::endl;
	}*/

