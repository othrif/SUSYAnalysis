# Othmane Rifki                                                                                                                                               

from ROOT import gSystem,gStyle,gROOT
from ROOT import TFile, TH1F, TH2F, TCanvas, TLatex,TArrayF,MakeNullPointer,TParameter, TGraph2D, TGraph, TLine, TText
from ROOT import RooStats, TLimit, TVectorD, TObjArray, TObjString, TLimitDataSource, TConfidenceLevel, Form
from os import listdir
from array import array
from math import sqrt
import os
import random
import sys

gROOT.SetBatch(True)


Dirbase=sys.argv[1]

bkgFilesNames=["4top.root"]

path="/raid05/users/othrif/results/v47/"+Dirbase+"/"

bkgFiles = [ TFile("/raid05/users/othrif/results/v47/"+Dirbase+"/"+filename) for filename in bkgFilesNames]

SR = ['SR3L1', 'SR3L2', 'SR0b1', 'SR0b2', 'SR1b1', 'SR1b2', 'SR1b3', 'SR1b4', 'SR1b3LSS', 'SR3b1', 'SR3b2', 'SRlow', 'SRhigh', 'SR1b_DD', 'SR3b_DD', 'SR1b_GG', 'SRRPV0b', 'SRRPV3b']

for j in SR:
    bkgYields=[MakeNullPointer(TH1F) for bkgFile in bkgFiles]
    for i in range(len(bkgFiles)):
#    bkgFiles[i].GetObject("NJETS_4top_mc_comb_SR3b2_SS3L",bkgYields[i])
        bkgYields[i] = bkgFiles[i].Get("NJETS_4top_mc_comb_"+j+"_SS3L")

    for ibkg in range(len(bkgYields)):
        bkgtmp = bkgYields[ibkg].Integral()*36450
        bkgstattmp = bkgYields[ibkg].GetEntries()
        
    print j, bkgtmp, bkgstattmp
