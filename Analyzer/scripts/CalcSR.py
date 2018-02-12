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

singleCut = 1
testMe = 0
luminosity= 36.45#/35000 # 30 # 70 # 100

LargeNum=999999999

lepptmax2_cut = [75, 100, 99999997952, ]
lepptmin2_cut = [ 10, 20, ]
lepptmax1_cut = [ 75, 100, 99999997952, ]
lepptmin1_cut = [ 10, 20, ]
bjets_cut = [ 3, ]
bjetptmax_cut = [ 99999997952, ]
bjetptmin_cut = [ 20, ]
nbjets_cut = [ 1, 2, 3, ]
jetptmax_cut = [ 99999997952, ]
jetptmin_cut = [ 25, ]
njets_cut = [ 6, ]
metmax_cut = [ 99999997952, ]
metmin_cut = [ 0, 100, 150, 200, 220, 250, 300, 350, 400, ]
mtMmax_cut = [ 99999997952, ]
mtMmin_cut = [ 0, ]
meff_cut = [ 0, 600, 700, 800, 900, 1000, 1100, 1200, ]
metOmeff_cut = [ 0.00, 0.20, 0.25, 0.30, ]

# cuts

#newOpt1
SRcuts = [
[2, 1, 2, 1, 0, 0, 0, 2, 0, 0, 0, 0, 2, 0, 0, 0, 1], # SR3b1
[2, 1, 2, 1, 0, 0, 0, 1, 0, 0, 0, 0, 3, 0, 0, 1, 3], # SR2b1
#[2, 1, 2, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1], # SR2b2


#[2, 1, 2, 1, 0, 0, 0, 2, 0, 0, 0, 0, 5, 0, 0, 7, 0], # SR3b2
#[2, 0, 2, 1, 0, 0, 0, 1, 0, 0, 0, 0, 3, 0, 0, 1, 2], # SRlow-nobound-pt
#[2, 0, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 3], # SRhigh-nobound-pt
[2, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 3, 0, 0, 1, 2], # SRlow-bound-pt
[2, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 3], # SRhigh-bound-pt
#[2, 1, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 1, 2], # SR1b1
#[2, 1, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 7, 1], # SR1b2
]


Dirbase=sys.argv[1]
SigSample=sys.argv[2]
OutName=sys.argv[3]

bkgFilesNames=["ttW.root", "ttZ.root", "WW.root", "WZ.root", "ZZ.root", "VVV.root", "tth.root", "Zh.root", "Wh.root", "ttWW.root", "3t.root", "4t.root", "tZ.root", "powhegpythia6TTBar.root", "otherNP.root", 
               "powhegpythia8Zjets.root", "powhegpythia8Wjets.root"]
useMinBkg=[0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0]

path="/afs/cern.ch/user/o/othrif/workarea/results/v48/"+Dirbase+"_"+SigSample+"/"
#path="/UserDisk2/othrif/Backup/v8_results_022417/v48/"+Dirbase+"_"+SigSample+"/"

#hFinalSig = TH2F("Significance","hFinalSig",24,600,1600,60,000,1200)
if SigSample == "GG_ttn1":
    hConfLevel = TH2F("ConfidenceLevel","95% Confidence level",24,600,1600,60,000,1200)
    hFinalSig = TH2F("Significance","hFinalSig",50,600,2100,175,0,1700)
    hFinallepptmax2 = [TH2F("lepptmax2","lepptmax2",50,600,2100,175,0,1700), "lepptmax2"]
    hFinallepptmin2 = [TH2F("lepptmin2","lepptmin2",50,600,2100,175,0,1700), "lepptmin2"]
    hFinallepptmax1 = [TH2F("lepptmax1","lepptmax1",50,600,2100,175,0,1700), "lepptmax1"]
    hFinallepptmin1 = [TH2F("lepptmin1","lepptmin1",50,600,2100,175,0,1700), "lepptmin1"]
    hFinalbjets = [TH2F("bjets","bjets",50,600,2100,175,0,1700), "bjets"]
    hFinalbjetptmax = [TH2F("bjetptmax","bjetptmax",50,600,2100,175,0,1700), "bjetptmax"]
    hFinalbjetptmin = [TH2F("bjetptmin","bjetptmin",50,600,2100,175,0,1700), "bjetptmin"]
    hFinalnbjets = [TH2F("nbjets","nbjets",50,600,2100,175,0,1700), "nbjets"]
    hFinaljetptmax = [TH2F("jetptmax","jetptmax",50,600,2100,175,0,1700), "jetptmax"]
    hFinaljetptmin = [TH2F("jetptmin","jetptmin",50,600,2100,175,0,1700), "jetptmin"]
    hFinalnjets = [TH2F("njets","njets",50,600,2100,175,0,1700), "njets"]
    hFinalmetmax = [TH2F("metmax","metmax",50,600,2100,175,0,1700), "metmax"]
    hFinalmetmin = [TH2F("metmin","metmin",50,600,2100,175,0,1700), "metmin"]
    hFinalmtMmax = [TH2F("mtMmax","mtMmax",50,600,2100,175,0,1700), "mtMmax"]
    hFinalmtMmin = [TH2F("mtMmin","mtMmin",50,600,2100,175,0,1700), "mtMmin"]
    hFinalmeff = [TH2F("meff","meff",50,600,2100,175,0,1700), "meff"]
    hFinalmeff_cut = [TH2F("meff_cut","meff_cut",50,600,2100,175,0,1700), "meff_cut"]
    hFinalmetOmeff = [TH2F("metOmeff","metOmeff",50,600,2100,175,0,1700), "metOmeff"]
    hFinalSig_Dm = TH2F("Significance_Dm","hFinalSig",40,600,2100,35,0,200)
    hFinallepptmax2_Dm = [TH2F("lepptmax2_Dm","lepptmax2",40,600,2100,35,0,200), "lepptmax2"]
    hFinallepptmin2_Dm = [TH2F("lepptmin2_Dm","lepptmin2",40,600,2100,35,0,200), "lepptmin2"]
    hFinallepptmax1_Dm = [TH2F("lepptmax1_Dm","lepptmax1",40,600,2100,35,0,200), "lepptmax1"]
    hFinallepptmin1_Dm = [TH2F("lepptmin1_Dm","lepptmin1",40,600,2100,35,0,200), "lepptmin1"]
    hFinalbjets_Dm = [TH2F("bjets_Dm","bjets",40,600,2100,35,0,200), "bjets"]
    hFinalbjetptmax_Dm = [TH2F("bjetptmax_Dm","bjetptmax",40,600,2100,35,0,200), "bjetptmax"]
    hFinalbjetptmin_Dm = [TH2F("bjetptmin_Dm","bjetptmin",40,600,2100,35,0,200), "bjetptmin"]
    hFinalnbjets_Dm = [TH2F("nbjets_Dm","nbjets",40,600,2100,35,0,200), "nbjets"]
    hFinaljetptmax_Dm = [TH2F("jetptmax_Dm","jetptmax",40,600,2100,35,0,200), "jetptmax"]
    hFinaljetptmin_Dm = [TH2F("jetptmin_Dm","jetptmin",40,600,2100,35,0,200), "jetptmin"]
    hFinalnjets_Dm = [TH2F("njets_Dm","njets",40,600,2100,35,0,200), "njets"]
    hFinalmetmax_Dm = [TH2F("metmax_Dm","metmax",40,600,2100,35,0,200), "metmax"]
    hFinalmetmin_Dm = [TH2F("metmin_Dm","metmin",40,600,2100,35,0,200), "metmin"]
    hFinalmtMmax_Dm = [TH2F("mtMmax_Dm","mtMmax",40,600,2100,35,0,200), "mtMmax"]
    hFinalmtMmin_Dm = [TH2F("mtMmin_Dm","mtMmin",40,600,2100,35,0,200), "mtMmin"]
    hFinalmeff_Dm = [TH2F("meff_Dm","meff",40,600,2100,35,0,200), "meff"]
    hFinalmeff_cut_Dm = [TH2F("meff_cut_Dm","meff_cut",50,600,2100,35,0,200), "meff_cut"]
    hFinalmetOmeff_Dm = [TH2F("metOmeff_Dm","metOmeff",40,600,2100,35,0,200), "metOmeff"]
elif SigSample == "GG_2stepWZ":
    hConfLevel = TH2F("ConfidenceLevel","95% Confidence level",12,550,1750,20,100,1600)
    hFinalSig = TH2F("Significance","hFinalSig",12,550,1750,20,100,1600)
    hFinalJetPtmax = [TH2F("JetPtmax","JetPtmax",12,550,1750,20,100,1600), "Jet Pt max Cut"]
    hFinalNBJet = [TH2F("NBJets","NBJet",12,550,1750,20,100,1600),"N BJet Cut"]
    hFinalNJet = [TH2F("NJets","NJet",12,550,1750,20,100,1600), "N Jet Cut"]
    hFinalMet = [TH2F("MET","Met",12,550,1750,20,100,1600), "Met Cut"]
    hFinalMeff = [TH2F("Meff","Meff",12,550,1750,20,100,1600), "Meff Cut"]
elif SigSample == "GG_SLN1":
    hConfLevel = TH2F("ConfidenceLevel","95% Confidence level",15,350,1850,20,000,1200)
    hFinalSig = TH2F("Significance","hFinalSig",15,350,1850,20,000,1200)
    hFinalJetPtmax = [TH2F("JetPtmax","JetPtmax",15,350,1850,20,000,1200), "Jet Pt max Cut"]
    hFinalNBJet = [TH2F("NBJets","NBJet",15,350,1850,20,000,1200),"N BJet Cut"]
    hFinalNJet = [TH2F("NJets","NJet",15,350,1850,20,000,1200), "N Jet Cut"]
    hFinalMet = [TH2F("MET","Met",15,350,1850,20,000,1200), "Met Cut"]
    hFinalMeff = [TH2F("Meff","Meff",15,350,1850,20,000,1200), "Meff Cut"]
elif SigSample == "BB_onestepC1": 
    hConfLevel = TH2F("ConfidenceLevel","95% Confidence level",12,325,925, 20,0,400)
    hFinalSig = TH2F("Significance","hFinalSig",12,325,925, 20,0,400)
    hFinalJetPtmax = [TH2F("JetPtmax","JetPtmax",12,325,925, 20,0,400), "Jet Pt max Cut"]
    hFinalNBJet = [TH2F("NBJets","NBJet",12,325,925, 20,0,400),"N BJet Cut"]
    hFinalNJet = [TH2F("NJets","NJet",12,325,925, 20,0,400), "N Jet Cut"]
    hFinalMet = [TH2F("MET","Met",12,325,925, 20,0,400), "Met Cut"]
    hFinalMeff = [TH2F("Meff","Meff",12,325,925, 20,0,400), "Meff Cut"]
else:
    print "ERROR: Wrong sample name"
    print "choose from: GG_ttn1, GG_2stepWZ, GG_SLN1, BB_onestepC1"
    sys.exit()

bestCutHists=[hFinallepptmax1,hFinallepptmin1,hFinallepptmax2,hFinallepptmin2,hFinalbjets,hFinalbjetptmax,hFinalbjetptmin,hFinalnbjets,hFinaljetptmax,hFinaljetptmin,hFinalnjets,hFinalmetmax,hFinalmetmin,hFinalmtMmax,hFinalmtMmin,hFinalmeff_cut,hFinalmeff,hFinalmetOmeff]
bestCutHists_Dm=[hFinallepptmax1_Dm,hFinallepptmin1_Dm,hFinallepptmax2_Dm,hFinallepptmin2_Dm,hFinalbjets_Dm,hFinalbjetptmax_Dm,hFinalbjetptmin_Dm,hFinalnbjets_Dm,hFinaljetptmax_Dm,hFinaljetptmin_Dm,hFinalnjets_Dm,hFinalmetmax_Dm,hFinalmetmin_Dm,hFinalmtMmax_Dm,hFinalmtMmin_Dm,hFinalmeff_cut_Dm,hFinalmeff_Dm,hFinalmetOmeff_Dm]
ignore_hist = []
#ignore_hist = [0, 2, 4, 5, 8, 11, 13, 14, 16] 
#ignore_hist = [4, 5, 8, 13, 14, 16] 
#############################################################################

def calcSig(sigFileName, SRindex, printbkg=False):
    #    print sigFileName
    bkgFiles = [ TFile("/afs/cern.ch/user/o/othrif/workarea/results/v48/"+Dirbase+"_Background/"+filename) for filename in bkgFilesNames]
    #bkgFiles = [ TFile("/UserDisk2/othrif/Backup/v8_results_022417/v48/"+Dirbase+"_Background/"+filename) for filename in bkgFilesNames]
    sigFile = TFile(sigFileName)

    sigYield=MakeNullPointer(TH1F)
    sigFile.GetObject("hyield_weighted",sigYield)

    bkgYields=[MakeNullPointer(TH1F) for bkgFile in bkgFiles]
    for i in range(len(bkgFiles)):
        #        print bkgFilesNames[i]
        #        bkgFiles[i].GetObject("ayield_weighted",bkgYields[i])
        bkgFiles[i].GetObject("hyield_weighted",bkgYields[i])

    # print bin numbers and cuts
    if(testMe):
        cutsname = path+"/logs/cuts.log"
        print "writing ", cutsname
        f = open(cutsname,'w')
        bin=1 
        for ilepptmax2 in range(0,len(lepptmax2_cut)):
            for ilepptmin2 in range(0,len(lepptmin2_cut)):
                for ilepptmax1 in range(0,len(lepptmax1_cut)):
                    for ilepptmin1 in range(0,len(lepptmin1_cut)):
                        for ibjets in range(0,len(bjets_cut)):
                            for ibjetptmax in range(0,len(bjetptmax_cut)):
                                for ibjetptmin in range(0,len(bjetptmin_cut)):
                                    for inbjets in range(0,len(nbjets_cut)):
                                        for ijetptmax in range(0,len(jetptmax_cut)):
                                            for ijetptmin in range(0,len(jetptmin_cut)):
                                                for injets in range(0,len(njets_cut)):
                                                    for imetmax in range(0,len(metmax_cut)):
                                                        for imetmin in range(0,len(metmin_cut)):
                                                            baseMeff=metmin_cut[imetmin]+njets_cut[injets]*jetptmin_cut[ijetptmin]+lepptmin1_cut[ilepptmin1]+lepptmin2_cut[ilepptmin2]
                                                            for imtMmax in range(0,len(mtMmax_cut)):
                                                                for imtMmin in range(0,len(mtMmin_cut)):
                                                                    for imeff in range(0,len(meff_cut)):
                                                                        for imetOmeff in range(0,len(metOmeff_cut)):
                                                                            print bin, sigYield.GetAt(bin), lepptmax1_cut[ilepptmax1], lepptmin1_cut[ilepptmin1], lepptmax2_cut[ilepptmax2], lepptmin2_cut[ilepptmin2], nbjets_cut[inbjets], njets_cut[injets], metmax_cut[imetmax], metmin_cut[imetmin], mtMmin_cut[imtMmin], meff_cut[imeff], meff_cut[imeff]+baseMeff, metOmeff_cut[imetOmeff]
                                                                            output_cuts = "bin={0:8.2f}, bin content={1:8.2f}, lepptmax1={2:8.2f}, lepptmin1={3:8.2f}, lepptmax2={4:8.2f}, lepptmin2={5:8.2f}, nbjets={6:8.2f}, njets={7:8.2f}, metmax={8:8.2f}, metmin={9:8.2f}, mtMmin={10:8.2f}, meff_cut={11:8.2f}, meff={12:8.2f}, metOmeff={13:8.2f}".format(bin, sigYield.GetAt(bin), lepptmax1_cut[ilepptmax1], lepptmin1_cut[ilepptmin1], lepptmax2_cut[ilepptmax2], lepptmin2_cut[ilepptmin2], nbjets_cut[inbjets], njets_cut[injets], metmax_cut[imetmax], metmin_cut[imetmin], mtMmin_cut[imtMmin], meff_cut[imeff], meff_cut[imeff]+baseMeff, metOmeff_cut[imetOmeff])
                                                                            bin +=1
                                                                            new_output_cuts =output_cuts.replace("1000000000.00", "     Inf")
                                                                            f.write(str(new_output_cuts))
                                                                            f.write(str(new_output_cuts))
                                                                            f.write("\n")
        f.close()
        
    
    relativeBkgUncert = 0.3 
    sigResults=[]

    bin=0
    for ilepptmax2 in range(0,len(lepptmax2_cut)):
        for ilepptmin2 in range(0,len(lepptmin2_cut)):
            for ilepptmax1 in range(0,len(lepptmax1_cut)):
                for ilepptmin1 in range(0,len(lepptmin1_cut)):
                    for ibjets in range(0,len(bjets_cut)):
                        for ibjetptmax in range(0,len(bjetptmax_cut)):
                            for ibjetptmin in range(0,len(bjetptmin_cut)):
                                for inbjets in range(0,len(nbjets_cut)):
                                    for ijetptmax in range(0,len(jetptmax_cut)):
                                        for ijetptmin in range(0,len(jetptmin_cut)):
                                            for injets in range(0,len(njets_cut)):
                                                for imetmax in range(0,len(metmax_cut)):
                                                    for imetmin in range(0,len(metmin_cut)):
                                                        baseMeff=metmin_cut[imetmin]+njets_cut[injets]*jetptmin_cut[ijetptmin]+lepptmin1_cut[ilepptmin1]+lepptmin2_cut[ilepptmin2]
                                                        for imtMmax in range(0,len(mtMmax_cut)):
                                                            for imtMmin in range(0,len(mtMmin_cut)):
                                                                for imeff in range(0,len(meff_cut)):
                                                                    for imetOmeff in range(0,len(metOmeff_cut)):
                                                                        bin +=1
                                                                        if ilepptmax2 != SRcuts[SRindex][0]:
                                                                            continue
                                                                        if ilepptmin2 != SRcuts[SRindex][1]:
                                                                            continue
                                                                        if ilepptmax1 != SRcuts[SRindex][2]:
                                                                            continue
                                                                        if ilepptmin1 != SRcuts[SRindex][3]:
                                                                            continue
                                                                        if ibjets != SRcuts[SRindex][4]:
                                                                            continue
                                                                        if ibjetptmax != SRcuts[SRindex][5]:
                                                                            continue
                                                                        if ibjetptmin != SRcuts[SRindex][6]:
                                                                            continue
                                                                        if inbjets != SRcuts[SRindex][7]:
                                                                            continue
                                                                        if ijetptmax != SRcuts[SRindex][8]:
                                                                            continue
                                                                        if ijetptmin != SRcuts[SRindex][9]:
                                                                            continue
                                                                        if injets != SRcuts[SRindex][10]:
                                                                            continue
                                                                        if imetmax != SRcuts[SRindex][11]:
                                                                            continue
                                                                        if imetmin != SRcuts[SRindex][12]:
                                                                            continue
                                                                        if imtMmax != SRcuts[SRindex][13]:
                                                                            continue                                                                        
                                                                        if imtMmin != SRcuts[SRindex][14]:
                                                                            continue
                                                                        if imeff != SRcuts[SRindex][15]:
                                                                            continue
                                                                        if imetOmeff != SRcuts[SRindex][16]:
                                                                            continue
                                                                        sig = sigYield.GetAt(bin) #*luminosity*1000
                                                                        bkg = 0.0
                                                                        statbkg = 0.0
                                                                        for ibkg in range(len(bkgYields)):          
                                                                            bkgtmp = bkgYields[ibkg].GetBinContent(bin) #*luminosity*1000
                                                                            bkgstattmp = bkgYields[ibkg].GetBinError(bin) #*luminosity*1000
                                                                            if printbkg:
                                                                                print bkgFilesNames[ibkg], bkgYields[ibkg].GetBinContent(bin), " +- ", bkgYields[ibkg].GetBinError(bin)
                                                                                #    if (bkgtmp == 0):
                                                                                #        bkgtmp = useMinBkg[ibkg]
                                                                                # print ibkg, bkgtmp
                                                                            bkg += bkgtmp
                                                                            statbkg += bkgstattmp*bkgstattmp
                                                                        statbkg = sqrt(statbkg)
                                                                        if printbkg:
                                                                            print "\n======================================================="
                                                                            print "Total = ", bkg, " +- ", statbkg
                                                                            print "=======================================================\n"
                                                                        zObs=0.0
                                                                        if(sig>=2 and bkg>=0.8 and statbkg/bkg <= 0.3 ): # and statbkg/bkg <= 0.3 
                                                                            #                                                                        if(sig>0 and bkg>0):
                                                                            zObs=RooStats.NumberCountingUtils.BinomialExpZ(sig, bkg, relativeBkgUncert)
#                                                                            print zObs, sig, bkg
                                                                        elif (bkg<0.8):
                                                                            zObs=0.01
                                                                        elif (sig<2):
                                                                            zObs=0.02
                                                                        elif (statbkg/bkg > 0.3):
                                                                            zObs=0.03
                                                                    
                                                                        if(zObs>0.0):
                                                                            sigResults.append([zObs,[
                                                                                        lepptmax1_cut[ilepptmax1],
                                                                                        lepptmin1_cut[ilepptmin1],
                                                                                        lepptmax2_cut[ilepptmax2],
                                                                                        lepptmin2_cut[ilepptmin2],
                                                                                        bjets_cut[ibjets],
                                                                                        bjetptmax_cut[ibjetptmax],
                                                                                        bjetptmin_cut[ibjetptmin],
                                                                                        nbjets_cut[inbjets],
                                                                                        jetptmax_cut[ijetptmax],
                                                                                        jetptmin_cut[ijetptmin],
                                                                                        njets_cut[injets],
                                                                                        metmax_cut[imetmax],
                                                                                        metmin_cut[imetmin],
                                                                                        mtMmax_cut[imtMmax],
                                                                                        mtMmin_cut[imtMmin],
                                                                                        meff_cut[imeff],
                                                                                        meff_cut[imeff]+baseMeff,
                                                                                        metOmeff_cut[imetOmeff]
                                                                                        ]
                                                                                               ,sig,bkg])
                                                                        #print bin, sig, bkg, zObs                                                                             
                                                                        #bin +=1
    sigResults.sort(key=lambda sig: sig[0])
    sigResults.reverse()
    return sigResults;

#############################################################################

# Method to compute 95% CL limits (author: G. Carrillo-Montoya)

def limit(signal_n, background_n, bkg_uncert):
    signal     = TH1F( "signal"+str(random.randrange(1e6)) ,"signal"    ,1,0,1)
    background = TH1F("background"+str(random.randrange(1e6)),"background",1,0,1)
    data       = TH1F("data"+str(random.randrange(1e6))    ,"data"      ,1,0,1)
    signal.Sumw2()  
    signal.SetBinContent(1,signal_n)
    signal.SetBinError(1,sqrt(signal_n))
    background.Sumw2()  
    background.SetBinContent(1,background_n)
    background.SetBinError(1,sqrt(background_n))
    errorsignal=TVectorD(1)
    errorbackground=TVectorD(1)
    errorsignal[0]    = 0.20 # hardcoded to 2015 approximate value
    errorbackground[0]=bkg_uncert
    names = TObjArray()  
    name1=TObjString("bkg uncertainty")   
    name2=TObjString("sig uncertainty")
    names.AddLast(name1)   
    names.AddLast(name2)
    datasource  = TLimitDataSource()
    datasource = TLimitDataSource(signal,background,data,errorsignal,errorbackground,names)
    confidence = TConfidenceLevel(TLimit.ComputeLimit(datasource,5000))  
    return 1-confidence.GetExpectedCLs_b()

#############################################################################

def drawHist(hist,confL,name,colz= True, contour = False , dec = False):

    can = TCanvas()
    can.cd()

    if(dec):
        gStyle.SetPaintTextFormat("3.2f")
    else:
        gStyle.SetPaintTextFormat("3.0f")

    if "metOmeff" in hist.GetName():
        gStyle.SetPaintTextFormat("3.2f")

    gStyle.SetStatX(50)
    #colors = array("i",[3,30, 40, 20, 46, 5, 6, 7, 8, 9,11,4]) #colors >= #levels - 1
    #gStyle.SetPalette(len(colors), colors)
    #levels = array("d",[.01, .20, 0.50, 1, 2, 3, 4, 7,9,10])
    #hist.SetContour(len(levels), levels)
    hist.SetMarkerSize(1.5)
    if colz:
        hist.Draw("colz,same")

    hist.Draw("text30, same")

    if SigSample == "GG_ttn1":
        xlabel=850
        ylabel=1400
    elif SigSample == "GG_2stepWZ":
        xlabel=600
        ylabel=1400
    elif SigSample == "GG_SLN1":
        xlabel=400
        ylabel=1000
    elif SigSample == "BB_onestepC1": 
        xlabel=350
        ylabel=300

    xlabel=650
    ylabel=1500

    if contour:
        g = TGraph2D()
        TH2toTGraph2D(hist,g)
        Ghisto=g.GetHistogram()
        level=array('d',[1.64,3])
        Ghisto.SetLineWidth(4)
        Ghisto.SetContour(2,level)
        Ghisto.Draw("cont1,list ,same")
        confL.SetLineColor(1)
        confL.Draw("colz,same")
        tex1=TLatex()
        if SigSample == "BB_onestepC1":
            tex1.DrawLatex(xlabel, ylabel+50, "#color[3]{1.64#sigma}")
        else:
            tex1.DrawLatex(xlabel, ylabel+100, "#color[3]{1.64#sigma}")
        tex1.DrawLatex(xlabel, ylabel, "#color[2]{3#sigma}")
        
        #sprintf(&title[0],"MET>%d GeV",met);
        #myText(.2,.84,kBlue,title);

        #sprintf(&title[0],"MEFF>%d GeV",meff);
        #myText(.2,.79,kBlue,title);

        #sprintf(&title[0],"Bkg: %3.1f evts",_bkg);
        #myText(.2,.74,kBlue,title);

        #        myLineText(.26, .8 , 0.05, kGreen,"1.64#sigma")
        #        myLineText(.26, .75, 0.05, kRed,  "3#sigma")

    hist.GetYaxis().SetTitleOffset(1.3)
    hist.GetXaxis().SetTitle("Gluino Mass (GeV)")  
    hist.GetYaxis().SetTitle("Neutralino Mass (GeV)") 
    gStyle.SetTitleX(100.0)  # move title off plot
    gStyle.SetTitleW(0.0)    # title width =0
    
    tex2=TLatex()
    if SigSample == "BB_onestepC1":
        tex2.DrawLatex(xlabel, ylabel+100, name+" "+str(luminosity)+" fb^{-1}: "+hist.GetName())
    else:
        tex2.DrawLatex(xlabel, ylabel+200, name+" "+str(luminosity)+" fb^{-1}: "+hist.GetName())

    # Draw m_gl - m_N1 = 2 (m_W+m_b)
    line = TLine(600, 429.6 ,1800, 1629.6)
    line.SetLineColor(16)
    line.SetLineStyle(7)
    line.Draw("same")
    th1 = TLatex(1450,1340,"m_{#tilde{g}} - m_{#tilde{#chi}_{1}^{0}} = 2 #left(m_{W}+m_{b}#right)")
    th1.SetTextAngle(30) 
    th1.SetTextColor(16)
    th1.SetTextSize(0.03)
    th1.Draw("same")

    # Draw m_gl - m_N1 = 2 m_t
    line2 = TLine(600, 255 ,2050, 1680)
    line2.SetLineColor(16)
    line2.SetLineStyle(7)
    line2.Draw("same")
    th2 = TLatex(1550,1240,"m_{#tilde{g}} - m_{#tilde{#chi}_{1}^{0}} = 2 m_{t}")
    th2.SetTextAngle(30) 
    th2.SetTextColor(16)
    th2.SetTextSize(0.03)
#    th2.Draw("same")

    if "Dm" in hist.GetName():
        line3 = TLine(600, 25 ,2100, 25)
        line3.SetLineColor(16)
        line3.SetLineStyle(7)
        line3.Draw("same")
        th3 = TLatex(1600,40,"#Delta m = m_{#tilde{#chi}_{1}^{0}} - #left(m_{#tilde{g}} -2 m_{t} #right)")
#        th3.SetTextAngle(32) 
        th3.SetTextColor(16)
        th3.SetTextSize(0.03)
        th3.Draw("same")
        hist.GetYaxis().SetTitle("#Delta m_{#tilde{#chi}_{1}^{0}} (above diagonal) (GeV)") 
    can.Update()
    directory="/afs/cern.ch/user/o/othrif/workarea/results/v48/Plots/"+Dirbase+"/"+OutName#+"/Lumi"+str(luminosity)+"/"+OutName
    if not os.path.exists(directory):
        os.makedirs(directory)
    can.SaveAs(directory+"/"+name+"_"+hist.GetName()+".png")

#############################################################################

def TH2toTGraph2D(histo,g):
    firstxbin = 1
    lastxbin = histo.GetXaxis().GetNbins()
    firstybin = 1
    lastybin = histo.GetYaxis().GetNbins()
    npoints = 0

    for j in range(firstybin,lastybin):
        for i in range(firstxbin,lastxbin):
            if(histo.GetBinContent(i,j)>0):
                g.SetPoint(npoints,
                           histo.GetXaxis().GetBinCenter(i),
                           histo.GetYaxis().GetBinCenter(j),
                           histo.GetBinContent(i,j))     
                npoints+=1
    return npoints

#############################################################################
count=1
directory="/afs/cern.ch/user/o/othrif/workarea/results/v48/Logs/"+Dirbase+"/"+SigSample
flog = []
#fname = ["SR3bXimo", "SR3bYang", "SRlow", "SRmed", "SRhigh"]
numSR = len(SRcuts)
for i in range(numSR):
    logname = directory+"/"+SigSample+"_SR"+str(i)+"-"+OutName+".log"
    print i, logname
    flog.append(open(logname,'w'))

for ifile in listdir(path):
    bpath = os.path.join(path, ifile)
    if os.path.isdir(bpath):
        # skip directories
        continue
    pointsplit = ifile.split(".")[0].split("_")
    mass1=pointsplit[1]
    mass2=pointsplit[3]
    gridpoint = [path+ifile, float(mass1),float(mass2)]
#    print gridpoint

    for i in range(numSR):
        sigResults=calcSig(gridpoint[0],i)
        sigResultOut = "{p1:f} {p2:f} {sig:f}".format(p1=gridpoint[1],p2=gridpoint[2],sig=sigResults[0][0])
#        print fname[i], "===============> ", sigResultOut
        flog[i].write(str(sigResultOut))
        flog[i].write("\n")

#    sigResults=calcSig(gridpoint[0],0) #SR3bICHEP
#    sigResults=calcSig(gridpoint[0],1) #SR3bYang
    if count ==1:
        print "\n\nSRlow"
        sigResults=calcSig(gridpoint[0],1,False) #SRlow
        print "\n\nSRhigh"
        sigResults=calcSig(gridpoint[0],2,False) #SRhigh
    
    if not sigResults:
        print "m_gl=",gridpoint[1], "m_neut=",gridpoint[2], "list is empty"
        continue

    if not os.path.exists(directory):
        os.makedirs(directory)

    # output mass point and cuts
    if(singleCut == 0):
        logname = directory+"/"+SigSample+"_"+mass1+"_"+mass2+".log"
        f = open(logname,'w')
        for i in range(0,len(sigResults)): 
            output_result = "zObs={sigResultsi0:8.2f}, sig={sigResultsi2:8.2f}, bkg={sigResultsi3:8.2f}, lepptmax1={sigResultsi10:8.2f}, lepptmin1={sigResultsi11:8.2f}, lepptmax2={sigResultsi12:8.2f}, lepptmin2={sigResultsi13:8.2f}, nbjets={sigResultsi17:8.2f}, njets={sigResultsi110:8.2f}, metmax={sigResultsi111:8.2f}, metmin={sigResultsi112:8.2f}, mtMmin={sigResultsi114:8.2f}, meff_cut={sigResultsi115:8.2f}, meff={sigResultsi116:8.2f}, metOmeff={sigResultsi117:8.2f}".format(sigResultsi0=sigResults[i][0], sigResultsi2=sigResults[i][2], sigResultsi3=sigResults[i][1], sigResultsi10=sigResults[i][1][0], sigResultsi11=sigResults[i][1][1], sigResultsi12=sigResults[i][1][2], sigResultsi13=sigResults[i][1][3], sigResultsi17=sigResults[i][1][7], sigResultsi110=sigResults[i][1][10], sigResultsi111=sigResults[i][1][11], sigResultsi112=sigResults[i][1][12], sigResultsi114=sigResults[i][1][14], sigResultsi115=sigResults[i][1][15], sigResultsi116=sigResults[i][1][16], sigResultsi117=sigResults[i][1][17])
            new_output_result =output_result.replace("1000000000.00", "     Inf")
            f.write(str(new_output_result))
            f.write("\n")
        f.close()

    print "m_gl=",gridpoint[1], "m_neut=",gridpoint[2], "sig=",sigResults[0][2], "bkg=",sigResults[0][3], "sigma=",sigResults[0][0]
    count+=1
    if testMe and count>1:
        print "Done since I am testing..."
        sys.exit()
    
    hFinalSig.Fill(gridpoint[1],gridpoint[2],sigResults[0][0])
    if (gridpoint[2]-(gridpoint[1]-2*172.5-25))>0:
        hFinalSig_Dm.Fill(gridpoint[1],gridpoint[2]-(gridpoint[1]-2*172.5-25),sigResults[0][0])
    hFinalSig.Fill(700,1,0.22) # artificial to fix the countour

    #print sigResults[0]#[2], sigResults[0][3], limit(sigResults[0][2], sigResults[0][3], 0.3)

    hConfLevel.Fill(gridpoint[1],gridpoint[2],limit(sigResults[0][2], sigResults[0][3], 0.3) )

    if(singleCut == 0):
        for i in range(len(bestCutHists)):
            if i in ignore_hist:
                continue
            bestCutHists[i][0].Fill(gridpoint[1],gridpoint[2],sigResults[0][1][i])
            if (gridpoint[2]-(gridpoint[1]-2*172.5-25))>0:
                bestCutHists_Dm[i][0].Fill(gridpoint[1],gridpoint[2]-(gridpoint[1]-2*172.5-25),sigResults[0][1][i])

drawHist(hFinalSig,hConfLevel,pointsplit[0],True, True, True)
if(singleCut == 0):
    i=-1
    for hist in bestCutHists:
        i+=1
        if i in ignore_hist:
            continue
        drawHist(hist[0],hConfLevel,pointsplit[0],True)

drawHist(hFinalSig_Dm,hConfLevel,pointsplit[0],True, True, True)
if(singleCut == 0):
    i=-1
    for hist in bestCutHists_Dm:
        i+=1
        if i in ignore_hist:
            continue
        drawHist(hist[0],hConfLevel,pointsplit[0],True)
for i in range(numSR):
    flog[i].close()
