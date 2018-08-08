#ifndef TruthValidation_TruthReader_H
#define TruthValidation_TruthReader_H

#include <stdlib.h>

#include <TH1.h>

#include <EventLoop/Algorithm.h>

class TruthReader : public EL::Algorithm
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


public:
  // float cutValue;


  // variables that don't get filled at submission time should be
  // protected from being send from the submission node to the worker
  // node (done by the //!)
public:

  // this is a standard constructor
  TruthReader ();

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
  ClassDef(TruthReader, 1);
};

#endif
