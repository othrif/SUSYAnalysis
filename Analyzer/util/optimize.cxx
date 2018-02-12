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
#include "Analyzer/MCTemplateCorr.h"  

// PILEUP REWEIGHTING
// The application's name:
const char* APP_NAME = "Monstres tronats";

//------------------------------------------------------------------------
//				-= General Declarations =-
//------------------------------------------------------------------------

#define luminosity 36470.16 
// lumi 2016: 33257.2 +- 4.5%
// lumi 2015: 3212.96 +- 2.1%
// lumi 2015+2016: 36470.16 +- 4.1%

bool GG = false;           // Gluino mediated processes
bool BB = false;           // sbottom mediated processes
bool strong = false;       // strong production for NUHM2
bool applyOR = true;
bool cutflow = false;      // to activate cutflow

bool useTTbarHT = true;    // only HT or MET is true, not both
bool useTTbarMET = false;

bool noXsection = true;

bool debugme = false;

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

  // PileupReweighing
  CP::PileupReweightingTool* m_Pileup;

  xAOD::EventInfo* eventInfo;
  xAOD::EventInfoContainer* eInfos;

  m_Pileup  = new CP::PileupReweightingTool("Pileup");
  std::vector<std::string> confFiles;
  std::vector<std::string> lcalcFiles;

  oldtree->GetEntry(0);

  std::cout << "MC15c sample" << std::endl;
  confFiles.push_back("/cvmfs/atlas.cern.ch/repo/sw/database/GroupData/dev/SUSYTools/merged_prw_mc15c.root");
  lcalcFiles.push_back("/afs/cern.ch/work/o/othrif/workarea/myFramework/Analyzer/data/ilumicalc_histograms_None_276262-284484.root");
  lcalcFiles.push_back("/afs/cern.ch/work/o/othrif/workarea/myFramework/Analyzer/data/ilumicalc_histograms_None_297730-311481_OflLumi-13TeV-005.root");

  CHECK(m_Pileup->setProperty( "ConfigFiles", confFiles) );
  CHECK(m_Pileup->setProperty( "DefaultChannel",410000) ); 
  CHECK(m_Pileup->setProperty( "LumiCalcFiles", lcalcFiles) );

  CHECK(m_Pileup->setProperty( "DataScaleFactor", 1.0/1.09) );
  CHECK(m_Pileup->setProperty( "DataScaleFactorUP", 1.0/1.0) );
  CHECK(m_Pileup->setProperty( "DataScaleFactorDOWN", 1.0/1.18) );


  CHECK(m_Pileup->initialize());

  // Dummy EventInfo object to manipulate later
  eInfos = new xAOD::EventInfoContainer();
  eInfos->setStore(new xAOD::EventInfoAuxContainer());
  eInfos->push_back(new xAOD::EventInfo());
  eventInfo = eInfos->at(0);
  
  // GoodRunsLists
  GoodRunsListSelectionTool *m_grl;
  m_grl = new GoodRunsListSelectionTool("GoodRunsListSelectionTool");
  std::vector<std::string> myvals;
  myvals.push_back("/afs/cern.ch/work/o/othrif/workarea/myFramework/Analyzer/data/data15_13TeV.periodAllYear_DetStatus-v79-repro20-02_DQDefects-00-02-02_PHYS_StandardGRL_All_Good_25ns.xml");
  myvals.push_back("/afs/cern.ch/work/o/othrif/workarea/myFramework/Analyzer/data/data16_13TeV.periodAllYear_DetStatus-v83-pro20-15_DQDefects-00-02-04_PHYS_StandardGRL_All_Good_25ns.xml");
  CHECK( m_grl->setProperty( "GoodRunsListVec", myvals) );
  CHECK( m_grl->setProperty("PassThrough", false) );
  CHECK( m_grl->initialize() );
  
  // Cross Sections
  SUSY::CrossSectionDB myXsection("/afs/cern.ch/work/o/othrif/workarea/myFramework/Analyzer/data/mc15_13TeV/");

  // Dilepton trigger weight
  DileptonTriggerWeight dtwTool;

  // MC template correction
  MCTemplateCorr fakeCorr;

  // create folder
  char fpath[512];
  sprintf(fpath, "/afs/cern.ch/work/o/othrif/workarea/results");
  int res = mkdir(fpath, 0700);
  if ( res == -1) {
	std::cout << "WARNING: Folder " << fpath  << " already exists!" << std::endl;
  }

  sprintf(fpath, "/afs/cern.ch/work/o/othrif/workarea/results/v48");
  res = mkdir(fpath, 0700);
  if ( res == -1) {
	std::cout << "WARNING: Folder " << fpath  << " already exists!" << std::endl;
  }

  sprintf(fpath, "/afs/cern.ch/work/o/othrif/workarea/results/v48/%s", name);
  res = mkdir(fpath, 0700);
  if ( res == -1) {
	std::cout << "WARNING: Folder " << fpath  << " already exists!" << std::endl;
  }

  // logs
  char lpath[512];
  sprintf(lpath, "/afs/cern.ch/work/o/othrif/workarea/results/v48/%s/logs", name);
  int res_log = mkdir(lpath, 0700);
  if ( res_log == -1) {
	std::cout << "WARNING: Folder " << lpath  << " already exists!" << std::endl;
  }

  // output file
  char fname[512];
  sprintf(fname, "/afs/cern.ch/work/o/othrif/workarea/results/v48/%s/%s.root", name,ftag);
  TFile file(fname, "RECREATE");

  // Save log file
  char logfile[512];
  sprintf(logfile,"/afs/cern.ch/work/o/othrif/workarea/results/v48/%s/logs/%s.log", name,ftag);
  FILE *fp;
  fp=fopen(logfile, "w+");
  if(!fp)
	std::cout << "ERROR: Cannot write to log file!" << std::endl;

  sprintf(logfile,"/afs/cern.ch/work/o/othrif/workarea/results/v48/%s/logs/%s_debug.log", name,ftag);
  FILE *fpd;
  fpd=fopen(logfile, "w+");
  if(!fpd)
	std::cout << "ERROR: Cannot write to debug log file!" << std::endl;

  sprintf(logfile,"/afs/cern.ch/work/o/othrif/workarea/results/v48/%s/logs/yields_per_file.log", name);
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

  // SR N-1 plots
  //-----------------------------------------------------------------------
  TH1D *SR3LmMET  = new TH1D("MET_SR3LmMET_SS3L", "mEt (N-1);E_{T}^{miss}  (N-1) [GeV];Events / 25 GeV", 7, 50, 225);
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
  SRrpv3bmMeff->Sumw2();

  // Initialize variables
  //-----------------------------------------------------------------------

  // other
  double pileupwgh=1.0;

  // Book histograms to be filled later
  //-----------------------------------------------------------------------
  if(!cutflow)
	{
	  //	  BookHistos_Channel(ftag, "OS");
	  //	  BookHistos_Channel(ftag, "SS3L");
	  //  BookHistos_Channel(ftag, "SS3L_noZ");
	  //	BookHistos_Channel(ftag, "SS");
	  //  BookHistos_Channel(ftag, "3L");
	}

  bool unique;
  
  // Fake and charge flip backgrounds
  //-----------------------------------------------------------------------
  TwoLepSSFakeBkg stdMxmTool;
  stdMxmTool.UseSplitErrBySource_OStoSS(true);

  // Optimization
  //-----------------------------------------------------------------------
  vector<Float_t> lepptmax_cut= {75, 100, LargeNum};
  vector<Float_t> lepptmin_cut= {10,20};
  vector<Float_t> jetptmax_cut= {LargeNum};
  vector<Float_t> jetptmin_cut= {25};
  vector<Float_t> njets_cut= {6};
  vector<Float_t> bjets_cut= {3};//0,1,2,3,4,5}; // Working points [30, 50, 60, 70, 77, 85]     
  vector<Float_t> bjetptmax_cut= {LargeNum};
  vector<Float_t> bjetptmin_cut= {20};  
  vector<Float_t> nbjets_cut= {1,2,3};
  vector<Float_t> metmax_cut= {LargeNum}; 
  vector<Float_t> metmin_cut= {0, 100, 150, 200, 220, 250, 300, 350, 400}; 
  vector<Float_t> mtMmax_cut= {LargeNum};
  vector<Float_t> mtMmin_cut= {0};
  vector<Float_t> meff_cut= {0,600,700,800,900,1000,1100,1200};
  vector<Float_t> metOmeff_cut= {0,0.2,0.25,0.3};
  Int_t optbins=1;
  optbins*=lepptmax_cut.size(); // lep1
  optbins*=lepptmin_cut.size(); // lep1    
  optbins*=lepptmax_cut.size(); // lep2   
  optbins*=lepptmin_cut.size(); // lep2
  optbins*=jetptmax_cut.size();
  optbins*=jetptmin_cut.size();
  optbins*=njets_cut.size();
  optbins*=bjets_cut.size();  
  optbins*=bjetptmax_cut.size();
  optbins*=bjetptmin_cut.size();
  optbins*=nbjets_cut.size();
  optbins*=metmax_cut.size();
  optbins*=metmin_cut.size();
  optbins*=mtMmax_cut.size();
  optbins*=mtMmin_cut.size();
  optbins*=meff_cut.size();
  optbins*=metOmeff_cut.size();

  std::cout << "Optimization ===============> Number of Bins=" << optbins << std::endl; 

  TH1F* hyield= new TH1F("hyield","hyield",optbins,1,optbins+1);
  hyield->Sumw2();
  
  TH1F* hyield_weighted= new TH1F("hyield_weighted","hyield weighted",optbins,1,optbins+1);
  hyield_weighted->Sumw2();

  int processed=0;
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
	  
	  // Pileup reweighting
	  pileupwgh = 1.0;
	  // nominal case
	  CP::SystematicSet defaultSet;
	  CHECK(m_Pileup->applySystematicVariation(defaultSet) );
	  // produces a decoration in Eventinfo
	  CHECK(m_Pileup->apply(*eventInfo,false) ); 
	  
	  // example to retrieve decoration:
	  pileupwgh = eventInfo->auxdata< float >( "PileupWeight" );
	  
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
	}

	evt.EventWeight /= pileupwgh;
	
	//========================================================================
	// General Selection
	//========================================================================

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
	if(evt.isMC)
	  RunNum =m_Pileup->getRandomRunNumber( *eventInfo , true); 
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

	if(!trigger)
	  continue;
	cut_flow->Fill(3.1,1.0);//evt.EventWeight);
	
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

	vector<my_jets> bjet_signal(bjets_cut.size());
	for (unsigned int icut=0; icut < bjets_cut.size();icut++){
	  bjet_signal[icut].num_jets = 0;
	  for (int jeti = 0; jeti < jet.num_jets; jeti++)
		if(is_signal_bjet(&evt, jet.index[jeti],bjets_cut[icut])){
		  bjet_signal[icut].index[bjet_signal[icut].num_jets] = jet.index[jeti];
		  bjet_signal[icut].E[bjet_signal[icut].num_jets] =  jet.E[jeti];
		  bjet_signal[icut].pT[bjet_signal[icut].num_jets] =  jet.pT[jeti];
		  bjet_signal[icut].eta[bjet_signal[icut].num_jets] =  jet.eta[jeti];
		  bjet_signal[icut].phi[bjet_signal[icut].num_jets] =  jet.phi[jeti];
		  bjet_signal[icut].MV2c20[bjet_signal[icut].num_jets] = jet.MV2c20[jeti];
		  bjet_signal[icut].num_jets++;
		}
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

	int n_jets_40 = 0;
	for (int jeti = 0; jeti < jet_signal.num_jets; jeti++)
	  if(jet_signal.pT[jeti]>40000)
		n_jets_40++;
	
	//	int n_bjets = bjet_signal.num_jets;
	vector<int> n_bjets( bjets_cut.size());
	for (unsigned int icut=0; icut <  bjets_cut.size();icut++){
	  n_bjets[icut] = bjet_signal[icut].num_jets;
	}

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

	int numLept = 0;
	for (int lepi = 0; lepi < lep_signal.num_leptons; lepi++)
	  {
		numLept++;
	  }
   

	// >=2 signal leptons with pT > 20 GeV
	if(num20GeVLept < 2)
	  continue;
	cut_flow->Fill(11.1,1.0);//evt.EventWeight);

	//sort jets
	sortJets(&jet_signal);
	//	sortJets(&bjet_signal);
  	for (unsigned int icut=0; icut <  bjets_cut.size();icut++)
	  sortJets(&bjet_signal[icut]);

	// Event contains Z
	containsZ(&evt, &lep_signal);
	dilepton_mass_comb(&evt, &lep_signal);

	// Separate events into ee em mm
	//	SetChannelSeparation(&lep_signal);

	// Determine fake and charge flipped leptons
	//	classify_leptons(&evt, &lep_signal);
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
	//	if(cutflow){
	//	  if(!lep_signal.has_ss)
	//		continue;
	//	}
	//	cut_flow->Fill(12.1,1.0);//evt.EventWeight);	
	
	//miss-Et variables
	float mis_Ex = evt.Etmiss_TST_Etx;
	float mis_Ey = evt.Etmiss_TST_Ety;
	float met = sqrt(mis_Ex * mis_Ex + mis_Ey * mis_Ey);
 
 	//========================================================================
	// re-weighting
	//========================================================================

	if(evt.isMC){

	  // Apply pileupwgh
	  evt.EventWeight *= pileupwgh;


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
	  
	  if(sumWeight) {};

	  double lepW = 1.;
	  double elW  = 1.;
	  double muW  = 1.;
	  
	  // lepton scale factors
	  for (int lepi = 0; lepi < lep_signal.num_leptons; lepi++)
		{
		  if(lep_signal.is_electron[lepi]) // electron scale factor
			{
			  if(evt.El_isMediumLH[lep_signal.index[lepi]]){
				elW *= evt.El_SFwMediumLH[lep_signal.index[lepi]]*evt.El_IsoSFwMediumLH[lep_signal.index[lepi]];
			  }
			  else
				elW *= 1.;
			} else {// muon scale factor
			muW *= evt.Mu_SFw[lep_signal.index[lepi]]*evt.Mu_IsoSFw[lep_signal.index[lepi]];	  
		  }
		}
	  
	  lepW = elW * muW;
	  evt.EventWeight *= lepW;


	  double jetW = 1.;
	  double jetjvt = 1.;
	  for (int jeti = 0; jeti < jet_signal.num_jets; jeti++) 
		if(fabs(jet_signal.eta[jeti])<2.5){
		  jetW *= evt.Jet_SFw[jet_signal.index[jeti]]*evt.Jet_JVTsf[jet_signal.index[jeti]];
		  jetjvt *= evt.Jet_JVTsf[jet_signal.index[jeti]];
		}

	  evt.EventWeight *= jetW;

	  event_weight_noXsec->Fill(evt.EventWeight/weightXsection,evt.EventWeight);
	  evtwgh_mu_noXsec->Fill(evt.AvgMu, evt.EventWeight/weightXsection,evt.EventWeight);
	}


	//========================================================================
	// Main part of the optimization
	//========================================================================
	
	double meff = 0.0;
	double ht = 0.0;
	double metOmeff = 0.0;
	//	double mtM = transverse_mass_min(&evt, &lep_signal);
	double mtM = transverse_mass(&evt, &lep_signal);
	vector<int> njets(jetptmin_cut.size(),0);
	vector<vector<int>> nbjets(bjets_cut.size(), vector<int>(bjetptmin_cut.size(),0));

	
	// leptons pt
	for (int i = 0; i < lep_signal.num_leptons; i++) 
	  meff += lep_signal.pT[i];
		
	// jets pt
	for (int i = 0; i < jet_signal.num_jets; i++) 
	  meff += jet_signal.pT[i];

	ht = meff; 	if(ht) {};
	meff += met;
	metOmeff = met/meff;
	for(unsigned int i_jetpt=0;i_jetpt<jetptmin_cut.size();i_jetpt++)
	  for (int i = 0; i < jet_signal.num_jets; i++) 
		if(jet_signal.pT[i]/1000.0>jetptmin_cut[i_jetpt]) 
		  njets[i_jetpt]++;

	for(unsigned int i_bjet_cut=0;i_bjet_cut<bjets_cut.size();i_bjet_cut++)
	  for(unsigned int i_bjetpt=0;i_bjetpt<bjetptmin_cut.size();i_bjetpt++)
		for (int i = 0; i < bjet_signal[i_bjet_cut].num_jets; i++) 
		  if(bjet_signal[i_bjet_cut].pT[i]/1000.0>bjetptmin_cut[i_bjetpt]) 
			nbjets[i_bjet_cut][i_bjetpt]++;

	double tmp_evtWgh = evt.EventWeight;
	for(unsigned int i_lepptmax2=0;i_lepptmax2<lepptmax_cut.size();i_lepptmax2++)
	  for(unsigned int i_lepptmin2=0;i_lepptmin2<lepptmin_cut.size();i_lepptmin2++)
		for(unsigned int i_lepptmax1=0;i_lepptmax1<lepptmax_cut.size();i_lepptmax1++)
		  for(unsigned int i_lepptmin1=0;i_lepptmin1<lepptmin_cut.size();i_lepptmin1++)
			{

			  // Separate events into ee em mm
			  SetChannelSeparation(&lep_signal, lepptmin_cut[i_lepptmin1], lepptmax_cut[i_lepptmax1], lepptmin_cut[i_lepptmin2],lepptmax_cut[i_lepptmax2]);
			  
			  
			  // same sign and passed lepton pt cuts
			  if(!lep_signal.has_ss)
				continue;
			  
			  if(evt.isMC){
			  // DileptonTriggerWeight
			  double dtW = 1.;
			  bool passMET = false;
			  if( RunNum > 290000 && met>250000 && (evt.HLT_xe100_mht_L1XE50 || evt.HLT_xe110_mht_L1XE50)) passMET = true;
			  if( RunNum <= 290000 && met>250000 && evt.HLT_xe70) passMET = true;
			  bool failMET =  ( (RunNum <= 290000 && (met < 250000 || !evt.HLT_xe70))  || (RunNum > 290000 && (met < 250000 || (!evt.HLT_xe100_mht_L1XE50 && !evt.HLT_xe110_mht_L1XE50)))  );

			  if( failMET )
				{
				  if(passMET)
					std::cout << "Problem with MET selection for DileptonTriggerWeight in RunNum=" << RunNum << ", with met=" << met << std::endl;

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
				} else 
				dtW = 1.;

			  double fakeW=1;
			  if(lep_signal.has_ss){
				// fake correction factors
				for (int lepi = 0; lepi < lep_signal.num_leptons; lepi++)
				  {
					if(lep_signal.is_electron[lepi]) 
					  fakeCorr.AddElectron(evt.ChannelNumber, lep_signal.pT[lepi], lep_signal.charge[lepi], evt.El_truthType[lep_signal.index[lepi]],  evt.El_truthOrigin[lep_signal.index[lepi]], evt.El_firstEgMotherPdgId[lep_signal.index[lepi]]);
					else 
					  fakeCorr.AddMuon(evt.ChannelNumber, lep_signal.pT[lepi], lep_signal.charge[lepi], evt.Mu_type[lep_signal.index[lepi]],  evt.Mu_origin[lep_signal.index[lepi]]);
				  }

				double uncertainty;
				fakeW = fakeCorr.GetFakeCorrection(uncertainty);	  

			  }
			  else
				fakeW = 1.;
			  fakeW = 1.; 
			  evt.EventWeight = tmp_evtWgh*dtW*fakeW;
			  }

			  for(unsigned int i_bjets=0;i_bjets<bjets_cut.size();i_bjets++)
				for(unsigned int i_bjetptmax=0;i_bjetptmax<bjetptmax_cut.size();i_bjetptmax++)
				  for(unsigned int i_bjetptmin=0;i_bjetptmin<bjetptmin_cut.size();i_bjetptmin++)
					for(unsigned int i_nbjets=0;i_nbjets<nbjets_cut.size();i_nbjets++)
					  if(nbjets[i_bjets][i_bjetptmin] == nbjets_cut[i_nbjets]) // missing case where we require exactly 0bjets
						for(unsigned int i_jetptmax=0;i_jetptmax<jetptmax_cut.size();i_jetptmax++)
						  for(unsigned int i_jetptmin=0;i_jetptmin<jetptmin_cut.size();i_jetptmin++)
							for(unsigned int i_njets=0;i_njets<njets_cut.size();i_njets++)
							  if(njets[i_jetptmin]>=njets_cut[i_njets]) 
								for(unsigned int i_metmax=0;i_metmax<metmax_cut.size();i_metmax++)
								  if(met/1000.0<metmax_cut[i_metmax]) 
									for(unsigned int i_metmin=0;i_metmin<metmin_cut.size();i_metmin++)
									  if(met/1000.0>metmin_cut[i_metmin] && metmin_cut[i_metmin]<metmax_cut[i_metmax]) {


										//										float baseMeff=metmin_cut[i_metmin]+njets_cut[i_njets]*jetptmin_cut[i_jetptmin]+lepptmin_cut[i_lepptmin1]+lepptmin_cut[i_lepptmin2];
										
										for(unsigned int i_mtMmax=0;i_mtMmax<mtMmax_cut.size();i_mtMmax++)
										  if(mtM/1000.0<mtMmax_cut[i_mtMmax]  ) 
											for(unsigned int i_mtMmin=0;i_mtMmin<mtMmin_cut.size();i_mtMmin++)
											  if(mtM/1000.0>mtMmin_cut[i_mtMmin] && mtMmin_cut[i_mtMmin]<mtMmax_cut[i_mtMmax]) 
												for(unsigned int i_meff=0;i_meff<meff_cut.size();i_meff++)
												  if (meff/1000.0>(/*baseMeff+*/meff_cut[i_meff]))
													for(unsigned int i_metOmeff=0;i_metOmeff<metOmeff_cut.size();i_metOmeff++)
													  if (metOmeff>metOmeff_cut[i_metOmeff])
														  {

														int bin=1;
														bin += i_metOmeff;
														bin += i_meff*metOmeff_cut.size();
														bin += i_mtMmin*metOmeff_cut.size()*meff_cut.size();
														bin += i_mtMmax*metOmeff_cut.size()*meff_cut.size()*mtMmin_cut.size();
														bin += i_metmin*metOmeff_cut.size()*meff_cut.size()*mtMmin_cut.size()*mtMmax_cut.size();
														bin += i_metmax*metOmeff_cut.size()*meff_cut.size()*mtMmin_cut.size()*mtMmax_cut.size()*metmin_cut.size();
														bin += i_njets*metOmeff_cut.size()*meff_cut.size()*mtMmin_cut.size()*mtMmax_cut.size()*metmin_cut.size()*metmax_cut.size();
														bin += i_jetptmin*metOmeff_cut.size()*meff_cut.size()*mtMmin_cut.size()*mtMmax_cut.size()*metmin_cut.size()*metmax_cut.size()*njets_cut.size();
														bin += i_jetptmax*metOmeff_cut.size()*meff_cut.size()*mtMmin_cut.size()*mtMmax_cut.size()*metmin_cut.size()*metmax_cut.size()*njets_cut.size()*jetptmin_cut.size();
														bin += i_nbjets*metOmeff_cut.size()*meff_cut.size()*mtMmin_cut.size()*mtMmax_cut.size()*metmin_cut.size()*metmax_cut.size()*njets_cut.size()*jetptmin_cut.size()*jetptmax_cut.size();
														bin += i_bjetptmin*metOmeff_cut.size()*meff_cut.size()*mtMmin_cut.size()*mtMmax_cut.size()*metmin_cut.size()*metmax_cut.size()*njets_cut.size()*jetptmin_cut.size()*jetptmax_cut.size()*nbjets_cut.size();
														bin += i_bjetptmax*metOmeff_cut.size()*meff_cut.size()*mtMmin_cut.size()*mtMmax_cut.size()*metmin_cut.size()*metmax_cut.size()*njets_cut.size()*jetptmin_cut.size()*jetptmax_cut.size()*nbjets_cut.size()*bjetptmin_cut.size();
														bin += i_bjets*metOmeff_cut.size()*meff_cut.size()*mtMmin_cut.size()*mtMmax_cut.size()*metmin_cut.size()*metmax_cut.size()*njets_cut.size()*jetptmin_cut.size()*jetptmax_cut.size()*nbjets_cut.size()*bjetptmin_cut.size()*bjetptmax_cut.size();
														bin += i_lepptmin1*metOmeff_cut.size()*meff_cut.size()*mtMmin_cut.size()*mtMmax_cut.size()*metmin_cut.size()*metmax_cut.size()*njets_cut.size()*jetptmin_cut.size()*jetptmax_cut.size()*nbjets_cut.size()*bjetptmin_cut.size()*bjetptmax_cut.size()*bjets_cut.size();
														bin += i_lepptmax1*metOmeff_cut.size()*meff_cut.size()*mtMmin_cut.size()*mtMmax_cut.size()*metmin_cut.size()*metmax_cut.size()*njets_cut.size()*jetptmin_cut.size()*jetptmax_cut.size()*nbjets_cut.size()*bjetptmin_cut.size()*bjetptmax_cut.size()*bjets_cut.size()*lepptmin_cut.size();
														bin += i_lepptmin2*metOmeff_cut.size()*meff_cut.size()*mtMmin_cut.size()*mtMmax_cut.size()*metmin_cut.size()*metmax_cut.size()*njets_cut.size()*jetptmin_cut.size()*jetptmax_cut.size()*nbjets_cut.size()*bjetptmin_cut.size()*bjetptmax_cut.size()*bjets_cut.size()*lepptmin_cut.size()*lepptmax_cut.size();
														bin += i_lepptmax2*metOmeff_cut.size()*meff_cut.size()*mtMmin_cut.size()*mtMmax_cut.size()*metmin_cut.size()*metmax_cut.size()*njets_cut.size()*jetptmin_cut.size()*jetptmax_cut.size()*nbjets_cut.size()*bjetptmin_cut.size()*bjetptmax_cut.size()*bjets_cut.size()*lepptmin_cut.size()*lepptmax_cut.size()*lepptmin_cut.size();

														hyield->Fill(bin);
														hyield_weighted->Fill(bin,evt.EventWeight);

														  }
									  }

			} // End of lepton loop
  } // End of event loop

fprintf(fp, "\nlepptmax2_cut = [");
for(unsigned int i_lepptmax2=0;i_lepptmax2<lepptmax_cut.size();i_lepptmax2++)
	fprintf(fp, "%.0f, ", lepptmax_cut[i_lepptmax2]);
  fprintf(fp, "]\nlepptmin2_cut = [ ");
  for(unsigned int i_lepptmin2=0;i_lepptmin2<lepptmin_cut.size();i_lepptmin2++)
	fprintf(fp, "%.0f, ", lepptmin_cut[i_lepptmin2]);
  fprintf(fp, "]\nlepptmax1_cut = [ ");
  for(unsigned int i_lepptmax1=0;i_lepptmax1<lepptmax_cut.size();i_lepptmax1++)
	fprintf(fp, "%.0f, ", lepptmax_cut[i_lepptmax1]);
  fprintf(fp, "]\nlepptmin1_cut = [ ");
  for(unsigned int i_lepptmin1=0;i_lepptmin1<lepptmin_cut.size();i_lepptmin1++)
	fprintf(fp, "%.0f, ", lepptmin_cut[i_lepptmin1]);
  fprintf(fp, "]\nbjets_cut = [ ");
  for(unsigned int i_bjets=0;i_bjets<bjets_cut.size();i_bjets++)
	fprintf(fp, "%.0f, ", bjets_cut[i_bjets]);
  fprintf(fp, "]\nbjetptmax_cut = [ ");
  for(unsigned int i_bjetptmax=0;i_bjetptmax<bjetptmax_cut.size();i_bjetptmax++)
	fprintf(fp, "%.0f, ", bjetptmax_cut[i_bjetptmax]);
  fprintf(fp, "]\nbjetptmin_cut = [ ");
  for(unsigned int i_bjetptmin=0;i_bjetptmin<bjetptmin_cut.size();i_bjetptmin++)
	fprintf(fp, "%.0f, ", bjetptmin_cut[i_bjetptmin]);
  fprintf(fp, "]\nnbjets_cut = [ ");
  for(unsigned int i_nbjets=0;i_nbjets<nbjets_cut.size();i_nbjets++)
	fprintf(fp, "%.0f, ", nbjets_cut[i_nbjets]);
  fprintf(fp, "]\njetptmax_cut = [ ");
  for(unsigned int i_jetptmax=0;i_jetptmax<jetptmax_cut.size();i_jetptmax++)
	fprintf(fp, "%.0f, ", jetptmax_cut[i_jetptmax]);
  fprintf(fp, "]\njetptmin_cut = [ ");
  for(unsigned int i_jetptmin=0;i_jetptmin<jetptmin_cut.size();i_jetptmin++)
	fprintf(fp, "%.0f, ", jetptmin_cut[i_jetptmin]);
  fprintf(fp, "]\nnjets_cut = [ ");
  for(unsigned int i_njets=0;i_njets<njets_cut.size();i_njets++)
	fprintf(fp, "%.0f, ", njets_cut[i_njets]);
  fprintf(fp, "]\nmetmax_cut = [ ");
  for(unsigned int i_metmax=0;i_metmax<metmax_cut.size();i_metmax++)
	fprintf(fp, "%.0f, ", metmax_cut[i_metmax]);
  fprintf(fp, "]\nmetmin_cut = [ ");
  for(unsigned int i_metmin=0;i_metmin<metmin_cut.size();i_metmin++)
	fprintf(fp, "%.0f, ", metmin_cut[i_metmin]);
  fprintf(fp, "]\nmtMmax_cut = [ ");
  for(unsigned int i_mtMmax=0;i_mtMmax<mtMmax_cut.size();i_mtMmax++)
	fprintf(fp, "%.0f, ", mtMmax_cut[i_mtMmax]);
  fprintf(fp, "]\nmtMmin_cut = [ ");
  for(unsigned int i_mtMmin=0;i_mtMmin<mtMmin_cut.size();i_mtMmin++)
	fprintf(fp, "%.0f, ", mtMmin_cut[i_mtMmin]);
  fprintf(fp, "]\nmeff_cut = [ ");
  for(unsigned int i_meff=0;i_meff<meff_cut.size();i_meff++)
	fprintf(fp, "%.0f, ", meff_cut[i_meff]);
  fprintf(fp, "]\nmetOmeff_cut = [ ");
  for(unsigned int i_metOmeff=0;i_metOmeff<metOmeff_cut.size();i_metOmeff++)
	fprintf(fp, "%.2f, ", metOmeff_cut[i_metOmeff]);
  fprintf(fp, "]\n");

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

