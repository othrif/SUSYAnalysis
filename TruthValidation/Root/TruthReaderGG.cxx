#include <EventLoop/Job.h>
#include <EventLoop/StatusCode.h>
#include <EventLoop/Worker.h>
#include <TruthValidation/TruthReaderGG.h>

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
ClassImp(TruthReaderGG)


TruthReaderGG :: TruthReaderGG ()
{
  // Here you put any code for the base initialization of variables,
  // e.g. initialize all pointers to 0.  Note that you should only put
  // the most basic initialization here, since this method will be
  // called on both the submission and the worker node.  Most of your
  // initialization code will go into histInitialize() and
  // initialize().
}



EL::StatusCode TruthReaderGG :: setupJob (EL::Job& job)
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



EL::StatusCode TruthReaderGG :: histInitialize ()
{
  // Here you do everything that needs to be done at the very
  // beginning on each worker node, e.g. create histograms and output
  // trees.  This method gets called before any input files are
  // connected.

  // Jet
  h_jetN   = new TH1F("h_jetN", "h_jetN;N_{jet};Events", 25, 0, 25);
  h_jetPt  = new TH1F("h_jetPt", "h_jetPt;Pt_{jet} [GeV];Events", 20, 0, 1500);
  h_jetE   = new TH1F("h_jetE", "h_jetE; E_{jet} [GeV];Events", 20, 0, 1700);
  h_jetEta = new TH1F("h_jetEta", "h_jetEta;#eta_{jet};Events", 20, -5, 5);
  h_jetPhi = new TH1F("h_jetPhi", "h_jetPhi;#phi_{jet};Events", 20, 0, 3.14);
  wk()->addOutput (h_jetN);
  wk()->addOutput (h_jetPt);
  wk()->addOutput (h_jetE);
  wk()->addOutput (h_jetEta);
  wk()->addOutput (h_jetPhi);

  // BJet
  h_bjetN   = new TH1F("h_bjetN", "h_bjetN;N_{b-jet};Events", 8, 0, 8);
  h_bjetPt  = new TH1F("h_bjetPt", "h_bjetPt;Pt_{b-jet} [GeV];Events", 20, 0, 1000);
  h_bjetE   = new TH1F("h_bjetE", "h_bjetE; E_{b-jet} [GeV];Events", 20, 0, 1200);
  h_bjetEta = new TH1F("h_bjetEta", "h_bjetEta;#eta_{b-jet};Events", 20, -5, 5);
  h_bjetPhi = new TH1F("h_bjetPhi", "h_bjetPhi;#phi_{b-jet};Events", 20, 0, 3.14);
  wk()->addOutput (h_bjetN);
  wk()->addOutput (h_bjetPt);
  wk()->addOutput (h_bjetE);
  wk()->addOutput (h_bjetEta);
  wk()->addOutput (h_bjetPhi);

  // Electron
  h_electronN   = new TH1F("h_electronN", "h_electronN;N_{el};Events", 7, 0, 7);
  h_electronPt  = new TH1F("h_electronPt", "h_electronPt;Pt_{el};Events", 20, 0, 300);
  h_electronE   = new TH1F("h_electronE", "h_electronE;E_{el};Events", 20, 0, 300);
  h_electronEta = new TH1F("h_electronEta", "h_electronEta;#eta_{el};Events", 20, -3, 3);
  h_electronPhi = new TH1F("h_electronPhi", "h_electronPhi;#phi_{el};Events", 20, 0, 3.14);
  h_electronQ   = new TH1F("h_electronQ", "h_electronQ;Q_{el};Events", 2, -1, 1);
  wk()->addOutput (h_electronN);
  wk()->addOutput (h_electronPt);
  wk()->addOutput (h_electronE);
  wk()->addOutput (h_electronEta);
  wk()->addOutput (h_electronPhi);
  wk()->addOutput (h_electronQ);

  // Muon
  h_muonN   = new TH1F("h_muonN", "h_muonN;N_{#mu};Events", 7, 0, 7);
  h_muonPt  = new TH1F("h_muonPt", "h_muonPt;Pt_{#mu};Events", 20, 0, 300);
  h_muonE   = new TH1F("h_muonE", "h_muonE;E_{#mu};Events", 20, 0, 300);
  h_muonEta = new TH1F("h_muonEta", "h_muonEta;#eta_{#mu};Events", 20, -3, 3);
  h_muonPhi = new TH1F("h_muonPhi", "h_muonPhi;#phi_{#mu};Events", 20, 0, 3.14);
  h_muonQ   = new TH1F("h_muonQ", "h_muonQ;Q_{#mu};Events", 2, -1, 1);
  wk()->addOutput (h_muonN);
  wk()->addOutput (h_muonPt);
  wk()->addOutput (h_muonE);
  wk()->addOutput (h_muonEta);
  wk()->addOutput (h_muonPhi);
  wk()->addOutput (h_muonQ);

  // Global Variable
  h_HT   = new TH1F("h_HT", "h_HT;H_{T};Events", 20, 0, 3000);
  h_meff   = new TH1F("h_meff", "h_meff;M_{eff};Events", 20, 0, 3000);
  h_met    = new TH1F("h_met", "h_met;M_{Et};Events", 20, 0, 600);
  h_metPhi = new TH1F("h_metPhi", "h_metPhi;#phi_{Met};Events", 20, 0, 3.14);
  wk()->addOutput (h_HT);
  wk()->addOutput (h_meff);
  wk()->addOutput (h_met);
  wk()->addOutput (h_metPhi);

  // Parton Level
  h_go1Pt  = new TH1F("h_go1Pt", "h_go1Pt;Pt_{#tilde{d}_{1}};Events", 20, 0, 1500);
  h_go1E   = new TH1F("h_go1E", "h_go1E;E_{#tilde{d}_{1}};Events", 20, 0, 2000);
  h_go1Eta = new TH1F("h_go1Eta", "h_go1Eta;#eta_{#tilde{d}_{1}};Events", 20, -3, 3);
  h_go1Phi = new TH1F("h_go1Phi", "h_go1Phi;#phi_{#tilde{d}_{1}};Events", 20, 0, 3.14); 
  wk()->addOutput (h_go1Pt);
  wk()->addOutput (h_go1E);
  wk()->addOutput (h_go1Eta);
  wk()->addOutput (h_go1Phi);

  h_go2Pt  = new TH1F("h_go2Pt", "h_go2Pt;Pt_{#tilde{d}_{2}};Events", 20, 0, 1500);
  h_go2E   = new TH1F("h_go2E", "h_go2E;E_{#tilde{d}_{2}};Events", 20, 0, 2000);
  h_go2Eta = new TH1F("h_go2Eta", "h_go2Eta;#eta_{#tilde{d}_{2}};Events", 20, -3, 3);
  h_go2Phi = new TH1F("h_go2Phi", "h_go2Phi;#phi_{#tilde{d}_{2}};Events", 20, 0, 3.14); 
  wk()->addOutput (h_go2Pt);
  wk()->addOutput (h_go2E);
  wk()->addOutput (h_go2Eta);
  wk()->addOutput (h_go2Phi);

  h_top1Pt  = new TH1F("h_top1Pt", "h_top1Pt;Pt_{t_{1}};Events", 20, 0, 1200);
  h_top1E   = new TH1F("h_top1E", "h_top1E;E_{t_{1}};Events", 20, 0, 1500);
  h_top1Eta = new TH1F("h_top1Eta", "h_top1Eta;#eta_{t_{1}};Events", 20, -3, 3);
  h_top1Phi = new TH1F("h_top1Phi", "h_top1Phi;#phi_{t_{1}};Events", 20, 0, 3.14);
  wk()->addOutput (h_top1Pt);
  wk()->addOutput (h_top1E);
  wk()->addOutput (h_top1Eta);
  wk()->addOutput (h_top1Phi);

  h_top2Pt  = new TH1F("h_top2Pt", "h_top2Pt;Pt_{t_{2}};Events", 20, 0, 1200);
  h_top2E   = new TH1F("h_top2E", "h_top2E;E_{t_{2}};Events", 20, 0, 1500);
  h_top2Eta = new TH1F("h_top2Eta", "h_top2Eta;#eta_{t_{2}};Events", 20, -3, 3);
  h_top2Phi = new TH1F("h_top2Phi", "h_top2Phi;#phi_{t_{2}};Events", 20, 0, 3.14);
  wk()->addOutput (h_top2Pt);
  wk()->addOutput (h_top2E);
  wk()->addOutput (h_top2Eta);
  wk()->addOutput (h_top2Phi);

  h_s1Pt  = new TH1F("h_s1Pt", "h_s1Pt;Pt_{s_{1}};Events", 20, 0, 1200);
  h_s1E   = new TH1F("h_s1E", "h_s1E;E_{s_{1}};Events", 20, 0, 1500);
  h_s1Eta = new TH1F("h_s1Eta", "h_s1Eta;#eta_{s_{1}};Events", 20, -3, 3);
  h_s1Phi = new TH1F("h_s1Phi", "h_s1Phi;#phi_{s_{1}};Events", 20, 0, 3.14);
  wk()->addOutput (h_s1Pt);
  wk()->addOutput (h_s1E);
  wk()->addOutput (h_s1Eta);
  wk()->addOutput (h_s1Phi);

  h_s2Pt  = new TH1F("h_s2Pt", "h_s2Pt;Pt_{s_{2}};Events", 20, 0, 1200);
  h_s2E   = new TH1F("h_s2E", "h_s2E;E_{s_{2}};Events", 20, 0, 1500);
  h_s2Eta = new TH1F("h_s2Eta", "h_s2Eta;#eta_{s_{2}};Events", 20, -3, 3);
  h_s2Phi = new TH1F("h_s2Phi", "h_s2Phi;#phi_{s_{2}};Events", 20, 0, 3.14);
  wk()->addOutput (h_s2Pt);
  wk()->addOutput (h_s2E);
  wk()->addOutput (h_s2Eta);
  wk()->addOutput (h_s2Phi);

  h_up1Pt  = new TH1F("h_up1Pt", "h_up1Pt;Pt_{up_{1}};Events", 20, 0, 1200);
  h_up1E   = new TH1F("h_up1E", "h_up1E;E_{up_{1}};Events", 20, 0, 1500);
  h_up1Eta = new TH1F("h_up1Eta", "h_up1Eta;#eta_{up_{1}};Events", 20, -3, 3);
  h_up1Phi = new TH1F("h_up1Phi", "h_up1Phi;#phi_{up_{1}};Events", 20, 0, 3.14);
  wk()->addOutput (h_up1Pt);
  wk()->addOutput (h_up1E);
  wk()->addOutput (h_up1Eta);
  wk()->addOutput (h_up1Phi);

  h_up2Pt  = new TH1F("h_up2Pt", "h_up2Pt;Pt_{up_{2}};Events", 20, 0, 1200);
  h_up2E   = new TH1F("h_up2E", "h_up2E;E_{up_{2}};Events", 20, 0, 1500);
  h_up2Eta = new TH1F("h_up2Eta", "h_up2Eta;#eta_{up_{2}};Events", 20, -3, 3);
  h_up2Phi = new TH1F("h_up2Phi", "h_up2Phi;#phi_{up_{2}};Events", 20, 0, 3.14);
  wk()->addOutput (h_up2Pt);
  wk()->addOutput (h_up2E);
  wk()->addOutput (h_up2Eta);
  wk()->addOutput (h_up2Phi);

  h_b1Pt  = new TH1F("h_b1Pt", "h_b1Pt;Pt_{b_{1}};Events", 20, 0, 700);
  h_b1E   = new TH1F("h_b1E", "h_b1E;E_{b_{1}};Events", 20, 0, 1000);
  h_b1Eta = new TH1F("h_b1Eta", "h_b1Eta;#eta_{b_{1}};Events", 20, -3, 3);
  h_b1Phi = new TH1F("h_b1Phi", "h_b1Phi;#phi_{b_{1}};Events", 20, 0, 3.14);
  wk()->addOutput (h_b1Pt);
  wk()->addOutput (h_b1E);
  wk()->addOutput (h_b1Eta);
  wk()->addOutput (h_b1Phi);

  h_b2Pt  = new TH1F("h_b2Pt", "h_b2Pt;Pt_{b_{2}};Events", 20, 0, 700);
  h_b2E   = new TH1F("h_b2E", "h_b2E;E_{b_{2}};Events", 20, 0, 1000);
  h_b2Eta = new TH1F("h_b2Eta", "h_b2Eta;#eta_{b_{2}};Events", 20, -3, 3);
  h_b2Phi = new TH1F("h_b2Phi", "h_b2Phi;#phi_{b_{2}};Events", 20, 0, 3.14);
  wk()->addOutput (h_b2Pt);
  wk()->addOutput (h_b2E);
  wk()->addOutput (h_b2Eta);
  wk()->addOutput (h_b2Phi);

  h_w1Pt  = new TH1F("h_w1Pt", "h_w1Pt;Pt_{W_{1}};Events", 20, 0, 700);
  h_w1E   = new TH1F("h_w1E", "h_w1E;E_{W_{1}};Events", 20, 0, 1000);
  h_w1Eta = new TH1F("h_w1Eta", "h_w1Eta;#eta_{W_{1}};Events", 20, -3, 3);
  h_w1Phi = new TH1F("h_w1Phi", "h_w1Phi;#phi_{W_{1}};Events", 20, 0, 3.14);
  wk()->addOutput (h_w1Pt);
  wk()->addOutput (h_w1E);
  wk()->addOutput (h_w1Eta);
  wk()->addOutput (h_w1Phi);

  h_w2Pt  = new TH1F("h_w2Pt", "h_w2Pt;Pt_{W_{2}};Events", 20, 0, 700);
  h_w2E   = new TH1F("h_w2E", "h_w2E;E_{W_{2}};Events", 20, 0, 1000);
  h_w2Eta = new TH1F("h_w2Eta", "h_w2Eta;#eta_{W_{2}};Events", 20, -3, 3);
  h_w2Phi = new TH1F("h_w2Phi", "h_w2Phi;#phi_{W_{2}};Events", 20, 0, 3.14);
  wk()->addOutput (h_w2Pt);
  wk()->addOutput (h_w2E);
  wk()->addOutput (h_w2Eta);
  wk()->addOutput (h_w2Phi);

  h_TrueElN   = new TH1F("h_TrueElN", "h_TrueElN;N_{el};Events", 7, 0, 7);
  h_TrueElPt  = new TH1F("h_TrueElPt", "h_TrueElPt;Pt_{el};Events", 20, 0, 300);
  h_TrueElE   = new TH1F("h_TrueElE", "h_TrueElE;E_{el};Events", 20, 0, 300);
  h_TrueElEta = new TH1F("h_TrueElEta", "h_TrueElEta;#eta_{el};Events", 20, -3, 3);
  h_TrueElPhi = new TH1F("h_TrueElPhi", "h_TrueElPhi;#phi_{el};Events", 20, 0, 3.14);
  h_TrueElQ   = new TH1F("h_TrueElQ", "h_TrueElQ;Q_{el};Events", 2, -1, 1);
  wk()->addOutput (h_TrueElN);
  wk()->addOutput (h_TrueElPt);
  wk()->addOutput (h_TrueElE);
  wk()->addOutput (h_TrueElEta);
  wk()->addOutput (h_TrueElPhi);
  wk()->addOutput (h_TrueElQ);

  h_TrueMuN   = new TH1F("h_TrueMuN", "h_TrueMuN;N_{#mu};Events", 7, 0, 7);
  h_TrueMuPt  = new TH1F("h_TrueMuPt", "h_TrueMuPt;Pt_{#mu};Events", 20, 0, 300);
  h_TrueMuE   = new TH1F("h_TrueMuE", "h_TrueMuE;E_{#mu};Events", 20, 0, 300);
  h_TrueMuEta = new TH1F("h_TrueMuEta", "h_TrueMuEta;#eta_{#mu};Events", 20, -3, 3);
  h_TrueMuPhi = new TH1F("h_TrueMuPhi", "h_TrueMuPhi;#phi_{#mu};Events", 20, 0, 3.14);
  h_TrueMuQ   = new TH1F("h_TrueMuQ", "h_TrueMuQ;Q_{#mu};Events", 2, -1, 1);
  wk()->addOutput (h_TrueMuN);
  wk()->addOutput (h_TrueMuPt);
  wk()->addOutput (h_TrueMuE);
  wk()->addOutput (h_TrueMuEta);
  wk()->addOutput (h_TrueMuPhi);
  wk()->addOutput (h_TrueMuQ);

  h_TrueJetN   = new TH1F("h_TrueJetN", "h_TrueJetN;N_{jet};Events", 15, 0, 15);
  h_TrueJetPt  = new TH1F("h_TrueJetPt", "h_TrueJetPt;Pt_{jet};Events", 20, 0, 1500);
  h_TrueJetE   = new TH1F("h_TrueJetE", "h_TrueJetE;E_{jet};Events", 20, 0, 2000);
  h_TrueJetEta = new TH1F("h_TrueJetEta", "h_TrueJetEta;#eta_{jet};Events", 20, -3, 3);
  h_TrueJetPhi = new TH1F("h_TrueJetPhi", "h_TrueJetPhi;#phi_{jet};Events", 20, 0, 3.14);
  wk()->addOutput (h_TrueJetN);
  wk()->addOutput (h_TrueJetPt);
  wk()->addOutput (h_TrueJetE);
  wk()->addOutput (h_TrueJetEta);
  wk()->addOutput (h_TrueJetPhi);

  h_TrueBJetN   = new TH1F("h_TrueBJetN", "h_TrueBJetN;N_{b-jet};Events", 8, 0, 8);
  h_TrueBJetPt  = new TH1F("h_TrueBJetPt", "h_TrueBJetPt;Pt_{b-jet};Events", 20, 0, 1200);
  h_TrueBJetE   = new TH1F("h_TrueBJetE", "h_TrueBJetE;E_{b-jet};Events", 20, 0, 1500);
  h_TrueBJetEta = new TH1F("h_TrueBJetEta", "h_TrueBJetEta;#eta_{b-jet};Events", 20, -3, 3);
  h_TrueBJetPhi = new TH1F("h_TrueBJetPhi", "h_TrueBJetPhi;#phi_{b-jet};Events", 20, 0, 3.14);
  wk()->addOutput (h_TrueBJetN);
  wk()->addOutput (h_TrueBJetPt);
  wk()->addOutput (h_TrueBJetE);
  wk()->addOutput (h_TrueBJetEta);
  wk()->addOutput (h_TrueBJetPhi);

  h_TrueMET   = new TH1F("h_TrueMET", "h_TrueMET;M_{ET};Events", 20, 0, 600);
  h_TruePhiMET   = new TH1F("h_TruePhiMET", "h_TruePhiMET;#phi_{Met};Events", 20, 0, 3.14);
  h_TrueHT  = new TH1F("h_TrueHT", "h_TrueHT;H_{T};Events", 20, 0, 3000);
  h_TrueMeff  = new TH1F("h_TrueMeff", "h_TrueMeff;M_{eff};Events", 20, 0, 3000);
  wk()->addOutput (h_TrueMET);
  wk()->addOutput (h_TruePhiMET);
  wk()->addOutput (h_TrueHT);
  wk()->addOutput (h_TrueMeff);

  return EL::StatusCode::SUCCESS;
}



EL::StatusCode TruthReaderGG :: fileExecute ()
{
  // Here you do everything that needs to be done exactly once for every
  // single file, e.g. collect a list of all lumi-blocks processed
  return EL::StatusCode::SUCCESS;
}



EL::StatusCode TruthReaderGG :: changeInput (bool firstFile)
{
  // Here you do everything you need to do when we change input files,
  // e.g. resetting branch addresses on trees.  If you are using
  // D3PDReader or a similar service this method is not needed.
  return EL::StatusCode::SUCCESS;
}



EL::StatusCode TruthReaderGG :: initialize ()
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



EL::StatusCode TruthReaderGG :: execute ()
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
  //  std::cout << eventInfo->eventNumber() << std::endl;

  //----------------------------
  // Jets
  //--------------------------- 
  const xAOD::JetContainer* jets = 0;
  EL_RETURN_CHECK("execute()",event->retrieve( jets, "AntiKt4TruthJets" ));

  std::vector<xAOD::Jet*> v_jet;

  xAOD::JetContainer::const_iterator jet_itr = jets->begin();
  xAOD::JetContainer::const_iterator jet_end = jets->end();
  for( ; jet_itr != jet_end; ++jet_itr ) {
    if(( (*jet_itr)->pt() * 0.001) < 20 ) continue;

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
    if(( (*electron_itr)->pt() * 0.001) < 10 ) continue;
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
    if(( (*muon_itr)->pt() * 0.001) < 10 ) continue;
    if( fabs((*muon_itr)->eta()) > 2.4 ) continue;

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

  h_met->Fill( (*met_it)->met() * 0.001 );
  h_metPhi->Fill( (*met_it)->phi() );

  double meff = (*met_it)->met() * 0.001 ;

  //----------------------------
  // Overlap Removal
  //--------------------------- 

  // Jet Removal
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

  // Muon Removal
  for(int i_mu = 0 ; i_mu < (int)v_muon.size() ; i_mu++ ){
    for(int i_jet = 0 ; i_jet < (int)v_jet.size() ; i_jet++ ){
      if( v_muon.at(i_mu)->p4().DeltaR(v_jet.at(i_jet)->p4()) < 0.4) { // Remove Muon element and move backward
        v_muon.erase( v_muon.begin()+i_mu);
        i_mu-- ;
        break;
      }
    }
  }

  // Leptons Removal
  for(int i_el = 0 ; i_el < (int)v_electron.size() ; i_el++ ){
    for(int i_mu = 0 ; i_mu < (int)v_muon.size() ; i_mu++ ){
      if( v_muon.at(i_mu)->p4().DeltaR(v_electron.at(i_el)->p4()) < 0.1) { // Remove electron element and move backward
	v_electron.erase( v_electron.begin()+i_el);
        i_el--;
	break;
      }
    }
  }

  //----------------------------
  // Fill Histograms
  //--------------------------- 

  Double_t ht=0;

  h_jetN->Fill( v_jet.size() ); 

  int N_bjet =0;
  for( int i_jet = 0 ; i_jet < (int)v_jet.size() ; i_jet++ ) {

    h_jetPt->Fill( ( v_jet.at(i_jet)->pt()) * 0.001); 
    h_jetE->Fill( ( v_jet.at(i_jet)->e()) * 0.001); 
    h_jetEta->Fill( v_jet.at(i_jet)->eta() ); 
    h_jetPhi->Fill( v_jet.at(i_jet)->phi() ); 

    meff += ( v_jet.at(i_jet)->pt() ) * 0.001 ;
    ht += ( v_jet.at(i_jet)->pt() ) * 0.001 ;

    if( abs( v_jet.at(i_jet)->auxdata<int>("PartonTruthLabelID") ) != 5 ) continue;

    h_bjetPt->Fill( ( v_jet.at(i_jet)->pt()) * 0.001); 
    h_bjetE->Fill( ( v_jet.at(i_jet)->e()) * 0.001); 
    h_bjetEta->Fill( v_jet.at(i_jet)->eta() ); 
    h_bjetPhi->Fill( v_jet.at(i_jet)->phi() ); 

    N_bjet++;
  }

  h_bjetN->Fill( N_bjet ); 
  h_electronN->Fill( v_electron.size() ); 

  for( int i_electron = 0 ; i_electron < (int)v_electron.size() ; i_electron++ ) {

    h_electronPt->Fill( ( v_electron.at(i_electron)->pt()) * 0.001); 
    h_electronE->Fill( ( v_electron.at(i_electron)->e()) * 0.001); 
    h_electronEta->Fill( v_electron.at(i_electron)->eta() ); 
    h_electronPhi->Fill( v_electron.at(i_electron)->phi() ); 
    h_electronQ->Fill( v_electron.at(i_electron)->charge()/2 ); 

    meff += ( v_electron.at(i_electron)->pt() ) * 0.001 ;
  }

  h_muonN->Fill( v_muon.size() ); 

  for( int i_muon = 0 ; i_muon < (int)v_muon.size() ; i_muon++ ) {

    h_muonPt->Fill( ( v_muon.at(i_muon)->pt()) * 0.001); 
    h_muonE->Fill( ( v_muon.at(i_muon)->e()) * 0.001); 
    h_muonEta->Fill( v_muon.at(i_muon)->eta() ); 
    h_muonPhi->Fill( v_muon.at(i_muon)->phi() ); 
    h_muonQ->Fill( v_muon.at(i_muon)->charge()/2 ); 

    meff += ( v_muon.at(i_muon)->pt() ) * 0.001 ;
  }

  h_meff->Fill( meff );
  h_HT->Fill( ht );

  //----------------------------
  // Parton Level
  //--------------------------- 

  const xAOD::TruthParticleContainer* TruthParticles = 0;
  EL_RETURN_CHECK( "execute", event->retrieve( TruthParticles, "TruthParticles" ) );

  const xAOD::TruthParticle *go1, *go2, *top1, *top2, *up1, *up2, *s1, *s2, *b1, *b2, *w1, *w2;
  std::vector<const xAOD::TruthParticle*> TrueEl, TrueMu, TrueJet, TrueBJet;
  TLorentzVector v_Met;
  Double_t HT=0,Meff=0;

  for( auto part_itr : *TruthParticles ){

    if( part_itr->pdgId() == 2212 ) continue;

    xAOD::TruthParticle* Particle = new xAOD::TruthParticle();
    Particle->makePrivateStore( *part_itr );

    if( part_itr->index() == 4 ||
	part_itr->index() == 5 ){

      if( part_itr->index() == 4 ) go1 = Particle;
      if( part_itr->index() == 5 ) go2 = Particle;

      std::cout << " Particle N "<<Particle->index()
      		<<" - ID = "<<Particle->pdgId()
      		<<" - Barcode = "<<Particle->barcode()
      		<<" - Status = "<<Particle->status()
      		<<" - NChild = "<<Particle->nChildren() << std::endl ;

      const xAOD::TruthParticle* ChildParticle = Particle->child(0);
      while( ChildParticle->child(0)->pdgId() == Particle->pdgId() ) {
	ChildParticle = ChildParticle->child(0);
      }

      const xAOD::TruthParticle* TopParticle = ChildParticle->child(0);
      std::cout << "      Top N "<< 1
		<<" - Index = "<<TopParticle->index()
		<<" - ID = "<<TopParticle->pdgId()
      		<<" - Barcode = "<<TopParticle->barcode()
		<<" - Status = "<<TopParticle->status() << std::endl ;

      if( part_itr->index() == 4 ) top1 = TopParticle;
      if( part_itr->index() == 5 ) top2 = TopParticle;

      const xAOD::TruthParticle* UpParticle = ChildParticle->child(1);
      std::cout << "      Up N "<< 1
		<<" - Index = "<<UpParticle->index()
		<<" - ID = "<<UpParticle->pdgId()
      		<<" - Barcode = "<<UpParticle->barcode()
		<<" - Status = "<<UpParticle->status() << std::endl ;

      if( part_itr->index() == 4 ) up1 = UpParticle;
      if( part_itr->index() == 5 ) up2 = UpParticle;      
      TrueJet.push_back( UpParticle );
      Meff+=UpParticle->pt();
      HT+=UpParticle->pt();

      const xAOD::TruthParticle* StrangeParticle = ChildParticle->child(2);
      std::cout << "      Strange N "<< 1
		<<" - Index = "<<StrangeParticle->index()
		<<" - ID = "<<StrangeParticle->pdgId()
      		<<" - Barcode = "<<StrangeParticle->barcode()
		<<" - Status = "<<StrangeParticle->status() << std::endl ;

      if( part_itr->index() == 4 ) s1 = StrangeParticle;
      if( part_itr->index() == 5 ) s2 = StrangeParticle;      
      TrueJet.push_back( StrangeParticle );
      Meff+=StrangeParticle->pt();
      HT+=StrangeParticle->pt();

      const xAOD::TruthParticle* TopChildParticle = TopParticle;
      while( TopChildParticle->child(0)->pdgId() == TopParticle->pdgId() ) {
	TopChildParticle = TopChildParticle->child(0);
      }
      
      const xAOD::TruthParticle* WbosonParticle = TopChildParticle->child(0);
      std::cout << "      Wboson N "<< 1
		<<" - Index = "<<WbosonParticle->index()
		<<" - ID = "<<WbosonParticle->pdgId()
      		<<" - Barcode = "<<WbosonParticle->barcode()
		<<" - Status = "<<WbosonParticle->status() << std::endl ;

      if( part_itr->index() == 4 ) w1 = WbosonParticle;
      if( part_itr->index() == 5 ) w2 = WbosonParticle;      

      const xAOD::TruthParticle* BottomParticle = TopChildParticle->child(1);
      std::cout << "      Bottom N "<< 1
		<<" - Index = "<<BottomParticle->index()
		<<" - ID = "<<BottomParticle->pdgId()
      		<<" - Barcode = "<<BottomParticle->barcode()
		<<" - Status = "<<BottomParticle->status() << std::endl ;

      if( part_itr->index() == 4 ) b1 = BottomParticle;
      if( part_itr->index() == 5 ) b2 = BottomParticle;      
      TrueJet.push_back( BottomParticle );
      TrueBJet.push_back( BottomParticle );
      Meff+=BottomParticle->pt();
      HT+=BottomParticle->pt();

      const xAOD::TruthParticle* WbosonChildParticle = WbosonParticle;
      while( WbosonChildParticle->child(0)->pdgId() == WbosonParticle->pdgId()  ) {
	WbosonChildParticle = WbosonChildParticle->child(0);
      }

      for( int i_child = 0 ; i_child < (int)WbosonChildParticle->nChildren() ; i_child++ ){
      	std::cout << "      Wboson Child N "<<i_child
      		  <<" - Index = "<<WbosonChildParticle->child(i_child)->index()
      		  <<" - ID = "<<WbosonChildParticle->child(i_child)->pdgId()
      		  <<" - Barcode = "<<WbosonChildParticle->child(i_child)->barcode()
      		  <<" - Status = "<<WbosonChildParticle->child(i_child)->status() << std::endl ;

	if( abs(WbosonChildParticle->child(i_child)->pdgId()) < 6 ) {
	  TrueJet.push_back( WbosonChildParticle->child(i_child) );
	  Meff+=WbosonChildParticle->child(i_child)->pt();
	  HT+=WbosonChildParticle->child(i_child)->pt();
	}
	if( abs(WbosonChildParticle->child(i_child)->pdgId()) == 5 ) TrueBJet.push_back( WbosonChildParticle->child(i_child) );
	if( abs(WbosonChildParticle->child(i_child)->pdgId()) == 11 ) {
	  TrueEl.push_back( WbosonChildParticle->child(i_child) );
	  Meff+=WbosonChildParticle->child(i_child)->pt();
	}
	if( abs(WbosonChildParticle->child(i_child)->pdgId()) == 13 ) {
	  TrueMu.push_back( WbosonChildParticle->child(i_child) );
	  Meff+=WbosonChildParticle->child(i_child)->pt();
	}
	if( abs(WbosonChildParticle->child(i_child)->pdgId()) == 12 ||
	    abs(WbosonChildParticle->child(i_child)->pdgId()) == 14 ||
	    abs(WbosonChildParticle->child(i_child)->pdgId()) == 16 ) v_Met += WbosonChildParticle->child(i_child)->p4();
	if( abs(WbosonChildParticle->child(i_child)->pdgId()) > 100  ) {
	  Meff+=WbosonChildParticle->child(i_child)->pt();
	  HT+=WbosonChildParticle->child(i_child)->pt();
	}
	if( abs(WbosonChildParticle->child(i_child)->pdgId()) == 15 ) {

	  const xAOD::TruthParticle* TauChildParticle = WbosonChildParticle->child(i_child);
	  while( TauChildParticle->child(0)->pdgId() ==  WbosonChildParticle->child(i_child)->pdgId() ) {
	    TauChildParticle = TauChildParticle->child(0);
	  }

	  for( int i_child = 0 ; i_child < (int)TauChildParticle->nChildren() ; i_child++ ){
	    std::cout << "      Tau Child N "<<i_child
		      <<" - Index = "<<TauChildParticle->child(i_child)->index()
		      <<" - ID = "<<TauChildParticle->child(i_child)->pdgId()
		      <<" - Barcode = "<<TauChildParticle->child(i_child)->barcode()
		      <<" - Status = "<<TauChildParticle->child(i_child)->status() << std::endl ;

	    if( abs(TauChildParticle->child(i_child)->pdgId()) < 6 ){
	      TrueJet.push_back( TauChildParticle->child(i_child) );
	      Meff+=TauChildParticle->child(i_child)->pt();
	      HT+=TauChildParticle->child(i_child)->pt();
	    }
	    if( abs(TauChildParticle->child(i_child)->pdgId()) == 5 ) TrueBJet.push_back( TauChildParticle->child(i_child) );
	    if( abs(TauChildParticle->child(i_child)->pdgId()) == 11 ){
	      TrueEl.push_back( TauChildParticle->child(i_child) );
	      Meff+=TauChildParticle->child(i_child)->pt();
	    }
	    if( abs(TauChildParticle->child(i_child)->pdgId()) == 13 ) {
	      TrueMu.push_back( TauChildParticle->child(i_child) );
	      Meff+=TauChildParticle->child(i_child)->pt();
	    }
	    if( abs(TauChildParticle->child(i_child)->pdgId()) == 12 ||
		abs(TauChildParticle->child(i_child)->pdgId()) == 14 ||
		abs(TauChildParticle->child(i_child)->pdgId()) == 16 ) v_Met += TauChildParticle->child(i_child)->p4();
	  }
	  if( abs(TauChildParticle->child(i_child)->pdgId()) > 100  ) {
	    Meff+=TauChildParticle->child(i_child)->pt();
	    HT+=TauChildParticle->child(i_child)->pt();
	  }
	}
      }
    }

    if( part_itr->index()>5 ) break;
  }

  h_go1Pt->Fill( ( go1->pt()) * 0.001);
  h_go1E->Fill( ( go1->e()) * 0.001);
  h_go1Eta->Fill( go1->eta() );
  h_go1Phi->Fill( go1->phi() );
  
  h_go2Pt->Fill( ( go2->pt()) * 0.001);
  h_go2E->Fill( ( go2->e()) * 0.001);
  h_go2Eta->Fill( go2->eta() );
  h_go2Phi->Fill( go2->phi() );
  
  h_top1Pt->Fill( ( top1->pt()) * 0.001);
  h_top1E->Fill( ( top1->e()) * 0.001);
  h_top1Eta->Fill( top1->eta() );
  h_top1Phi->Fill( top1->phi() );
  
  h_top2Pt->Fill( ( top2->pt()) * 0.001);
  h_top2E->Fill( ( top2->e()) * 0.001);
  h_top2Eta->Fill( top2->eta() );
  h_top2Phi->Fill( top2->phi() );
  
  h_up1Pt->Fill( ( up1->pt()) * 0.001);
  h_up1E->Fill( ( up1->e()) * 0.001);
  h_up1Eta->Fill( up1->eta() );
  h_up1Phi->Fill( up1->phi() );
  
  h_up2Pt->Fill( ( up2->pt()) * 0.001);
  h_up2E->Fill( ( up2->e()) * 0.001);
  h_up2Eta->Fill( up2->eta() );
  h_up2Phi->Fill( up2->phi() );

  h_s1Pt->Fill( ( s1->pt()) * 0.001);
  h_s1E->Fill( ( s1->e()) * 0.001);
  h_s1Eta->Fill( s1->eta() );
  h_s1Phi->Fill( s1->phi() );
  
  h_s2Pt->Fill( ( s2->pt()) * 0.001);
  h_s2E->Fill( ( s2->e()) * 0.001);
  h_s2Eta->Fill( s2->eta() );
  h_s2Phi->Fill( s2->phi() );
  
  h_b1Pt->Fill( ( b1->pt()) * 0.001);
  h_b1E->Fill( ( b1->e()) * 0.001);
  h_b1Eta->Fill( b1->eta() );
  h_b1Phi->Fill( b1->phi() );
  
  h_b2Pt->Fill( ( b2->pt()) * 0.001);
  h_b2E->Fill( ( b2->e()) * 0.001);
  h_b2Eta->Fill( b2->eta() );
  h_b2Phi->Fill( b2->phi() );
  
  h_w1Pt->Fill( ( w1->pt()) * 0.001);
  h_w1E->Fill( ( w1->e()) * 0.001);
  h_w1Eta->Fill( w1->eta() );
  h_w1Phi->Fill( w1->phi() );
  
  h_w2Pt->Fill( ( w2->pt()) * 0.001);
  h_w2E->Fill( ( w2->e()) * 0.001);
  h_w2Eta->Fill( w2->eta() );
  h_w2Phi->Fill( w2->phi() );

  h_TrueElN->Fill( TrueEl.size() );
  for( int i = 0 ; i < (int)TrueEl.size() ; i++ ) {
    h_TrueElPt->Fill( ( TrueEl.at(i)->pt()) * 0.001);
    h_TrueElE->Fill( ( TrueEl.at(i)->e()) * 0.001);
    h_TrueElEta->Fill( TrueEl.at(i)->eta() );
    h_TrueElPhi->Fill( TrueEl.at(i)->phi() );
    h_TrueElQ->Fill( TrueEl.at(i)->charge()/2 );
  }

  h_TrueMuN->Fill( TrueMu.size() );
  for( int i = 0 ; i < (int)TrueMu.size() ; i++ ) {
    h_TrueMuPt->Fill( ( TrueMu.at(i)->pt()) * 0.001);
    h_TrueMuE->Fill( ( TrueMu.at(i)->e()) * 0.001);
    h_TrueMuEta->Fill( TrueMu.at(i)->eta() );
    h_TrueMuPhi->Fill( TrueMu.at(i)->phi() );
    h_TrueMuQ->Fill( TrueMu.at(i)->charge()/2 );
  }

  h_TrueJetN->Fill( TrueJet.size() );
  for( int i = 0 ; i < (int)TrueJet.size() ; i++ ) {
    h_TrueJetPt->Fill( ( TrueJet.at(i)->pt()) * 0.001);
    h_TrueJetE->Fill( ( TrueJet.at(i)->e()) * 0.001);
    h_TrueJetEta->Fill( TrueJet.at(i)->eta() );
    h_TrueJetPhi->Fill( TrueJet.at(i)->phi() );
  }

  h_TrueBJetN->Fill( TrueBJet.size() );
  for( int i = 0 ; i < (int)TrueBJet.size() ; i++ ) {
    h_TrueBJetPt->Fill( ( TrueBJet.at(i)->pt()) * 0.001);
    h_TrueBJetE->Fill( ( TrueBJet.at(i)->e()) * 0.001);
    h_TrueBJetEta->Fill( TrueBJet.at(i)->eta() );
    h_TrueBJetPhi->Fill( TrueBJet.at(i)->phi() );
  }

  h_TrueMET->Fill( v_Met.Pt()*0.001 );
  h_TruePhiMET->Fill( v_Met.Phi() );

  h_TrueHT->Fill( HT*0.001 );
  Meff += v_Met.Pt();
  h_TrueMeff->Fill( Meff*0.001 );  

  return EL::StatusCode::SUCCESS;
}



EL::StatusCode TruthReaderGG :: postExecute ()
{
  // Here you do everything that needs to be done after the main event
  // processing.  This is typically very rare, particularly in user
  // code.  It is mainly used in implementing the NTupleSvc.
  return EL::StatusCode::SUCCESS;
}



EL::StatusCode TruthReaderGG :: finalize ()
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



EL::StatusCode TruthReaderGG :: histFinalize ()
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

  h_jetPhi->SetMinimum(0.1);
  h_bjetPhi->SetMinimum(0.1);
  h_electronPhi->SetMinimum(0.1);
  h_electronQ->SetMinimum(0.1);
  h_muonPhi->SetMinimum(0.1);
  h_muonQ->SetMinimum(0.1);
  h_metPhi->SetMinimum(0.1);

  h_go1Phi->SetMinimum(0.1); 
  h_go2Phi->SetMinimum(0.1); 
  h_top1Phi->SetMinimum(0.1);
  h_top2Phi->SetMinimum(0.1);
  h_up1Phi->SetMinimum(0.1);
  h_up2Phi->SetMinimum(0.1);
  h_s1Phi->SetMinimum(0.1);
  h_s2Phi->SetMinimum(0.1);
  h_b1Phi->SetMinimum(0.1);
  h_b2Phi->SetMinimum(0.1);
  h_w1Phi->SetMinimum(0.1);
  h_w2Phi->SetMinimum(0.1);

  h_TruePhiMET->SetMinimum(0.1);
  h_TrueElPhi->SetMinimum(0.1);
  h_TrueElQ->SetMinimum(0.1);
  h_TrueMuPhi->SetMinimum(0.1);
  h_TrueMuQ->SetMinimum(0.1);
  h_TrueJetPhi->SetMinimum(0.1);
  h_TrueBJetPhi->SetMinimum(0.1);

  return EL::StatusCode::SUCCESS;
}
