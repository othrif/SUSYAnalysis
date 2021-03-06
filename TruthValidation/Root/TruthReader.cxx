#include <EventLoop/Job.h>
#include <EventLoop/StatusCode.h>
#include <EventLoop/Worker.h>
#include <TruthValidation/TruthReader.h>

#include "xAODRootAccess/Init.h"
#include "xAODRootAccess/TEvent.h"
#include "xAODRootAccess/tools/Message.h"
#include "xAODEventInfo/EventInfo.h"
#include "xAODTruth/TruthParticleContainer.h"
#include "xAODJet/JetContainer.h"
#include "xAODJet/JetAuxContainer.h"
#include "xAODMissingET/MissingETContainer.h"

/// Helper macro for checking xAOD::TReturnCode return values
#define EL_RETURN_CHECK( CONTEXT, EXP )			   \
  do {                                                     \
    if( ! EXP.isSuccess() ) {				   \
      Error( CONTEXT,					   \
	     XAOD_MESSAGE( "Failed to execute: %s" ),	   \
	     #EXP );					   \
      return EL::StatusCode::FAILURE;			   \
    }							   \
  } while( false )


// this is needed to distribute the algorithm to the workers
ClassImp(TruthReader)


TruthReader :: TruthReader ()
{
  // Here you put any code for the base initialization of variables,
  // e.g. initialize all pointers to 0.  Note that you should only put
  // the most basic initialization here, since this method will be
  // called on both the submission and the worker node.  Most of your
  // initialization code will go into histInitialize() and
  // initialize().
}



EL::StatusCode TruthReader :: setupJob (EL::Job& job)
{
  // Here you put code that sets up the job on the submission object
  // so that it is ready to work with your algorithm, e.g. you can
  // request the D3PDReader service or add output files.  Any code you
  // put here could instead also go into the submission script.  The
  // sole advantage of putting it here is that it gets automatically
  // activated/deactivated when you add/remove the algorithm from your
  // job, which may or may not be of value to you.

  // let's initialize the algorithm to use the xAODRootAccess package
  job.useXAOD ();
  EL_RETURN_CHECK( "setupJob()", xAOD::Init() ); // call before opening first file

  return EL::StatusCode::SUCCESS;
}



EL::StatusCode TruthReader :: histInitialize ()
{
  // Here you do everything that needs to be done at the very
  // beginning on each worker node, e.g. create histograms and output
  // trees.  This method gets called before any input files are
  // connected.

  // Acceptance
  //  h_AcceptanceTot   = new TH1F("h_AcceptanceTot", "h_AcceptanceTot;SR;A", 8, 0, 8);
  h_AcceptanceTot   = new TH1F("h_AcceptanceTot", "h_AcceptanceTot;SR;A", 3, 0, 3);
  h_AcceptanceTot->Sumw2();
  wk()->addOutput (h_AcceptanceTot);

  //  h_Acceptance   = new TH1F("h_Acceptance", "h_Acceptance;SR;A", 8, 0, 8);
  h_Acceptance   = new TH1F("h_Acceptance", "h_Acceptance;SR;A", 3, 0, 3);
  h_Acceptance->Sumw2();
  wk()->addOutput (h_Acceptance);

  h_Norm   = new TH1F("h_Norm", "h_Norm;;Norm", 1, 0, 1);
  h_Norm->Sumw2();
  wk()->addOutput (h_Norm);

  return EL::StatusCode::SUCCESS;
}



EL::StatusCode TruthReader :: fileExecute ()
{
  // Here you do everything that needs to be done exactly once for every
  // single file, e.g. collect a list of all lumi-blocks processed
  return EL::StatusCode::SUCCESS;
}



EL::StatusCode TruthReader :: changeInput (bool firstFile)
{
  // Here you do everything you need to do when we change input files,
  // e.g. resetting branch addresses on trees.  If you are using
  // D3PDReader or a similar service this method is not needed.
  return EL::StatusCode::SUCCESS;
}



EL::StatusCode TruthReader :: initialize ()
{
  // Here you do everything that you need to do after the first input
  // file has been connected and before the first event is processed,
  // e.g. create additional histograms based on which variables are
  // available in the input files.  You can also create all of your
  // histograms and trees in here, but be aware that this method
  // doesn't get called if no events are processed.  So any objects
  // you create here won't be available in the output if you have no
  // input events.

  xAOD::TEvent* event = wk()->xaodEvent();

  // as a check, let's see the number of events in our xAOD
  Info("initialize()", "Number of events = %lli", event->getEntries() ); // print long long int

  return EL::StatusCode::SUCCESS;
}



EL::StatusCode TruthReader :: execute ()
{
  // Here you do everything that needs to be done on every single
  // events, e.g. read input variables, apply cuts, and fill
  // histograms and trees.  This is where most of your actual analysis
  // code will go.

  xAOD::TEvent* event = wk()->xaodEvent();

  //----------------------------
  // Event information
  //--------------------------- 
  const xAOD::EventInfo* eventInfo = 0;
  EL_RETURN_CHECK("execute",event->retrieve( eventInfo, "EventInfo")); 
  // std::cout << eventInfo->eventNumber() << std::endl;

  //----------------------------
  // Jets
  //--------------------------- 
  const xAOD::JetContainer* jets = 0;
  EL_RETURN_CHECK("execute()",event->retrieve( jets, "AntiKt4TruthJets" ));

  std::vector<xAOD::Jet*> v_jet;

  xAOD::JetContainer::const_iterator jet_itr = jets->begin();
  xAOD::JetContainer::const_iterator jet_end = jets->end();
  for( ; jet_itr != jet_end; ++jet_itr ) {
    if(( (*jet_itr)->pt() * 0.001) < 25 ) continue;
    if( fabs((*jet_itr)->eta()) > 2.5 ) continue;

    xAOD::Jet* jet = new xAOD::Jet();
    jet->makePrivateStore( **jet_itr );
    v_jet.push_back(jet);
  }

  //----------------------------
  // Electron
  //--------------------------- 
  const xAOD::TruthParticleContainer* electrons = 0;
  EL_RETURN_CHECK("execute",event->retrieve( electrons, "TruthElectrons" ));

  std::vector<xAOD::TruthParticle*> v_electron;

  xAOD::TruthParticleContainer::const_iterator electron_itr = electrons->begin();
  xAOD::TruthParticleContainer::const_iterator electron_end = electrons->end();
  for( ; electron_itr != electron_end; ++electron_itr ) {
    if(( (*electron_itr)->pt() * 0.001) < 25 ) continue;
    if( fabs((*electron_itr)->eta()) > 2.47 ) continue;

    xAOD::TruthParticle* electron = new xAOD::TruthParticle();
    electron->makePrivateStore( **electron_itr );
    v_electron.push_back(electron);
  }

  //----------------------------
  // Muons
  //--------------------------- 
  const xAOD::TruthParticleContainer* muons = 0;
  EL_RETURN_CHECK("execute",event->retrieve( muons, "TruthMuons" ));

  std::vector<xAOD::TruthParticle*> v_muon;

  xAOD::TruthParticleContainer::const_iterator muon_itr = muons->begin();
  xAOD::TruthParticleContainer::const_iterator muon_end = muons->end();
  for( ; muon_itr != muon_end; ++muon_itr ) {
    if(( (*muon_itr)->pt() * 0.001) < 25 ) continue;
    if( fabs((*muon_itr)->eta()) > 2.5 ) continue;

    xAOD::TruthParticle* muon = new xAOD::TruthParticle();
    muon->makePrivateStore( **muon_itr );
    v_muon.push_back(muon);
  }

  //----------------------------
  // MET
  //--------------------------- 
  const xAOD::MissingETContainer* met = 0;
  EL_RETURN_CHECK("execute()",event->retrieve( met, "MET_Truth" ));

  xAOD::MissingETContainer::const_iterator met_it = met->begin();

  //----------------------------
  // Overlap Removal
  //--------------------------- 

  // Jet Removal with electron
  for(int i_jet = 0 ; i_jet < (int)v_jet.size() ; i_jet++ ){
    for(int i_el = 0 ; i_el < (int)v_electron.size() ; i_el++ ){
      if( v_jet.at(i_jet)->p4().DeltaR(v_electron.at(i_el)->p4()) < 0.2) { // Remove Jet element and move backward
        v_jet.erase( v_jet.begin()+i_jet);
        i_jet-- ;
        break;
      }
    }
  }

  // Electron Removal
  for(int i_el = 0 ; i_el < (int)v_electron.size() ; i_el++ ){
    for(int i_jet = 0 ; i_jet < (int)v_jet.size() ; i_jet++ ){
      if( v_electron.at(i_el)->p4().DeltaR(v_jet.at(i_jet)->p4()) < 0.4) { // Remove Electron element and move backward
        v_electron.erase( v_electron.begin()+i_el);
        i_el-- ;
        break;
      }
    }
  }

  // Jet Removal with muon
  for(int i_jet = 0 ; i_jet < (int)v_jet.size() ; i_jet++ ){
    for(int i_mu = 0 ; i_mu < (int)v_muon.size() ; i_mu++ ){
      if( v_jet.at(i_jet)->p4().DeltaR(v_muon.at(i_mu)->p4()) < 0.2) { // Remove Jet element and move backward
        v_jet.erase( v_jet.begin()+i_jet);
        i_jet-- ;
        break;
      }
    }
  }

  // Muon Removal
  for(int i_mu = 0 ; i_mu < (int)v_muon.size() ; i_mu++ ){
    for(int i_jet = 0 ; i_jet < (int)v_jet.size() ; i_jet++ ){
      if( v_muon.at(i_mu)->p4().DeltaR(v_jet.at(i_jet)->p4()) < ( 0.04 + 10e3/v_muon.at(i_mu)->pt() ) ) { // Remove Muon element and move backward
        v_muon.erase( v_muon.begin()+i_mu);
        i_mu-- ;
        break;
      }
    }
  }

  //----------------------------
  // Compute selection variable
  //--------------------------- 

  // Check the 3LSS requirement
  std::vector<xAOD::TruthParticle*> Lep;

  for( int i = 0 ; i < (int)v_electron.size() ; i++ ) 
	Lep.push_back(v_electron.at(i));
  for( int j = 0 ; j < (int)v_muon.size() ; j++ ) 
  	Lep.push_back(v_muon.at(j));

  bool is3LSS = false;

  int numLept = 0;
  int chLept = 1;
  for( int i = 0 ; i < (int)Lep.size() ; i++ ) {
	numLept++;
	chLept *= Lep.at(i)->charge();
  }
  
  int N_lep = (int) Lep.size();
  if( N_lep> 2)
	  for (int i = 0; i < N_lep; i++) 
		for (int j = i+1; j < N_lep; j++) 
		  for (int k = j+1; k < N_lep; k++) 
			if((Lep.at(i)->charge()*Lep.at(j)->charge())>0 && (Lep.at(i)->charge()*Lep.at(k)->charge())>0)
			  is3LSS = true;

  // Check the SS/3L requirement
  bool isSS = false;

  int N_el = (int)v_electron.size();
  int N_mu = (int)v_muon.size();

  if( (N_el+N_mu) > 2 ) isSS = true; // 3L
  else if ( (N_el+N_mu) == 2 ){ // SS ?
    if( N_el == 2 ) //ee
      isSS = v_electron.at(0)->charge() == v_electron.at(1)->charge() ;      
    else if( N_el == 1 && N_mu == 1 ) //em
      isSS = v_electron.at(0)->charge() == v_muon.at(0)->charge() ;
    else if( N_mu == 2 ) //mm
      isSS = v_muon.at(0)->charge() == v_muon.at(1)->charge() ;
  }

  // Compute Number b-jets
  int N_bjet =0;
  for( int i_jet = 0 ; i_jet < (int)v_jet.size() ; i_jet++ ) {
    if( abs( v_jet.at(i_jet)->auxdata<int>("PartonTruthLabelID") ) == 5 ) 
      N_bjet++;
  }

  // Compute HT
  Double_t ht=0;
  for( int i_jet = 0 ; i_jet < (int)v_jet.size() ; i_jet++ ) {
    ht += ( v_jet.at(i_jet)->pt() ) * 0.001 ;
  }
  for( int i_electron = 0 ; i_electron < (int)v_electron.size() ; i_electron++ ) {
    ht += ( v_electron.at(i_electron)->pt() ) * 0.001 ;
  }
  for( int i_muon = 0 ; i_muon < (int)v_muon.size() ; i_muon++ ) {
    ht += ( v_muon.at(i_muon)->pt() ) * 0.001 ;
  }

  // Compute MET
  Double_t MET = (*met_it)->met() * 0.001 ;

  // Mc Weight Event
  Double_t mcWeight = eventInfo->mcEventWeight();

  //----------------------------
  // Fill Histograms
  //--------------------------- 

  h_Norm->Fill(0.,mcWeight);

  if( (int)v_jet.size() >= 2 && isSS ){

    // All SS/3L
	h_AcceptanceTot->Fill(0.,mcWeight);
    
	h_Acceptance->Fill(0.,mcWeight);
	// >=1 bjet
	if( N_bjet >= 1 )
	h_Acceptance->Fill(1.,mcWeight);

	// 3LSS
	if( is3LSS )
	  h_AcceptanceTot->Fill(2.,mcWeight);

  }

  for( int i = 0 ; i < v_jet.size(); i++)
    delete v_jet[i];

  for( int i = 0 ; i < v_electron.size(); i++)
    delete v_electron[i];

  for( int i = 0 ; i < v_muon.size(); i++)
    delete v_muon[i];

  v_jet.clear();
  v_electron.clear();
  v_muon.clear();

  return EL::StatusCode::SUCCESS;
}



EL::StatusCode TruthReader :: postExecute ()
{
  // Here you do everything that needs to be done after the main event
  // processing.  This is typically very rare, particularly in user
  // code.  It is mainly used in implementing the NTupleSvc.
  return EL::StatusCode::SUCCESS;
}



EL::StatusCode TruthReader :: finalize ()
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

  xAOD::TEvent* event = wk()->xaodEvent();

  return EL::StatusCode::SUCCESS;
}



EL::StatusCode TruthReader :: histFinalize ()
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

  h_Acceptance->Scale( 1./h_Norm->Integral() );
  h_AcceptanceTot->Scale( 1./h_Norm->Integral() );

  return EL::StatusCode::SUCCESS;
}
