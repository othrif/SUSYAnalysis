# Resort to https://twiki.cern.ch/twiki/bin/view/Atlas/PandaRun for documentation
# Alexander Paramonov
# April 2010
#
def main():
    import sys
    import user
    import glob
    import os
    
    fpath = '/UserDisk2/othrif/data/MiniNtuple/v44-3/'
#    folder = sys.argv[1]
    filename = sys.argv[1]

    # output                                                                    
#    outputFile = os.path.join(fpath, 'user.othrif.'+filename)
    outputFile = os.path.join(fpath, filename)

    # input
    path = os.path.join('/UserDisk2/othrif/data/Ximo/v44-3/'+filename)
    inputFiles = glob.glob(path)

#    outputFile = "/tmp/test_out1.root"
#    inputFiles = glob.glob('/UserDisk2/othrif/susy/mc_method/Ximo.v18/user.jpoveda.t0616_v18.00270816.physics_Main.DAOD_SUSY2.f611_m1463_p2375_output.root/*.root')
 #   inputFiles = glob.glob('/UserDisk2/othrif/susy/test/mc15_13TeV.370602.MGPy8EG_A14N23LO_NUHM2_m12_400_strong.merge.DAOD.e4209_a766_a777_r6282.root')

#    filename = sys.argv[1]
    # output
#    outputFile = "/tmp/test_out1.root"
#    outputFile = '/tmp/',filename,'.root'
    # input
#    inputFiles = glob.glob('/users/orifki/workarea/susy_ss3l/input/user.jpoveda.5286937._000001.output.root')
#    inputFiles = glob.glob('/data3/orifki/gtt_above_diag_FULL/validation/mc12_8TeV.156581.Herwigpp_UEEE3_CTEQ6L1_Gtt_G1100_T2500_L200.merge.NTUP_SUSY.e1221_s1469_s1470_r3542_r3549_p1328_tid01151387_00/NTUP_SUSY.01151387._000001.root.1')


    # run over data
#    inputFiles = glob.glob('/data3/orifki/susy/cutflow/user.jpoveda.t0609_v12.00266904.physics_Main.DAOD_SUSY9.f594_m1435_p2361_output.root.30695488/user.jpoveda.5632900._000001.output.root')
#    inputFiles = glob.glob('/afs/cern.ch/user/o/othrif/data/user.jpoveda.t0609_v12.00266904.physics_Main.DAOD_SUSY9.f594_m1435_p2361_output.root.30695488/user.jpoveda.5632900._000001.output.root')

#    inputFiles = glob.glob('/afs/cern.ch/user/o/othrif/data/user.jpoveda.t0609_v12.410000.PowhegPythiaEvtGen_P2012_ttbar_hdamp172p5_nonallhad.DAOD_SUSY1.s2608_r6633_p2353_output.root.*/*.root')

#    inputFiles = glob.glob('/UserDisk2/othrif/susy/mc_method/user.jpoveda.t0615_v17.00266904.physics_Main.DAOD_SUSY9.r6847_p2358_p2361_output.root/*.root')

#    inputFiles = glob.glob('/UserDisk2/othrif/susy/mc_method/user.jpoveda.t0616_v18.410067.MadGraphPythia8EvtGen_A14NNPDF23LO_ttW_Np1.DAOD_SUSY2.s2608_r6793_p2375_output.root/user.jpoveda.6120928._000001.output.root')

#    inputFiles = glob.glob('/UserDisk2/othrif/susy/mc_method/user.jpoveda.t0615_v17.361106.PowhegPythia8EvtGen_AZNLOCTEQ6L1_Zee.DAOD_SUSY2.s2576_r6630_p2375_output.root/*.root')

    from GaudiPython import AppMgr
    theApp = AppMgr()
    theApp.EvtMax = 100
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
    myNtp.MinLeptonPt = 13000.

    theApp.topAlg = ["TMiniNtuple"]

    theApp.config()
    theApp.initialize()
    theApp.run(1)
    theApp.exit()

    
if __name__ == "__main__":
    main()
