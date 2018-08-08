#include "xAODRootAccess/Init.h"
#include "SampleHandler/SampleHandler.h"
#include "SampleHandler/ToolsDiscovery.h"
#include "SampleHandler/ScanDir.h"
#include "EventLoop/Job.h"
#include "EventLoop/DirectDriver.h"
#include "SampleHandler/DiskListLocal.h"
#include <TSystem.h>

#include "TruthValidation/TruthReaderDD.h"

#include <iostream>

int main( int argc, char* argv[] ) {

  // Take the submit directory from the input if provided:
  std::string submitDir = "/afs/cern.ch/work/s/sberlend/McGeneration/Rpv/Truth1Files/submitDir";
  std::string inputSample = "/afs/cern.ch/work/s/sberlend/McGeneration/Rpv/Truth1Files/user.sberlend.MGPy8EG_A14N23LO_Rpv_lampp312_dd_msq1000_mgo1200.reco.v4_EXT0/";

  if( argc > 1 ) inputSample = argv[ 1 ];
  if( argc > 2 ) submitDir = argv[ 2 ];

  // Set up the job for xAOD access:
  xAOD::Init().ignore();

  // Construct the samples to run on:
  SH::SampleHandler sh;
  SH::ScanDir().scan (sh, inputSample);

  // Set the name of the input TTree. It's always "CollectionTree"
  sh.setMetaString( "nc_tree", "CollectionTree" );

  // Print what we found:
  sh.print();

  // Create an EventLoop job:
  EL::Job job;
  job.sampleHandler( sh );
  //job.options()->setDouble (EL::Job::optMaxEvents, 10);

  // Add our analysis to the job:
  TruthReaderDD* aTruth = new TruthReaderDD();
  job.algsAdd( aTruth );

  // // Run the job using the local/direct driver:
  EL::DirectDriver driver;
  driver.submit( job, submitDir );

  return 0;
}
