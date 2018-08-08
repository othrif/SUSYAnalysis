#ifndef TruthValidation_TruthReaderGG_H
#define TruthValidation_TruthReaderGG_H

#include <stdlib.h>

#include <TH1.h>

#include <EventLoop/Algorithm.h>

class TruthReaderGG : public EL::Algorithm
{
  // put your configuration variables here as public variables.
  // that way they can be set directly from CINT and python.

private:

  // Jet
  TH1 *h_jetN; //!
  TH1 *h_jetPt; //!
  TH1 *h_jetE; //!
  TH1 *h_jetEta; //!
  TH1 *h_jetPhi; //!

  // BJet
  TH1 *h_bjetN; //!
  TH1 *h_bjetPt; //!
  TH1 *h_bjetE; //!
  TH1 *h_bjetEta; //!
  TH1 *h_bjetPhi; //!

  // Electron
  TH1 *h_electronN; //!
  TH1 *h_electronPt; //!
  TH1 *h_electronE; //!
  TH1 *h_electronEta; //!
  TH1 *h_electronPhi; //!
  TH1 *h_electronQ; //!

  // Muon
  TH1 *h_muonN; //!
  TH1 *h_muonPt; //!
  TH1 *h_muonE; //!
  TH1 *h_muonEta; //!
  TH1 *h_muonPhi; //!
  TH1 *h_muonQ; //!

  // Global Variable
  TH1 *h_HT; //!
  TH1 *h_meff; //!
  TH1 *h_met; //!
  TH1 *h_metPhi; //!

  //Parton Level
  TH1 *h_go1Pt; //!
  TH1 *h_go1E; //!
  TH1 *h_go1Eta; //!
  TH1 *h_go1Phi; //!

  TH1 *h_go2Pt; //!
  TH1 *h_go2E; //!
  TH1 *h_go2Eta; //!
  TH1 *h_go2Phi; //!

  TH1 *h_top1Pt; //!
  TH1 *h_top1E; //!
  TH1 *h_top1Eta; //!
  TH1 *h_top1Phi; //!

  TH1 *h_top2Pt; //!
  TH1 *h_top2E; //!
  TH1 *h_top2Eta; //!
  TH1 *h_top2Phi; //!

  TH1 *h_up1Pt; //!
  TH1 *h_up1E; //!
  TH1 *h_up1Eta; //!
  TH1 *h_up1Phi; //!

  TH1 *h_up2Pt; //!
  TH1 *h_up2E; //!
  TH1 *h_up2Eta; //!
  TH1 *h_up2Phi; //!

  TH1 *h_s1Pt; //!
  TH1 *h_s1E; //!
  TH1 *h_s1Eta; //!
  TH1 *h_s1Phi; //!

  TH1 *h_s2Pt; //!
  TH1 *h_s2E; //!
  TH1 *h_s2Eta; //!
  TH1 *h_s2Phi; //!

  TH1 *h_b1Pt; //!
  TH1 *h_b1E; //!
  TH1 *h_b1Eta; //!
  TH1 *h_b1Phi; //!

  TH1 *h_b2Pt; //!
  TH1 *h_b2E; //!
  TH1 *h_b2Eta; //!
  TH1 *h_b2Phi; //!

  TH1 *h_w1Pt; //!
  TH1 *h_w1E; //!
  TH1 *h_w1Eta; //!
  TH1 *h_w1Phi; //!

  TH1 *h_w2Pt; //!
  TH1 *h_w2E; //!
  TH1 *h_w2Eta; //!
  TH1 *h_w2Phi; //!

  TH1 *h_TrueElN; //!
  TH1 *h_TrueElPt; //!
  TH1 *h_TrueElE; //!
  TH1 *h_TrueElEta; //!
  TH1 *h_TrueElPhi; //!
  TH1 *h_TrueElQ; //!

  TH1 *h_TrueMuN; //!
  TH1 *h_TrueMuPt; //!
  TH1 *h_TrueMuE; //!
  TH1 *h_TrueMuEta; //!
  TH1 *h_TrueMuPhi; //!
  TH1 *h_TrueMuQ; //!

  TH1 *h_TrueJetN; //!
  TH1 *h_TrueJetPt; //!
  TH1 *h_TrueJetE; //!
  TH1 *h_TrueJetEta; //!
  TH1 *h_TrueJetPhi; //!

  TH1 *h_TrueBJetN; //!
  TH1 *h_TrueBJetPt; //!
  TH1 *h_TrueBJetE; //!
  TH1 *h_TrueBJetEta; //!
  TH1 *h_TrueBJetPhi; //!

  TH1 *h_TrueMET; //!
  TH1 *h_TruePhiMET; //!
  TH1 *h_TrueHT; //!
  TH1 *h_TrueMeff; //!


public:
  // float cutValue;


  // variables that don't get filled at submission time should be
  // protected from being send from the submission node to the worker
  // node (done by the //!)
public:

  // this is a standard constructor
  TruthReaderGG ();

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
  ClassDef(TruthReaderGG, 1);
};

#endif
