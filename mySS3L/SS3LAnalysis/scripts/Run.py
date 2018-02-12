import ROOT
import logging

logging.basicConfig(level=logging.INFO)
from optparse import OptionParser

parser = OptionParser()
parser.add_option("--submitDir", help="dir to store the output", default="submit_dir")
parser.add_option("--inputDS", help="input DS from DQ2", default="none")
parser.add_option("--outputDS", help="output DS name", default="none")
parser.add_option("--driver", help="select where to run", choices=("direct", "prooflite", "grid"), default="direct")
parser.add_option("--nevents", type=int, help="number of events to process for all the datasets")
parser.add_option("--skip-events", type=int, help="skip the first n events")
parser.add_option("-w", "--overwrite", action='store_true', default=True, help="overwrite previous submitDir")
parser.add_option("--isData", help="Data flag [0/1]", default=0)
parser.add_option("--isFirstWeek", help="First week flag [0/1]", default=0)
#parser.add_option("--is50ns", help="50ns flag [0/1]", default=0)
#parser.add_option("--isDerived", help="Derived flag [0/1]", default=0)
parser.add_option("--isAtlfast", help="ATLFAST flag [0/1]", default=0)
parser.add_option("--ismc15c", help="mc15c flag [0/1]", default=0)
#parser.add_option("--skipBtag", help="skip b-tagging in p1846 [0/1=skip]", default=0)
parser.add_option("--doSyst", help="Create Trees with systemtic variations [0/1]", default=0)

(options, args) = parser.parse_args()

import atexit
@atexit.register
def quite_exit():
    ROOT.gSystem.Exit(0)

logging.info("loading packages")
ROOT.gROOT.Macro("$ROOTCOREDIR/scripts/load_packages.C")

if options.overwrite:
    import shutil
    shutil.rmtree(options.submitDir, True)


#Set up the job for xAOD access:
ROOT.xAOD.Init().ignore();

# create a new sample handler to describe the data files we use
logging.info("creating new sample handler")
sh_all = ROOT.SH.SampleHandler()

if options.outputDS != "none":
    ROOT.SH.scanRucio (sh_all, options.inputDS);
else :
  search_directories = []
#  search_directories = ("/afs/cern.ch/work/o/othrif/workarea/myAthena/derivation/truthel/test2/WorkArea/run",)  
  print "isData: ", options.isData
  if int(options.isData)==1:
      search_directories = ("/UserDisk2/othrif/data/SUSY2/data/",)
  else:
      search_directories = ("/UserDisk2/othrif/data/SUSY2/mc15/",)      
  # scan for datasets in the given directories
  for directory in search_directories:
    ROOT.SH.scanDir(sh_all, directory)

  print "Search directories:", search_directories

# print out the samples we found
logging.info("%d different datasets found scanning all directories", len(sh_all))

# set the name of the tree in our files
sh_all.setMetaString("nc_tree", "CollectionTree")

# this is the basic description of our job
logging.info("creating new job")
job = ROOT.EL.Job()
job.sampleHandler(sh_all)
  
if options.nevents:
    logging.info("processing only %d events", options.nevents)
    job.options().setDouble(ROOT.EL.Job.optMaxEvents, options.nevents)

if options.skip_events:
    logging.info("skipping first %d events", options.skip_events)
    job.options().setDouble(ROOT.EL.Job.optSkipEvents, options.skip_events)

# add our algorithm to the job
logging.info("creating algorithms")
alg = ROOT.MyxAODAnalysis()
print "isData?",options.isData
print "isDerivation?",options.isData
print "isAF?",options.isAtlfast
print "ismc15c?",options.ismc15c

#print "skipBtag?",options.skipBtag
logging.info("adding data")
alg.isData = int(options.isData)
logging.info("adding AF")
alg.isAtlfast = int(options.isAtlfast)
logging.info("adding mc15c")
alg.ismc15c = int(options.ismc15c )
#alg.skipBtag = int(options.skipBtag)
alg.doSyst = options.doSyst
alg.inputDS = options.inputDS

logging.info("adding algorithms")
job.algsAdd(alg)

# make the driver we want to use:
# this one works by running the algorithm directly
logging.info("creating driver")
driver = None
if (options.driver == "direct"):
    logging.info("running on direct")
    driver = ROOT.EL.DirectDriver()
    logging.info("submit job")
    driver.submit(job, options.submitDir)
#    print "submit dir:", options.submitDir
    logging.info("done submit job")
elif (options.driver == "prooflite"):
    logging.info("running on prooflite")
    driver = ROOT.EL.ProofDriver()
    logging.info("submit job")
    driver.submit(job, options.submitDir)
elif (options.driver == "grid"):
    logging.info("running on Grid") 
    driver = ROOT.EL.PrunDriver()   
    #driver.options().setString("nc_outputSampleName", "user.jpoveda.t0607_v07.%in:name[2]%.%in:name[3].%in:name[6]%")
    driver.options().setString("nc_outputSampleName", options.outputDS)
    #    driver.options().setString("nc_outputSampleName", "user.jpoveda.pilot.test")
    driver.options().setDouble("nc_disableAutoRetry", 1)
    driver.options().setDouble("nc_nGBPerJob", 5)
    driver.options().setString("nc_nGBPerJob", "5")
    if int(options.isData)==1:
        driver.options().setDouble("nc_nFilesPerJob", 1)
        driver.options().setString("nc_nFilesPerJob", "1")
    # If willing to specify an output Storage element for your job
#    driver.options().setString("nc_destSE", "CERN-PROD_LOCALGROUPDISK")
#    driver.options().setString("nc_destSE", "OU_OCHEP_SWT2_LOCALGROUPDISK")
    driver.options().setString("nc_destSE", "LUCILLE_LOCALGROUPDISK")
    # If willing to veto certain sites
    driver.options().setString('nc_excludedSite','ANALY_MWT2_SL6')    
    logging.info("submit job")
    driver.submitOnly(job, options.submitDir)

