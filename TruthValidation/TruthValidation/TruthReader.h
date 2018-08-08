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

  TH1 *h_AcceptanceTot; //!
  TH1 *h_Acceptance; //!
  TH1 *h_Norm; //!

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
