# Resort to https://twiki.cern.ch/twiki/bin/view/Atlas/PandaRun for documentation
# Alexander Paramonov
# April 2010
#
def main():
    import sys
    import user

#    sys.path.append("../i686-slc5-gcc43-opt/")

    # output
    outputFile = "out1.root"
    # input
    inputFiles = sys.argv[1].split(',')


    from GaudiPython import AppMgr
    theApp = AppMgr()
    theApp.EvtMax = 1
    # Verboseness threshold level: 0=NIL,1=VERBOSE, 2=DEBUG, 3=INFO, 4=WARNING, 5=ERROR, 6=FATAL, 7=ALWAYS
#    theApp.outputLevel = 4
#    MessageSvc.OutputLevel = 4
#    EventSelector.OutputLevel = 4
    theApp.JobOptionsType = "NONE"
    theApp.EvtSel = "NONE"
    theApp.Dlls = ["GaudiAlg", "MiniNtuple"]


    myNtp = theApp.algorithm("TMiniNtuple")
    myNtp.InputFileName = inputFiles
    myNtp.OutputFileName = outputFile 
    myNtp.Debug =  False
    myNtp.ApplyLeptonSkim = True
    myNtp.MinLeptonPt = 9000.

    theApp.topAlg = ["TMiniNtuple"]

    theApp.config()
    theApp.initialize()
    theApp.run(1)
    theApp.exit()

    
if __name__ == "__main__":
    main()
