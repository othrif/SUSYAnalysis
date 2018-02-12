from ROOT import gSystem,gStyle,gROOT, Double
from ROOT import TFile, TH1F, TH2F, TCanvas, TLatex,TArrayF,MakeNullPointer,TParameter, TGraph2D, TGraph
from ROOT import RooStats, TLimit, TVectorD, TObjArray, TObjString, TLimitDataSource, TConfidenceLevel, Form
from os import listdir
from array import array
from math import sqrt
import os
import sys 

gROOT.SetBatch(True)

# chMisId, el HF, el LF, mu HF, mu LF
corr_pythia = [1.33, 1.82, 2.81, 1.54, 1.]
err_corr_pythia = [0.41,0.40,0.62,0.06,0.79]

corr_sherpa = [1.02,2.72,1.81,1.16,1.84]
err_corr_sherpa = [0.09,0.57,0.75,0.18,1.16]

nocorr = [1.,1.,1.,1.,1.]
err_nocorr = [0.,0.,0.,0.,0.]

OUTPUT_FOLDER = sys.argv[1]
OUTPUT_PATH = "/afs/cern.ch/work/o/othrif/workarea/results/v52/"+OUTPUT_FOLDER

sr = ['SR0b2', 'SR0b1', 'SR3b2', 'SR3b1', 'SR1b2', 'SR1b1', 'SRhigh', 'SRlow', 'SR3L0b2', 'SR3L0b1', 'SR1b_3LSS', 'SR3L1b2', 'SR3L1b1', 'SRRPV0b', 'SR1b_GG', 'SR1b_DD_high', 'SR1b_DD_low', 'SRRPV3b', 'SR3b_DD']
#'SR3L0b1', 'SR3L0b2', 'SR3L1b1', 'SR3L1b2', 'SR0b1', 'SR0b2', 'SR1b1', 'SR1b2', 'SR3b1', 'SR3b2', 'SRlow', 'SRhigh', 'SR1b_3LSS', 'SR1b_DD_low', 'SR1b_DD_high', 'SR3b_DD', 'SR1b_GG', 'SRRPV0b', 'SRRPV3b']
cr = ['VRttW','VRttZ','VRWW','VRWZ4j','VRWZ5j']
shower=0
detail=1
note=1
lumi=1#34500
for i in sr:
#for i in cr:
    print "\n", i
    yields = []
    yXimo = []
    yPeter = []
    total = 0
    totalerr = 0
    count = 0
    undesired = ["merged", "data", "old", "ttn1", "TTBar", "Wjets", "otherNP", "Zjets", "mg", "TT_2step"]
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
            total += histo.Integral()
            totalerr += stattmp*stattmp
#    print "Total Background yield: %.2f" % (total) 
    totalerr = sqrt(totalerr)
    dict['total_prompt'] = total
    dict['diboson'] = dict['WW']+dict['ZZ']+dict['WZ']
    dict['rare'] = dict['tth']+dict['ttWW']+dict['tZ']+dict['tWZ']+dict['Vh']+dict['VVV']+dict['3t']+dict['4t']
    dict['err_total_prompt'] = totalerr
    dict['err_diboson'] = sqrt(pow(dict['err_WW'],2)+pow(dict['err_ZZ'],2)+pow(dict['err_WZ'],2))
    dict['err_rare'] = sqrt(pow(dict['err_tth'],2)+pow(dict['err_ttWW'],2)+pow(dict['err_tZ'],2)+pow(dict['err_tWZ'],2)+pow(dict['err_Vh'],2)+pow(dict['err_VVV'],2)+pow(dict['err_3t'],2)+pow(dict['err_4t'],2))

    if note == 1:
        print "==============================="
        print "ttZ = %.2f +- %.2f"% (dict['ttZ'], dict['err_ttZ'])
        print "ttW = %.2f +- %.2f"% (dict['ttW'], dict['err_ttW'])
        print "Diboson = %.2f +- %.2f"% (dict['diboson'], dict['err_diboson'])
        print "Rare = %.2f +- %.2f"% (dict['rare'], dict['err_rare'])
        print "==============================="
        print "Total Prompt = %.2f +- %.2f" % (dict['total_prompt'], dict['err_total_prompt'])
        print "==============================="

    # fake determination

    # Pythia

    total_pure_mc = 0
    total_pure_mc_err_stat = 0

    total_charge_misid = 0
    total_charge_misid_err_stat = 0
    total_charge_misid_err_sys = 0

    total_fake = 0
    total_fake_err_stat = 0
    total_fake_err_sys = 0

    for ifile in listdir(OUTPUT_PATH):
        if ifile.endswith(".root") and any(s in ifile for s in fakes_pythia) and 'merged' not in ifile:
#            print "Pythia ", ifile
            pointsplit = ifile.split(".")[0]
            f = TFile(OUTPUT_PATH+"/"+ifile)
            histo=f.Get("NJETS_"+pointsplit+"_mc_comb_"+i+"_SS3L")
            histo.Scale(lumi)
            stattmp = Double(0)
            maxbin = histo.GetNbinsX()+1
            pure_mc = histo.IntegralAndError(0,maxbin,stattmp)
            pure_mc_err_stat = stattmp 

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

            corr = nocorr #corr_pythia

            charge_misid = corr[0]*charge_misid
            charge_misid_err_stat = corr[0]*charge_misid_stat
            charge_misid_err_sys = 0
            fake  = corr[1]*fake_HF_e + corr[2]*fake_LF_e + corr[3]*fake_HF_m+ corr[4]*fake_LF_m
            fake_err_stat = sqrt(pow(corr[1]*fake_HF_e_stat,2) + pow(corr[2]*fake_LF_e_stat,2) + pow(corr[3]*fake_HF_m_stat,2) + pow(corr[4]*fake_LF_m_stat,2))
            # Important!!! must add the syst error due to the uncertainty in the correction factor: sys_up = corr_up - nominal, sys_dn = nominal - corr_dn, sys = (sys_up + sys_dn)/2
            fake_err_sys = 0

            total_pure_mc += pure_mc
            total_pure_mc_err_stat += pow(pure_mc_err_stat,2)

            total_charge_misid += charge_misid
            total_charge_misid_err_stat += pow(charge_misid_err_stat,2)
            total_charge_misid_err_sys += pow(charge_misid_err_sys,2)

            total_fake += fake
            total_fake_err_stat += pow(fake_err_stat,2)
            total_fake_err_sys += pow(fake_err_sys,2)

            if detail == 1:
                print "%s Pure MC pythia = %.2f +- %.2f // fake pythia = %.2f +- %.2f +- %.2f // chmisid pythia = %.2f +- %.2f +- %.2f" % (pointsplit, pure_mc, pure_mc_err_stat, fake, fake_err_stat, fake_err_sys, charge_misid, charge_misid_err_stat, charge_misid_err_sys)
    
    total_pure_mc_err_stat = sqrt(total_pure_mc_err_stat)
    total_charge_misid_err_stat = sqrt(total_charge_misid_err_stat)
    total_charge_misid_err_sys = sqrt(total_charge_misid_err_sys)
    total_fake_err_stat = sqrt(total_fake_err_stat)
    total_fake_err_sys = sqrt(total_fake_err_sys)

    dict['pythia_total_fake'] = total_fake 
    dict['pythia_total_fake_err_stat'] = total_fake_err_stat 
    dict['pythia_total_fake_err_sys'] = total_fake_err_sys 
    dict['pythia_total_charge_misid'] = total_charge_misid 
    dict['pythia_total_charge_misid_err_stat'] = total_charge_misid_err_stat 
    dict['pythia_total_charge_misid_err_sys'] = total_charge_misid_err_sys 

    if shower == 1:
        print "Pythia Pure MC = %.2f +- %.2f // Pythia Fake = %.2f +- %.2f +- %.2f // Pythia Chmisid = %.2f +- %.2f +- %.2f" % (total_pure_mc, total_pure_mc_err_stat, total_fake, total_fake_err_stat, total_fake_err_sys, total_charge_misid, total_charge_misid_err_stat, total_charge_misid_err_sys)

    # Sherpa

    total_pure_mc = 0
    total_pure_mc_err_stat = 0

    total_charge_misid = 0
    total_charge_misid_err_stat = 0
    total_charge_misid_err_sys = 0

    total_fake = 0
    total_fake_err_stat = 0
    total_fake_err_sys = 0

    for ifile in listdir(OUTPUT_PATH):
        if ifile.endswith(".root") and any(s in ifile for s in fakes_sherpa) and 'merged' not in ifile:
#            print "Sherpa ", ifile
            pointsplit = ifile.split(".")[0]
            f = TFile(OUTPUT_PATH+"/"+ifile)
            histo=f.Get("NJETS_"+pointsplit+"_mc_comb_"+i+"_SS3L")
            histo.Scale(lumi)
            stattmp = Double(0)
            maxbin = histo.GetNbinsX()+1
            pure_mc = histo.IntegralAndError(0,maxbin,stattmp)
            pure_mc_err_stat = stattmp 

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

            corr = nocorr #corr_sherpa

            charge_misid = corr[0]*charge_misid
            charge_misid_err_stat = corr[0]*charge_misid_stat
            charge_misid_err_sys = 0
            fake  = corr[1]*fake_HF_e + corr[2]*fake_LF_e + corr[3]*fake_HF_m+ corr[4]*fake_LF_m
            fake_err_stat = sqrt(pow(corr[1]*fake_HF_e_stat,2) + pow(corr[2]*fake_LF_e_stat,2) + pow(corr[3]*fake_HF_m_stat,2) + pow(corr[4]*fake_LF_m_stat,2))
            # Important!!! must add the syst error due to the uncertainty in the correction factor: sys_up = corr_up - nominal, sys_dn = nominal - corr_dn, sys = (sys_up + sys_dn)/2
            fake_err_sys = 0

            total_pure_mc += pure_mc
            total_pure_mc_err_stat += pow(pure_mc_err_stat,2)

            total_charge_misid += charge_misid
            total_charge_misid_err_stat += pow(charge_misid_err_stat,2)
            total_charge_misid_err_sys += pow(charge_misid_err_sys,2)

            total_fake += fake
            total_fake_err_stat += pow(fake_err_stat,2)
            total_fake_err_sys += pow(fake_err_sys,2)

            if detail == 1:
                print "Pure MC sherpa = %.2f +- %.2f // fake sherpa = %.2f +- %.2f +- %.2f // chmisid sherpa = %.2f +- %.2f +- %.2f" % (pure_mc, pure_mc_err_stat, fake, fake_err_stat, fake_err_sys, charge_misid, charge_misid_err_stat, charge_misid_err_sys)
    
    total_pure_mc_err_stat = sqrt(total_pure_mc_err_stat)
    total_charge_misid_err_stat = sqrt(total_charge_misid_err_stat)
    total_charge_misid_err_sys = sqrt(total_charge_misid_err_sys)
    total_fake_err_stat = sqrt(total_fake_err_stat)
    total_fake_err_sys = sqrt(total_fake_err_sys)

    dict['sherpa_total_fake'] = total_fake 
    dict['sherpa_total_fake_err_stat'] = total_fake_err_stat 
    dict['sherpa_total_fake_err_sys'] = total_fake_err_sys 
    dict['sherpa_total_charge_misid'] = total_charge_misid 
    dict['sherpa_total_charge_misid_err_stat'] = total_charge_misid_err_stat 
    dict['sherpa_total_charge_misid_err_sys'] = total_charge_misid_err_sys 

    if shower == 1:
        print "Sherpa Pure MC = %.2f +- %.2f // Sherpa Fake = %.2f +- %.2f +- %.2f // Sherpa Chmisid = %.2f +- %.2f +- %.2f" % (total_pure_mc, total_pure_mc_err_stat, total_fake, total_fake_err_stat, total_fake_err_sys, total_charge_misid, total_charge_misid_err_stat, total_charge_misid_err_sys)


    # Summary of fakes and charge flips
    dict['fake'] = max(dict['pythia_total_fake'],dict['sherpa_total_fake']) # dict['pythia_total_fake']
#    dict['fake_err'] = sqrt(pow(dict['pythia_total_fake_err_stat'],2)+pow(dict['pythia_total_fake_err_sys'],2)+pow(dict['pythia_total_fake']-dict['sherpa_total_fake'],2))
    dict['fake_err'] = sqrt(pow(dict['pythia_total_fake_err_sys'],2)+pow(dict['pythia_total_fake']-dict['sherpa_total_fake'],2))
    dict['fake_stat'] = dict['pythia_total_fake_err_stat']
    dict['charge_misid'] = max(dict['pythia_total_charge_misid'],dict['pythia_total_charge_misid']) # dict['pythia_total_charge_misid'] #
#    dict['charge_misid_err'] = sqrt(pow(dict['pythia_total_charge_misid_err_stat'],2)+pow(dict['pythia_total_charge_misid_err_sys'],2)+pow(dict['pythia_total_charge_misid']-dict['sherpa_total_charge_misid'],2))
    dict['charge_misid_err'] = sqrt(pow(dict['pythia_total_charge_misid_err_sys'],2)+pow(dict['pythia_total_charge_misid']-dict['sherpa_total_charge_misid'],2))
    dict['charge_misid_stat'] = dict['pythia_total_charge_misid_err_stat']


    dict['totalSM'] = dict['total_prompt']+dict['fake']+dict['charge_misid']
    dict['totalSM_err'] = sqrt(pow(dict['err_total_prompt'],2)+pow(dict['fake_err'],2)+pow(dict['charge_misid_err'],2))

    if note == 1:
        print "Fake = %.2f +- %.2f +- %.2f"% (dict['fake'], dict['fake_stat'], dict['fake_err'])
        print "Charge flip = %.2f +- %.2f +- %.2f"% (dict['charge_misid'], dict['charge_misid_stat'], dict['charge_misid_err'])
        print "==============================="
        print "Total SM Background = %.2f +- %.2f" % (dict['totalSM'],dict['totalSM_err'])
        print "==============================="

