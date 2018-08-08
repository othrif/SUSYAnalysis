#include "xAODRootAccess/Init.h"
#include "SampleHandler/SampleHandler.h"
#include "SampleHandler/ToolsDiscovery.h"
#include "SampleHandler/ScanDir.h"
#include "EventLoop/Job.h"
#include "EventLoop/DirectDriver.h"
// #include "EventLoopGrid/PrunDriver.h"
#include "SampleHandler/DiskListLocal.h"
#include <TSystem.h>

#include "TruthValidation/TruthReader.h"

#include <iostream>

int main( int argc, char* argv[] ) {

  // Take the submit directory from the input if provided:
  std::string submitDir = "submitDir";
  std::string inputSample = "../TruthSample/mc15_13TeV.410066.MadGraphPythia8EvtGen_A14NNPDF23LO_ttW_Np0.merge.DAOD_TRUTH1.e4111_p2514/";

  if( argc > 1 ) inputSample = argv[ 1 ];
  if( argc > 2 ) submitDir = argv[ 2 ];

  // Set up the job for xAOD access:
  xAOD::Init().ignore();

  // Construct the samples to run on:
  SH::SampleHandler sh;
  SH::scanDQ2(sh, inputSample);

  // Set the name of the input TTree. It's always "CollectionTree"
  sh.setMetaString( "nc_tree", "CollectionTree" );

  // Print what we found:
  sh.print();

  // Create an EventLoop job:
  EL::Job job;
  job.sampleHandler( sh );
  // job.options()->setDouble (EL::Job::optMaxEvents, 400000);
  // job.options()->setDouble (EL::Job::optSkipEvents, 500000);

  // add our analysis to the job:
  TruthReader* aTruth = new TruthReader();
  job.algsAdd( aTruth );

  // // Run the job using the local/direct driver:
  // EL::PrunDriver driver;
  // driver.options()->setString("nc_outputSampleName", "user.sberlend.test.%in:name[2]%.%in:name[6]%");
  // driver.submit( job, submitDir );

  return 0;
}
