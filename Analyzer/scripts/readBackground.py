from ROOT import gSystem,gStyle,gROOT
from ROOT import TFile, TH1F, TH2F, TCanvas, TLatex,TArrayF,MakeNullPointer,TParameter, TGraph2D, TGraph
from ROOT import RooStats, TLimit, TVectorD, TObjArray, TObjString, TLimitDataSource, TConfidenceLevel, Form
from os import listdir
from array import array
from math import sqrt
import os
import sys 

gROOT.SetBatch(True)

OUTPUT_FOLDER = sys.argv[1]
OUTPUT_PATH = "/afs/cern.ch/work/o/othrif/workarea/results/v48/"+OUTPUT_FOLDER

sr = ['SR3L1', 'SR0b1', 'SR0b2', 'SR0b5j', 'SR1b', 'SR2b1', 'SR2b2', 'SR3b', 'SR3l3b']
cr = ['CR0b', 'CR1b']
detail=1
ximo=1
peter=1
lumi=34500
#for i in sr:
for i in cr:
    print "\n", i
    yields = []
    yXimo = []
    yPeter = []
    total = 0
    count = 0
    for ifile in listdir(OUTPUT_PATH):
        if ifile.endswith(".root") and "merged" not in ifile and "data" not in ifile and "old" not in ifile and "ttn1" not in ifile and "6TTBar" not in ifile and "Wbkg" not in ifile and "Zjets" not in ifile and "mg" not in ifile:
            #            print ifile
            pointsplit = ifile.split(".")[0]
            f = TFile(OUTPUT_PATH+"/"+ifile)
            histo=f.Get("NJETS_"+pointsplit+"_mc_comb_"+i+"_SS3L")
#            print "%.2f" % (histo.GetEntries())
            if detail == 1:
                print "%s %d %.2f" % (pointsplit, histo.GetEntries(), histo.Integral()*lumi)
                count = count +1
            total += histo.Integral()*lumi
    print "Total Background yield: %.2f" % (total) 
            #        histo2=f.Get("NJETS_"+pointsplit+"_mc_comb_SR3b2_SS3L")
            #        print "%s %.2f %.2f" % (pointsplit, histo1.Integral(), histo2.Integral())
            #        print "%s" % (pointsplit)
'''
            yields.append(histo.Integral())
    if ximo == 1:
        print "\nXimo"
        print "%.2f" % (yields[15])
        print "%.2f" % (yields[16])
        print "%.2f" % (yields[2]+yields[3]+yields[4]+yields[12])
        print "%.2f" % (yields[13])
        print "%.2f" % (yields[0]+yields[1]+yields[9]+yields[10]+yields[11]+yields[8])
        print "%.2f" % (yields[5])
    if peter == 1:
        print "\nPeter"
        print "%.2f" % (yields[2])
        print "%.2f" % (yields[3])
        print "%.2f" % (yields[1])
        print "%.2f" % (yields[0])
        print "%.2f" % (yields[9]+yields[5]+yields[6]+yields[7]+yields[12]+yields[11]+yields[10]+yields[8])
        print "%.2f" % (yields[4])
    print "total=",total
'''
