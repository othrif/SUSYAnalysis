from ROOT import gSystem,gStyle,gROOT,Double
from ROOT import TFile, TH1F, TH2F, TCanvas, TLatex,TArrayF,MakeNullPointer,TParameter, TGraph2D, TGraph
from ROOT import RooStats, TLimit, TVectorD, TObjArray, TObjString, TLimitDataSource, TConfidenceLevel, Form
from os import listdir
from array import array
from math import sqrt
import os
import sys 

gROOT.SetBatch(True)

lumi = 36450

OUTPUT_FOLDER = sys.argv[1]
OUTPUT_PATH = "/afs/cern.ch/work/o/othrif/workarea/results/v47/"+OUTPUT_FOLDER

# chMisId, el HF, el LF, mu HF, mu LF
#corr = [1., 1., 1., 1., 1.]
corr = [0.98, 1.6, 1.3, 1.5, 3.1]
#err_corr = [0., 0., 0., 0., 0.]
sr = ['SR3L1', 'SR3L2', 'SR0b1', 'SR0b2', 'SR1b1', 'SR1b2', 'SR1b3', 'SR1b4', 'SR1b3LSS', 'SR3b1', 'SR3b2', 'SRlow', 'SRhigh', 'SR1b_DD', 'SR3b_DD', 'SR1b_GG', 'SRRPV0b', 'SRRPV3b']
detail=1

for i in sr:
    print "\n", i
    yields = []
    total = 0
    count = 0
    ifile = "ttbar2"
    f = TFile(OUTPUT_PATH+"/"+ifile+".root")


    histo=f.Get("NJETS_"+ifile+"_mc_comb_"+i+"_SS3L")
    histo.Scale(lumi)
    stattmp = Double(0)
    maxbin = histo.GetNbinsX()+1
    total_mc = histo.IntegralAndError(0,maxbin,stattmp)
    total_mc_stat = stattmp 
    histo=f.Get("NJETS_chmisid_comb_"+i+"_SS3L")
    histo.Scale(lumi)
    stattmp = Double(0)
    maxbin = histo.GetNbinsX()+1
    charge_misid = histo.IntegralAndError(0,maxbin,stattmp)
    charge_misid_stat = stattmp 
    histo=f.Get("NJETS_fake_HF_e_comb_"+i+"_SS3L")
    histo.Scale(lumi)
    stattmp = Double(0)
    maxbin = histo.GetNbinsX()+1
    fake_HF_e = histo.IntegralAndError(0,maxbin,stattmp)
    fake_HF_e_stat = stattmp
    histo=f.Get("NJETS_fake_LF_e_comb_"+i+"_SS3L")
    histo.Scale(lumi)
    stattmp = Double(0)
    maxbin = histo.GetNbinsX()+1
    fake_LF_e = histo.IntegralAndError(0,maxbin,stattmp)
    fake_LF_e_stat = stattmp
    histo=f.Get("NJETS_fake_HF_m_comb_"+i+"_SS3L")
    histo.Scale(lumi)
    stattmp = Double(0)
    maxbin = histo.GetNbinsX()+1
    fake_HF_m = histo.IntegralAndError(0,maxbin,stattmp)
    fake_HF_m_stat = stattmp
    histo=f.Get("NJETS_fake_LF_m_comb_"+i+"_SS3L")
    histo.Scale(lumi)
    stattmp = Double(0)
    maxbin = histo.GetNbinsX()+1
    fake_LF_m = histo.IntegralAndError(0,maxbin,stattmp)
    fake_LF_m_stat = stattmp

    charge_misid = corr[0]*charge_misid
    charge_misid_err = corr[0]*charge_misid_stat
    fake  = corr[1]*fake_HF_e + corr[2]*fake_LF_e + corr[3]*fake_HF_m+ corr[4]*fake_LF_m
    fake_err = sqrt(pow(corr[1]*fake_HF_e_stat,2) + pow(corr[2]*fake_LF_e_stat,2) + pow(corr[3]*fake_HF_m_stat,2) + pow(corr[4]*fake_LF_m_stat,2))
    print "Pure ttbar = %.2f +- %.2f // fake = %.2f +- %.2f // chmisid = %.2f +- %.2f" % (total_mc, total_mc_stat, fake, fake_err, charge_misid, charge_misid_err)
