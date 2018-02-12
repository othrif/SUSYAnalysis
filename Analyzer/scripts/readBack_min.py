from ROOT import gSystem,gStyle,gROOT, Double
from ROOT import TFile, TH1F, TH2F, TCanvas, TLatex,TArrayF,MakeNullPointer,TParameter, TGraph2D, TGraph
from ROOT import RooStats, TLimit, TVectorD, TObjArray, TObjString, TLimitDataSource, TConfidenceLevel, Form
from os import listdir
from array import array
from math import sqrt
import os
import sys 

gROOT.SetBatch(True)


OUTPUT_FOLDER = sys.argv[1]
OUTPUT_PATH = "/afs/cern.ch/work/o/othrif/workarea/results/v52/"+OUTPUT_FOLDER

sr = ['SR0b2', 'SR0b1', 'SR3b2', 'SR3b1', 'SR1b2', 'SR1b1', 'SRhigh', 'SRlow', 'SR3L0b2', 'SR3L0b1', 'SR1b_3LSS', 'SR3L1b2', 'SR3L1b1', 'SRRPV0b', 'SR1b_GG', 'SR1b_DD_high', 'SR1b_DD_low', 'SRRPV3b', 'SR3b_DD']
srcr = ['SR0b2', 'SR0b1', 'SR3b2', 'SR3b1', 'SR1b2', 'SR1b1', 'SRhigh', 'SRlow', 'SR3L0b2', 'SR3L0b1', 'SR1b_3LSS', 'SR3L1b2', 'SR3L1b1', 'SRRPV0b', 'SR1b_GG', 'SR1b_DD_high', 'SR1b_DD_low', 'SRRPV3b', 'SR3b_DD', 'VRttW','VRttZ','VRWW','VRWZ4j','VRWZ5j','Rpc2L2bH','Rpc2L2bS','Rpv2L2bH','Rpv2L2bS']
#'SR3L0b1', 'SR3L0b2', 'SR3L1b1', 'SR3L1b2', 'SR0b1', 'SR0b2', 'SR1b1', 'SR1b2', 'SR3b1', 'SR3b2', 'SRlow', 'SRhigh', 'SR1b_3LSS', 'SR1b_DD_low', 'SR1b_DD_high', 'SR3b_DD', 'SR1b_GG', 'SRRPV0b', 'SRRPV3b']
cr = ['VRttW','VRttZ','VRWW','VRWZ4j','VRWZ5j']
test = ['SR1b_3LSS']
shower=0
detail=0
note=1
lumi=1#34500
#for i in sr:
#for i in cr:
for i in srcr:
#for i in test:
    print "\n", i
    yields = []
    yXimo = []
    yPeter = []
    total = 0
    totalerr = 0
    count = 0
#    undesired = ["merged", "data", "old", "ttn1", "TTBar", "Wjets", "otherNP", "Zjets", "mg", "TT_2step"]
    undesired = ["merged", "old", "ttn1", "TTBar", "Wjets", "otherNP", "Zjets", "mg", "TT_2step"]
    fakes_sherpa = ["sherpa"]
    fakes_pythia = ["pythia"]
    dict = {}
    for ifile in listdir(OUTPUT_PATH):
        if ifile.endswith(".root") and not any(s in ifile for s in undesired):
#            continue
#            print ifile
            pointsplit = ifile.split(".")[0]
            f = TFile(OUTPUT_PATH+"/"+ifile)
            histo=f.Get("NJETS_"+pointsplit+"_mc_comb_"+i+"_SS3L")
            if(i == 'SR1b_3LSS'):
                histo=f.Get("NJETS_"+pointsplit+"_prompt_comb_"+i+"_SS3L")
            if(pointsplit == 'data'):
                histo=f.Get("NJETS_data_comb_"+i+"_SS3L")
            histo.Scale(lumi)
            if detail == 1:
                print "%s %d %.2f" % (pointsplit, histo.GetEntries(), histo.Integral())
                count = count +1

            stattmp = Double(0)
            maxbin = histo.GetNbinsX()+1
            tmp = histo.IntegralAndError(0,maxbin,stattmp)
            dict[pointsplit] = tmp;
            dict['err_'+pointsplit] = stattmp
            yields.append(histo.Integral())
            if (pointsplit != 'data'):
                total += histo.Integral()
                totalerr += stattmp*stattmp
#    print "Total Background yield: %.2f" % (total) 
    totalerr = sqrt(totalerr)
    dict['total_prompt'] = total
    dict['diboson'] = dict['WW']+dict['ZZ']+dict['WZ']
    dict['rare'] = dict['ttWW']+dict['tZ']+dict['tWZ']+dict['Vh']+dict['VVV']+dict['3t']+dict['ttWZ']
    dict['err_total_prompt'] = totalerr
    dict['err_diboson'] = sqrt(pow(dict['err_WW'],2)+pow(dict['err_ZZ'],2)+pow(dict['err_WZ'],2))
    dict['err_rare'] = sqrt(pow(dict['err_ttWW'],2)+pow(dict['err_tZ'],2)+pow(dict['err_tWZ'],2)+pow(dict['err_Vh'],2)+pow(dict['err_VVV'],2)+pow(dict['err_3t'],2))

    if note == 1:
        print "==============================="
#        print "ttW = %.2f +- %.2f"% (dict['ttW'], dict['err_ttW'])
#        print "ttZ = %.2f +- %.2f"% (dict['ttZ'], dict['err_ttZ'])
#        print "WZ = %.2f +- %.2f"% (dict['WZ'], dict['err_WZ'])
#        print "WW = %.2f +- %.2f"% (dict['WW'], dict['err_WW'])
#        print "ZZ = %.2f +- %.2f"% (dict['ZZ'], dict['err_ZZ'])

        print "ttV = %.2f +- %.2f"% (dict['ttW']+dict['ttZ'], sqrt(pow(dict['err_ttW'],2)+pow(dict['err_ttZ'],2)))
        print "VV = %.2f +- %.2f"% (dict['diboson'], dict['err_diboson'])
        print "tth = %.2f +- %.2f"% (dict['tth'], dict['err_tth'])
        print "4top = %.2f +- %.2f"% (dict['4t'], dict['err_4t'])
        print "Rare = %.2f +- %.2f"% (dict['rare'], dict['err_rare'])
        print "==============================="
        print "Total Prompt = %.2f +- %.2f" % (dict['total_prompt'], dict['err_total_prompt'])
        print "==============================="
        print "Data = %.2f"% (dict['data'])
        print "==============================="
