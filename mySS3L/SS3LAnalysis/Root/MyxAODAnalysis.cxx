#include <EventLoop/Job.h>
#include <EventLoop/StatusCode.h>
#include <EventLoop/Worker.h>
#include <SS3LAnalysis/MyxAODAnalysis.h>
#include "EventLoop/OutputStream.h"

// EDM includes:
#include "xAODEventInfo/EventInfo.h"
#include "xAODJet/JetContainer.h"
#include "xAODJet/JetAuxContainer.h"
#include "xAODMuon/MuonContainer.h"
#include "xAODEgamma/ElectronContainer.h"
#include "xAODEgamma/PhotonContainer.h"
#include "xAODTau/TauJetContainer.h"
#include "xAODCaloEvent/CaloCluster.h"
#include "xAODTruth/TruthParticleContainer.h"
#include "xAODTruth/TruthEventContainer.h"
#include "xAODTruth/TruthEvent.h"
#include "xAODCore/ShallowCopy.h"
#include "xAODMissingET/MissingETContainer.h"
#include "xAODMissingET/MissingETAuxContainer.h"
#include "xAODBTaggingEfficiency/BTaggingEfficiencyTool.h"
#include "xAODTracking/TrackParticle.h"
#include "xAODTracking/TrackParticlexAODHelpers.h"
#include "xAODRootAccess/tools/TFileAccessTracer.h"

#include "xAODCutFlow/CutBookkeeper.h"
#include "xAODCutFlow/CutBookkeeperContainer.h"

// GRL
#include "GoodRunsLists/GoodRunsListSelectionTool.h"
//PU Reweighting
#include "PileupReweighting/PileupReweightingTool.h"

#include "CPAnalysisExamples/errorcheck.h"
#include "SUSYTools/SUSYObjDef_xAOD.h"
// Amg include
#include "EventPrimitives/EventPrimitivesHelpers.h"

#include "SS3LAnalysis/CutClass.h"
#include "xAODEgamma/EgammaxAODHelpers.h"

#include <TTreeFormula.h>

#include "IsolationSelection/IsolationSelectionTool.h"

#include "ElectronPhotonSelectorTools/AsgElectronIsEMSelector.h" 
#include "ElectronPhotonSelectorTools/AsgElectronLikelihoodTool.h" 
#include "ElectronEfficiencyCorrection/AsgElectronEfficiencyCorrectionTool.h"

#include "MuonSelectorTools/MuonSelectionTool.h"

#include "ElectronPhotonSelectorTools/AsgElectronChargeIDSelectorTool.h"

// added for trigger scale factors
#include "TriggerAnalysisInterfaces/ITrigGlobalEfficiencyCorrectionTool.h"
#include "TrigGlobalEfficiencyCorrection/TrigGlobalEfficiencyCorrectionTool.h"
#include "ElectronEfficiencyCorrection/IAsgElectronEfficiencyCorrectionTool.h"
#include "PATCore/PATCoreEnums.h"
#include "MuonEfficiencyCorrections/MuonTriggerScaleFactors.h"
#include "AsgTools/AnaToolHandle.h"

//ttbar+HF classification
#include "SS3LAnalysis/ClassifyAndCalculateHF.h"

// this is needed to distribute the algorithm to the workers
ClassImp(MyxAODAnalysis)

//#include <valgrind/callgrind.h>
#include "SS3LAnalysis/chargeflip.h"


MyxAODAnalysis :: MyxAODAnalysis ()
{
  // Here you put any code for the base initialization of variables,
  // e.g. initialize all pointers to 0.  Note that you should only put
  // the most basic initialization here, since this method will be
  // called on both the submission and the worker node.  Most of your
  // initialization code will go into histInitialize() and
  // initialize().
}



EL::StatusCode MyxAODAnalysis :: setupJob (EL::Job& job)
{
  // Here you put code that sets up the job on the submission object
  // so that it is ready to work with your algorithm, e.g. you can
  // request the D3PDReader service or add output files.  Any code you
  // put here could instead also go into the submission script.  The
  // sole advantage of putting it here is that it gets automatically
  // activated/deactivated when you add/remove the algorithm from your
  // job, which may or may not be of value to you.

  const char* APP_NAME = "MyxAODAnalysis::setupJob()";   
  Info(APP_NAME, "Start of method..." );   

  job.useXAOD ();

  // let's initialize the algorithm to use the xAODRootAccess package
  xAOD::Init( "MyxAODAnalysis" ).ignore(); // call before opening first file

  // tell EventLoop about our output:
  EL::OutputStream out ("output");
  job.outputAdd (out);

  return EL::StatusCode::SUCCESS;
}



EL::StatusCode MyxAODAnalysis :: histInitialize ()
{
  // Here you do everything that needs to be done at the very
  // beginning on each worker node, e.g. create histograms and output
  // trees.  This method gets called before any input files are
  // connected.
   
  const char* APP_NAME = "MyxAODAnalysis::histInitialize()";   
  //  Info(APP_NAME, "Start of method..." );   

  hWeights = new TH1D("DerivationStat_Weights", "", 3, 0, 3);
  hWeights->GetXaxis()->SetBinLabel(1, "original xAOD");
  hWeights->GetXaxis()->SetBinLabel(2, "DxAOD");
  hWeights->GetXaxis()->SetBinLabel(3, "Ntup");

  hEvents = new TH1D("DerivationStat_RawEvents", "", 3, 0, 3);
  hEvents->GetXaxis()->SetBinLabel(1, "original xAOD");
  hEvents->GetXaxis()->SetBinLabel(2, "DxAOD");
  hEvents->GetXaxis()->SetBinLabel(3, "Ntup");

  hWeightsSquared = new TH1D("DerivationStat_Weights_Squared", "", 3, 0, 3);
  hWeightsSquared->GetXaxis()->SetBinLabel(1, "original xAOD");
  hWeightsSquared->GetXaxis()->SetBinLabel(2, "DxAOD");
  hWeightsSquared->GetXaxis()->SetBinLabel(3, "Ntup");
  
  //  wk()->addOutput(hEvents);
  //  wk()->addOutput(hWeights);
  
  //  Info(APP_NAME, "End of method..." );   

  return EL::StatusCode::SUCCESS;
}



EL::StatusCode MyxAODAnalysis :: fileExecute ()
{
  // Here you do everything that needs to be done exactly once for every
  // single file, e.g. collect a list of all lumi-blocks processed
  //  const char* APP_NAME = "MyxAODAnalysis::fileExecute()";   
  //  Info(APP_NAME, "Start of method..." );   
  return EL::StatusCode::SUCCESS;
}



EL::StatusCode MyxAODAnalysis :: changeInput (bool firstFile)
{
  // Here you do everything you need to do when we change input files,
  // e.g. resetting branch addresses on trees.  If you are using
  // D3PDReader or a similar service this method is not needed.
  
  // get the MetaData tree once a new file is opened, with
  const char* APP_NAME = "MyxAODAnalysis::changeInput()";   
  //  Info(APP_NAME, "Start of method..." );   

  Info("changeInput()", "About to get metaData....");


  // read event tree and print number of events
  m_event = wk()->xaodEvent();
  Info("changeInput()", "Number of events in this file = %lli", m_event->getEntries() ); // print long long int

  //Read the CutBookkeeper container
  const xAOD::CutBookkeeperContainer* completeCBC = 0;
  if (!m_event->retrieveMetaInput(completeCBC, "CutBookkeepers").isSuccess()) {
    Error( "changeInput()", "Failed to retrieve CutBookkeepers from MetaData! Exiting.");
  }

  const xAOD::CutBookkeeper* allEventsCBK = 0;
  int maxcycle=-1;
  //let's find the right CBK (latest with StreaAOD input before derivations)
  for ( auto cbk : *completeCBC ) {
    if ( cbk->name() == "AllExecutedEvents" && cbk->inputStream() == "StreamAOD" && cbk->cycle() > maxcycle){
      maxcycle = cbk->cycle();
      allEventsCBK = cbk;
    }
  }
  
  uint64_t nEventsProcessed  = -1;
  double sumOfWeights        = -1;
  double sumOfWeightsSquared = -1;
  if (allEventsCBK) {
    nEventsProcessed  = allEventsCBK->nAcceptedEvents();
    sumOfWeights        = allEventsCBK->sumOfEventWeights();
    sumOfWeightsSquared = allEventsCBK->sumOfEventWeightsSquared();
    Info( "changeInput()", "CutBookkeepers Accepted %lu SumWei %f sumWei2 %f ",nEventsProcessed,sumOfWeights,sumOfWeightsSquared);
  } else { 
    Info( APP_NAME, "No relevent CutBookKeepers found" ); 
  }
    
  hWeights->Fill(0.,sumOfWeights);
  hEvents->Fill(0.,nEventsProcessed);
  hWeightsSquared->Fill(0.,sumOfWeightsSquared);
    

  //  Info(APP_NAME, "Out of method..." );   

  return EL::StatusCode::SUCCESS;
}



EL::StatusCode MyxAODAnalysis :: initialize ()
{
  // Here you do everything that you need to do after the first input
  // file has been connected and before the first event is processed,
  // e.g. create additional histograms based on which variables are
  // available in the input files.  You can also create all of your
  // histograms and trees in here, but be aware that this method
  // doesn't get called if no events are processed.  So any objects
  // you create here won't be available in the output if you have no
  // input events.

  xAOD::TFileAccessTracer::enableDataSubmission( false );  

  const char* APP_NAME = "MyxAODAnalysis::initialise()";   
  m_event = wk()->xaodEvent();

  // Dump Flags:
  cout << "IsData:" << isData << endl;
  cout << "IsAF:" << isAtlfast << endl;
  cout << "IsMc15c:" << ismc15c << endl;

  objTool = new SUSYObjDef_xAOD( "SUSYObjDef_xAOD" );  
  //  objTool->msg().setLevel( MSG::VERBOSE);
  //  CHECK( objTool->setProperty("DebugMode",  true) );
  objTool->msg().setLevel( MSG::INFO);
  ST::ISUSYObjDef_xAODTool::DataSource datasource = isData ? ST::ISUSYObjDef_xAODTool::Data : (isAtlfast ? ST::ISUSYObjDef_xAODTool::AtlfastII : ST::ISUSYObjDef_xAODTool::FullSim );
  CHECK( objTool->setProperty("DataSource",datasource) ) ;
  //  cout << __LINE__ << ": " << (int) datasource << endl;       
  CHECK( objTool->setProperty("ConfigFile", "SS3LAnalysis/SS3L_Default.conf") );

  // MC to MC SFs
  cout << "InputDS:" << inputDS << endl;
  int ShowerType = !isData ? objTool->getMCShowerType(inputDS) : 0;
  CHECK( objTool->setProperty("ShowerType", ShowerType) );

  /// set ORtool 
  auto toolName = "MyORTool";
  ORUtils::ORFlags orFlags(toolName, "baseline", "passMyOR");
  orFlags.bJetLabel= "bjet_loose";
  orFlags.boostedLeptons = false; /// no boosted OR in isMyOR
  orFlags.outputPassValue = true;
  orFlags.doEleEleOR = false;
  orFlags.doElectrons = true;
  orFlags.doMuons = true;
  orFlags.doJets = true;
  orFlags.doTaus = false;
  orFlags.doPhotons = false;
  orFlags.doFatJets  = false;
  CHECK( ORUtils::recommendedTools(orFlags, my_orToolbox));
  CHECK(my_orToolbox.initialize());

  ///////////////////////////////////////////////////////////////////////////////////////////
  std::vector<std::string> prw_conf;
  if(!isData){
	if(ismc15c){
	  //	  prw_conf.push_back("dev/SUSYTools/merged_prw_mc15c_latest.root");
	  //	  prw_conf.push_back("dev/SUSYTools/merged_prw_mc15c_signal_latest.root");
	  prw_conf.push_back("SS3LAnalysis/merged_prw_mc15c_Feb20.root"); 
	  //	  prw_conf.push_back("SS3LAnalysis/merged_prw_mc15c_signal_Mar1.root"); 
	  prw_conf.push_back("SS3LAnalysis/merged_prw_mc15c_signal_Mar8.root"); 
	}else{
	  prw_conf.push_back("SS3LAnalysis/merged_prw.root");
	  prw_conf.push_back("SS3LAnalysis/mergedSignals_prw.root");
	}
  }
  CHECK( objTool->setProperty("PRWConfigFiles", prw_conf) );
       
  std::vector<std::string> prw_lumicalc;
  if(!isData){
	//  prw_lumicalc.push_back("/cvmfs/atlas.cern.ch/repo/sw/database/GroupData/dev/SUSYTools/ilumicalc_histograms_None_297730-299243.root");
	prw_lumicalc.push_back("SS3LAnalysis/ilumicalc_histograms_None_276262-284484.root");
	//  prw_lumicalc.push_back("SS3LAnalysis/ilumicalc_histograms_None_297730-302956.root");
	//  prw_lumicalc.push_back("SS3LAnalysis/ilumicalc_histograms_None_297730-303560.root");
	//	prw_lumicalc.push_back("SS3LAnalysis/ilumicalc_histograms_None_297730-311481_OflLumi-13TeV-005.root");
	prw_lumicalc.push_back("SS3LAnalysis/ilumicalc_histograms_None_297730-311481_OflLumi-13TeV-008.root"); 
  }
  CHECK( objTool->setProperty("PRWLumiCalcFiles", prw_lumicalc) );

  ///////////////////////////////////////////////////////////////////////////////////////////
  
  m_elecSelLikelihood_LhTight = new AsgElectronLikelihoodTool("EleSelLikelihood_TightLH");
  CHECK( m_elecSelLikelihood_LhTight->setProperty("ConfigFile","ElectronPhotonSelectorTools/offline/mc15_20160512/ElectronLikelihoodTightOfflineConfig2016.conf"));
  CHECK( m_elecSelLikelihood_LhTight->initialize() );
  
  m_electronSF_reco = new AsgElectronEfficiencyCorrectionTool("ElectronSF_reco");
  std::vector< std::string > corrFileNameList_reco;
  //  corrFileNameList_reco.push_back("ElectronEfficiencyCorrection/2015_2016/rel20.7/ICHEP_June2016_v1/offline/efficiencySF.offline.RecoTrk.2015_2016.13TeV.rel20.7.25ns.v01.root");
  corrFileNameList_reco.push_back("ElectronEfficiencyCorrection/2015_2016/rel20.7/Moriond_February2017_v1/offline/efficiencySF.offline.RecoTrk.root");
  CHECK( m_electronSF_reco->setProperty("CorrectionFileNameList",corrFileNameList_reco) );
  if(!isData){
    if(isAtlfast)
      CHECK( m_electronSF_reco->setProperty("ForceDataType",(int) PATCore::ParticleDataType::Fast ));
    else
      CHECK( m_electronSF_reco->setProperty("ForceDataType",(int) PATCore::ParticleDataType::Full ));
  }
  CHECK( m_electronSF_reco->initialize() );
    

  m_electronSF_LhLoose = new AsgElectronEfficiencyCorrectionTool("ElectronSF_LhLoose");
  std::vector< std::string > corrFileNameList_LhLoose;
  //  corrFileNameList_LhLoose.push_back("ElectronEfficiencyCorrection/2015_2016/rel20.7/ICHEP_June2016_v1/offline/efficiencySF.offline.LooseAndBLayerLLH_d0z0_v11.2015_2016.13TeV.rel20.7.25ns.v01.root");
  corrFileNameList_LhLoose.push_back("ElectronEfficiencyCorrection/2015_2016/rel20.7/Moriond_February2017_v1/offline/efficiencySF.offline.LooseAndBLayerLLH_d0z0_v11.root");
  CHECK( m_electronSF_LhLoose->setProperty("CorrectionFileNameList",corrFileNameList_LhLoose) );
  if(!isData){
    if(isAtlfast)
      CHECK( m_electronSF_LhLoose->setProperty("ForceDataType",(int) PATCore::ParticleDataType::Fast ));
    else
      CHECK( m_electronSF_LhLoose->setProperty("ForceDataType",(int) PATCore::ParticleDataType::Full ));
  }

  CHECK( m_electronSF_LhLoose->initialize() );
    
 
  m_electronSF_trig_LhLoose = new AsgElectronEfficiencyCorrectionTool("ElectronSF_trig_LhLoose");
  std::vector< std::string > corrFileNameList_trig_LhLoose;
  //  corrFileNameList_trig_LhLoose.push_back("ElectronEfficiencyCorrection/2015_2016/rel20.7/ICHEP_June2016_v1/trigger/efficiency.DI_E_2015_e12_lhloose_L1EM10VH_2016_e15_lhvloose_nod0_L1EM13VH.LooseAndBLayerLLH_d0z0_v11.root");
  corrFileNameList_trig_LhLoose.push_back("ElectronEfficiencyCorrection/2015_2016/rel20.7/Moriond_February2017_v1/trigger/efficiency.DI_E_2015_e12_lhloose_L1EM10VH_2016_e15_lhvloose_nod0_L1EM13VH.LooseAndBLayerLLH_d0z0_v11.root");
  CHECK( m_electronSF_trig_LhLoose->setProperty("CorrectionFileNameList",corrFileNameList_trig_LhLoose) );
  if(!isData){ 
    if(isAtlfast) 
      CHECK( m_electronSF_trig_LhLoose->setProperty("ForceDataType",(int) PATCore::ParticleDataType::Fast )); 
    else 
      CHECK( m_electronSF_trig_LhLoose->setProperty("ForceDataType",(int) PATCore::ParticleDataType::Full )); 
  } 
  CHECK( m_electronSF_trig_LhLoose->initialize() );
    

  m_electronSF_LhTight = new AsgElectronEfficiencyCorrectionTool("ElectronSF_LhTight");
  std::vector< std::string > corrFileNameList_LhTight;
  //  corrFileNameList_LhTight.push_back("ElectronEfficiencyCorrection/2015_2016/rel20.7/ICHEP_June2016_v1/offline/efficiencySF.offline.TightLLH_d0z0_v11.2015_2016.13TeV.rel20.7.25ns.v01.root");
  corrFileNameList_LhTight.push_back("ElectronEfficiencyCorrection/2015_2016/rel20.7/Moriond_February2017_v1/offline/efficiencySF.offline.TightLLH_d0z0_v11.root");
  CHECK( m_electronSF_LhTight->setProperty("CorrectionFileNameList",corrFileNameList_LhTight) );
  if(!isData){  
    if(isAtlfast)  
      CHECK( m_electronSF_LhTight->setProperty("ForceDataType",(int) PATCore::ParticleDataType::Fast ));  
    else  
      CHECK( m_electronSF_LhTight->setProperty("ForceDataType",(int) PATCore::ParticleDataType::Full ));  
  }
  CHECK( m_electronSF_LhTight->initialize() );
    

  m_electronSF_trig_LhTight = new AsgElectronEfficiencyCorrectionTool("ElectronSF_trig_LhTight");
  std::vector< std::string > corrFileNameList_trig_LhTight;
  //  corrFileNameList_trig_LhTight.push_back("ElectronEfficiencyCorrection/2015_2016/rel20.7/ICHEP_June2016_v1/trigger/efficiency.DI_E_2015_e12_lhloose_L1EM10VH_2016_e15_lhvloose_nod0_L1EM13VH.TightLLH_d0z0_v11.root");
  corrFileNameList_trig_LhTight.push_back("ElectronEfficiencyCorrection/2015_2016/rel20.7/Moriond_February2017_v1/trigger/efficiency.DI_E_2015_e12_lhloose_L1EM10VH_2016_e15_lhvloose_nod0_L1EM13VH.TightLLH_d0z0_v11.root");
  CHECK( m_electronSF_trig_LhTight->setProperty("CorrectionFileNameList",corrFileNameList_trig_LhTight) );
  if(!isData){   
    if(isAtlfast)   
      CHECK( m_electronSF_trig_LhTight->setProperty("ForceDataType",(int) PATCore::ParticleDataType::Fast ));   
    else   
      CHECK( m_electronSF_trig_LhTight->setProperty("ForceDataType",(int) PATCore::ParticleDataType::Full ));   
  } 
  CHECK( m_electronSF_trig_LhTight->initialize() );  

  // Scale factor needed for the Charge Flip Tagger (charge flip killer)
  m_electronSF_CFT = new AsgElectronEfficiencyCorrectionTool("ElectronSF_CFT");
  std::vector< std::string > corrFileNameList_CFT;
  corrFileNameList_CFT.push_back("ElectronEfficiencyCorrection/2015_2016/rel20.7/Moriond_February2017_v1/charge_misID/efficiencySF.ChargeID.MediumLLH_d0z0_v11_isolFixedCutTight_MediumCFT.root");
  CHECK( m_electronSF_CFT->setProperty("CorrectionFileNameList",corrFileNameList_CFT) );
  if(!isData){   
    if(isAtlfast)   
      CHECK( m_electronSF_CFT->setProperty("ForceDataType",(int) PATCore::ParticleDataType::Fast ));   
    else   
      CHECK( m_electronSF_CFT->setProperty("ForceDataType",(int) PATCore::ParticleDataType::Full ));   
  } 
  CHECK( m_electronSF_CFT->initialize() );  


  m_muonSelectionTool = new CP::MuonSelectionTool("MuonSelTool_Tight");
  //  muonSelectionTool->msg().setLevel( MSG::VERBOSE );
  CHECK( m_muonSelectionTool->setProperty( "MaxEta", 2.4) );
  CHECK( m_muonSelectionTool->setProperty( "MuQuality", int(xAOD::Muon::Tight) ) );
  //  CHECK( m_muonSelectionTool->setProperty( "MuQuality", int(xAOD::Muon::Medium) ) );
  CHECK( m_muonSelectionTool->initialize() );
  

  //  Info(APP_NAME,"SUSYObjDef_xAOD before initialize()... " );
  if( objTool->initialize() != StatusCode::SUCCESS){
    Error(APP_NAME, "Cannot intialize SUSYObjDef_xAOD..." );
    Error(APP_NAME, "Exiting... " );
    return EL::StatusCode::FAILURE;
  }else{
    Info(APP_NAME,"SUSYObjDef_xAOD initialized... " );
  }

  isoLooseTO = new CP::IsolationSelectionTool("isoLooseTO");
  CHECK( isoLooseTO->setProperty("ElectronWP","LooseTrackOnly") );
  CHECK( isoLooseTO->setProperty("MuonWP","LooseTrackOnly") );
  CHECK( isoLooseTO->initialize() ); 

  isoLoose = new CP::IsolationSelectionTool("isoLoose");
  CHECK( isoLoose->setProperty("ElectronWP","Loose") );
  CHECK( isoLoose->setProperty("MuonWP","Loose") );
  CHECK( isoLoose->initialize() ); 

  isoTight = new CP::IsolationSelectionTool("isoTight");
  CHECK( isoTight->setProperty("ElectronWP","Tight") );
  CHECK( isoTight->setProperty("MuonWP","Tight") );
  CHECK( isoTight->initialize() ); 

  isoGrad = new CP::IsolationSelectionTool("isoGrad");
  CHECK( isoGrad->setProperty("ElectronWP","Gradient") );
  CHECK( isoGrad->setProperty("MuonWP","Gradient") );
  CHECK( isoGrad->initialize() ); 

  isoGradLoose = new CP::IsolationSelectionTool("isoGradLoose");
  CHECK( isoGradLoose->setProperty("ElectronWP","GradientLoose") );
  CHECK( isoGradLoose->setProperty("MuonWP","GradientLoose") );
  CHECK( isoGradLoose->initialize() ); 

  isoGradCustom = new CP::IsolationSelectionTool("isoGradCustom");
  std::vector< std::pair<xAOD::Iso::IsolationType, std::string> > myCuts;
  myCuts.push_back(std::make_pair<xAOD::Iso::IsolationType, std::string>(xAOD::Iso::ptvarcone20, "0.1713*x+88.71"));
  myCuts.push_back(std::make_pair<xAOD::Iso::IsolationType, std::string>(xAOD::Iso::topoetcone20, "0.1713*x+88.71"));
  std::vector< std::pair<xAOD::Iso::IsolationType, std::string> > myCutsMu;
  myCutsMu.push_back(std::make_pair<xAOD::Iso::IsolationType, std::string>(xAOD::Iso::ptvarcone30, "0.1713*x+88.71"));
  myCutsMu.push_back(std::make_pair<xAOD::Iso::IsolationType, std::string>(xAOD::Iso::topoetcone20, "0.1713*x+88.71"));
  CHECK( isoGradCustom->initialize() );
  CHECK( isoGradCustom->addUserDefinedWP("GradientCustom", xAOD::Type::Muon, myCutsMu));
  CHECK( isoGradCustom->addUserDefinedWP("GradientCustom", xAOD::Type::Electron, myCuts));

  isoGradCustomTight = new CP::IsolationSelectionTool("isoGradCustomTight");
  std::vector< std::pair<xAOD::Iso::IsolationType, std::string> > myCutsT;
  myCutsT.push_back(std::make_pair<xAOD::Iso::IsolationType, std::string>(xAOD::Iso::ptvarcone20, "0.2283*x+85.28"));
  myCutsT.push_back(std::make_pair<xAOD::Iso::IsolationType, std::string>(xAOD::Iso::topoetcone20, "0.2283*x+85.28"));
  std::vector< std::pair<xAOD::Iso::IsolationType, std::string> > myCutsTMu;
  myCutsTMu.push_back(std::make_pair<xAOD::Iso::IsolationType, std::string>(xAOD::Iso::ptvarcone30, "0.2283*x+85.28"));
  myCutsTMu.push_back(std::make_pair<xAOD::Iso::IsolationType, std::string>(xAOD::Iso::topoetcone20, "0.2283*x+85.28"));
  CHECK( isoGradCustomTight->initialize() );
  CHECK( isoGradCustomTight->addUserDefinedWP("GradientCustomTight", xAOD::Type::Electron, myCutsT));
  CHECK( isoGradCustomTight->addUserDefinedWP("GradientCustomTight", xAOD::Type::Muon, myCutsTMu));

  CFTToolmedium = new AsgElectronChargeIDSelectorTool("ChargeFlipTaggerToolMedium");
  CFTToolmedium->msg().setLevel( MSG::WARNING );
  //  CFTToolmedium->msg().setLevel( MSG::FATAL );
  //  std::string trainingfile="SS3LAnalysis/CFT_tight.root";
  std::string trainingfile    = "ElectronPhotonSelectorTools/ECIDS_20161125for2017Moriond.root";
  float BDT_OP=0;
  CHECK( CFTToolmedium->setProperty("TrainingFile",trainingfile) );
  CHECK( CFTToolmedium->setProperty("WorkingPoint", "MediumLHElectron"));
  CHECK( CFTToolmedium->setProperty("CutOnBDT",BDT_OP) );
  CHECK( CFTToolmedium->initialize() );


  CFTToolLoose = new AsgElectronChargeIDSelectorTool("ChargeFlipTaggerToolLoose");
  CFTToolLoose->msg().setLevel( MSG::WARNING );
  //  CFTToolLoose->msg().setLevel( MSG::FATAL );
  //  std::string trainingfile="SS3LAnalysis/CFT_tight.root";
  //  std::string trainingfile    = "ElectronPhotonSelectorTools/ECIDS_20161125for2017Moriond.root";
  //  float BDT_OP=0;
  CHECK( CFTToolLoose->setProperty("TrainingFile",trainingfile) );
  CHECK( CFTToolLoose->setProperty("WorkingPoint", "LooseLHElectron"));
  CHECK( CFTToolLoose->setProperty("CutOnBDT",BDT_OP) );
  CHECK( CFTToolLoose->initialize() );


  // Trigger efficiency/scale factor CP tools for electrons and muons

  std::map<std::string,std::string> legsPerTool;
  

  // Electrons
  AsgElectronEfficiencyCorrectionTool* elEffTool1 = new AsgElectronEfficiencyCorrectionTool("ElTrigEff-1");
  elEffTool1->setProperty("MapFilePath","/cvmfs/atlas.cern.ch/repo/sw/database/GroupData/ElectronEfficiencyCorrection/2015_2016/rel20.7/Moriond_February2017_v1/map0.txt").ignore();
  elEffTool1->setProperty("TriggerKey","Eff_MULTI_L_2015_e17_lhloose_2016_e17_lhloose_nod0").ignore();
  elEffTool1->setProperty("IdKey","Medium").ignore();
  //  elEffTool1->setProperty("IsoKey","Gradient").ignore(); 
  elEffTool1->setProperty("IsoKey","FixedCutTight").ignore(); 
  elEffTool1->setProperty("CorrelationModel","TOTAL").ignore();
  if(!isData){  
    if(isAtlfast)  
	  elEffTool1->setProperty("ForceDataType", (int) PATCore::ParticleDataType::Fast).ignore();
    else  
	  elEffTool1->setProperty("ForceDataType", (int) PATCore::ParticleDataType::Full).ignore();
  }
  if(elEffTool1->initialize() != StatusCode::SUCCESS)
	{
	  Error(APP_NAME, "Unable to initialize CP tool!");
	  return 3;
	}
  legsPerTool["ElTrigEff-1"] = "e17_lhloose,e17_lhloose_nod0";

  AsgElectronEfficiencyCorrectionTool* elSFTool1 = new AsgElectronEfficiencyCorrectionTool("ElTrigSF-1");
  elSFTool1->setProperty("MapFilePath","/cvmfs/atlas.cern.ch/repo/sw/database/GroupData/ElectronEfficiencyCorrection/2015_2016/rel20.7/Moriond_February2017_v1/map0.txt").ignore();
  elSFTool1->setProperty("TriggerKey","MULTI_L_2015_e17_lhloose_2016_e17_lhloose_nod0").ignore();
  elSFTool1->setProperty("IdKey","Medium").ignore();
  //  elSFTool1->setProperty("IsoKey","Gradient").ignore();
  elSFTool1->setProperty("IsoKey","FixedCutTight").ignore();
  elSFTool1->setProperty("CorrelationModel","TOTAL").ignore();
  if(!isData){  
    if(isAtlfast)  
	  elSFTool1->setProperty("ForceDataType", (int) PATCore::ParticleDataType::Fast).ignore();
    else  
	  elSFTool1->setProperty("ForceDataType", (int) PATCore::ParticleDataType::Full).ignore();
  }
  if(elSFTool1->initialize() != StatusCode::SUCCESS)
	{
	  Error(APP_NAME, "Unable to initialize CP tool!");
	  return 3;
	}
  legsPerTool["ElTrigSF-1"] = legsPerTool["ElTrigEff-1"];

  AsgElectronEfficiencyCorrectionTool* elEffTool2 = new AsgElectronEfficiencyCorrectionTool("ElTrigEff-2");
  elEffTool2->setProperty("MapFilePath","/cvmfs/atlas.cern.ch/repo/sw/database/GroupData/ElectronEfficiencyCorrection/2015_2016/rel20.7/Moriond_February2017_v1/map0.txt").ignore();
  elEffTool2->setProperty("TriggerKey","Eff_DI_E_2015_e12_lhloose_L1EM10VH_2016_e17_lhvloose_nod0").ignore();
  elEffTool2->setProperty("IdKey","Medium").ignore();
  //  elEffTool2->setProperty("IsoKey","Gradient").ignore();
  elEffTool2->setProperty("IsoKey","FixedCutTight").ignore();
  elEffTool2->setProperty("CorrelationModel","TOTAL").ignore();
  if(!isData){  
    if(isAtlfast)  
	  elEffTool2->setProperty("ForceDataType", (int) PATCore::ParticleDataType::Fast).ignore();
    else  
	  elEffTool2->setProperty("ForceDataType", (int) PATCore::ParticleDataType::Full).ignore();
  }
  if(elEffTool2->initialize() != StatusCode::SUCCESS)
	{
	  Error(APP_NAME, "Unable to initialize CP tool!");
	  return 3;
	}
  legsPerTool["ElTrigEff-2"] = "e12_lhloose_L1EM10VH,e17_lhvloose_nod0";

  AsgElectronEfficiencyCorrectionTool* elSFTool2 = new AsgElectronEfficiencyCorrectionTool("ElTrigSF-2");
  elSFTool2->setProperty("MapFilePath","/cvmfs/atlas.cern.ch/repo/sw/database/GroupData/ElectronEfficiencyCorrection/2015_2016/rel20.7/Moriond_February2017_v1/map0.txt").ignore();
  elSFTool2->setProperty("TriggerKey","DI_E_2015_e12_lhloose_L1EM10VH_2016_e17_lhvloose_nod0").ignore();
  elSFTool2->setProperty("IdKey","Medium").ignore();
  //  elSFTool2->setProperty("IsoKey","Gradient").ignore();
  elSFTool2->setProperty("IsoKey","FixedCutTight").ignore();
  elSFTool2->setProperty("CorrelationModel","TOTAL").ignore();
  if(!isData){  
    if(isAtlfast)  
	  elSFTool2->setProperty("ForceDataType", (int) PATCore::ParticleDataType::Fast).ignore();
    else  
	  elSFTool2->setProperty("ForceDataType", (int) PATCore::ParticleDataType::Full).ignore();
  }
  if(elSFTool2->initialize() != StatusCode::SUCCESS)
	{
	  Error(APP_NAME, "Unable to initialize CP tool!");
	  return 3;
	}
  legsPerTool["ElTrigSF-2"] = legsPerTool["ElTrigEff-2"];

  electronEffTools.push_back(elEffTool1);
  electronEffTools.push_back(elEffTool2);
  electronSFTools.push_back(elSFTool1);
  electronSFTools.push_back(elSFTool2);
  
  // Muons
  CP::MuonTriggerScaleFactors* toolMuons1 =  new CP::MuonTriggerScaleFactors("MuonTrigEff-2015");
  toolMuons1->setProperty("CalibrationRelease", "170209_Moriond").ignore();
  toolMuons1->setProperty("MuonQuality", "Tight").ignore();
  toolMuons1->setProperty("Isolation", "GradientLoose").ignore();
  toolMuons1->setProperty("Year", "2015").ignore();
  if(toolMuons1->initialize() != StatusCode::SUCCESS)
	{
	  Error(APP_NAME, "Unable to initialize CP tool!");
	  //	  return 3;
	}
  muonTools.push_back(toolMuons1);
  
  CP::MuonTriggerScaleFactors* toolMuons2 =  new CP::MuonTriggerScaleFactors("MuonTrigEff-2016");
  toolMuons2->setProperty("CalibrationRelease", "170209_Moriond").ignore();
  toolMuons2->setProperty("MuonQuality", "Tight").ignore();
  toolMuons2->setProperty("Isolation", "GradientLoose").ignore();
  toolMuons2->setProperty("Year", "2016").ignore();
  if(toolMuons2->initialize() != StatusCode::SUCCESS)
	{
	  Error(APP_NAME, "Unable to initialize CP tool!");
	  //	  return 3;
	}
  muonTools.push_back(toolMuons2);

  // Configure the trigger SF tools
  myTriggerSFTool = new TrigGlobalEfficiencyCorrectionTool("TrigGlobalEfficiencyCorrectionTool");
  myTriggerSFTool->setProperty("ElectronEfficiencyTools",electronEffTools).ignore();
  myTriggerSFTool->setProperty("ElectronScaleFactorTools",electronSFTools).ignore();
  myTriggerSFTool->setProperty("MuonTools",muonTools).ignore();
  myTriggerSFTool->setProperty("ListOfLegsPerTool",legsPerTool).ignore();
  myTriggerSFTool->setProperty("TriggerCombination2015", "2e12_lhloose_L12EM10VH || mu18_mu8noL1 || e17_lhloose_mu14").ignore();
  myTriggerSFTool->setProperty("TriggerCombination2016", "2e17_lhvloose_nod0 || e17_lhloose_nod0_mu14 || mu22_mu8noL1").ignore();
  // myTriggerSFTool->setProperty("OutputLevel", MSG::DEBUG).ignore();
  if(myTriggerSFTool->initialize() != StatusCode::SUCCESS)
	{
	  Error( APP_NAME, "Unable to initialize tool!" );
	  return 3;
	}
  
  /*

	m_electronSF_reco = new AsgElectronEfficiencyCorrectionTool("ElectronSF_reco");
	std::vector< std::string > corrFileNameList_reco;
	corrFileNameList_reco.push_back("ElectronEfficiencyCorrection/2015_2016/rel20.7/ICHEP_June2016_v1/offline/efficiencySF.offline.RecoTrk.2015_2016.13TeV.rel20.7.25ns.v01.root");
	CHECK( m_electronSF_reco->setProperty("CorrectionFileNameList",corrFileNameList_reco) );
	if(!isData){
    if(isAtlfast)
	CHECK( m_electronSF_reco->setProperty("ForceDataType",(int) PATCore::ParticleDataType::Fast ));
    else
	CHECK( m_electronSF_reco->setProperty("ForceDataType",(int) PATCore::ParticleDataType::Full ));
	}
	CHECK( m_electronSF_reco->initialize() );
  */



  TFile *file = wk()->getOutputFile ("output");
  MyTree = new TTree ("AnaNtup", "AnaNtup");
  MyTree->SetDirectory (file);  
  
  for(int t=0; t<nTrig;t++){
    trig_map.insert (std::pair<std::string, bool>(nameTrig[t].Data(), false));
    MyTree->Branch(nameTrig[t].Data(), 
				   &trig_map[nameTrig[t].Data()]);
  }

  MyTree->Branch("EventNumber",&tEventNumber,"EventNumber/l");
  MyTree->Branch("ChannelNumber",&tChannelNumber,"ChannelNumber/I");
  MyTree->Branch("AvgMu",&tAvgMu,"AvgMu/D");
  MyTree->Branch("EventWeight",&EventWeight,"EventWeight/D");
  MyTree->Branch("PRWWeight",&PRWWeight,"PRWWeight/D");
  MyTree->Branch("PRWrandomRunNumber",&PRWrandomRunNumber,"PRWrandomRunNumber/I");
  MyTree->Branch("TriggerDileptonSF",&TriggerDileptonSF,"TriggerDileptonSF/D");
  MyTree->Branch("bcid",&bcid,"bcid/I");
  MyTree->Branch("LB",&LB,"LB/I");
  //  MyTree->Branch("passGRL",&passGRL,"passGRL/I");
  MyTree->Branch("RunNb",&RunNb,"RunNb/I");

  MyTree->Branch("DetError",&tDetError,"DetError/I");

  MyTree->Branch("NMu", &NMu, "NMu/I");
  MyTree->Branch("Mu_eta",&Mu_eta);
  MyTree->Branch("Mu_phi",&Mu_phi);
  MyTree->Branch("Mu_pT",&Mu_pT);
  MyTree->Branch("Mu_SFw",&Mu_SFw);
  MyTree->Branch("Mu_IsoSFw",&Mu_IsoSFw);
  MyTree->Branch("Mu_charge",&Mu_charge);
  MyTree->Branch("Mu_d0pvtx",&Mu_d0pvtx);
  //  MyTree->Branch("Mu_d0old",&Mu_d0old);
  //  MyTree->Branch("Mu_d0pvtxerr",&Mu_d0pvtxerr);
  MyTree->Branch("Mu_sigd0",&Mu_sigd0);
  //  MyTree->Branch("Mu_sigd0old",&Mu_sigd0old);
  MyTree->Branch("Mu_z0sinTheta",&Mu_z0pvtx);
  MyTree->Branch("Mu_isBad",&Mu_isBad);
  MyTree->Branch("Mu_passOR",&Mu_passOR);
  MyTree->Branch("Mu_isTight",&Mu_isTight);
  //  MyTree->Branch("Mu_isSig",&Mu_isSig);
  MyTree->Branch("Mu_isCosmic",&Mu_isCosmic);
  if(!isData){
    MyTree->Branch("Mu_type",&Mu_type);
    MyTree->Branch("Mu_origin",&Mu_origin);
  }
  MyTree->Branch("Mu_ptcone20",&Mu_ptcone20);
  MyTree->Branch("Mu_ptcone30",&Mu_ptcone30);
  MyTree->Branch("Mu_ptcone40",&Mu_ptcone40);
  MyTree->Branch("Mu_ptvarcone20",&Mu_ptvarcone20);
  MyTree->Branch("Mu_ptvarcone30",&Mu_ptvarcone30);
  MyTree->Branch("Mu_ptvarcone40",&Mu_ptvarcone40);
  MyTree->Branch("Mu_topoetcone20",&Mu_topoetcone20);
  MyTree->Branch("Mu_topoetcone30",&Mu_topoetcone30);
  MyTree->Branch("Mu_topoetcone40",&Mu_topoetcone40);
  MyTree->Branch("Mu_passIsoLooseTO",&Mu_passIsoLooseTO);
  MyTree->Branch("Mu_passIsoLoose",&Mu_passIsoLoose);
  MyTree->Branch("Mu_passIsoTight",&Mu_passIsoTight);
  MyTree->Branch("Mu_passIsoGrad", &Mu_passIsoGrad);
  MyTree->Branch("Mu_passIsoGradCustomTight", &Mu_passIsoGradCustomTight);
  MyTree->Branch("Mu_passIsoGradCustom", &Mu_passIsoGradCustom);
  MyTree->Branch("Mu_passIsoGradLoose", &Mu_passIsoGradLoose);
  //  MyTree->Branch("MuTrigSF_2mu14", &MuTrigSF_2mu14);
  //  MyTree->Branch("Mu_TrigMatch_mu14", &Mu_TrigMatch_mu14); 
  //  MyTree->Branch("Mu_TrigMatch_mu18", &Mu_TrigMatch_mu18); 
  MyTree->Branch("MuTrigSF_HLT_mu20_iloose_L1MU15_OR_HLT_mu50", &MuTrigSF_HLT_mu20_iloose_L1MU15_OR_HLT_mu50); 
  MyTree->Branch("Mu_trigMatch_mu26_ivarmedium", &Mu_TrigMatch_mu26_ivarmedium );
  MyTree->Branch("Mu_trigMatch_mu20_iloose_L1MU15", &Mu_TrigMatch_mu20_iloose_L1MU15 );
  MyTree->Branch("Mu_trigMatch_mu40", &Mu_TrigMatch_mu40);
  MyTree->Branch("Mu_trigMatch_mu50", &Mu_TrigMatch_mu50);
  MyTree->Branch("Mu_trigMatch_mu8noL1", &Mu_TrigMatch_mu8noL1);
  MyTree->Branch("Mu_trigMatch_mu14", &Mu_TrigMatch_mu14);
  MyTree->Branch("Mu_trigMatch_mu18", &Mu_TrigMatch_mu18);
  MyTree->Branch("Mu_trigMatch_mu18_mu8noL1", &Mu_TrigMatch_mu18_mu8noL1);
  MyTree->Branch("Mu_trigMatch_e17_lhloose_mu14", &Mu_TrigMatch_e17_lhloose_mu14);
  MyTree->Branch("Mu_trigMatch_e17_lhloose_nod0_mu14", &Mu_TrigMatch_e17_lhloose_nod0_mu14);
  MyTree->Branch("Mu_trigMatch_mu20_mu8noL1", &Mu_TrigMatch_mu20_mu8noL1);
  MyTree->Branch("Mu_trigMatch_mu22_mu8noL1", &Mu_TrigMatch_mu22_mu8noL1);
  MyTree->Branch("Mu_trigMatch_mu24_iloose"          , &Mu_TrigMatch_mu24_iloose );
  MyTree->Branch("Mu_trigMatch_mu24_ivarloose"	     , &Mu_TrigMatch_mu24_ivarloose	);  
  MyTree->Branch("Mu_trigMatch_mu24_iloose_L1MU15"   , &Mu_TrigMatch_mu24_iloose_L1MU15	); 
  MyTree->Branch("Mu_trigMatch_mu24_ivarloose_L1MU15", &Mu_TrigMatch_mu24_ivarloose_L1MU15);
  MyTree->Branch("Mu_trigMatchPair_mu18_mu8noL1", &Mu_TrigMatchPair_mu18_mu8noL1);
  MyTree->Branch("Mu_trigMatchPair_mu20_mu8noL1", &Mu_TrigMatchPair_mu20_mu8noL1);
  MyTree->Branch("Mu_trigMatchPair_mu22_mu8noL1", &Mu_TrigMatchPair_mu22_mu8noL1);
  
  MyTree->Branch("NEl",&NEl,"NEl/I");
  MyTree->Branch("El_eta",&El_eta);
  MyTree->Branch("El_etaclus",&El_etaclus);
  MyTree->Branch("El_phi",&El_phi);
  MyTree->Branch("El_pT",&El_pT);
  MyTree->Branch("El_E",&El_E);
  MyTree->Branch("El_charge",&El_charge);
  MyTree->Branch("El_sigd0",&El_sigd0);
  //  MyTree->Branch("El_sigd0old",&El_sigd0old);
  MyTree->Branch("El_z0sinTheta",&El_z0pvtx);
  MyTree->Branch("El_d0pvtx",&El_d0pvtx);
  //  MyTree->Branch("El_d0old",&El_d0old);
  //  MyTree->Branch("El_d0pvtxerr",&El_d0pvtxerr);
  //  MyTree->Branch("El_SFw",&El_SFw);

  //  MyTree->Branch("El_SFwMedium",  &El_SFwMedium);
  MyTree->Branch("El_passOR",&El_passOR);
  MyTree->Branch("El_SFwMediumLH",&El_SFwMediumLH);
  //  MyTree->Branch("El_SFwTight",   &El_SFwTight); 
  MyTree->Branch("El_IsoSFwMediumLH", &El_IsoSFwMediumLH);
  MyTree->Branch("El_SFwTightLH", &El_SFwTightLH);
  MyTree->Branch("El_SFwLooseAndBLayerLH", &El_SFwLooseLH);
  MyTree->Branch("El_SFweightCFT", &El_SFweightCFT);

  //  MyTree->Branch("El_SFwTrigMedium",  &El_SFwTrigMedium);
  //  MyTree->Branch("El_SFwTrigMediumLH_e12_lhloose_L1EM10VH",&El_SFwTrigMediumLH);
  //  MyTree->Branch("El_SFwTrigTight",   &El_SFwTrigTight);
  //  MyTree->Branch("El_SFwTrigTightLH", &El_SFwTrigTightLH);
  MyTree->Branch("El_SFwTrigMediumLH_e12_lhloose_L1EM10VH", &El_SFwTrigMediumLH_e12_lhloose_L1EM10VH);
  MyTree->Branch("El_SFwTrigMediumLH_e17_lhloose",          &El_SFwTrigMediumLH_e17_lhloose);
  MyTree->Branch("El_SFwTrigMediumLH_single",               &El_SFwTrigMediumLH_single);
  MyTree->Branch("El_SFwTrigLooseAndBLayerLH_e12_lhloose_L1EM10VH", &El_SFwTrigLooseLH);

  MyTree->Branch("El_isLooseAndBLayerLH",&El_isLooseLH);
  MyTree->Branch("El_isMediumLH",&El_isMediumLH);
  MyTree->Branch("El_isTightLH",&El_isTightLH);
  //  MyTree->Branch("El_isLoose",&El_isLoose);
  //MyTree->Branch("El_isMedium",&El_isMedium);
  //MyTree->Branch("El_isTight",&El_isTight);
  MyTree->Branch("El_nBLayerHits",&El_nBLayerHits);
  MyTree->Branch("El_expectBLayerHit",&El_expectBLayerHit);
  if(!isData){
    MyTree->Branch("El_truthType",&El_truthType);
    MyTree->Branch("El_truthOrigin",&El_truthOrigin); 
    MyTree->Branch("El_bkgTruthType",&El_bkgTruthType);
    MyTree->Branch("El_bkgTruthOrigin",&El_bkgTruthOrigin); 
    MyTree->Branch("El_bkgMotherPdgId",&El_bkgMotherPdgId);
    MyTree->Branch("El_firstEgMotherTruthType",&El_firstEgMotherTruthType); 
    MyTree->Branch("El_firstEgMotherTruthOrigin",&El_firstEgMotherTruthOrigin);
    MyTree->Branch("El_firstEgMotherPdgId",&El_firstEgMotherPdgId);
    MyTree->Branch("El_chFlip",&El_chFlip);   
  }
  MyTree->Branch("El_ptcone20",&El_ptcone20);
  MyTree->Branch("El_ptcone30",&El_ptcone30);
  MyTree->Branch("El_ptcone40",&El_ptcone40);
  MyTree->Branch("El_ptvarcone20",&El_ptvarcone20);
  MyTree->Branch("El_ptvarcone30",&El_ptvarcone30);
  MyTree->Branch("El_ptvarcone40",&El_ptvarcone40);
  MyTree->Branch("El_topoetcone20",&El_topoetcone20);
  MyTree->Branch("El_topoetcone30",&El_topoetcone30);
  MyTree->Branch("El_topoetcone40",&El_topoetcone40);
  MyTree->Branch("El_passIsoLooseTO",&El_passIsoLooseTO);
  MyTree->Branch("El_passIsoLoose",&El_passIsoLoose);
  MyTree->Branch("El_passIsoTight",&El_passIsoTight);
  MyTree->Branch("El_passIsoGrad", &El_passIsoGrad);
  //  MyTree->Branch("El_passIsoGradCustom", &El_passIsoGradCustom);
  MyTree->Branch("El_passIsoGradCustomTight", &El_passIsoGradCustomTight);
  MyTree->Branch("El_passIsoGradCustom", &El_passIsoGradCustom);
  MyTree->Branch("El_passIsoGradLoose", &El_passIsoGradLoose);
  MyTree->Branch("El_trigMatch_e12_lhloose_L1EM10VH", &El_TrigMatch_e12_lhloose_L1EM10VH );
  MyTree->Branch("El_trigMatch_e17_lhloose", &El_TrigMatch_e17_lhloose );
  MyTree->Branch("El_trigMatch_e60_lhmedium", &El_TrigMatch_e60_lhmedium );
  MyTree->Branch("El_trigMatch_e24_lhmedium_L1EM20VH", &El_TrigMatch_e24_lhmedium_L1EM20VH);
  MyTree->Branch("El_trigMatch_e24_lhmedium_iloose_L1EM20VH", &El_TrigMatch_e24_lhmedium_iloose_L1EM20VH);
  MyTree->Branch("El_trigMatch_e26_lhtight_nod0_ivarloose", &El_TrigMatch_e26_lhtight_nod0_ivarloose);
  MyTree->Branch("El_trigMatch_2e12_lhloose_L12EM10VH", &El_TrigMatch_2e12_lhloose_L12EM10VH);
  MyTree->Branch("El_trigMatch_2e15_lhloose_L12EM10VH", &El_TrigMatch_2e15_lhloose_L12EM10VH);
  MyTree->Branch("El_trigMatch_2e15_lhvloose_L12EM13VH",&El_TrigMatch_2e15_lhvloose_L12EM13VH);
  MyTree->Branch("El_trigMatch_2e15_lhvloose_nod0_L12EM13VH", &El_TrigMatch_2e15_lhvloose_nod0_L12EM13VH);
  MyTree->Branch("El_trigMatch_2e17_lhvloose_nod0", &El_TrigMatch_2e17_lhvloose_nod0);
  MyTree->Branch("El_trigMatch_e17_lhloose_mu14", &El_TrigMatch_e17_lhloose_mu14);
  MyTree->Branch("El_trigMatch_e17_lhloose_nod0_mu14", &El_TrigMatch_e17_lhloose_nod0_mu14);
  MyTree->Branch("El_trigMatch_e24_lhmedium_nod0_ivarloose", &El_TrigMatch_e24_lhmedium_nod0_ivarloose );
  MyTree->Branch("El_trigMatch_e24_lhtight_nod0_ivarloose",  &El_TrigMatch_e24_lhtight_nod0_ivarloose );
  MyTree->Branch("El_trigMatch_e60_lhmedium_nod0",           &El_TrigMatch_e60_lhmedium_nod0 );

  MyTree->Branch("El_passChargeFlipTaggerBDTmedium", &El_passChargeFlipTaggerBDTmedium);
  MyTree->Branch("El_passChargeFlipTaggerBDTloose", &El_passChargeFlipTaggerBDTloose);

  MyTree->Branch("NJet",&NJet,"NJet/I");
  MyTree->Branch("Jet_isSig",&Jet_isSig);
  MyTree->Branch("Jet_eta",&Jet_eta);
  MyTree->Branch("Jet_phi",&Jet_phi);
  MyTree->Branch("Jet_pT",&Jet_pT);
  MyTree->Branch("Jet_E",&Jet_E);
  MyTree->Branch("Jet_quality",&Jet_quality);
  //  MyTree->Branch("Jet_JVF",&Jet_JVF);
  MyTree->Branch("Jet_JVT",&Jet_JVT);
  MyTree->Branch("Jet_JVTsf",&Jet_JVTsf);
  MyTree->Branch("Jet_MV2c20",&Jet_MV2c20);
  MyTree->Branch("Jet_MV2c10",&Jet_MV2c10);
  MyTree->Branch("Jet_SFw",&Jet_SFw);
  MyTree->Branch("Jet_isSig",&Jet_isSig);
  if(!isData){
    MyTree->Branch("Jet_ConeTruthLabel",  &Jet_ConeTruthLabel);
    MyTree->Branch("Jet_PartonTruthLabel",&Jet_PartonTruthLabel);
    MyTree->Branch("Jet_HadronConeExclTruthLabel",&Jet_HadronConeExclTruthLabel);
    MyTree->Branch("Jet_deltaR",&Jet_deltaR);
  }
  MyTree->Branch("Jet_nTrk",&Jet_nTrk);
  MyTree->Branch("Jet_passOR",&Jet_passOR);

  MyTree->Branch("totalJVTsf",&totalJVTsf,"totalJVTsf/F");

  MyTree->Branch("Etmiss_CST_Etx",&Etmiss_CST_Etx,"Etmiss_CST_Etx/F");
  MyTree->Branch("Etmiss_CST_Ety",&Etmiss_CST_Ety,"Etmiss_CST_Ety/F");
  MyTree->Branch("Etmiss_CST_Et", &Etmiss_CST_Et, "Etmiss_CST_Et/F");

  MyTree->Branch("Etmiss_TST_Etx",&Etmiss_TST_Etx,"Etmiss_TST_Etx/F");
  MyTree->Branch("Etmiss_TST_Ety",&Etmiss_TST_Ety,"Etmiss_TST_Ety/F");
  MyTree->Branch("Etmiss_TST_Et", &Etmiss_TST_Et, "Etmiss_TST_Et/F");

  MyTree->Branch("Etmiss_TSTterm_Etx",&Etmiss_TSTterm_Etx,"Etmiss_TSTterm_Etx/F");
  MyTree->Branch("Etmiss_TSTterm_Ety",&Etmiss_TSTterm_Ety,"Etmiss_TSTterm_Ety/F");
  MyTree->Branch("Etmiss_TSTterm_Et", &Etmiss_TSTterm_Et, "Etmiss_TSTterm_Et/F");

  MyTree->Branch("Etmiss_Truth_Etx",&Etmiss_Truth_Etx,"Etmiss_Truth_Etx/F");
  MyTree->Branch("Etmiss_Truth_Ety",&Etmiss_Truth_Ety,"Etmiss_Truth_Ety/F");
  MyTree->Branch("Etmiss_Truth_Et", &Etmiss_Truth_Et, "Etmiss_Truth_Et/F");
  
  if(!isData){
    
    MyTree->Branch("NTruthJet",&NTruthJet,"NTruthJet/I");
    MyTree->Branch("TruthJet_eta",&TruthJet_eta);
    MyTree->Branch("TruthJet_phi",&TruthJet_phi);
    MyTree->Branch("TruthJet_pT", &TruthJet_pT);
    MyTree->Branch("TruthJet_E",  &TruthJet_E);
    MyTree->Branch("TruthJet_ConeTruthLabel",  &TruthJet_ConeTruthLabel);
    MyTree->Branch("TruthJet_PartonTruthLabel",&TruthJet_PartonTruthLabel);
    //    MyTree->Branch("TruthJet_HadronConeExclTruthLabel",&TruthJet_HadronConeExclTruthLabel);
    MyTree->Branch("TruthJet_ClassHF",  &TruthJet_ClassHF);

    MyTree->Branch("NTruthL",  &NTruthL,"NTruthL/I");
    MyTree->Branch("TruthL_eta",&TruthL_eta);
    MyTree->Branch("TruthL_phi",&TruthL_phi);
    MyTree->Branch("TruthL_pT", &TruthL_pT);
    MyTree->Branch("TruthL_id", &TruthL_id);
    
    MyTree->Branch("SUSY_Spart_pdgId1",&pdgid1,"SUSY_Spart_pdgId1/I");
    MyTree->Branch("SUSY_Spart_pdgId2",&pdgid2,"SUSY_Spart_pdgId2/I");

    MyTree->Branch("SUSY_Gluino_decay1",&gluDecay1,"SUSY_Gluino_decay1/I");
    MyTree->Branch("SUSY_Gluino_decay2",&gluDecay2,"SUSY_Gluino_decay2/I");

    MyTree->Branch("GenFiltHT", &GenFiltHT, "GenFiltHT/F");
    MyTree->Branch("GenFiltMET",&GenFiltMET,"GenFiltMET/F");

  }
  MyTree->Branch("PV_z",&primvertex_z,"PV_z/F");
  MyTree->Branch("Nvtx",&Nvtx,"Nvtx/I");
  // MyTree->Branch("PV_x",&primvertex_x,"PV_x/F");
  // MyTree->Branch("PV_y",&primvertex_y,"PV_y/F");

  MyTree->Branch("TruthX1",&TruthX1,"TruthX1/F");
  MyTree->Branch("TruthX2",&TruthX2,"TruthX2/F"); 
  //   MyTree->Branch("TruthXF1",&TruthXF1,"TruthXF1/F");
  //   MyTree->Branch("TruthXF2",&TruthXF2,"TruthXF2/F"); 
  MyTree->Branch("TruthQ",  &TruthQ,  "TruthQ/F"); 

  MyTree->Branch("SherpaNjetWeight",  &SherpaNjetWeight,  "SherpaNjetWeight/F"); 

  MyTree->Branch("TruthPDGID1",&TruthPDGID1,"TruthPDGID1/I");
  MyTree->Branch("TruthPDGID2",&TruthPDGID2,"TruthPDGID2/I");
  //   MyTree->Branch("TruthPDFID1",&TruthPDFID1,"TruthPDFID1/I");
  //   MyTree->Branch("TruthPDFID2",&TruthPDFID2,"TruthPDFID2/I");
  

  MyTree->Branch("extraB",&extraB,"extraB/I");
  MyTree->Branch("extraC",&extraC,"extraC/I");

  //  Info(APP_NAME, "Tree booking done..." );   
  
  TDirectory *out_TDir = (TDirectory*) wk()->getOutputFile ("output");
  hWeights->SetDirectory(out_TDir);
  hEvents->SetDirectory(out_TDir);
  hWeightsSquared->SetDirectory(out_TDir);

  //  Info(APP_NAME, "Out of method..." );   
           
  return EL::StatusCode::SUCCESS;
}



EL::StatusCode MyxAODAnalysis :: execute ()
{
  //  CALLGRIND_START_INSTRUMENTATION;

  // Here you do everything that needs to be done on every single
  // events, e.g. read input variables, apply cuts, and fill
  // histograms and trees.  This is where most of your actual analysis
  // code will go.
   
  isMyOR = true;
  pT_treshold = 50000.;

  const char* APP_NAME = "MyxAODAnalysis::execute()";   
  //Info(APP_NAME, "Start of method..." );   
  //  std::vector<CP::SystematicSet>::const_iterator sysListItr;
  

  // Not needed for tag23
  //  if(isDerived){                       
  //    // Temporary code for DC14 DxAOD   
  //    // rename the event density object 
  //    Info(APP_NAME, "Gonna run renameEventDensities()" );
  //    escopier->renameEventDensities();  
  //    //  if(debug)                      
  //    store.print();                     
  //  }    

  //----------------------------
  // Event information
  //--------------------------- 
  const xAOD::EventInfo* eventInfo = 0;
  if( ! m_event->retrieve( eventInfo, "EventInfo").isSuccess() ){
    Error(APP_NAME, "Failed to retrieve event info collection. Exiting." );
    return EL::StatusCode::FAILURE;
  }

  //  Info(APP_NAME, "EventInfo retrieved..." );   

  // check if the event is data or MC
  // (many tools are applied either to data or MC)
  bool isMC = false;
  // check if the event is MC
  if(eventInfo->eventType( xAOD::EventInfo::IS_SIMULATION ) ){
    isMC = true; // can do something with this later
  }   

  tEventNumber = eventInfo->eventNumber();
  RunNb = eventInfo->runNumber();

  //  if(tEventNumber != 170283)
  //	return EL::StatusCode::SUCCESS;
  //  std::cout << "\n\nWorking on run/evt: "<<  RunNb << " / " << tEventNumber << "\n\n" << std::endl;
  
  LB = eventInfo->lumiBlock();
  bcid = eventInfo->bcid();
  tAvgMu = eventInfo->averageInteractionsPerCrossing();
  if(isMC)
    tChannelNumber = eventInfo->mcChannelNumber();
  else
    tChannelNumber = -1;

  if(isMC)
    EventWeight = (eventInfo->mcEventWeights()).at(0);
  else
    EventWeight = 1;

  tDetError = 0;
  
  

  UInt_t runNumber_forMu = 0;
  if(isMC){
    GenFiltHT  = eventInfo->auxdata<float>("GenFiltHT");
    GenFiltMET = eventInfo->auxdata<float>("GenFiltMET");

    // Needed by muon trigger SF tool
    CHECK( objTool->ApplyPRWTool());
    // Needed by muon trigger SF tool
    PRWrandomRunNumber = eventInfo->auxdata<unsigned int>("RandomRunNumber");
    PRWWeight = eventInfo->auxdata< float >( "PileupWeight" );
    if(runNumber_forMu == 0) runNumber_forMu = 276073;
    CHECK( objTool->setRunNumber(PRWrandomRunNumber));
	tAvgMu = eventInfo->auxdata< float >( "corrected_averageInteractionsPerCrossing" );
  }
  else
	PRWrandomRunNumber = RunNb;
  

  passGRL = -1;
  //  cout << "isMC? " << isMC << endl;
  if(!isMC){ // it's data!
    passGRL = 0; 
    
    if(   (eventInfo->errorState(xAOD::EventInfo::LAr)==xAOD::EventInfo::Error ) || 
		  (eventInfo->errorState(xAOD::EventInfo::Tile)==xAOD::EventInfo::Error ) || 
		  (eventInfo->errorState(xAOD::EventInfo::SCT)==xAOD::EventInfo::Error ) || 
		  (eventInfo->isEventFlagBitSet(xAOD::EventInfo::Core, 18) )  ){
      Info(APP_NAME,"Event %llu with detector errors", tEventNumber );   
	  tDetError = 1;       
	  //       return EL::StatusCode::SUCCESS; // go to the next event
    } // end if event flags check

  } // end if not MC
  
  primvertex_z = -999;
  primvertex_x = 0;
  primvertex_y = 0;
  Nvtx = 0;
  const xAOD::VertexContainer* vertices(0);
  if( m_event->retrieve( vertices, "PrimaryVertices" ).isSuccess() ) {
    for( const auto& vx : *vertices ) {
      Nvtx++;
      if(vx->vertexType() == xAOD::VxType::PriVtx){
		// Found THE vertex
		primvertex_z = vx->z(); 
		// primvertex_x = vx->y(); 
		// primvertex_y = vx->x(); 
      }
    }
  } else { 
    Error(APP_NAME, "Failed to retrieve PV container. Exiting." );
    return EL::StatusCode::FAILURE;
  } 
  
  //  cout << __LINE__ << " " << Nvtx << endl;

  if(Nvtx==0)
    return EL::StatusCode::SUCCESS;

  // Muon Block
  NMu=0;
  Mu_eta.clear();
  Mu_phi.clear();
  Mu_pT.clear();
  Mu_SFw.clear();
  Mu_IsoSFw.clear();
  Mu_charge.clear();
  Mu_d0pvtx.clear();
  Mu_d0pvtxerr.clear();
  Mu_z0pvtx.clear();
  Mu_sigd0.clear();
  Mu_sigd0old.clear();
  Mu_d0old.clear();
  Mu_isBad.clear();
  Mu_isTight.clear();
  Mu_isSig.clear();
  Mu_isCosmic.clear();
  Mu_type.clear();
  Mu_origin.clear();
  Mu_ptcone20.clear();
  Mu_ptcone30.clear();
  Mu_ptcone40.clear();
  Mu_ptvarcone20.clear();
  Mu_ptvarcone30.clear();
  Mu_ptvarcone40.clear();
  Mu_topoetcone20.clear();
  Mu_topoetcone30.clear();
  Mu_topoetcone40.clear();
  Mu_passIsoLooseTO.clear();
  Mu_passIsoLoose.clear();
  Mu_passIsoTight.clear();
  Mu_passIsoGrad.clear();
  Mu_passIsoGradCustom.clear();
  Mu_passIsoGradCustomTight.clear();
  Mu_passIsoGradLoose.clear();
  Mu_passOR.clear();

  Mu_TrigMatch_mu26_ivarmedium.clear();
  Mu_TrigMatch_mu20_iloose_L1MU15.clear();
  Mu_TrigMatch_mu40.clear();
  Mu_TrigMatch_mu50.clear();
  Mu_TrigMatch_mu8noL1.clear();
  Mu_TrigMatch_mu14.clear();
  Mu_TrigMatch_mu18.clear();
  Mu_TrigMatch_mu18_mu8noL1.clear();
  Mu_TrigMatch_e17_lhloose_mu14.clear();
  Mu_TrigMatch_e17_lhloose_nod0_mu14.clear();
  Mu_TrigMatch_mu20_mu8noL1.clear();
  Mu_TrigMatch_mu22_mu8noL1.clear();
  Mu_TrigMatch_mu24_iloose.clear(); 
  Mu_TrigMatch_mu24_ivarloose.clear(); 
  Mu_TrigMatch_mu24_iloose_L1MU15.clear();  
  Mu_TrigMatch_mu24_ivarloose_L1MU15.clear(); 
  Mu_TrigMatchPair_mu18_mu8noL1.clear();
  Mu_TrigMatchPair_mu20_mu8noL1.clear();
  Mu_TrigMatchPair_mu22_mu8noL1.clear();
  
  //  Mu_TrigMatch_MU10.clear();
  //  Mu_TrigMatch_MU15.clear();
  //  Mu_TrigMatch_MU20.clear();
  //   EtaMuons .clear();
  //   pTMuons  .clear();
  //   MassMuons.clear();
  //   PhiMuons .clear();

  // Electron Block
  NEl=0;
  El_eta.clear();
  El_etaclus.clear();
  El_phi.clear();
  El_pT.clear();
  El_E.clear();
  El_charge.clear();
  El_sigd0.clear();
  //  El_sigd0old.clear();
  El_d0old.clear();
  El_z0pvtx.clear();
  El_d0pvtx.clear();
  El_d0pvtxerr.clear();

  El_SFwMedium.clear();
  El_SFwMediumLH.clear();
  El_SFwTight.clear();
  El_SFwTightLH.clear();
  El_SFwLooseLH.clear();
  El_SFweightCFT.clear();

  El_IsoSFwMediumLH.clear();

  El_SFwTrigMedium.clear();
  El_SFwTrigMediumLH.clear();
  El_SFwTrigTight.clear();
  El_SFwTrigMediumLH_e12_lhloose_L1EM10VH.clear();
  El_SFwTrigMediumLH_e17_lhloose.clear();
  El_SFwTrigMediumLH_single.clear();
  El_SFwTrigLooseLH.clear();

  El_isLooseLH.clear();
  El_isLoose  .clear();
  El_isMedium.clear();
  El_isMediumLH.clear();
  El_isTight.clear();
  El_isTightLH.clear();
  El_nBLayerHits.clear();
  El_expectBLayerHit.clear();
  El_truthType.clear();
  El_truthOrigin.clear();
  El_bkgTruthType.clear();
  El_bkgTruthOrigin.clear();
  El_bkgMotherPdgId.clear();
  El_firstEgMotherTruthType.clear();
  El_firstEgMotherTruthOrigin.clear();
  El_firstEgMotherPdgId.clear();
  El_chFlip.clear();
  El_ptcone20.clear();
  El_ptcone30.clear();
  El_ptcone40.clear();
  El_ptvarcone20.clear();
  El_ptvarcone30.clear();
  El_ptvarcone40.clear();
  El_topoetcone20.clear();
  El_topoetcone30.clear();
  El_topoetcone40.clear();
  El_passIsoLooseTO.clear();
  El_passIsoLoose.clear();
  El_passIsoTight.clear();
  El_passIsoGrad.clear();
  El_passIsoGradCustom.clear();
  El_passIsoGradCustomTight.clear();
  El_passIsoGradLoose.clear();
  El_TrigMatch_e12_lhloose_L1EM10VH.clear();
  El_TrigMatch_e17_lhloose.clear();
  El_TrigMatch_e60_lhmedium.clear();
  El_TrigMatch_e24_lhmedium_L1EM20VH.clear();
  El_TrigMatch_e24_lhmedium_iloose_L1EM20VH.clear();
  El_TrigMatch_e26_lhtight_nod0_ivarloose.clear();
  El_TrigMatch_2e12_lhloose_L12EM10VH.clear();
  El_TrigMatch_2e15_lhloose_L12EM10VH.clear();
  El_TrigMatch_2e15_lhvloose_L12EM13VH.clear();
  El_TrigMatch_2e15_lhvloose_nod0_L12EM13VH.clear();
  El_TrigMatch_2e17_lhvloose_nod0.clear();
  El_TrigMatch_e17_lhloose_mu14.clear();
  El_TrigMatch_e17_lhloose_nod0_mu14.clear();
  El_TrigMatch_e24_lhmedium_nod0_ivarloose.clear(); 
  El_TrigMatch_e24_lhtight_nod0_ivarloose.clear(); 
  El_TrigMatch_e60_lhmedium_nod0.clear(); 
  El_passOR.clear();
  //  El_passChargeFlipTagger.clear();
  El_passChargeFlipTaggerBDTmedium.clear();
  El_passChargeFlipTaggerBDTloose.clear();

  TruthV_eta   .clear();
  TruthV_phi   .clear();
  TruthV_pT    .clear();
  TruthV_m     .clear();
  TruthV_id    .clear();
  TruthV_index .clear();

  NTruthL = 0;
  TruthL_eta   .clear();
  TruthL_phi   .clear();
  TruthL_pT    .clear();
  TruthL_id    .clear();

  NTruthJet=0;
  TruthJet_eta.clear();
  TruthJet_phi.clear();
  TruthJet_pT.clear();
  TruthJet_E.clear();
  TruthJet_PartonTruthLabel.clear();
  TruthJet_ConeTruthLabel.clear();
  TruthJet_HadronConeExclTruthLabel.clear();
  TruthJet_ClassHF.clear();

  // JETS
  NJet=0;
  Jet_isSig.clear();
  Jet_eta.clear();
  Jet_phi.clear();
  Jet_pT.clear();
  Jet_E.clear();
  Jet_quality.clear();
  //  Jet_JVF.clear();
  Jet_JVT.clear();
  Jet_JVTsf.clear();
  totalJVTsf=0;
  Jet_MV2c20.clear();
  Jet_MV2c10.clear();
  Jet_SFw.clear();
  Jet_isSig.clear();
  //  Jet_noMV1.clear();
  Jet_PartonTruthLabel.clear();
  Jet_ConeTruthLabel.clear();
  Jet_HadronConeExclTruthLabel.clear();
  Jet_isBad.clear();
  Jet_nTrk.clear();
  Jet_deltaR.clear();
  Jet_passOR.clear();

  // MET
  Etmiss_CST_Etx=0.;
  Etmiss_CST_Ety=0.;
  Etmiss_CST_Et=0.;

  Etmiss_TST_Etx=0.;
  Etmiss_TST_Ety=0.;
  Etmiss_TST_Et=0.;

  Etmiss_TSTterm_Etx=0.;
  Etmiss_TSTterm_Ety=0.;
  Etmiss_TSTterm_Et=0.;

  //  my_x_1=0.;

  

  static SG::AuxElement::Accessor<int> dec_type("truthType");
  static SG::AuxElement::Accessor<int> dec_origin("truthOrigin");

  // Get all the objects  
  xAOD::ElectronContainer* electrons_copy(0);
  xAOD::ShallowAuxContainer* electrons_copyaux(0);

  CHECK( objTool->GetElectrons(electrons_copy,electrons_copyaux, true) );

  xAOD::JetContainer* jets_copy(0);
  xAOD::ShallowAuxContainer* jets_copyaux(0);
  //  CHECK( objTool->GetJets(jets_copy,jets_copyaux, true));
  CHECK( objTool->GetJets(jets_copy,jets_copyaux,true));
  
  xAOD::MuonContainer* muons_copy(0);
  xAOD::ShallowAuxContainer* muons_copyaux(0);
  CHECK( objTool->GetMuons(muons_copy,muons_copyaux,true) );

  std::vector<const xAOD::Electron*> myTriggeringElectrons;
  std::vector<const xAOD::Muon*> myTriggeringMuons;

  // All objects done
  

 
  //------------
  // JETS
  //------------

  CutClass::Particle theJet;

  /// OVERLAP REMOVAL
  CHECK( objTool->OverlapRemoval(electrons_copy, muons_copy, jets_copy) );
  auto& my_orTool = my_orToolbox.masterTool;
  CHECK( my_orTool->removeOverlaps(electrons_copy, muons_copy, jets_copy) );

  //   xAOD::JetContainer* goodJets = new xAOD::JetContainer(SG::VIEW_ELEMENTS);
  //   CHECK( store.record(goodJets, "MySelJets" ) );
  for (const auto& jet : *jets_copy) {
	//     if (jet->auxdata<char>("baseline") == 1  &&
	// 	jet->auxdata<char>("passOR") == 1  &&
	// 	jet->pt() > 20000.  && ( fabs( jet->eta()) < 2.8) ) {
	//       goodJets->push_back(jet);
	//     }
    objTool->IsBJet( *jet );  
  }
  if(isMC){
    objTool->BtagSF( jets_copy );
    totalJVTsf = objTool->JVT_SF( jets_copy );
  }

  

  // Get the TruthJets from the event:
  const xAOD::JetContainer* truthJets = 0;
  if(isMC)
    CHECK( m_event->retrieve( truthJets, "AntiKt4TruthJets" ) );
  
  xAOD::JetContainer::iterator jet_itr = (jets_copy)->begin();
  xAOD::JetContainer::iterator jet_end = (jets_copy)->end();
  for( ; jet_itr != jet_end; ++jet_itr ) {
    
	Jet_isSig.push_back( (int)(*jet_itr)->auxdata< char >("signal") );
    theJet.FourVector.SetPtEtaPhiE( (*jet_itr)->pt(), (*jet_itr)->eta(), (*jet_itr)->phi(), (*jet_itr)->e() );
    
	
	Jet_eta.push_back(theJet.FourVector.Eta());
	Jet_phi.push_back(theJet.FourVector.Phi());
	Jet_pT.push_back(theJet.FourVector.Pt());
	Jet_E.push_back(theJet.FourVector.E());
      
	if(isMC){
	  float min_delR = 10.;
	  for (const auto& truthJet : *truthJets) {
		float deltaEta = fabs((*jet_itr)->eta() - truthJet->eta());
		float deltaPhi = fabs((*jet_itr)->phi() - truthJet->phi());
		if (deltaPhi > TMath::Pi() ){
		  deltaPhi = 2*TMath::Pi() - deltaPhi;
		}
		float deltaR = sqrt(pow(deltaEta,2) + pow(deltaPhi,2));
		if(deltaR < min_delR)
		  min_delR = deltaR;
	  }
	  Jet_deltaR.push_back( min_delR );
	}

	Jet_quality.push_back(  (int)(*jet_itr)->auxdata< char >("bad")  );
	Jet_isSig.push_back( (int)(*jet_itr)->auxdata< char >("signal") );
	//      Jet_noMV1.push_back((int)(*jet_itr)->auxdata< char >("bjet") );
	Double_t weight_mv2c20 = -1;
	if ( !(*jet_itr)->btagging()->MVx_discriminant("MV2c20", weight_mv2c20)) {
	  Error(APP_NAME,"Failed to retrieve MV2c20 weight!");
	}
	Jet_MV2c20.push_back(weight_mv2c20);
	Jet_SFw.push_back( isMC ? (*jet_itr)->auxdata< double >("effscalefact") : 1 );

	Double_t weight_mv2c10 = -1;
	if ( !(*jet_itr)->btagging()->MVx_discriminant("MV2c10", weight_mv2c10)) {
	  Error(APP_NAME,"Failed to retrieve MV2c10 weight!");
	}
	Jet_MV2c10.push_back(weight_mv2c10);
	
	/*	std::vector<float> vret;
	(*jet_itr)->getAttribute(xAOD::JetAttribute::JVF, vret);
	Jet_JVF.push_back( vret[0] );*/
	// This is recalculated in SUSYTools FillJet method!
	/*	
	  bool update_jvt;
	bool passJVT = objTool->JetPassJVT(**jet_itr, update_jvt);
	const static SG::AuxElement::Accessor<float> acc_jvt("Jvt");
	double tmpjvt =	acc_jvt(**jet_itr);
	std::cout << " -> acc_jvt jet pT=" << theJet.FourVector.Pt() << ", jvt=" << tmpjvt << std::endl;
	//	m_jetJvtUpdateTool->updateJvt(**jet_itr);*/

	bool passJVT = objTool->JetPassJVT(**jet_itr, true);
	float jvt = (*jet_itr)->auxdata<float>("Jvt");
	//	if(tEventNumber == 147934)
	//	  std::cout << " -> jet pT=" << theJet.FourVector.Pt() << ", jvt=" << jvt << std::endl;
	Jet_JVT.push_back( jvt );
	float jvtsf = (*jet_itr)->auxdata<float>("jvtscalefact");
	Jet_JVTsf.push_back( jvtsf ); 
	int iret = -1;
	if(isMC){
	  iret = (*jet_itr)->auxdata<int>("PartonTruthLabelID") ;
	}
	Jet_PartonTruthLabel.push_back( iret );
	iret = -1;
	if(isMC){
	  iret = (*jet_itr)->auxdata<int>("ConeTruthLabelID") ;
	}
	Jet_ConeTruthLabel.push_back( iret );

	iret = -1;
	if(isMC){
	  iret = (*jet_itr)->auxdata<int>("HadronConeExclTruthLabelID") ;
	}
	Jet_HadronConeExclTruthLabel.push_back( iret );
      
	Jet_passOR.push_back( (int)(*jet_itr)->auxdata< char >("passOR") );

	std::vector<int> nTrkVec;
	(*jet_itr)->getAttribute(xAOD::JetAttribute::NumTrkPt500, nTrkVec);
	int jet_nTrk = (objTool->GetPrimVtx() == 0 || nTrkVec.size() == 0) ? 0 : nTrkVec[objTool->GetPrimVtx()->index()];
	Jet_nTrk.push_back( jet_nTrk );
   
	NJet++;
      
  }
  
     
  // Needed for the dilepton trigger scale factor tool
  int ne20=0, nmu20=0, nmu21=0, nmu23=0, nmu10=0;

  //------------
  // MUONS
  //------------
  
  // to store baseline muons for matching
  //   xAOD::MuonContainer* goodMu = new xAOD::MuonContainer(SG::VIEW_ELEMENTS);
  //   CHECK( store.record(goodMu, "MySelMu") );

  xAOD::MuonContainer::iterator mu_itr = (muons_copy)->begin();
  xAOD::MuonContainer::iterator mu_end  = (muons_copy)->end();
  

  static SG::AuxElement::Accessor<int> acc_truthType("truthType");
  static SG::AuxElement::Accessor<int> acc_truthOrigin("truthOrigin");
  

  CutClass::Particle theMu;
  std::vector<const xAOD::IParticle*> stored_muon_particles;

  //  if(false){
  for( ; mu_itr != mu_end; ++mu_itr ) {
    
	
    theMu.FourVector.SetPtEtaPhiM( (*mu_itr)->pt(), (*mu_itr)->eta(), (*mu_itr)->phi(), 105.65837 );
	
    
    const xAOD::TrackParticle* track;
	
    if ((*mu_itr)->muonType() == xAOD::Muon::SiliconAssociatedForwardMuon) {
      track = (*mu_itr)->trackParticle(xAOD::Muon::ExtrapolatedMuonSpectrometerTrackParticle);
      if (!track) continue; // don't treat SAF muons without ME track further
    }else{
      track = (*mu_itr)->primaryTrackParticle();
    }
      
    theMu.ID = track->charge()*-13; // mu-:13, mu+:-13
	
    theMu.d0pvtx = track->d0();
    theMu.z0pvtx = (*mu_itr)->auxdata< float >("z0sinTheta") ; 
    theMu.d0pvtxerr = Amg::error( track->definingParametersCovMatrix(),0);
	theMu.sigd0 = (*mu_itr)->auxdata< float >("d0sig");
	

    if ((*mu_itr)->auxdata<char >("baseline")== 1){

	  if(theMu.FourVector.Pt()<10000. ||
		 fabs(theMu.FourVector.Eta())>2.5 ) continue;
	
	  theMu.SFweight = isMC ? objTool->GetSignalMuonSF(**mu_itr, true, false) : 1. ;

	  Mu_pT.push_back(theMu.FourVector.Pt());
	  Mu_eta.push_back(theMu.FourVector.Eta());
	  Mu_phi.push_back(theMu.FourVector.Phi());
	  Mu_SFw.push_back(theMu.SFweight);
      
	  if(theMu.ID < 0)
		Mu_charge.push_back( 1 );
	  else
		Mu_charge.push_back( -1 );
	  Mu_d0pvtx.push_back(theMu.d0pvtx);
	  Mu_d0pvtxerr.push_back(theMu.d0pvtxerr);
	  Mu_sigd0.push_back(theMu.sigd0);
	  Mu_z0pvtx.push_back(theMu.z0pvtx);
	  bool isTight = false;
	  isTight = m_muonSelectionTool->accept(*mu_itr);
	  Mu_isTight.push_back( (int)isTight );
	  Mu_isBad.push_back( (int)(*mu_itr)->auxdata< char >("bad") );
	  Mu_isSig.push_back( (int)(*mu_itr)->auxdata< char >("signal") );
	  Mu_isCosmic.push_back( (int)(*mu_itr)->auxdata< char >("cosmic") );

	  /// play with OR here!
	  Mu_passOR.push_back( (int)(*mu_itr)->auxdata< char >("passOR") );
	  /*	  if(isMyOR==false || (isMyOR==true && theMu.FourVector.Pt()>pT_treshold))
			  {
			  Mu_passOR.push_back( (int)(*mu_itr)->auxdata< char >("passOR") );  /// boosted
			  }
			  else 
			  {
			  Mu_passOR.push_back( (int)(*mu_itr)->auxdata< char >("passMyOR") ); /// standard OR
			  }*/	  

	  Mu_ptcone20.push_back( (*mu_itr)->auxdata<float>("ptcone20") );
	  Mu_ptcone30.push_back( (*mu_itr)->auxdata<float>("ptcone30") );
	  Mu_ptcone40.push_back( (*mu_itr)->auxdata<float>("ptcone40") );
	  Mu_ptvarcone20.push_back( (*mu_itr)->auxdata<float>("ptvarcone20") );
	  Mu_ptvarcone30.push_back( (*mu_itr)->auxdata<float>("ptvarcone30") );
	  Mu_ptvarcone40.push_back( (*mu_itr)->auxdata<float>("ptvarcone40") );
	  Mu_topoetcone20.push_back( (*mu_itr)->auxdata<float>("topoetcone20") );
	  Mu_topoetcone30.push_back( (*mu_itr)->auxdata<float>("topoetcone30") );
	  Mu_topoetcone40.push_back( (*mu_itr)->auxdata<float>("topoetcone40") );
	
	  float sf  = isMC ? objTool->GetSignalMuonSF(**mu_itr, false, true) : 1. ;
	  Mu_IsoSFw.push_back(sf);
	
	  Mu_TrigMatch_mu26_ivarmedium.push_back(objTool->IsTrigMatched(*mu_itr, "HLT_mu26_ivarmedium"));
	  Mu_TrigMatch_mu20_iloose_L1MU15.push_back(objTool->IsTrigMatched(*mu_itr, "HLT_mu20_iloose_L1MU15"));
	  Mu_TrigMatch_mu40.push_back(objTool->IsTrigMatched(*mu_itr, "HLT_mu40"));
	  Mu_TrigMatch_mu50.push_back(objTool->IsTrigMatched(*mu_itr, "HLT_mu50"));

	  Mu_TrigMatch_mu14.push_back(objTool->IsTrigMatched(*mu_itr, "HLT_mu14"));
	  Mu_TrigMatch_mu18.push_back(objTool->IsTrigMatched(*mu_itr, "HLT_mu18"));
	  Mu_TrigMatch_mu8noL1.push_back(objTool->IsTrigMatched(*mu_itr, "HLT_mu8noL1"));

	  // 2015 items
	  Mu_TrigMatch_mu18_mu8noL1.push_back(objTool->IsTrigMatched(*mu_itr, "HLT_mu18_mu8noL1"));
	  Mu_TrigMatch_e17_lhloose_mu14.push_back(objTool->IsTrigMatched(*mu_itr, "HLT_e17_lhloose_mu14"));

	  // 2016 items
	  Mu_TrigMatch_mu20_mu8noL1.push_back(objTool->IsTrigMatched(*mu_itr, "HLT_mu20_mu8noL1"));
	  Mu_TrigMatch_mu22_mu8noL1.push_back(objTool->IsTrigMatched(*mu_itr, "HLT_mu22_mu8noL1"));
	  Mu_TrigMatch_e17_lhloose_nod0_mu14.push_back(objTool->IsTrigMatched(*mu_itr, "HLT_e17_lhloose_nod0_mu14"));

	  // 2016 single lepton
	  Mu_TrigMatch_mu24_iloose          .push_back(objTool->IsTrigMatched(*mu_itr, "HLT_mu24_iloose") );
	  Mu_TrigMatch_mu24_ivarloose	  .push_back(objTool->IsTrigMatched(*mu_itr, "HLT_mu24_ivarloose") );
	  Mu_TrigMatch_mu24_iloose_L1MU15	  .push_back(objTool->IsTrigMatched(*mu_itr, "HLT_mu24_iloose_L1MU15") );
	  Mu_TrigMatch_mu24_ivarloose_L1MU15.push_back(objTool->IsTrigMatched(*mu_itr, "HLT_mu24_ivarloose_L1MU15") );
	  // pair matching --> do after main loop
	  stored_muon_particles.push_back(*mu_itr);

	  //    	Mu_TrigMatch_MU10.push_back(objTool->IsTrigMatchedL1(*mu_itr, "L1_MU10"));
	  //    	Mu_TrigMatch_MU15.push_back(objTool->IsTrigMatchedL1(*mu_itr, "L1_MU15"));
	  //  	Mu_TrigMatch_MU20.push_back(objTool->IsTrigMatchedL1(*mu_itr, "L1_MU20"));
	  //    	Mu_TrigMatch_MU10.push_back(0);
	  //    	Mu_TrigMatch_MU15.push_back(0);
	  //  	Mu_TrigMatch_MU20.push_back(0);

	  bool passLooseTO = false;
	  if (isoLooseTO->accept( **mu_itr )) passLooseTO = true;
	  Mu_passIsoLooseTO.push_back((int)passLooseTO);

	  bool passLoose = false;
	  if (isoLoose->accept( **mu_itr )) passLoose = true;
	  Mu_passIsoLoose.push_back((int)passLoose);

	  bool passTight = false;
	  if (isoTight->accept( **mu_itr )) passTight = true;
	  Mu_passIsoTight.push_back((int)passTight);

	  bool passGrad = false;
	  if (isoGrad->accept( **mu_itr )) passGrad = true;
	  Mu_passIsoGrad.push_back((int)passGrad);

	  bool passGradCustom = false;
	  if (isoGradCustom->accept( **mu_itr )) passGradCustom = true;
	  Mu_passIsoGradCustom.push_back((int)passGradCustom);

	  bool passGradCustomTight = false;
	  if (isoGradCustomTight->accept( **mu_itr )) passGradCustomTight = true;
	  Mu_passIsoGradCustomTight.push_back((int)passGradCustomTight);

	  bool passGradLoose = false;
	  if (isoGradLoose->accept( **mu_itr )) passGradLoose = true;
	  Mu_passIsoGradLoose.push_back((int)passGradLoose);

	  int muonTruthType = -1;
	  int muonTruthOrigin = -1;

	  if(isMC){
		// Example to access MC type/origin
		const xAOD::TrackParticle* trackParticle = track;
		if (trackParticle) {
		  if (acc_truthType.isAvailable(*trackParticle)  ) muonTruthType   = acc_truthType(*trackParticle);
		  if (acc_truthOrigin.isAvailable(*trackParticle)) muonTruthOrigin = acc_truthOrigin(*trackParticle);
		}   
		Mu_type.push_back(  muonTruthType );
		Mu_origin.push_back( muonTruthOrigin );
	  }

	  // Analysis level signal muons:
	  
	  bool signal_muon = true;
	  signal_muon &= theMu.FourVector.Pt() > 10000;
	  signal_muon &= fabs(theMu.FourVector.Eta()) < 2.5;
	  signal_muon &= (*mu_itr)->auxdata<float>("ptvarcone30")/theMu.FourVector.Pt() < 0.06;
	  signal_muon &= fabs(theMu.sigd0) < 3;
	  signal_muon &= fabs(theMu.z0pvtx) < 0.5;

	  if ( signal_muon){
		myTriggeringMuons.push_back(*mu_itr);
		nmu10++;
		if (theMu.FourVector.Pt() > 20000)
		  nmu20++;
		if (theMu.FourVector.Pt() > 21000)
		  nmu21++;
		if (theMu.FourVector.Pt() > 23000)
		  nmu23++;
	  }

	  NMu++;

    }
  }

  // now fill trigger matching pairs
  for(auto mu1 : stored_muon_particles){
    Mu_TrigMatchPair_mu18_mu8noL1.emplace_back();
    Mu_TrigMatchPair_mu20_mu8noL1.emplace_back();
    Mu_TrigMatchPair_mu22_mu8noL1.emplace_back();
    for(auto mu2 : stored_muon_particles){
      Mu_TrigMatchPair_mu18_mu8noL1.back().push_back((mu1!=mu2)? objTool->IsTrigMatched(mu1,mu2,"HLT_mu18_mu8noL1") : false);
      Mu_TrigMatchPair_mu20_mu8noL1.back().push_back((mu1!=mu2)? objTool->IsTrigMatched(mu1,mu2,"HLT_mu20_mu8noL1") : false);
      Mu_TrigMatchPair_mu22_mu8noL1.back().push_back((mu1!=mu2)? objTool->IsTrigMatched(mu1,mu2,"HLT_mu22_mu8noL1") : false);
    }
  }

  //------------
  // ELECTRONS
  //------------

  // To fill Electron charge misId info
  const xAOD::TruthParticleContainer* truthP = 0;
  if (isMC) {
    CHECK( m_event->retrieve( truthP, "TruthParticles" ) );
    fillElectronChargeFlip(electrons_copy, truthP, eventInfo->mcChannelNumber() );
  }

  CutClass::Particle theEl;
   
  // Print their properties, using the tools:
  xAOD::ElectronContainer::iterator el_itr = (electrons_copy)->begin();
  xAOD::ElectronContainer::iterator el_end = (electrons_copy)->end();

  for( ; el_itr != el_end; ++el_itr ) {

    theEl.FourVector.SetPtEtaPhiM( (*el_itr)->pt(), (*el_itr)->eta(), (*el_itr)->phi(), 0.5109989 );
       
    theEl.ID = (*el_itr)->trackParticle()->charge()*-11; // e-:11, e+:-11
    theEl.d0pvtx = (*el_itr)->trackParticle()->d0();
    // theEl.z0pvtx = (*el_itr)->trackParticle()->z0() + 
    // (*el_itr)->trackParticle()->vz() - primvertex_z;     
    theEl.z0pvtx = (*el_itr)->auxdata< float >("z0sinTheta"); 
    
    theEl.d0pvtxerr = Amg::error((*el_itr)->trackParticle()->definingParametersCovMatrix(),0);
    theEl.sigd0old = 
      (*el_itr)->trackParticle()->d0() /
      Amg::error((*el_itr)->trackParticle()->definingParametersCovMatrix(),0);

    theEl.sigd0 =
      xAOD::TrackingHelpers::d0significance( (*el_itr)->trackParticle(),
											 eventInfo->beamPosSigmaX(), 
											 eventInfo->beamPosSigmaY(), 
											 eventInfo->beamPosSigmaXY() );
    
    int isLooseLH = (int)(*el_itr)->auxdata< char >("baseline");

    if ( isLooseLH ){
      
	  //       if(theEl.FourVector.Pt()<10000. ||
	  // 	 fabs(theEl.FourVector.Eta())>2.47 ) continue;
     
      El_isLooseLH.push_back( isLooseLH );

      double theSf_reco(1.);
      if(!isAtlfast && isMC ){
		CHECK(  m_electronSF_reco->getEfficiencyScaleFactor (**el_itr ,theSf_reco) );
      }

      double theSf_LhLoose(1.);
	  double theSf_trig_LhLoose(1.);
      if(!isAtlfast  && isMC ){
		CHECK(  m_electronSF_LhLoose->getEfficiencyScaleFactor (**el_itr ,theSf_LhLoose) );
		CHECK(  m_electronSF_trig_LhLoose->getEfficiencyScaleFactor (**el_itr ,theSf_trig_LhLoose) );
      }
      theEl.SFweightLooseLH = (isMC ) ? theSf_reco*theSf_LhLoose : 1.;
      theEl.SFweightTrigLooseLH = (isMC ) ? theSf_trig_LhLoose : 1.;

      int pass = -1;
      pass = (int)m_elecSelLikelihood_LhTight->accept(**el_itr) ; 
      El_isTightLH.push_back( pass ); 
      double theSf_LhTight(1.);
      double theSf_trig_LhTight(1.);
      if(!isAtlfast  && isMC ){
		CHECK(  m_electronSF_LhTight->getEfficiencyScaleFactor (**el_itr ,theSf_LhTight) );
		CHECK(  m_electronSF_trig_LhTight->getEfficiencyScaleFactor (**el_itr ,theSf_trig_LhTight) );
      }
      theEl.SFweightTightLH = (isMC  ? theSf_reco*theSf_LhTight : 1.);
      theEl.SFweightTrigTightLH = (isMC ? theSf_trig_LhTight : 1.);
	  
	  // Scale factor needed for the Charge Flip Tagger (charge flip killer)
	  double theSf_CFT(1.);
	  if(!isAtlfast  && isMC ){
		CHECK(  m_electronSF_CFT->getEfficiencyScaleFactor (**el_itr ,theSf_CFT) );
	  }


	  double tmpCFT = (isMC  ? theSf_CFT : 1.);
	  El_SFweightCFT.push_back(tmpCFT);
	  //	  std::cout << "el pt=" << theEl.FourVector.Pt() << ", SFweightCFT=" << tmpCFT << std::endl;


      // Apply no isolation or z0/d0 cuts for optimizations
      El_isMediumLH.push_back( (int)(*el_itr)->auxdata< char >("signal") );
      theEl.SFweightMediumLH = (isMC  ? objTool->GetSignalElecSF( **el_itr, true, true, false, false) : 1 );


      El_pT.push_back(theEl.FourVector.Pt());
      El_eta.push_back(theEl.FourVector.Eta());
      El_etaclus.push_back( (*el_itr)->caloCluster()->eta() );
      El_phi.push_back(theEl.FourVector.Phi());
      El_E.push_back(theEl.FourVector.E());

      El_SFwMediumLH.push_back(theEl.SFweightMediumLH);
      El_SFwTightLH.push_back(theEl.SFweightTightLH);
      El_SFwLooseLH.push_back(theEl.SFweightLooseLH);

      float sf  = isMC ? objTool->GetSignalElecSF( **el_itr, false, false, false, true) : 1. ;
      El_IsoSFwMediumLH.push_back(sf);
      
      //      El_SFwTrigTightLH.push_back(theEl.SFweightTrigTightLH);
      El_SFwTrigLooseLH.push_back (theEl.SFweightTrigLooseLH);

      float theSf = 1;
      theSf = (isMC ? objTool->GetSignalElecSF( **el_itr, false, false, true, false, "e12_lhloose_L1EM10VH") : 1 );
      El_SFwTrigMediumLH_e12_lhloose_L1EM10VH.push_back(theSf);
      theSf = (isMC ? objTool->GetSignalElecSF( **el_itr, false, false, true, false, "e17_lhloose") : 1 );
      El_SFwTrigMediumLH_e17_lhloose.push_back(theSf);
      theSf = (isMC ? objTool->GetSignalElecSF( **el_itr, false, false, true, false, "e24_lhmedium_L1EM20VH_OR_e60_lhmedium_OR_e120_lhloose") : 1 );
      El_SFwTrigMediumLH_single.push_back(theSf);

      if(theEl.ID < 0)
		El_charge.push_back( 1 );
      else
		El_charge.push_back( -1 );
      El_d0pvtx.push_back(theEl.d0pvtx);
      El_d0pvtxerr.push_back(theEl.d0pvtxerr);
      El_sigd0.push_back(theEl.sigd0);
      //      El_sigd0old.push_back(theEl.sigd0old);
      El_z0pvtx.push_back(theEl.z0pvtx);
           
      if(isMC){
        El_truthType.push_back( (*el_itr)->auxdata<int>("truthType") );
        El_truthOrigin.push_back(  (*el_itr)->auxdata<int>("truthOrigin") );
        El_bkgTruthType.push_back( (*el_itr)->auxdata<int>("bkgTruthType") );
        El_bkgTruthOrigin.push_back(  (*el_itr)->auxdata<int>("bkgTruthOrigin") );
        El_bkgMotherPdgId.push_back( (*el_itr)->auxdata<int>("bkgMotherPdgId") );
        El_firstEgMotherTruthType.push_back( (*el_itr)->auxdata<int>("firstEgMotherTruthType") );
        El_firstEgMotherTruthOrigin.push_back(  (*el_itr)->auxdata<int>("firstEgMotherTruthOrigin") );
        El_firstEgMotherPdgId.push_back( (*el_itr)->auxdata<int>("firstEgMotherPdgId") );
		El_chFlip.push_back(  (*el_itr)->auxdata< int >("chargeFlip") );
      }

      /// play with OR here!
	  El_passOR.push_back( (*el_itr)->auxdata<char>("passOR") );
	  /*if(isMyOR==false || (isMyOR==true && theEl.FourVector.Pt()>pT_treshold))
		{
		El_passOR.push_back( (int)(*el_itr)->auxdata< char >("passOR") );   /// boosted
		}
		else 
		{
		El_passOR.push_back( (int)(*el_itr)->auxdata< char >("passMyOR") ); /// standard OR
		}		
	  */
      El_ptcone20.push_back( (*el_itr)->auxdata<float>("ptcone20") );
      El_ptcone30.push_back( (*el_itr)->auxdata<float>("ptcone30") );
      El_ptcone40.push_back( (*el_itr)->auxdata<float>("ptcone40") );
      El_ptvarcone20.push_back( (*el_itr)->auxdata<float>("ptvarcone20") );
      El_ptvarcone30.push_back( (*el_itr)->auxdata<float>("ptvarcone30") );
      El_ptvarcone40.push_back( (*el_itr)->auxdata<float>("ptvarcone40") );
      El_topoetcone20.push_back( (*el_itr)->auxdata<float>("topoetcone20") );
      El_topoetcone30.push_back( (*el_itr)->auxdata<float>("topoetcone30") );
      El_topoetcone40.push_back( (*el_itr)->auxdata<float>("topoetcone40") );

      El_TrigMatch_e12_lhloose_L1EM10VH.push_back(objTool->IsTrigMatched(*el_itr, "HLT_e12_lhloose_L1EM10VH"));
      El_TrigMatch_e17_lhloose.push_back(objTool->IsTrigMatched(*el_itr, "HLT_e17_lhloose"));
      El_TrigMatch_e60_lhmedium.push_back(objTool->IsTrigMatched(*el_itr, "HLT_e60_lhmedium"));
      El_TrigMatch_e24_lhmedium_L1EM20VH.push_back(objTool->IsTrigMatched(*el_itr, "HLT_e24_lhmedium_L1EM20VH"));   
      El_TrigMatch_e24_lhmedium_iloose_L1EM20VH.push_back(objTool->IsTrigMatched(*el_itr, "HLT_e24_lhmedium_iloose_L1EM20VH"));   
	  El_TrigMatch_e26_lhtight_nod0_ivarloose.push_back(objTool->IsTrigMatched(*el_itr, "HLT_e26_lhtight_nod0_ivarloose")); 
      El_TrigMatch_2e12_lhloose_L12EM10VH      .push_back(objTool->IsTrigMatched(*el_itr,"HLT_2e12_lhloose_L12EM10VH")); 
      El_TrigMatch_2e15_lhloose_L12EM10VH      .push_back(objTool->IsTrigMatched(*el_itr,"HLT_2e15_lhloose_L12EM10VH")); 
      El_TrigMatch_2e15_lhvloose_L12EM13VH     .push_back(objTool->IsTrigMatched(*el_itr,"HLT_2e15_lhvloose_L12EM13VH")); 
      El_TrigMatch_2e15_lhvloose_nod0_L12EM13VH.push_back(objTool->IsTrigMatched(*el_itr,"HLT_2e15_lhvloose_nod0_L12EM13VH")); 
      El_TrigMatch_2e17_lhvloose_nod0          .push_back(objTool->IsTrigMatched(*el_itr,"HLT_2e17_lhvloose_nod0")); 
      El_TrigMatch_e17_lhloose_mu14            .push_back(objTool->IsTrigMatched(*el_itr,"HLT_e17_lhloose_mu14")); 
      El_TrigMatch_e17_lhloose_nod0_mu14       .push_back(objTool->IsTrigMatched(*el_itr,"HLT_e17_lhloose_nod0_mu14")); 
      El_TrigMatch_e24_lhmedium_nod0_ivarloose.push_back( objTool->IsTrigMatched(*el_itr,"HLT_e24_lhmedium_nod0_ivarloose") ); 
      El_TrigMatch_e24_lhtight_nod0_ivarloose .push_back( objTool->IsTrigMatched(*el_itr,"HLT_e24_lhtight_nod0_ivarloose") ); 
      El_TrigMatch_e60_lhmedium_nod0          .push_back( objTool->IsTrigMatched(*el_itr,"HLT_e60_lhmedium_nod0") ); 

      uint8_t nBLHits = 0;
      uint8_t expectBlayer(1);
      (*el_itr)->trackParticle()->summaryValue( nBLHits, xAOD::numberOfBLayerHits);
      (*el_itr)->trackParticle()->summaryValue( expectBlayer, xAOD::expectBLayerHit);
      //      cout << "NBlayer: " << (int)nBLHits << endl; 
      El_nBLayerHits.push_back( (int)nBLHits );
      El_expectBLayerHit.push_back( (int)expectBlayer );
      
      bool passLooseTO = false;
      if (isoLooseTO->accept( **el_itr )) passLooseTO = true;
      El_passIsoLooseTO.push_back((int)passLooseTO);

      bool passLoose = false;
      if (isoLoose->accept( **el_itr )) passLoose = true;
      El_passIsoLoose.push_back((int)passLoose);
      
      bool passTight = false;
      if (isoTight->accept( **el_itr )) passTight = true;
      El_passIsoTight.push_back((int)passTight);
      
      bool passGrad = false;
      if (isoGrad->accept( **el_itr )) passGrad = true;
      El_passIsoGrad.push_back((int)passGrad);

      bool passGradCustom = false;
      if (isoGradCustom->accept( **el_itr )) passGradCustom = true;
      El_passIsoGradCustom.push_back((int)passGradCustom);

      bool passGradCustomTight = false;
      if (isoGradCustomTight->accept( **el_itr )) passGradCustomTight = true;
      El_passIsoGradCustomTight.push_back((int)passGradCustomTight);

      bool passGradLoose = false;
      if (isoGradLoose->accept( **el_itr )) passGradLoose = true;
      El_passIsoGradLoose.push_back((int)passGradLoose);
      
	  bool CFT_accept = false;
	  //	  if ( CFTToolmedium->accept( **el_itr )) CFT_accept = true;
	  //      El_passChargeFlipTagger.push_back((int)CFT_accept);
      El_passChargeFlipTaggerBDTmedium.push_back((double)CFTToolmedium->calculate( *el_itr));

	  bool CFTLoose_accept = false;
	  //	  if ( CFTToolLoose->accept( **el_itr )) CFTLoose_accept = true;
	  //      El_passChargeFlipTagger.push_back((int)CFTLoose_accept);
      El_passChargeFlipTaggerBDTloose.push_back((double)CFTToolLoose->calculate( *el_itr));


	  // Analysis level signal electrons:

	  bool signal_electron = true;
	  signal_electron &= (int)(*el_itr)->auxdata< char >("signal");
	  signal_electron &= theEl.FourVector.Pt() > 10000;
	  signal_electron &= fabs(theEl.FourVector.Eta()) <=2.;
	  signal_electron &= (fabs((*el_itr)->caloCluster()->eta()) < 2.47 && (fabs((*el_itr)->caloCluster()->eta()) >= 1.52 || fabs((*el_itr)->caloCluster()->eta()) <= 1.37));
	  signal_electron &= (*el_itr)->auxdata<float>("ptvarcone20")/theEl.FourVector.Pt() < 0.06;
	  signal_electron &= (*el_itr)->auxdata<float>("topoetcone20")/theEl.FourVector.Pt() < 0.06;
	  signal_electron &= fabs(theEl.z0pvtx) < 0.5;
	  signal_electron &= fabs(theEl.sigd0) < 5;

	  if ( signal_electron){
		myTriggeringElectrons.push_back(*el_itr);
		if (theEl.FourVector.Pt() > 20000)
		  ne20++;
	  }

      NEl++;
    }
    //    ++el_itr_med;    
  }
  

  // Dilepton trigger scale factors
  // and finally retrieve the trigger scale factor
  double trigger_sf = 1.;
  bool triggermatch = (ne20>=2 || (ne20>=1 && nmu20>=1) || (nmu21>=1 && nmu10>=2 && PRWrandomRunNumber<290000) || (nmu23>=1 && nmu10>=2 && PRWrandomRunNumber>290000));
  if(isMC && triggermatch){
	auto cc = myTriggerSFTool->getEfficiencyScaleFactor(myTriggeringElectrons, myTriggeringMuons, trigger_sf);
	if(cc != CP::CorrectionCode::Ok)
	  {
		Warning(APP_NAME, "Scale factor evaluation failed");
	  }
	TriggerDileptonSF = trigger_sf;

	//	if( tEventNumber == 158230 || tEventNumber == 160679 || tEventNumber == 159403 || tEventNumber ==  160593) 
	//	  std::cout << tEventNumber << " " << trigger_sf << std::endl;

  }
  
  // Trigger
  for(int t=0; t<nTrig;t++){
    //cout << "debug " << nameTrig[t] << ": "  << objTool->isTrigPassed(nameTrig[t].Data()) << endl;  
    trig_map[ nameTrig[t].Data() ] = objTool->IsTrigPassed(nameTrig[t].Data());
  }
  
  MuTrigSF_HLT_mu20_iloose_L1MU15_OR_HLT_mu50 = 1.;

  //------------
  // PHOTONS
  //------------
  // Get the Photons from the event
  // const xAOD::PhotonContainer* photons = 0;
  // CHECK( m_event->retrieve( photons, "PhotonCollection" ) );
  // Info( APP_NAME, "Number of photons: %i",
  // static_cast< int >( photons->size() ) );
  
  xAOD::PhotonContainer* photons_copy(0);
  xAOD::ShallowAuxContainer* photons_copyaux(0);
  CHECK( objTool->GetPhotons(photons_copy,photons_copyaux,true) );
  
  // Print their properties, using the tools:
  xAOD::PhotonContainer::iterator ph_itr = (photons_copy)->begin();
  xAOD::PhotonContainer::iterator ph_end = (photons_copy)->end();
 

  //------------
  // GET REBUILT MET
  //------------
  
  double mpx = 0;
  double mpy = 0;
  xAOD::MissingETContainer* metcst = new xAOD::MissingETContainer;
  xAOD::MissingETAuxContainer* metcst_aux = new xAOD::MissingETAuxContainer;
  metcst->setStore(metcst_aux);
  
  xAOD::MissingETContainer* mettst = new xAOD::MissingETContainer;
  xAOD::MissingETAuxContainer* mettst_aux = new xAOD::MissingETAuxContainer;
  mettst->setStore(mettst_aux);

  // Temporary protection against events with no PV (needed to avoid MET crashes)
  const xAOD::Vertex* pv = objTool->GetPrimVtx();
  if(!pv){
    Info( APP_NAME,
		  "No primary vertex found, skip event" );
  }else{
    CHECK( objTool->GetMET(*metcst,
						   jets_copy,
						   electrons_copy,
						   muons_copy,
						   photons_copy,
						   NULL,
						   false,
						   false
						   ) );
    
    xAOD::MissingETContainer::const_iterator metcst_it = metcst->find("Final");     
    if (metcst_it == metcst->end())
      {
		Error( APP_NAME, "No RefFinal inside MET container" );
      }
    
    mpx = (*metcst_it)->mpx();
    mpy = (*metcst_it)->mpy();
    
    // Info( APP_NAME, " MET CST px = %f py = %f ", mpx, mpy );

    Etmiss_CST_Etx = mpx;
    Etmiss_CST_Ety = mpy;
    Etmiss_CST_Et = sqrt(Etmiss_CST_Etx*Etmiss_CST_Etx + Etmiss_CST_Ety*Etmiss_CST_Ety);
        
    CHECK( objTool->GetMET(*mettst,
						   jets_copy,
						   electrons_copy,
						   muons_copy,
						   photons_copy, 
						   NULL,
						   true) );

	int Nmu  = muons_copy ? muons_copy->size() : 0;
	int Nel  = electrons_copy ? electrons_copy->size() : 0;
	int Njet = jets_copy ? jets_copy->size() : 0;
	int Ntau = 0;//tau ? tau->size() : 0;
	int Nph  = photons_copy ? photons_copy->size() : 0;
	bool doTST = true;
	bool doJVT = true;

    // Info( APP_NAME, " MET TST px = %f py = %f ", (*mettst)["Final"]->mpx(), (*mettst)["Final"]->mpy() );

    mpx = (*mettst)["Final"]->mpx();
    mpy = (*mettst)["Final"]->mpy();

    Etmiss_TST_Etx = mpx;
    Etmiss_TST_Ety = mpy;
    Etmiss_TST_Et = sqrt(Etmiss_TST_Etx*Etmiss_TST_Etx + Etmiss_TST_Ety*Etmiss_TST_Ety);

    mpx = (*mettst)["PVSoftTrk"]->mpx();
    mpy = (*mettst)["PVSoftTrk"]->mpy();

    Etmiss_TSTterm_Etx = mpx;
    Etmiss_TSTterm_Ety = mpy;
    Etmiss_TSTterm_Et = sqrt(Etmiss_TSTterm_Etx*Etmiss_TSTterm_Etx + Etmiss_TSTterm_Ety*Etmiss_TSTterm_Ety);

	/*  if(tEventNumber == 169557)
		{
		std::cout<<APP_NAME<<Form(" DEBUG EvtNbr = %i\t Objects for MET: %i mu, %i el, %i jets, %i ph, %i tau [JVT=%i|TST=%i]",tEventNumber,Nmu,Nel,Njet,Nph,Ntau,doTST,doJVT)<<std::endl;
		std::cout << APP_NAME<< "MET=" << Etmiss_TST_Et << std::endl;
		std::cout << APP_NAME<< "MET TSTterm=" << Etmiss_TSTterm_Et << std::endl;
		}*/ 

  }

  //  Info( APP_NAME, "Starting truth...." );

  // Truth business 

  
  int ttbarHF(-999), ttbarHF_ext(-999), ttbarHF_prompt(-999); 
  std::map<int,int> mapJetClassHF;
  mapJetClassHF.clear();
  if (isMC) {
  // Ttbar + HF classification
  bool debugme=false;
  if(debugme)
    std::cout << "\nEventNumber=" << tEventNumber << std::endl;
  
  ClassifyAndCalculateHF classHF(m_event,"TruthParticles","AntiKt4TruthJets");
  classHF.apply(ttbarHF, ttbarHF_ext, ttbarHF_prompt, mapJetClassHF);
  
  //	int counter=0;
  //	int jet_n=truthJets->size();
  //	for(auto jptr : *truthJets){
  //	  std::cout << " MyxAODAna -> jet " << counter << "/" << jet_n << ", pT=" << jptr->pt() << ", eta=" << jptr->eta() << ", classHF=" << mapJetClassHF[counter]<< std::endl;
  //	  	counter++;
  //	}
  
  int extB = 0; 
  int extC = 0; 
  
  //  ext_code = 1000*b+100*B+10*c+1*C;
  int itr=0;
  int ttbarHF_ext_tmp = ttbarHF_ext;
  while (ttbarHF_ext_tmp > 0) {
    int digit = ttbarHF_ext_tmp % 10;
    if(itr == 0 || itr == 1)
      extC += digit;
    if(itr == 2 || itr == 3)
      extB += digit;
    ttbarHF_ext_tmp /= 10;
    itr++;
  }
  
  if(debugme){
    //	if(ttbarHF_ext != 0){
    //	   std::cout << "====>  ttbarHF=" << ttbarHF << ", ttbarHF_ext=" << ttbarHF_ext << ", ttbarHF_prompt=" << ttbarHF_prompt << std::endl;
    std ::cout << "============>  #b=" << extB << ", #c=" << extC << std::endl;
    //	}
  }
  
  extraB = extB;
  extraC = extC;
  
  
  // Cross check classification
  if(debugme)
    std::cout << "------------- cross check -------------" << std::endl;
  // Get the Truth Particles from the event:
  const xAOD::TruthParticleContainer* truthPximo = 0;
  ANA_CHECK( m_event->retrieve( truthPximo, "TruthParticles" ) );
  if(debugme)
    Info( APP_NAME, "Number of TRUTH particles: %i",
	  static_cast< int >( truthPximo->size() ) );
  
  int extratestB = 0;
  int extratestC = 0;
  for (const auto& tp : *truthPximo) {

      if( tp->pt() < 10E03) // omit low-pT stuff
    continue;
      if( fabs(tp->pdgId())==5 || fabs(tp->pdgId())==4 ){
    int firstMo = 0;
    if(tp->nParents() >0){
      for (const auto& tpC : *truthPximo) {
        if (tpC->barcode() == tp->parent(0)->barcode() ) {
          firstMo = tpC->pdgId();
        }
      }
    }

    if(firstMo == tp->pdgId()) continue;

    if(fabs(tp->pdgId())==5){
      if( fabs(firstMo)!=6)
        extratestB++;
    }
    if(fabs(tp->pdgId())==4){
      if( fabs(firstMo)!=24 )
        extratestC++;
    }

	if(debugme){
    Info( APP_NAME, "TRUTH pdgID:%d   pT/eta/phi: %g/%g/%g   barcode: %d status: %d  parents: %d %d",
          tp->pdgId(),  tp->pt(),   tp->eta(),   tp->phi(),
          tp->barcode(),    tp->status(),
          tp->nParents(), firstMo
          );
	}
	  }
	if(debugme)
	  std ::cout << "============>  #b=" << extratestB << ", #c=" << extratestC << std::endl;
	}

	// End Ttbar + HF classification
}

  // find Z,W and decay products
  vector<CutClass::Particle> vTruthL; vTruthL.clear();
  //   vector<CutClass::Particle> vTruthV; vTruthV.clear();
  //   vector<CutClass::Particle> vTruthVch; vTruthVch.clear();
  
  //  const xAOD::TruthParticleContainer* truthP = 0;
  if (isMC) {

    for (const auto& truthJet : *truthJets) {
    
      theJet.FourVector.SetPtEtaPhiE( truthJet->pt(), 
									  truthJet->eta(), 
									  truthJet->phi(), 
									  truthJet->e() );
    
	  //	  if(theJet.FourVector.Pt()<20000. ) continue;

      int iret = -1;
      iret = truthJet->auxdata<int>("PartonTruthLabelID") ;
      TruthJet_PartonTruthLabel.push_back( iret );
      iret = -1;
      iret = truthJet->auxdata<int>("ConeTruthLabelID") ;
      TruthJet_ConeTruthLabel.push_back( iret );
	  // iret = -1;
	  // iret = truthJet->auxdata<int>("HadronConeExclTruthLabelID") ;
	  // TruthJet_HadronConeExclTruthLabel.push_back( iret );
	
      TruthJet_eta.push_back(theJet.FourVector.Eta());
      TruthJet_phi.push_back(theJet.FourVector.Phi());
      TruthJet_pT.push_back (theJet.FourVector.Pt());
      TruthJet_E.push_back  (theJet.FourVector.E());
      TruthJet_ClassHF.push_back  (mapJetClassHF[NTruthJet]);
      NTruthJet++;
    }
    

    const xAOD::MissingETContainer* TruthMET = 0;
    CHECK(m_event->retrieve( TruthMET, "MET_Truth" ) );
    
    xAOD::MissingETContainer::const_iterator TruthMET_it = TruthMET->find("NonInt");
    if (TruthMET_it == TruthMET->end()) std::cout << "No NonINT inside MET container" << std::endl;
    xAOD::MissingET* TruthMET_NonInt = *TruthMET_it;

    //     const xAOD::MissingETContainer* truth_met = 0 ;
    //     CHECK(m_event->retrieve(truth_met, "MET_Truth"));
    //     xAOD::MissingETContainer* met= new xAOD::MissingETContainer();
    //     xAOD::MissingETAuxContainer* met_aux = new xAOD::MissingETAuxContainer();
    //     met->setStore(met_aux);
    //     met->push_back(new xAOD::MissingET(truth_met->at(0)->mpx(),truth_met->at(0)->mpy(),truth_met->at(0)->sumet(),"Final",MissingETBase::Source::total()));
    Etmiss_Truth_Etx = TruthMET_NonInt->mpx(); 
    Etmiss_Truth_Ety = TruthMET_NonInt->mpy(); 
    Etmiss_Truth_Et  = sqrt(Etmiss_Truth_Etx*Etmiss_Truth_Etx+Etmiss_Truth_Ety*Etmiss_Truth_Ety); 
    
	//     cout << " MEt: " << Etmiss_Truth_Etx
	// 	 << " / " << Etmiss_Truth_Ety 
	// 	 << " / " << Etmiss_Truth_Et << endl; 


	//     CutClass::Particle theV;
	//     CutClass::Particle theVchild1;
	//     CutClass::Particle theVchild2;
	//     int nVfound = 0;
    
	//     bool foundFirst = false;
	//     bool foundSecond = false; 
    
    // Get the Truth Particles from the event:
    //  CHECK( m_event->retrieve( truthP, "TruthParticles" ) );
	//     Info( APP_NAME, "Number of truth particles: %i",
	// 	  static_cast< int >( truthP->size() ) ); 

    pdgid1 = 0;
    pdgid2 = 0;
    gluDecay1 = 0;
    gluDecay2 = 0;

    if( isMC ){ 
      CHECK(objTool->FindSusyHP(truthP, pdgid1, pdgid2) );
      //     Info( APP_NAME, "Initial SUSY particles: %i %i",pdgid1, pdgid2 );
          
      xAOD::TruthParticleContainer::const_iterator truthP_itr = truthP->begin();
      xAOD::TruthParticleContainer::const_iterator truthP_end = truthP->end();
      int nGoodL = 0;
      CutClass::Particle theL;
      for (const auto& tp : *truthP) {
       
		if( tp->pt() > 10000. ){  // dump only particles with pT>10 GeV
	  
		  // 	 Info( APP_NAME, "pdgID:%d   pT/eta/phi: %g/%g/%g   barcode: %d  status: %d  parents: %d %d",
		  // 	       tp->pdgId(),  tp->pt(),   tp->eta(),   tp->phi(),
		  // 	       tp->barcode(),    tp->status(),
		  // 	       tp->nParents(),
		  // 	       tp->parent(0)->barcode()
		  // 	       );
		  if(
			 (fabs( tp->pdgId() ) == 11 || fabs( tp->pdgId() ) ==13 || 
			  fabs( tp->pdgId() ) ==12 || fabs( tp->pdgId() ) ==14 || fabs( tp->pdgId() ) ==16) 
			 //(fabs( tp->pdgId() ) >= 11 && fabs( tp->pdgId() ) <=16 ) 
			 && tp->nParents()>0){
			for (const auto& tpC : *truthP) {
			  if (tpC->barcode() == tp->parent(0)->barcode() ) {
				if( abs(tpC->pdgId()) > 1000000 || abs(tpC->pdgId())==23 || abs(tpC->pdgId()) ==24 
					// || abs(tpC->pdgId()) ==15 
					){
				  //		  Info( APP_NAME, "This is a good lepton mothered by a %d !!!", tpC->pdgId());
				  nGoodL++;
				  theL.FourVector.SetPtEtaPhiM(tp->pt(),tp->eta(),tp->phi(),tp->m() );
				  theL.ID=(int)(tp->pdgId());
				  vTruthL.push_back(theL);
				} // End SUSY/W/Z
		
				if( //(fabs( tp->pdgId() ) == 11 || fabs( tp->pdgId() ) ==13) && 
				   abs(tpC->pdgId()) ==15 && tpC->nParents()>0 ){
				  // Need to check the mother of the tau too!
				  for (const auto& tpCC : *truthP) {
					if (tpCC->barcode() == tpC->parent(0)->barcode() ) {
					  if( abs(tpCC->pdgId()) > 1000000 || abs(tpCC->pdgId())==23 || abs(tpCC->pdgId()) ==24 ){
						// That's a e/m coming with mother tau and grandmother SUSY/W/Z -> save it
		     
						// Info( APP_NAME, "This is a good lepton mothered by a %d !!!", tpC->pdgId());
						nGoodL++;
						theL.FourVector.SetPtEtaPhiM(tp->pt(),tp->eta(),tp->phi(),tp->m() );
						theL.ID=(int)(tp->pdgId());
						vTruthL.push_back(theL);
					  }
					} // end tpCC barcode loop
				  } // end truthP block
				} // End tau loop	
		
			  }
			}
	    
		  }
		}
      }
      //     Info( APP_NAME, "Total number of good leptons: %d ", nGoodL );

      for (const auto& tp : *truthP) {
		//check if gluino
		if (tp->pdgId()==1000021){
		  int _ch[2]={0}; int ich=0;
		  bool foundSUSY = false;
		  if (tp->nChildren() == 3) {
			for(unsigned int ch=0; ch<tp->nChildren(); ch++){
			  for (const auto& tpC : *truthP) {
				if (tpC->barcode() == tp->child(ch)->barcode() ) {
				  if((abs(tpC->pdgId()) > 1000020 && abs(tpC->pdgId()) < 1000040)){
					foundSUSY=true;
				  }else{
					_ch[ich]=tpC->pdgId(); 
					ich++;
					//  cout << " `- AA Ch: " <<tpC->pdgId() << " " << tpC->barcode() <<  " " << tpC->nChildren() << endl;
				  }
				}
			  }
			}
		  }
		  if(foundSUSY && _ch[0]==-1*_ch[1]){
			if(gluDecay1==0) gluDecay1=abs(_ch[0]);
			else gluDecay2=abs(_ch[0]);
		  }
		} //END if gluino
       
      }
      //     Info( APP_NAME, "Gluino decays: %i %i",gluDecay1, gluDecay2 );
      
    }
    
	//	Info( APP_NAME, "Ended truth...." );
    
    
    // PDF INFO!!!
    // Get the Truth Event information from the event:
    const xAOD::TruthEventContainer* truthE = 0;
    CHECK( m_event->retrieve( truthE, "TruthEvents" ) );
    
	xAOD::TruthEventContainer::const_iterator truthE_itr = truthE->begin();
	xAOD::TruthEventContainer::const_iterator truthE_end = truthE->end();
	for( ; truthE_itr != truthE_end; ++truthE_itr ) {
     
	  if((*truthE_itr)->isAvailable< float >( "X1" ) ){
		TruthX1 = (*truthE_itr)->auxdata<float>("X1");
		TruthX2 = (*truthE_itr)->auxdata<float>("X2");
		TruthXF1 = (*truthE_itr)->auxdata<float>("XF1");
		TruthXF2 = (*truthE_itr)->auxdata<float>("XF2");
		TruthQ   = (*truthE_itr)->auxdata<float>("Q");
		TruthPDGID1 = (*truthE_itr)->auxdata<int>("PDGID1");
		TruthPDGID2 = (*truthE_itr)->auxdata<int>("PDGID2");
		TruthPDFID1 = (*truthE_itr)->auxdata<int>("PDFID1");
		TruthPDFID2 = (*truthE_itr)->auxdata<int>("PDFID2");
	  }else{ // Somehow it does not exist
		TruthX1     = -1;
		TruthX2     = -1;
		TruthXF1    = -1;
		TruthXF2    = -1;
		TruthQ      = -1;
		TruthPDGID1 = -1;
		TruthPDGID2 = -1;
		TruthPDFID1 = -1;
		TruthPDFID2 = -1;    
	  }
	}

	//   Info( APP_NAME, "Ended PDF...." );

   
    
	NTruthL = vTruthL.size();
	for(Int_t i=0;i<NTruthL;i++){
	  TruthL_eta.push_back(vTruthL[i].FourVector.Eta());
	  TruthL_phi.push_back(vTruthL[i].FourVector.Phi());
	  TruthL_pT.push_back(vTruthL[i].FourVector.Pt());
	  TruthL_id.push_back((int)vTruthL[i].ID);
	}
  


    // END truth business

	/*
	// Sherpa weights
	// SherpaNjetWeight
	//        The reweight was obtained using Anti-kt R=0.4 at the particle level and removing leptons from 
	//        the decay of the Z. Therefore it should be applied as a function of the number of truth jets 
	//        with pt>20 and |eta|<4.5 after removing overlapping leptons (e.g. by using AntiKt4TruthWZJets 
	//        or AntiKt4TruthJets where jets within DR<0.2 of stable leptons with pt>25 and |eta|<2.5 
	//        have been removed). 
	// Get the TruthJets from the event:
	int njet = 0;
	for (const auto& truthJet : *truthJets) {
	if( truthJet->pt()>20E03 && 
	fabs(truthJet->eta())<4.5){

	theJet.FourVector.SetPtEtaPhiE( truthJet->pt(), 
	truthJet->eta(), 
	truthJet->phi(), 
	truthJet->e() );
	 
	bool overlapped = false;
	for(Int_t i=0;i<NTruthL;i++){
	if( theJet.FourVector.DeltaR(vTruthL[i].FourVector)<0.2 )
	overlapped = true;
	}
	if(!overlapped)
	njet++;      


	}
	}
	SherpaNjetWeight =  objTool->getSherpaVjetsNjetsWeight(njet);
	*/     
       
	// Default SUSYTools
	SherpaNjetWeight =  objTool->getSherpaVjetsNjetsWeight();

  }

  

  //   return EL::StatusCode::SUCCESS;

 
  //  Info( APP_NAME, "Time to fill...." );
  
  // keep track of all the events
  hWeights->Fill(1., EventWeight);
  hEvents-> Fill(1., 1.);
  hWeightsSquared->Fill(1., EventWeight*EventWeight);
  //Fill our tree    
  if( isMC || 
      (NMu+NEl)>0 
	  ){
    hWeights->Fill(2., EventWeight);
    hEvents-> Fill(2., 1.);
    hWeightsSquared->Fill(2., EventWeight*EventWeight);
    
    MyTree->Fill();
  }

  //    Info( APP_NAME, "Filled, time to delete...." );

  //  return EL::StatusCode::SUCCESS;

  // The containers created by the shallow copy are owned by you. Remember to delete them
  //  delete jets_copy;
  //  delete jets_copyaux;
  //  delete muons_copy;
  //  delete muons_copyaux;
  //  delete electrons_copy;
  //  delete electrons_copyaux;
  //  delete photons_copy;
  //  delete photons_copyaux;
  delete metcst;
  delete metcst_aux;
  delete mettst;
  delete mettst_aux;
  //  delete goodJets;

  store.clear(); 

  //  Info( APP_NAME, "Out of method...." );
  
  //  CALLGRIND_STOP_INSTRUMENTATION;

  return EL::StatusCode::SUCCESS;
}



EL::StatusCode MyxAODAnalysis :: postExecute ()
{
  // Here you do everything that needs to be done after the main event
  // processing.  This is typically very rare, particularly in user
  // code.  It is mainly used in implementing the NTupleSvc.
  return EL::StatusCode::SUCCESS;
}



EL::StatusCode MyxAODAnalysis :: finalize ()
{
  // This method is the mirror image of initialize(), meaning it gets
  // called after the last event has been processed on the worker node
  // and allows you to finish up any objects you created in
  // initialize() before they are written to disk.  This is actually
  // fairly rare, since this happens separately for each worker node.
  // Most of the time you want to do your post-processing on the
  // submission node after all your histogram outputs have been
  // merged.  This is different from histFinalize() in that it only
  // gets called on worker nodes that processed input events.

  const char* APP_NAME = "finalize()";   
  //  Info(APP_NAME, "starting" );


  if( objTool ) {
	delete objTool;
	objTool = 0;
  }

  //   if( objTool_lhmed ) {
  //    delete objTool_lhmed;
  //    objTool_lhmed = 0;
  //   }

  //   if( objTool_tight ) {
  //    delete objTool_tight;
  //    objTool_tight = 0;
  //   }

  //   if( objTool_med ) {
  //    delete objTool_med;
  //    objTool_med = 0;
  //   }

  if( isoLooseTO ){
    delete isoLooseTO;
    isoLooseTO = 0;
  }

  if( isoLoose ){
    delete isoLoose;
    isoLoose = 0;
  }

  if( isoTight ){
    delete isoTight;
    isoTight = 0;
  }

  if( isoGrad ){
    delete isoGrad;
    isoGrad = 0;
  }

  if( isoGradLoose ){
    delete isoGradLoose;
    isoGradLoose = 0;
  }

  if( isoGradCustomTight ){
    delete isoGradCustomTight;
    isoGradCustomTight = 0;
  }

  if( isoGradCustom ){
    delete isoGradCustom;
    isoGradCustom = 0;
  }

  if( CFTToolmedium ){
    delete CFTToolmedium;
    CFTToolmedium = 0;
  }

  if( CFTToolLoose ){
    delete CFTToolLoose;
    CFTToolLoose = 0;
  }

  //   // GRL
  //   if( m_grl ) {
  //     delete m_grl;
  //     m_grl = 0;
  //   }
  
  //   // Pileup_Reweighting
  //   if( m_pileupReweightingTool ) {
  //    delete m_pileupReweightingTool;
  //    m_pileupReweightingTool = 0;
  //   }
  

  //  CALLGRIND_DUMP_STATS;
  //  Info(APP_NAME, "All done, bye!" );
  //  MyTree->Print();

  return EL::StatusCode::SUCCESS;
}



EL::StatusCode MyxAODAnalysis :: histFinalize ()
{
  // This method is the mirror image of histInitialize(), meaning it
  // gets called after the last event has been processed on the worker
  // node and allows you to finish up any objects you created in
  // histInitialize() before they are written to disk.  This is
  // actually fairly rare, since this happens separately for each
  // worker node.  Most of the time you want to do your
  // post-processing on the submission node after all your histogram
  // outputs have been merged.  This is different from finalize() in
  // that it gets called on all worker nodes regardless of whether
  // they processed input events.

  //   hEvents->SetBinContent(1, m_initialNevents);
  //   hEvents->SetBinContent(2, m_finalNevents);
  
  //   hWeights->SetBinContent(1, m_finalSumOfWeights);
  //   hWeights->SetBinContent(2, m_initialSumOfWeights);
  


  return EL::StatusCode::SUCCESS;
}
