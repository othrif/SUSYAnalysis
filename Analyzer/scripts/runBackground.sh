export ATLAS_LOCAL_ROOT_BASE=/cvmfs/atlas.cern.ch/repo/ATLASLocalRootBase
alias setupATLAS='source ${ATLAS_LOCAL_ROOT_BASE}/user/atlasLocalSetup.sh'
export RUCIO_ACCOUNT=othrif
setupATLAS

#!/bin/bash

# Analyze samples according to desired grouping

loc=`pwd`

if ! type -p "analyze" > /dev/null; then
	printf "Setting up the environment...\n"
	source rcSetup.sh
fi

printf "Compiling...\n"
rc compile


# output folder name
if [ $# -eq 0 ]
  then
    printf "\nERROR: No output folder supplied\n\n"
	return # change to exit when not sourcing
fi
export OUTPUT_FOLDER=$1
export BASE_PATH=/afs/cern.ch/work/o/othrif/workarea/results/v52/
mkdir -p $BASE_PATH
export OUTPUT_PATH=/afs/cern.ch/work/o/othrif/workarea/results/v52/$OUTPUT_FOLDER
mkdir -p $OUTPUT_PATH

# path to input files
export INPUT_PATH=/UserDisk2/othrif/data/MiniNtuple/v52_mini
export INPUT_PATH_v48=/UserDisk2/othrif/data/MiniNtuple/v48_0
export INPUT_PATH_test=/UserDisk2/othrif/data/MiniNtuple/test
######################
# DATA
######################

## 2015+2016 ##
DATA="$INPUT_PATH/user.othrif*physics_Main*.root" 
DATA="$DATA $INPUT_PATH/user.othrif*debugrec*.root" 

DATAperiodA="$INPUT_PATH/user.othrif*periodA*.root"
DATAperiodB="$INPUT_PATH/user.othrif*periodB*.root"
DATAperiodC="$INPUT_PATH/user.othrif*periodC*.root"
DATAperiodD="$INPUT_PATH/user.othrif*periodD*.root"
DATAperiodE="$INPUT_PATH/user.othrif*periodE*.root"
DATAperiodF="$INPUT_PATH/user.othrif*periodF*.root"
DATAperiodG="$INPUT_PATH/user.othrif*periodG*.root"
DATAperiodH="$INPUT_PATH/user.othrif*periodH*.root"
DATAperiodI="$INPUT_PATH/user.othrif*periodI*.root"
DATAperiodJ="$INPUT_PATH/user.othrif*periodJ*.root"
DATAperiodK="$INPUT_PATH/user.othrif*periodK*.root"
DATAperiodL="$INPUT_PATH/user.othrif*periodL*.root"
DATAdebug="$INPUT_PATH/user.othrif*debugrec*.root" 

######################
# MC
######################

# All the samples below do produce SS/3L #

#ttW  
ttW="$INPUT_PATH/user.othrif*410155.aMcAtNloPythia8EvtGen_MEN30NLO_A14N23LO_ttW*.root"

#ttZ
ttZ="$INPUT_PATH/user.othrif*410218.aMcAtNloPythia8EvtGen_MEN30NLO_A14N23LO_ttee*.root"
ttZ="$ttZ $INPUT_PATH/user.othrif*410219.aMcAtNloPythia8EvtGen_MEN30NLO_A14N23LO_ttmumu*.root"
ttZ="$ttZ $INPUT_PATH/user.othrif*410220.aMcAtNloPythia8EvtGen_MEN30NLO_A14N23LO_tttautau*.root"

#WW
WW="$INPUT_PATH/user.othrif*361069.Sherpa_CT10_llvvjj_ss_EW4*.root"
#WW="$WW $INPUT_PATH/user.othrif*361070.Sherpa_CT10_llvvjj_ss_EW6*.root"
WW="$WW $INPUT_PATH/user.othrif.361070.Sherpa_CT10_llvvjj_ss_EW6.s2608_r7725_p2879_output.root"

#ZZ
ZZ="$INPUT_PATH/user.othrif*363490.Sherpa_221_NNPDF30NNLO_llll.s2726_r7676_output.root"
ZZ="$ZZ $INPUT_PATH/user.othrif*361072.Sherpa_CT10_lllljj_EW6.s2608_r7772_p2879_output.root"
ZZ="$ZZ $INPUT_PATH/user.othrif*361073.Sherpa_CT10_ggllll.s2608_r7772_p2879_output.root"

#WZ
WZ="$INPUT_PATH/user.othrif*363491.Sherpa_221_NNPDF30NNLO_lllv.s2726_r7676_output.root"
WZ="$WZ $INPUT_PATH/user.othrif*361071.Sherpa_CT10_lllvjj_EW6.s2726_r7676_output.root"

#Rare
ttH="$INPUT_PATH/user.othrif*343365.aMcAtNloPythia8EvtGen_A14_NNPDF23_NNPDF30ME_ttH125_di*.root"
ttH="$ttH $INPUT_PATH/user.othrif*343366.aMcAtNloPythia8EvtGen_A14_NNPDF23_NNPDF30ME_ttH125_se*.root"
ttH="$ttH $INPUT_PATH/user.othrif*343367.aMcAtNloPythia8EvtGen_A14_NNPDF23_NNPDF30ME_ttH125_al.root" 
Wh="$INPUT_PATH/user.othrif*342284.Pythia8EvtGen_A14NNPDF23LO_WH125_inc*.root"
Zh="$INPUT_PATH/user.othrif*342285.Pythia8EvtGen_A14NNPDF23LO_ZH125_inc*.root"
tttt="$INPUT_PATH/user.othrif*410080.MadGraphPythia8EvtGen_A14NNPDF23_4topSM*.root"
ttt="$INPUT_PATH/user.othrif*304014.MadGraphPythia8EvtGen_A14NNPDF23_3top_SM*.root"
tZ="$INPUT_PATH/user.othrif*410050.MadGraphPythiaEvtGen_P2012_tZ_4fl_tchan_noAllHad*.root"
ttWW="$INPUT_PATH/user.othrif*410081.MadGraphPythia8EvtGen_A14NNPDF23_ttbarWW*.root"
VVV="$INPUT_PATH/user.othrif*361620.Sherpa_CT10_WWW_3l3v*.root"
VVV="$VVV $INPUT_PATH/user.othrif*361621.Sherpa_CT10_WWZ_4l2v*.root"
VVV="$VVV $INPUT_PATH/user.othrif*361622.Sherpa_CT10_WWZ_2l4v*.root"
VVV="$VVV $INPUT_PATH/user.othrif*361623.Sherpa_CT10_WZZ_5l1v*.root"
VVV="$VVV $INPUT_PATH/user.othrif*361624.Sherpa_CT10_WZZ_3l3v*.root"
VVV="$VVV $INPUT_PATH/user.othrif*361625.Sherpa_CT10_ZZZ_6l0v*.root"
VVV="$VVV $INPUT_PATH/user.othrif*361626.Sherpa_CT10_ZZZ_4l2v*.root"
VVV="$VVV $INPUT_PATH/user.othrif*361627.Sherpa_CT10_ZZZ_2l4v*.root"
tWZ="$INPUT_PATH/user.othrif*410215.aMcAtNloPythia8EvtGen_A14_NNPDF23LO_260000_tWZDR*.root"
DPS="$INPUT_PATH/user.othrif*407309.Pythia8EvtGen_A14_NNPDF23LO_DPS_W_W_2l.s2726_r7676_output.root" 
ttWZ="$INPUT_PATH/user.othrif*407321.MadGraphPythia8EvtGen_A14NNPDF23LO_ttbarWll.s2726_r7676_output.root" 

# All the samples below do NOT produce SS/3L #

#singletop
singletop="$INPUT_PATH/user.othrif*410011.PowhegPythiaEvtGen_P2012_singletop_tchan_lept_top*.root"
singletop="$singletop $INPUT_PATH/user.othrif*410012.PowhegPythiaEvtGen_P2012_singletop_tchan_lept_antitop*.root"

#WWos
WWos="$INPUT_PATH/user.othrif*363492.Sherpa_221_NNPDF30NNLO_llvv*.root"

#Wt
Wt="$INPUT_PATH/user.othrif*410015.PowhegPythiaEvtGen_P2012_Wt_dilepton_top*.root"
Wt="$Wt $INPUT_PATH/user.othrif*410016.PowhegPythiaEvtGen_P2012_Wt_dilepton_antitop*.root"

###########################################################################################################################
# TTBar
###########################################################################################################################

#powhegpythia8TTBar

#powhegpythia6TTBar
#powhegpythia6TTBar="$INPUT_PATH/user.othrif*410000.PowhegPythiaEvtGen_P2012_ttbar_hdamp172p5_nonallhad*.root"

#powhegpythia6TTBarHT
powhegpythia6TTBarHT="$INPUT_PATH/user.othrif*410000.PowhegPythiaEvtGen_P2012_ttbar_hdamp172p5_nonallhad.s2608_r7725_p2927_output.root"
powhegpythia6TTBarHT="$powhegpythia6TTBarHT $INPUT_PATH/user.othrif*407009.PowhegPythiaEvtGen_P2012CT10_ttbarHT6c_1k_hdamp172p5*.root" 
powhegpythia6TTBarHT="$powhegpythia6TTBarHT $INPUT_PATH/user.othrif*407010.PowhegPythiaEvtGen_P2012CT10_ttbarHT1k_1k5_hdamp172p5*.root"
powhegpythia6TTBarHT="$powhegpythia6TTBarHT $INPUT_PATH/user.othrif*407011.PowhegPythiaEvtGen_P2012CT10_ttbarHT1k5_hdamp172p5_no*.root"

#powhegpythia8TTBar
powhegpythia8TTBar="$INPUT_PATH/410501.PowhegPythia8EvtGen_A14_ttbar_hdamp258p75_nonallhad.s2726_r7676.root" 
#410500 1*mtop, >=1L 10M
#410501 1.5*mtop, >=1L 30M
#410502 1.5*mtop, 0L 10M
#410503 1.5*mtop, >=2L 10M
#410504 1.5*mtop, >=1L w/ b 10M (AF2)
#410505 1.5*mtop, >=2L w/ b 10M


#SherpaTTBar
sherpaTTBar="$INPUT_PATH/user.othrif*410250.Sherpa_221_NNPDF30NNLO_ttbar_SingleLeptonP_MEPS_NLO.s2726_r7676_output.root"
sherpaTTBar="$sherpaTTBar $INPUT_PATH/user.othrif*410251.Sherpa_221_NNPDF30NNLO_ttbar_SingleLeptonM_MEPS_NLO.s2726_r7676_output.root"
sherpaTTBar="$sherpaTTBar $INPUT_PATH/user.othrif*410252.Sherpa_221_NNPDF30NNLO_ttbar_dilepton_MEPS_NLO.s2726_r7676_output.root"

#madgraphpythia8TTBar
madgraphpythia8TTBar="$INPUT_PATH/user.othrif*407200.MGPy8EG_A14N30NLO_ttbarNp012p_MET0to200_HT0to500.s2726_r7676_output.root"
madgraphpythia8TTBar="$madgraphpythia8TTBar $INPUT_PATH/user.othrif*407201.MGPy8EG_A14N30NLO_ttbarNp012p_MET0to200_HT500to700.s2726_r7676_output.root"
madgraphpythia8TTBar="$madgraphpythia8TTBar $INPUT_PATH/user.othrif*407202.MGPy8EG_A14N30NLO_ttbarNp012p_MET0to200_HT700to1000.s2726_r7676_output.root"
madgraphpythia8TTBar="$madgraphpythia8TTBar $INPUT_PATH/user.othrif*407203.MGPy8EG_A14N30NLO_ttbarNp012p_MET200p_HT0to1000.s2726_r7676_output.root"
madgraphpythia8TTBar="$madgraphpythia8TTBar $INPUT_PATH/user.othrif*407204.MGPy8EG_A14N30NLO_ttbarNp012p_HT1000p.s2726_r7676_output.root"

###########################################################################################################################
# W + Jets
###########################################################################################################################

#powhegpythiaWjets
powhegpythia8Wjets="$INPUT_PATH/user.othrif*361100.PowhegPythia8EvtGen_AZNLOCTEQ6L1_Wplusenu*.root"
powhegpythia8Wjets="$powhegpythia8Wjets $INPUT_PATH/user.othrif*361101.PowhegPythia8EvtGen_AZNLOCTEQ6L1_Wplusmunu*.root"
powhegpythia8Wjets="$powhegpythia8Wjets $INPUT_PATH/user.othrif*361102.PowhegPythia8EvtGen_AZNLOCTEQ6L1_Wplustaunu*.root"
#powhegpythia8Wjets="$powhegpythia8Wjets $INPUT_PATH/user.othrif*361103.PowhegPythia8EvtGen_AZNLOCTEQ6L1_Wminusenu*.root" #missing
powhegpythia8Wjets="$powhegpythia8Wjets $INPUT_PATH/user.othrif*361104.PowhegPythia8EvtGen_AZNLOCTEQ6L1_Wminusmunu*.root"
powhegpythia8Wjets="$powhegpythia8Wjets $INPUT_PATH/user.othrif*361105.PowhegPythia8EvtGen_AZNLOCTEQ6L1_Wminustaunu*.root"

#sherpaWjets
sherpaWjets="$INPUT_PATH/user.othrif*364156.Sherpa_221_NNPDF30NNLO_Wmunu_MAXHTPTV0_70_CVetoBVeto.s2726_r7676_output.root"
sherpaWjets="$sherpaWjets $INPUT_PATH/user.othrif*364157.Sherpa_221_NNPDF30NNLO_Wmunu_MAXHTPTV0_70_CFilterBVet.s2726_r7676_output.root"
sherpaWjets="$sherpaWjets $INPUT_PATH/user.othrif*364158.Sherpa_221_NNPDF30NNLO_Wmunu_MAXHTPTV0_70_BFilter.s2726_r7676_output.root"
sherpaWjets="$sherpaWjets $INPUT_PATH/user.othrif*364159.Sherpa_221_NNPDF30NNLO_Wmunu_MAXHTPTV70_140_CVetoBVet.s2726_r7676_output.root"
sherpaWjets="$sherpaWjets $INPUT_PATH/user.othrif*364160.Sherpa_221_NNPDF30NNLO_Wmunu_MAXHTPTV70_140_CFilterBV.s2726_r7676_output.root"
sherpaWjets="$sherpaWjets $INPUT_PATH/user.othrif*364161.Sherpa_221_NNPDF30NNLO_Wmunu_MAXHTPTV70_140_BFilter.s2726_r7676_output.root"
sherpaWjets="$sherpaWjets $INPUT_PATH/user.othrif*364162.Sherpa_221_NNPDF30NNLO_Wmunu_MAXHTPTV140_280_CVetoBVe.s2726_r7676_output.root"
sherpaWjets="$sherpaWjets $INPUT_PATH/user.othrif*364163.Sherpa_221_NNPDF30NNLO_Wmunu_MAXHTPTV140_280_CFilterB.s2726_r7676_output.root"
sherpaWjets="$sherpaWjets $INPUT_PATH/user.othrif*364164.Sherpa_221_NNPDF30NNLO_Wmunu_MAXHTPTV140_280_BFilter.s2726_r7676_output.root" 
sherpaWjets="$sherpaWjets $INPUT_PATH/user.othrif*364165.Sherpa_221_NNPDF30NNLO_Wmunu_MAXHTPTV280_500_CVetoBVe.s2726_r7676_output.root"
sherpaWjets="$sherpaWjets $INPUT_PATH/user.othrif*364166.Sherpa_221_NNPDF30NNLO_Wmunu_MAXHTPTV280_500_CFilterB.s2726_r7676_output.root" 
sherpaWjets="$sherpaWjets $INPUT_PATH/user.othrif*364167.Sherpa_221_NNPDF30NNLO_Wmunu_MAXHTPTV280_500_BFilter.s2726_r7676_output.root"
sherpaWjets="$sherpaWjets $INPUT_PATH/user.othrif*364168.Sherpa_221_NNPDF30NNLO_Wmunu_MAXHTPTV500_1000.s2726_r7676_output.root"
sherpaWjets="$sherpaWjets $INPUT_PATH/user.othrif*364169.Sherpa_221_NNPDF30NNLO_Wmunu_MAXHTPTV1000_E_CMS.s2726_r7676_output.root"
sherpaWjets="$sherpaWjets $INPUT_PATH/user.othrif*364170.Sherpa_221_NNPDF30NNLO_Wenu_MAXHTPTV0_70_CVetoBVeto.s2726_r7676_output.root"
sherpaWjets="$sherpaWjets $INPUT_PATH/user.othrif*364171.Sherpa_221_NNPDF30NNLO_Wenu_MAXHTPTV0_70_CFilterBVeto.s2726_r7676_output.root"
sherpaWjets="$sherpaWjets $INPUT_PATH/user.othrif*364172.Sherpa_221_NNPDF30NNLO_Wenu_MAXHTPTV0_70_BFilter.s2726_r7676_output.root"
sherpaWjets="$sherpaWjets $INPUT_PATH/user.othrif*364173.Sherpa_221_NNPDF30NNLO_Wenu_MAXHTPTV70_140_CVetoBVeto.s2726_r7676_output.root"
sherpaWjets="$sherpaWjets $INPUT_PATH/user.othrif*364174.Sherpa_221_NNPDF30NNLO_Wenu_MAXHTPTV70_140_CFilterBVe.s2726_r7676_output.root"
sherpaWjets="$sherpaWjets $INPUT_PATH/user.othrif*364175.Sherpa_221_NNPDF30NNLO_Wenu_MAXHTPTV70_140_BFilter.s2726_r7676_output.root"
sherpaWjets="$sherpaWjets $INPUT_PATH/user.othrif*364176.Sherpa_221_NNPDF30NNLO_Wenu_MAXHTPTV140_280_CVetoBVet.s2726_r7676_output.root"
sherpaWjets="$sherpaWjets $INPUT_PATH/user.othrif*364177.Sherpa_221_NNPDF30NNLO_Wenu_MAXHTPTV140_280_CFilterBV.s2726_r7676_output.root"
sherpaWjets="$sherpaWjets $INPUT_PATH/user.othrif*364178.Sherpa_221_NNPDF30NNLO_Wenu_MAXHTPTV140_280_BFilter.s2726_r7676_output.root"
sherpaWjets="$sherpaWjets $INPUT_PATH/user.othrif*364179.Sherpa_221_NNPDF30NNLO_Wenu_MAXHTPTV280_500_CVetoBVet.s2726_r7676_output.root"
sherpaWjets="$sherpaWjets $INPUT_PATH/user.othrif*364180.Sherpa_221_NNPDF30NNLO_Wenu_MAXHTPTV280_500_CFilterBV.s2726_r7676_output.root"
sherpaWjets="$sherpaWjets $INPUT_PATH/user.othrif*364181.Sherpa_221_NNPDF30NNLO_Wenu_MAXHTPTV280_500_BFilter.s2726_r7676_output.root"
sherpaWjets="$sherpaWjets $INPUT_PATH/user.othrif*364182.Sherpa_221_NNPDF30NNLO_Wenu_MAXHTPTV500_1000.s2726_r7676_output.root"
sherpaWjets="$sherpaWjets $INPUT_PATH/user.othrif*364183.Sherpa_221_NNPDF30NNLO_Wenu_MAXHTPTV1000_E_CMS.s2726_r7676_output.root"
sherpaWjets="$sherpaWjets $INPUT_PATH/user.othrif*364184.Sherpa_221_NNPDF30NNLO_Wtaunu_MAXHTPTV0_70_CVetoBVeto.s2726_r7676_output.root"
sherpaWjets="$sherpaWjets $INPUT_PATH/user.othrif*364185.Sherpa_221_NNPDF30NNLO_Wtaunu_MAXHTPTV0_70_CFilterBVe.s2726_r7676_output.root"
sherpaWjets="$sherpaWjets $INPUT_PATH/user.othrif*364186.Sherpa_221_NNPDF30NNLO_Wtaunu_MAXHTPTV0_70_BFilter.s2726_r7676_output.root"
sherpaWjets="$sherpaWjets $INPUT_PATH/user.othrif*364187.Sherpa_221_NNPDF30NNLO_Wtaunu_MAXHTPTV70_140_CVetoBVe.s2726_r7676_output.root"
sherpaWjets="$sherpaWjets $INPUT_PATH/user.othrif*364188.Sherpa_221_NNPDF30NNLO_Wtaunu_MAXHTPTV70_140_CFilterB.s2726_r7676_output.root"
sherpaWjets="$sherpaWjets $INPUT_PATH/user.othrif*364189.Sherpa_221_NNPDF30NNLO_Wtaunu_MAXHTPTV70_140_BFilter.s2726_r7676_output.root"
sherpaWjets="$sherpaWjets $INPUT_PATH/user.othrif*364190.Sherpa_221_NNPDF30NNLO_Wtaunu_MAXHTPTV140_280_CVetoBV.s2726_r7676_output.root"
sherpaWjets="$sherpaWjets $INPUT_PATH/user.othrif*364191.Sherpa_221_NNPDF30NNLO_Wtaunu_MAXHTPTV140_280_CFilter.s2726_r7676_output.root"  
sherpaWjets="$sherpaWjets $INPUT_PATH/user.othrif*364192.Sherpa_221_NNPDF30NNLO_Wtaunu_MAXHTPTV140_280_BFilter.s2726_r7676_output.root"
sherpaWjets="$sherpaWjets $INPUT_PATH/user.othrif*364193.Sherpa_221_NNPDF30NNLO_Wtaunu_MAXHTPTV280_500_CVetoBV.s2726_r7676_output.root"
sherpaWjets="$sherpaWjets $INPUT_PATH/user.othrif*364194.Sherpa_221_NNPDF30NNLO_Wtaunu_MAXHTPTV280_500_CFilter.s2726_r7676_output.root"
sherpaWjets="$sherpaWjets $INPUT_PATH/user.othrif*364195.Sherpa_221_NNPDF30NNLO_Wtaunu_MAXHTPTV280_500_BFilter.s2726_r7676_output.root"
sherpaWjets="$sherpaWjets $INPUT_PATH/user.othrif*364196.Sherpa_221_NNPDF30NNLO_Wtaunu_MAXHTPTV500_1000.s2726_r7676_output.root"
sherpaWjets="$sherpaWjets $INPUT_PATH/user.othrif*364197.Sherpa_221_NNPDF30NNLO_Wtaunu_MAXHTPTV1000_E_CMS.s2726_r7676_output.root"

###########################################################################################################################
# Z + Jets
###########################################################################################################################

#powhegpythia8Zjets
powhegpythia8Zjets="$INPUT_PATH/user.othrif*361106.PowhegPythia8EvtGen_AZNLOCTEQ6L1_Zee.s2576_r7725_p2879_output.root"
powhegpythia8Zjets="$powhegpythia8Zjets $INPUT_PATH/user.othrif*361107.PowhegPythia8EvtGen_AZNLOCTEQ6L1_Zmumu.s2576_r7725_p2879_output.root"
powhegpythia8Zjets="$powhegpythia8Zjets $INPUT_PATH/user.othrif*361108.PowhegPythia8EvtGen_AZNLOCTEQ6L1_Ztautau*.root"

#sherpaZjets
sherpaZjets="$INPUT_PATH/user.othrif*364100.Sherpa_221_NNPDF30NNLO_Zmumu_MAXHTPTV0_70_CVetoBVeto*.root"
sherpaZjets="$sherpaZjets $INPUT_PATH/user.othrif*364101.Sherpa_221_NNPDF30NNLO_Zmumu_MAXHTPTV0_70_CFilterBVet*.root"
sherpaZjets="$sherpaZjets $INPUT_PATH/user.othrif*364102.Sherpa_221_NNPDF30NNLO_Zmumu_MAXHTPTV0_70_BFilter*.root"
sherpaZjets="$sherpaZjets $INPUT_PATH/user.othrif*364103.Sherpa_221_NNPDF30NNLO_Zmumu_MAXHTPTV70_140_CVetoBVet*.root"
sherpaZjets="$sherpaZjets $INPUT_PATH/user.othrif*364104.Sherpa_221_NNPDF30NNLO_Zmumu_MAXHTPTV70_140_CFilterBV.s2726_r7676_output.root" 
sherpaZjets="$sherpaZjets $INPUT_PATH/user.othrif*364105.Sherpa_221_NNPDF30NNLO_Zmumu_MAXHTPTV70_140_BFilter*.root"
sherpaZjets="$sherpaZjets $INPUT_PATH/user.othrif*364106.Sherpa_221_NNPDF30NNLO_Zmumu_MAXHTPTV140_280_CVetoBVe*.root"
sherpaZjets="$sherpaZjets $INPUT_PATH/user.othrif*364107.Sherpa_221_NNPDF30NNLO_Zmumu_MAXHTPTV140_280_CFilterB*.root"
sherpaZjets="$sherpaZjets $INPUT_PATH/user.othrif*364108.Sherpa_221_NNPDF30NNLO_Zmumu_MAXHTPTV140_280_BFilter*.root"
sherpaZjets="$sherpaZjets $INPUT_PATH/user.othrif*364109.Sherpa_221_NNPDF30NNLO_Zmumu_MAXHTPTV280_500_CVetoBVe*.root"
sherpaZjets="$sherpaZjets $INPUT_PATH/user.othrif*364110.Sherpa_221_NNPDF30NNLO_Zmumu_MAXHTPTV280_500_CFilterB*.root"
sherpaZjets="$sherpaZjets $INPUT_PATH/user.othrif*364111.Sherpa_221_NNPDF30NNLO_Zmumu_MAXHTPTV280_500_BFilter*.root"
sherpaZjets="$sherpaZjets $INPUT_PATH/user.othrif*364112.Sherpa_221_NNPDF30NNLO_Zmumu_MAXHTPTV500_1000*.root"
sherpaZjets="$sherpaZjets $INPUT_PATH/user.othrif*364113.Sherpa_221_NNPDF30NNLO_Zmumu_MAXHTPTV1000_E_CMS*.root"
sherpaZjets="$sherpaZjets $INPUT_PATH/user.othrif*364114.Sherpa_221_NNPDF30NNLO_Zee_MAXHTPTV0_70_CVetoBVeto*.root"
sherpaZjets="$sherpaZjets $INPUT_PATH/user.othrif*364115.Sherpa_221_NNPDF30NNLO_Zee_MAXHTPTV0_70_CFilterBVeto*.root"
sherpaZjets="$sherpaZjets $INPUT_PATH/user.othrif*364116.Sherpa_221_NNPDF30NNLO_Zee_MAXHTPTV0_70_BFilter*.root"
sherpaZjets="$sherpaZjets $INPUT_PATH/user.othrif*364117.Sherpa_221_NNPDF30NNLO_Zee_MAXHTPTV70_140_CVetoBVeto*.root"
sherpaZjets="$sherpaZjets $INPUT_PATH/user.othrif*364118.Sherpa_221_NNPDF30NNLO_Zee_MAXHTPTV70_140_CFilterBVet*.root"
sherpaZjets="$sherpaZjets $INPUT_PATH/user.othrif*364119.Sherpa_221_NNPDF30NNLO_Zee_MAXHTPTV70_140_BFilter*.root"
sherpaZjets="$sherpaZjets $INPUT_PATH/user.othrif*364120.Sherpa_221_NNPDF30NNLO_Zee_MAXHTPTV140_280_CVetoBVeto*.root"
sherpaZjets="$sherpaZjets $INPUT_PATH/user.othrif*364121.Sherpa_221_NNPDF30NNLO_Zee_MAXHTPTV140_280_CFilterBVe*.root"
sherpaZjets="$sherpaZjets $INPUT_PATH/user.othrif*364122.Sherpa_221_NNPDF30NNLO_Zee_MAXHTPTV140_280_BFilter*.root"
sherpaZjets="$sherpaZjets $INPUT_PATH/user.othrif*364123.Sherpa_221_NNPDF30NNLO_Zee_MAXHTPTV280_500_CVetoBVeto*.root"
sherpaZjets="$sherpaZjets $INPUT_PATH/user.othrif*364124.Sherpa_221_NNPDF30NNLO_Zee_MAXHTPTV280_500_CFilterBVe*.root"
sherpaZjets="$sherpaZjets $INPUT_PATH/user.othrif*364125.Sherpa_221_NNPDF30NNLO_Zee_MAXHTPTV280_500_BFilter*.root"
sherpaZjets="$sherpaZjets $INPUT_PATH/user.othrif*364126.Sherpa_221_NNPDF30NNLO_Zee_MAXHTPTV500_1000*.root"
sherpaZjets="$sherpaZjets $INPUT_PATH/user.othrif*364127.Sherpa_221_NNPDF30NNLO_Zee_MAXHTPTV1000_E_CMS*.root"
sherpaZjets="$sherpaZjets $INPUT_PATH/user.othrif*364128.Sherpa_221_NNPDF30NNLO_Ztautau_MAXHTPTV0_70_CVetoBVet*.root"
sherpaZjets="$sherpaZjets $INPUT_PATH/user.othrif*364129.Sherpa_221_NNPDF30NNLO_Ztautau_MAXHTPTV0_70_CFilterBV*.root"
sherpaZjets="$sherpaZjets $INPUT_PATH/user.othrif*364130.Sherpa_221_NNPDF30NNLO_Ztautau_MAXHTPTV0_70_BFilter*.root"
sherpaZjets="$sherpaZjets $INPUT_PATH/user.othrif*364131.Sherpa_221_NNPDF30NNLO_Ztautau_MAXHTPTV70_140_CVetoBV*.root"
sherpaZjets="$sherpaZjets $INPUT_PATH/user.othrif*364132.Sherpa_221_NNPDF30NNLO_Ztautau_MAXHTPTV70_140_CFilter*.root"
sherpaZjets="$sherpaZjets $INPUT_PATH/user.othrif*364133.Sherpa_221_NNPDF30NNLO_Ztautau_MAXHTPTV70_140_BFilter*.root"
sherpaZjets="$sherpaZjets $INPUT_PATH/user.othrif*364134.Sherpa_221_NNPDF30NNLO_Ztautau_MAXHTPTV140_280_CVetoB*.root"
sherpaZjets="$sherpaZjets $INPUT_PATH/user.othrif*364135.Sherpa_221_NNPDF30NNLO_Ztautau_MAXHTPTV140_280_CFilte*.root"
sherpaZjets="$sherpaZjets $INPUT_PATH/user.othrif*364136.Sherpa_221_NNPDF30NNLO_Ztautau_MAXHTPTV140_280_BFilte*.root"
sherpaZjets="$sherpaZjets $INPUT_PATH/user.othrif*364137.Sherpa_221_NNPDF30NNLO_Ztautau_MAXHTPTV280_500_CVetoB*.root"
sherpaZjets="$sherpaZjets $INPUT_PATH/user.othrif*364138.Sherpa_221_NNPDF30NNLO_Ztautau_MAXHTPTV280_500_CFilte*.root"
sherpaZjets="$sherpaZjets $INPUT_PATH/user.othrif*364139.Sherpa_221_NNPDF30NNLO_Ztautau_MAXHTPTV280_500_BFilte*.root"
sherpaZjets="$sherpaZjets $INPUT_PATH/user.othrif*364140.Sherpa_221_NNPDF30NNLO_Ztautau_MAXHTPTV500_1000*.root"
sherpaZjets="$sherpaZjets $INPUT_PATH/user.othrif*364141.Sherpa_221_NNPDF30NNLO_Ztautau_MAXHTPTV1000_E_CMS*.root"

sherpaZjetslowM="$INPUT_PATH/user.othrif*361468.Sherpa_CT10_Zee_Mll10to40_Pt0_70_BVeto.s2608_r7772_p2879_output.root"
sherpaZjetslowM="$sherpaZjetslowM $INPUT_PATH/user.othrif*361469.Sherpa_CT10_Zee_Mll10to40_Pt0_70_BFilter.s2608_r7772_p2879_output.root"
sherpaZjetslowM="$sherpaZjetslowM $INPUT_PATH/user.othrif*361470.Sherpa_CT10_Zee_Mll10to40_Pt70_140_BVeto.s2608_r7772_p2879_output.root"
sherpaZjetslowM="$sherpaZjetslowM $INPUT_PATH/user.othrif*361471.Sherpa_CT10_Zee_Mll10to40_Pt70_140_BFilter.s2608_r7772_p2879_output.root"
sherpaZjetslowM="$sherpaZjetslowM $INPUT_PATH/user.othrif*361472.Sherpa_CT10_Zee_Mll10to40_Pt140_400_BVeto.s2608_r7772_p2879_output.root"
sherpaZjetslowM="$sherpaZjetslowM $INPUT_PATH/user.othrif*361473.Sherpa_CT10_Zee_Mll10to40_Pt140_400_BFilter.s2608_r7772_p2879_output.root"
sherpaZjetslowM="$sherpaZjetslowM $INPUT_PATH/user.othrif*361474.Sherpa_CT10_Zee_Mll10to40_Pt400_E_CMS_BVeto.s2608_r7772_p2879_output.root"
sherpaZjetslowM="$sherpaZjetslowM $INPUT_PATH/user.othrif*361475.Sherpa_CT10_Zee_Mll10to40_Pt400_E_CMS_BFilter.s2608_r7772_p2879_output.root"
sherpaZjetslowM="$sherpaZjetslowM $INPUT_PATH/user.othrif*361476.Sherpa_CT10_Zmumu_Mll10to40_Pt0_70_BVeto.s2608_r7772_p2879_output.root"
sherpaZjetslowM="$sherpaZjetslowM $INPUT_PATH/user.othrif*361477.Sherpa_CT10_Zmumu_Mll10to40_Pt0_70_BFilter.s2608_r7772_p2879_output.root"
sherpaZjetslowM="$sherpaZjetslowM $INPUT_PATH/user.othrif*361478.Sherpa_CT10_Zmumu_Mll10to40_Pt70_140_BVeto.s2608_r7772_p2879_output.root"
sherpaZjetslowM="$sherpaZjetslowM $INPUT_PATH/user.othrif*361479.Sherpa_CT10_Zmumu_Mll10to40_Pt70_140_BFilter.s2608_r7772_p2879_output.root"
sherpaZjetslowM="$sherpaZjetslowM $INPUT_PATH/user.othrif*361480.Sherpa_CT10_Zmumu_Mll10to40_Pt140_400_BVeto.s2608_r7772_p2879_output.root"
sherpaZjetslowM="$sherpaZjetslowM $INPUT_PATH/user.othrif*361481.Sherpa_CT10_Zmumu_Mll10to40_Pt140_400_BFilter.s2608_r7772_p2879_output.root"
sherpaZjetslowM="$sherpaZjetslowM $INPUT_PATH/user.othrif*361482.Sherpa_CT10_Zmumu_Mll10to40_Pt400_E_CMS_BVeto.s2608_r7772_p2879_output.root"
sherpaZjetslowM="$sherpaZjetslowM $INPUT_PATH/user.othrif*361483.Sherpa_CT10_Zmumu_Mll10to40_Pt400_E_CMS_BFilter.s2608_r7772_p2879_output.root"
sherpaZjetslowM="$sherpaZjetslowM $INPUT_PATH/user.othrif*361484.Sherpa_CT10_Ztautau_Mll10to40_Pt0_70_BVeto.s2608_r7772_p2879_output.root"
sherpaZjetslowM="$sherpaZjetslowM $INPUT_PATH/user.othrif*361485.Sherpa_CT10_Ztautau_Mll10to40_Pt0_70_BFilter.s2608_r7772_p2879_output.root"
sherpaZjetslowM="$sherpaZjetslowM $INPUT_PATH/user.othrif*361486.Sherpa_CT10_Ztautau_Mll10to40_Pt70_140_BVeto.s2608_r7772_p2879_output.root"
sherpaZjetslowM="$sherpaZjetslowM $INPUT_PATH/user.othrif*361487.Sherpa_CT10_Ztautau_Mll10to40_Pt70_140_BFilter.s2608_r7772_p2879_output.root"
sherpaZjetslowM="$sherpaZjetslowM $INPUT_PATH/user.othrif*361488.Sherpa_CT10_Ztautau_Mll10to40_Pt140_400_BVeto.s2608_r7772_p2879_output.root"
sherpaZjetslowM="$sherpaZjetslowM $INPUT_PATH/user.othrif*361489.Sherpa_CT10_Ztautau_Mll10to40_Pt140_400_BFilter.s2608_r7772_p2879_output.root"
sherpaZjetslowM="$sherpaZjetslowM $INPUT_PATH/user.othrif*361490.Sherpa_CT10_Ztautau_Mll10to40_Pt400_E_CMS_BVeto.s2608_r7772_p2879_output.root"
sherpaZjetslowM="$sherpaZjetslowM $INPUT_PATH/user.othrif*361491.Sherpa_CT10_Ztautau_Mll10to40_Pt400_E_CMS_BFilter.s2608_r7772_p2879_output.root"


###########################################################################################################################
# Process samples
###########################################################################################################################

printf "\n\nRunning over data...\n\n"
nohup analyze $OUTPUT_FOLDER data $DATA > nohup_data.log &
<<EOF 
nohup analyze $OUTPUT_FOLDER dataA $DATAperiodA > nohup_data.log &
nohup analyze $OUTPUT_FOLDER dataB $DATAperiodB >> nohup_data.log &
nohup analyze $OUTPUT_FOLDER dataC $DATAperiodC >> nohup_data.log &
nohup analyze $OUTPUT_FOLDER dataD $DATAperiodD >> nohup_data.log &
nohup analyze $OUTPUT_FOLDER dataE $DATAperiodE >> nohup_data.log &
nohup analyze $OUTPUT_FOLDER dataF $DATAperiodF >> nohup_data.log &
nohup analyze $OUTPUT_FOLDER dataG $DATAperiodG >> nohup_data.log &
nohup analyze $OUTPUT_FOLDER dataH $DATAperiodH >> nohup_data.log &
nohup analyze $OUTPUT_FOLDER dataI $DATAperiodI >> nohup_data.log &
nohup analyze $OUTPUT_FOLDER dataJ $DATAperiodJ >> nohup_data.log &
nohup analyze $OUTPUT_FOLDER dataK $DATAperiodK >> nohup_data.log &
nohup analyze $OUTPUT_FOLDER dataL $DATAperiodL >> nohup_data.log &
nohup analyze $OUTPUT_FOLDER debugrec $DATAdebug >> nohup_data.log &
EOF
printf "\nDone running over data...\n\n"

printf "Running over MC...\n"

# Main
nohup analyze $OUTPUT_FOLDER ttW $ttW > nohup_bkg.log &
nohup analyze $OUTPUT_FOLDER ttZ $ttZ >> nohup_bkg.log &
nohup analyze $OUTPUT_FOLDER WW $WW >> nohup_bkg.log &
nohup analyze $OUTPUT_FOLDER WZ $WZ  >> nohup_bkg.log &
nohup analyze $OUTPUT_FOLDER ZZ $ZZ >> nohup_bkg.log &
nohup analyze $OUTPUT_FOLDER tth $ttH >> nohup_bkg.log &
nohup analyze $OUTPUT_FOLDER Vh $Wh $Zh >> nohup_bkg.log &
nohup analyze $OUTPUT_FOLDER ttWW $ttWW >> nohup_bkg.log &
nohup analyze $OUTPUT_FOLDER 3t $ttt >> nohup_bkg.log &
nohup analyze $OUTPUT_FOLDER 4t $tttt >> nohup_bkg.log &
nohup analyze $OUTPUT_FOLDER tZ $tZ >> nohup_bkg.log &
nohup analyze $OUTPUT_FOLDER VVV $VVV >> nohup_bkg.log &
nohup analyze $OUTPUT_FOLDER tWZ $tWZ  >> nohup_bkg.log & #$DPS
nohup analyze $OUTPUT_FOLDER ttWZ $ttWZ >> nohup_bkg.log & #$DPS
nohup analyze $OUTPUT_FOLDER otherNP $WWos $Wt $singletop >> nohup_bkg.log  & 

# Benchmark signals
#nohup analyze $OUTPUT_FOLDER GG_ttn1_1200_5000_855 $INPUT_PATH/user.othrif*370122.MGPy8EG_A14N_GG_ttn1_1200_5000_855.*_output*.root >> nohup_bkg.log & # missing

# Sherpa
nohup analyze $OUTPUT_FOLDER sherpaTTBar $sherpaTTBar >> nohup_bkg.log &
nohup analyze $OUTPUT_FOLDER sherpaZjets $sherpaZjets $sherpaZjetslowM >> nohup_bkg.log &
nohup analyze $OUTPUT_FOLDER sherpaWjets $sherpaWjets >> nohup_bkg.log &

# Pythia
nohup analyze $OUTPUT_FOLDER powhegpythia6TTBar $powhegpythia6TTBarHT >> nohup_bkg.log &
nohup analyze $OUTPUT_FOLDER powhegpythia8TTBar $powhegpythia8TTBar >> nohup_bkg.log &
nohup analyze $OUTPUT_FOLDER madgraphpythia8TTBar $madgraphpythia8TTBar >> nohup_bkg.log &
nohup analyze $OUTPUT_FOLDER powhegpythia8Wjets $powhegpythia8Wjets >> nohup_bkg.log &
nohup analyze $OUTPUT_FOLDER powhegpythia8Zjets $powhegpythia8Zjets >> nohup_bkg.log 

<<EOF

cd $OUTPUT_PATH
hadd merged.${OUTPUT_FOLDER}_ximo.root data.root ttW.root ttZ.root WW.root WZ.root ZZ.root tth.root Vh.root ttWW.root 3t.root 4t.root tZ.root VVV.root tWZ.root otherNP.root  powhegpythia6TTBar.root sherpaZjets.root sherpaWjets.root
hadd merged.${OUTPUT_FOLDER}_sherpa.root data.root ttW.root ttZ.root WW.root WZ.root ZZ.root tth.root Vh.root ttWW.root 3t.root 4t.root tZ.root VVV.root tWZ.root otherNP.root sherpaTTBar.root sherpaZjets.root sherpaWjets.root
hadd merged.${OUTPUT_FOLDER}_pythia6.root data.root ttW.root ttZ.root WW.root WZ.root ZZ.root tth.root Vh.root ttWW.root 3t.root 4t.root tZ.root VVV.root tWZ.root otherNP.root powhegpythia6TTBar.root powhegpythia8Zjets.root powhegpythia8Wjets.root
hadd merged.${OUTPUT_FOLDER}_pythia8.root data.root ttW.root ttZ.root WW.root WZ.root ZZ.root tth.root Vh.root ttWW.root 3t.root 4t.root tZ.root VVV.root tWZ.root otherNP.root powhegpythia8TTBar.root powhegpythia8Zjets.root powhegpythia8Wjets.root
hadd merged.${OUTPUT_FOLDER}_madgraph.root data.root ttW.root ttZ.root WW.root WZ.root ZZ.root tth.root Vh.root ttWW.root 3t.root 4t.root tZ.root VVV.root tWZ.root otherNP.root madgraphpythia8TTBar.root powhegpythia8Zjets.root powhegpythia8Wjets.root
cd $loc
EOF
printf "Done running over MC...\n\n"


###############
# sample signal 
###############
<<EOF


printf "Start running over signal...\n\n"


analyze $OUTPUT_FOLDER GG_2stepWZ_1100_800_650_50 $INPUT_PATH/user.othrif*371224.MadGraphPythia8EvtGen_A14N_GG_2stepWZ_1100_800_650_50.*_output*.root
analyze $OUTPUT_FOLDER GG_2stepWZ_800_700_650_600 $INPUT_PATH/user.othrif*371210.MadGraphPythia8EvtGen_A14N_GG_2stepWZ_800_700_650_600.*_output*.root

analyze $OUTPUT_FOLDER GG_ttn1_1200_5000_855 $INPUT_PATH/user.othrif*370122.MGPy8EG_A14N_GG_ttn1_1200_5000_855.*_output*.root
analyze $OUTPUT_FOLDER GG_ttn1_1400_5000_1000 $INPUT_PATH/user.othrif*370135.MGPy8EG_A14N_GG_ttn1_1400_5000_1000.*_output*.root
analyze $OUTPUT_FOLDER GG_ttn1_1400_5000_100 $INPUT_PATH/user.othrif*370130.MGPy8EG_A14N_GG_ttn1_1400_5000_100.*_output*.root

analyze $OUTPUT_FOLDER GG_N2_SLN1_1200_100 $INPUT_PATH/user.othrif*372460.MGPy8EG_A14N23LO_SM_GG_N2_SLN1_1200_100_2L.*_output*.root
analyze $OUTPUT_FOLDER GG_N2_SLN1_1600_100 $INPUT_PATH/user.othrif*372472.MGPy8EG_A14N23LO_SM_GG_N2_SLN1_1600_100_2L.*_output*.root

analyze $OUTPUT_FOLDER BB_onestepC1_550_200_100 $INPUT_PATH/user.othrif*372313.MGPy8EG_A14N_BB_onestepC1_550_200_100_SS2L.*_output*.root
analyze $OUTPUT_FOLDER BB_onestepC1_550_340_240 $INPUT_PATH/user.othrif*372316.MGPy8EG_A14N_BB_onestepC1_550_340_240_SS2L.*_output*.root
analyze $OUTPUT_FOLDER BB_onestepC1_550_375_275 $INPUT_PATH/user.othrif*372317.MGPy8EG_A14N_BB_onestepC1_550_375_275_SS2L.*_output*.root


analyze $OUTPUT_FOLDER DD_Rpvlampp321_2000_400 $INPUT_PATH/user.othrif*403380.MGPy8EG_A14N23LO_DD_Rpvlampp321_2000_400.*_output*.root
analyze $OUTPUT_FOLDER DD_Rpvlampp331_2000_180 $INPUT_PATH/user.othrif*403409.MGPy8EG_A14N23LO_DD_Rpvlampp331_2000_1800.*_output*.root
analyze $OUTPUT_FOLDER GG_Rpvlampp321_400_2000 $INPUT_PATH/user.othrif*403410.MGPy8EG_A14N23LO_GG_Rpvlampp321_400_2000.*_output*.root
analyze $OUTPUT_FOLDER GG_Rpvlampp331_1800_1600 $INPUT_PATH/user.othrif*403481.MGPy8EG_A14N23LO_GG_Rpvlampp331_1800_1600.*_output*.root

analyze $OUTPUT_FOLDER GG_ttn1_700_5000_355_4body $INPUT_PATH/user.othrif*370189.MGPy8EG_A14N23LO_GG_ttn1_700_5000_355_4body.*_output*.root
analyze $OUTPUT_FOLDER GG_ttn1_700_5000_400_4body $INPUT_PATH/user.othrif*370190.MGPy8EG_A14N23LO_GG_ttn1_700_5000_400_4body.*_output*.root
analyze $OUTPUT_FOLDER GG_ttn1_700_5000_465_5body $INPUT_PATH/user.othrif*370192.MGPy8EG_A14N23LO_GG_ttn1_700_5000_465_5body.*_output*.root
analyze $OUTPUT_FOLDER GG_ttn1_800_5000_565_5body $INPUT_PATH/user.othrif*370198.MGPy8EG_A14N23LO_GG_ttn1_800_5000_565_5body.*_output*.root
analyze $OUTPUT_FOLDER GG_ttn1_800_5000_590_5body $INPUT_PATH/user.othrif*370199.MGPy8EG_A14N23LO_GG_ttn1_800_5000_590_5body.*_output*.root
analyze $OUTPUT_FOLDER GG_ttn1_900_5000_555_4body $INPUT_PATH/user.othrif*370200.MGPy8EG_A14N23LO_GG_ttn1_900_5000_555_4body.*_output*.root
analyze $OUTPUT_FOLDER GG_ttn1_900_5000_600_4body $INPUT_PATH/user.othrif*370201.MGPy8EG_A14N23LO_GG_ttn1_900_5000_600_4body.*_output*.root
analyze $OUTPUT_FOLDER GG_ttn1_900_5000_640_4body $INPUT_PATH/user.othrif*370202.MGPy8EG_A14N23LO_GG_ttn1_900_5000_640_4body.*_output*.root
analyze $OUTPUT_FOLDER GG_ttn1_900_5000_690_5body $INPUT_PATH/user.othrif*370204.MGPy8EG_A14N23LO_GG_ttn1_900_5000_690_5body.*_output*.root
analyze $OUTPUT_FOLDER GG_ttn1_1000_5000_655_4body $INPUT_PATH/user.othrif*370205.MGPy8EG_A14N23LO_GG_ttn1_1000_5000_655_4body.*_output*.root
analyze $OUTPUT_FOLDER GG_ttn1_1000_5000_740_4body $INPUT_PATH/user.othrif*370207.MGPy8EG_A14N23LO_GG_ttn1_1000_5000_740_4body.*_output*.root
analyze $OUTPUT_FOLDER GG_ttn1_1000_5000_790_5body $INPUT_PATH/user.othrif*370209.MGPy8EG_A14N23LO_GG_ttn1_1000_5000_790_5body.*_output*.root
analyze $OUTPUT_FOLDER GG_ttn1_1100_5000_755_4body $INPUT_PATH/user.othrif*370210.MGPy8EG_A14N23LO_GG_ttn1_1100_5000_755_4body.*_output*.root
analyze $OUTPUT_FOLDER GG_ttn1_1100_5000_800_4body $INPUT_PATH/user.othrif*370211.MGPy8EG_A14N23LO_GG_ttn1_1100_5000_800_4body.*_output*.root
analyze $OUTPUT_FOLDER GG_ttn1_1100_5000_840_4body $INPUT_PATH/user.othrif*370212.MGPy8EG_A14N23LO_GG_ttn1_1100_5000_840_4body.*_output*.root
analyze $OUTPUT_FOLDER GG_ttn1_1100_5000_890_5body $INPUT_PATH/user.othrif*370214.MGPy8EG_A14N23LO_GG_ttn1_1100_5000_890_5body.*_output*.root
analyze $OUTPUT_FOLDER GG_ttn1_1200_5000_855_4body $INPUT_PATH/user.othrif*370216.MGPy8EG_A14N23LO_GG_ttn1_1200_5000_855_4body.*_output*.root
analyze $OUTPUT_FOLDER GG_ttn1_1200_5000_940_4body $INPUT_PATH/user.othrif*370219.MGPy8EG_A14N23LO_GG_ttn1_1200_5000_940_4body.*_output*.root
analyze $OUTPUT_FOLDER GG_ttn1_1200_5000_965_5body $INPUT_PATH/user.othrif*370220.MGPy8EG_A14N23LO_GG_ttn1_1200_5000_965_5body.*_output*.root
analyze $OUTPUT_FOLDER GG_ttn1_1200_5000_990_5body $INPUT_PATH/user.othrif*370222.MGPy8EG_A14N23LO_GG_ttn1_1200_5000_990_5body.*_output*.root
analyze $OUTPUT_FOLDER GG_ttn1_1300_5000_955_4body $INPUT_PATH/user.othrif*370223.MGPy8EG_A14N23LO_GG_ttn1_1300_5000_955_4body.*_output*.root
analyze $OUTPUT_FOLDER GG_ttn1_1300_5000_1040_4body $INPUT_PATH/user.othrif*370225.MGPy8EG_A14N23LO_GG_ttn1_1300_5000_1040_4body.*_output*.root
analyze $OUTPUT_FOLDER GG_ttn1_1400_5000_1055_4body $INPUT_PATH/user.othrif*370228.MGPy8EG_A14N23LO_GG_ttn1_1400_5000_1055_4body.*_output*.root
analyze $OUTPUT_FOLDER GG_ttn1_1400_5000_1100_4body $INPUT_PATH/user.othrif*370229.MGPy8EG_A14N23LO_GG_ttn1_1400_5000_1100_4body.*_output*.root
analyze $OUTPUT_FOLDER GG_ttn1_1400_5000_1165_5body $INPUT_PATH/user.othrif*370231.MGPy8EG_A14N23LO_GG_ttn1_1400_5000_1165_5body.*_output*.root
analyze $OUTPUT_FOLDER GG_ttn1_1400_5000_1190_5body $INPUT_PATH/user.othrif*370232.MGPy8EG_A14N23LO_GG_ttn1_1400_5000_1190_5body.*_output*.root
analyze $OUTPUT_FOLDER GG_ttn1_1600_5000_1255_4body $INPUT_PATH/user.othrif*370233.MGPy8EG_A14N23LO_GG_ttn1_1600_5000_1255_4body.*_output*.root
analyze $OUTPUT_FOLDER GG_ttn1_1600_5000_1390_5body $INPUT_PATH/user.othrif*370235.MGPy8EG_A14N23LO_GG_ttn1_1600_5000_1390_5body.*_output*.root
analyze $OUTPUT_FOLDER GG_ttn1_1800_5000_1540_4body $INPUT_PATH/user.othrif*370237.MGPy8EG_A14N23LO_GG_ttn1_1800_5000_1540_4body.*_output*.root
EOF

printf "Done running over signal...\n\n"

#WZ Old
#WZold="$INPUT_PATH/user.othrif*361064.Sherpa_CT10_lllvSFMinus*.root"
#WZold="$WZold $INPUT_PATH/user.othrif*361065.Sherpa_CT10_lllvOFMinus*.root"
#WZold="$WZold $INPUT_PATH/user.othrif*361066.Sherpa_CT10_lllvSFPlus*.root"
#WZold="$WZold $INPUT_PATH/user.othrif*361067.Sherpa_CT10_lllvOFPlus*.root"
#WZold="$WZold $INPUT_PATH/user.othrif*361071.Sherpa_CT10_lllvjj_EW6*.root"

#WZ New
#WZ="$INPUT_PATH/user.othrif*344424.Sherpa_CT10_lllvSFMinus_BFilter*.root"
#WZ="$WZ $INPUT_PATH/user.othrif*344425.Sherpa_CT10_lllvSFMinus_BVeto*.root"
#WZ="$WZ $INPUT_PATH/user.othrif*344426.Sherpa_CT10_lllvOFMinus_BFilter*.root"
#WZ="$WZ $INPUT_PATH/user.othrif*344427.Sherpa_CT10_lllvOFMinus_BVeto*.root"
#WZ="$WZ $INPUT_PATH/user.othrif*344428.Sherpa_CT10_lllvSFPlus_BFilter*.root"
#WZ="$WZ $INPUT_PATH/user.othrif*344429.Sherpa_CT10_lllvSFPlus_BVeto*.root"
#WZ="$WZ $INPUT_PATH/user.othrif*344430.Sherpa_CT10_lllvOFPlus_BFilter*.root"
#WZ="$WZ $INPUT_PATH/user.othrif*344431.Sherpa_CT10_lllvOFPlus_BVeto*.root"
#WZ="$WZ $INPUT_PATH/user.othrif*361071.Sherpa_CT10_lllvjj_EW6*.root"

#ZZ Old
#ZZold="$INPUT_PATH/user.othrif*361063.Sherpa_CT10_llll*.root"
#ZZold="$ZZold $INPUT_PATH/user.othrif*361072.Sherpa_CT10_lllljj_EW6*.root"
#ZZold="$ZZold $INPUT_PATH/user.othrif*361073.Sherpa_CT10_ggllll*.root"

#ZZ New
#ZZ="$INPUT_PATH/user.othrif*344422.Sherpa_CT10_llll_BFilter*.root"
#ZZ="$ZZ $INPUT_PATH/user.othrif*344423.Sherpa_CT10_llll_BVeto*.root"
#ZZ="$ZZ $INPUT_PATH/user.othrif*361072.Sherpa_CT10_lllljj_EW6*.root"
#ZZ="$ZZ $INPUT_PATH/user.othrif*361073.Sherpa_CT10_ggllll*.root"

#WWos="$INPUT_PATH/user.othrif*361077.Sherpa_CT10_ggllvv*.root"
#WWos="$WWos $INPUT_PATH/user.othrif*361068.Sherpa_CT10_llvv*.root"

#aMcAtNlowHerwigppTTbar
#aMcAtNlowHerwigppTTbar="$INPUT_PATH/user.othrif*410003.aMcAtNloHerwigppEvtGen_ttbar_nonallhad.s2726_r7676_output.root"

#powhegpythia6TTBarMET
#powhegpythia6TTBarMET="$INPUT_PATH/user.othrif*410000.PowhegPythiaEvtGen_P2012_ttbar_hdamp172p5_nonallhad*.root" # NOT NEEDED
#powhegpythia6TTBarMET="$powhegpythia6TTBarMET $INPUT_PATH/user.othrif*407012.*.root" # NOT NEEDED

#powhegpythia8TTBar
#powhegpythia8TTBar="$INPUT_PATH/user.othrif*410500.PowhegPythia8EvtGen_A14_ttbar_hdamp172p5_nonallhad.s2726_r7676_output.root" # NOT RECOMMENDED

<<EOF
#mgWjets
mgWjets="$INPUT_PATH/user.othrif*361520.MadGraphPythia8EvtGen_A14NNPDF23LO_Wenu_Np0.s2608_r7725_p2613_output*.root"
mgWjets="$mgWjets $INPUT_PATH/user.othrif*361521.MadGraphPythia8EvtGen_A14NNPDF23LO_Wenu_Np1.s2608_r7725_p2613_output*.root"
mgWjets="$mgWjets $INPUT_PATH/user.othrif*361522.MadGraphPythia8EvtGen_A14NNPDF23LO_Wenu_Np2.s2608_r7772_p2613_output*.root"
mgWjets="$mgWjets $INPUT_PATH/user.othrif*361523.MadGraphPythia8EvtGen_A14NNPDF23LO_Wenu_Np3.s2608_r7725_p2613_output*.root"
mgWjets="$mgWjets $INPUT_PATH/user.othrif*361524.MadGraphPythia8EvtGen_A14NNPDF23LO_Wenu_Np4.s2608_r7772_p2613_output*.root"
mgWjets="$mgWjets $INPUT_PATH/user.othrif*361525.MadGraphPythia8EvtGen_A14NNPDF23LO_Wmunu_Np0.s2608_r7725_p2613_output*.root"
mgWjets="$mgWjets $INPUT_PATH/user.othrif*361526.MadGraphPythia8EvtGen_A14NNPDF23LO_Wmunu_Np1.s2608_r7725_p2613_output*.root"
mgWjets="$mgWjets $INPUT_PATH/user.othrif*361527.MadGraphPythia8EvtGen_A14NNPDF23LO_Wmunu_Np2.s2608_r7772_p2613_output*.root"
mgWjets="$mgWjets $INPUT_PATH/user.othrif*361528.MadGraphPythia8EvtGen_A14NNPDF23LO_Wmunu_Np3.s2608_r7725_p2613_output*.root"
mgWjets="$mgWjets $INPUT_PATH/user.othrif*361529.MadGraphPythia8EvtGen_A14NNPDF23LO_Wmunu_Np4.s2608_r7725_p2613_output*.root"
mgWjets="$mgWjets $INPUT_PATH/user.othrif*361530.MadGraphPythia8EvtGen_A14NNPDF23LO_Wtaunu_Np0.s2608_r7772_p2613_output*.root"
mgWjets="$mgWjets $INPUT_PATH/user.othrif*361531.MadGraphPythia8EvtGen_A14NNPDF23LO_Wtaunu_Np1.s2608_r7725_p2613_output*.root"
mgWjets="$mgWjets $INPUT_PATH/user.othrif*361532.MadGraphPythia8EvtGen_A14NNPDF23LO_Wtaunu_Np2.s2608_r7772_p2613_output*.root"
mgWjets="$mgWjets $INPUT_PATH/user.othrif*361533.MadGraphPythia8EvtGen_A14NNPDF23LO_Wtaunu_Np3.s2608_r7725_p2613_output*.root"
mgWjets="$mgWjets $INPUT_PATH/user.othrif*361534.MadGraphPythia8EvtGen_A14NNPDF23LO_Wtaunu_Np4.s2608_r7725_p2613_output*.root"
EOF

<<EOF
mgZjets="$INPUT_PATH/user.othrif*363123.MGPy8EG_N30NLO_Zmumu_Ht0_70_CVetoBVeto.s2726_r7676_output*.root"
mgZjets="$mgZjets $INPUT_PATH/user.othrif*363124.MGPy8EG_N30NLO_Zmumu_Ht0_70_CFilterBVeto.s2726_r7676_output*.root"
mgZjets="$mgZjets $INPUT_PATH/user.othrif*363125.MGPy8EG_N30NLO_Zmumu_Ht0_70_BFilter.s2726_r7676_output*.root"
mgZjets="$mgZjets $INPUT_PATH/user.othrif*363126.MGPy8EG_N30NLO_Zmumu_Ht70_140_CVetoBVeto.s2726_r7676_output*.root"
mgZjets="$mgZjets $INPUT_PATH/user.othrif*363127.MGPy8EG_N30NLO_Zmumu_Ht70_140_CFilterBVeto.s2726_r7676_output*.root"
mgZjets="$mgZjets $INPUT_PATH/user.othrif*363128.MGPy8EG_N30NLO_Zmumu_Ht70_140_BFilter.s2726_r7676_output*.root"
mgZjets="$mgZjets $INPUT_PATH/user.othrif*363129.MGPy8EG_N30NLO_Zmumu_Ht140_280_CVetoBVeto.s2726_r7676_output*.root"
mgZjets="$mgZjets $INPUT_PATH/user.othrif*363130.MGPy8EG_N30NLO_Zmumu_Ht140_280_CFilterBVeto.s2726_r7676_output*.root"
mgZjets="$mgZjets $INPUT_PATH/user.othrif*363131.MGPy8EG_N30NLO_Zmumu_Ht140_280_BFilter.s2726_r7676_output*.root"
mgZjets="$mgZjets $INPUT_PATH/user.othrif*363132.MGPy8EG_N30NLO_Zmumu_Ht280_500_CVetoBVeto.s2726_r7676_output*.root"
mgZjets="$mgZjets $INPUT_PATH/user.othrif*363133.MGPy8EG_N30NLO_Zmumu_Ht280_500_CFilterBVeto.s2726_r7676_output*.root"
mgZjets="$mgZjets $INPUT_PATH/user.othrif*363134.MGPy8EG_N30NLO_Zmumu_Ht280_500_BFilter.s2726_r7676_output*.root"
mgZjets="$mgZjets $INPUT_PATH/user.othrif*363135.MGPy8EG_N30NLO_Zmumu_Ht500_700_CVetoBVeto.s2726_r7676_output*.root"
mgZjets="$mgZjets $INPUT_PATH/user.othrif*363136.MGPy8EG_N30NLO_Zmumu_Ht500_700_CFilterBVeto.s2726_r7676_output*.root"
mgZjets="$mgZjets $INPUT_PATH/user.othrif*363137.MGPy8EG_N30NLO_Zmumu_Ht500_700_BFilter.s2726_r7676_output*.root"
mgZjets="$mgZjets $INPUT_PATH/user.othrif*363138.MGPy8EG_N30NLO_Zmumu_Ht700_1000_CVetoBVeto.s2726_r7676_output*.root"
mgZjets="$mgZjets $INPUT_PATH/user.othrif*363139.MGPy8EG_N30NLO_Zmumu_Ht700_1000_CFilterBVeto.s2726_r7676_output*.root"
mgZjets="$mgZjets $INPUT_PATH/user.othrif*363140.MGPy8EG_N30NLO_Zmumu_Ht700_1000_BFilter.s2726_r7676_output*.root"
mgZjets="$mgZjets $INPUT_PATH/user.othrif*363141.MGPy8EG_N30NLO_Zmumu_Ht1000_2000_CVetoBVeto.s2726_r7676_output*.root"
mgZjets="$mgZjets $INPUT_PATH/user.othrif*363142.MGPy8EG_N30NLO_Zmumu_Ht1000_2000_CFilterBVeto.s2726_r7676_output*.root"
mgZjets="$mgZjets $INPUT_PATH/user.othrif*363143.MGPy8EG_N30NLO_Zmumu_Ht1000_2000_BFilter.s2726_r7676_output*.root"
mgZjets="$mgZjets $INPUT_PATH/user.othrif*363144.MGPy8EG_N30NLO_Zmumu_Ht2000_E_CMS_CVetoBVeto.s2726_r7676_output*.root"
mgZjets="$mgZjets $INPUT_PATH/user.othrif*363145.MGPy8EG_N30NLO_Zmumu_Ht2000_E_CMS_CFilterBVeto.s2726_r7676_output*.root"
mgZjets="$mgZjets $INPUT_PATH/user.othrif*363146.MGPy8EG_N30NLO_Zmumu_Ht2000_E_CMS_BFilter.s2726_r7676_output*.root"
mgZjets="$mgZjets $INPUT_PATH/user.othrif*363147.MGPy8EG_N30NLO_Zee_Ht0_70_CVetoBVeto.s2726_r7676_output*.root"
mgZjets="$mgZjets $INPUT_PATH/user.othrif*363148.MGPy8EG_N30NLO_Zee_Ht0_70_CFilterBVeto.s2726_r7676_output*.root"
mgZjets="$mgZjets $INPUT_PATH/user.othrif*363149.MGPy8EG_N30NLO_Zee_Ht0_70_BFilter.s2726_r7676_output*.root"
mgZjets="$mgZjets $INPUT_PATH/user.othrif*363150.MGPy8EG_N30NLO_Zee_Ht70_140_CVetoBVeto.s2726_r7676_output*.root"
mgZjets="$mgZjets $INPUT_PATH/user.othrif*363151.MGPy8EG_N30NLO_Zee_Ht70_140_CFilterBVeto.s2726_r7676_output*.root"
mgZjets="$mgZjets $INPUT_PATH/user.othrif*363152.MGPy8EG_N30NLO_Zee_Ht70_140_BFilter.s2726_r7676_output*.root"
mgZjets="$mgZjets $INPUT_PATH/user.othrif*363153.MGPy8EG_N30NLO_Zee_Ht140_280_CVetoBVeto.s2726_r7676_output*.root"
mgZjets="$mgZjets $INPUT_PATH/user.othrif*363154.MGPy8EG_N30NLO_Zee_Ht140_280_CFilterBVeto.s2726_r7676_output*.root"
mgZjets="$mgZjets $INPUT_PATH/user.othrif*363155.MGPy8EG_N30NLO_Zee_Ht140_280_BFilter.s2726_r7676_output*.root"
mgZjets="$mgZjets $INPUT_PATH/user.othrif*363156.MGPy8EG_N30NLO_Zee_Ht280_500_CVetoBVeto.s2726_r7676_output*.root"
mgZjets="$mgZjets $INPUT_PATH/user.othrif*363157.MGPy8EG_N30NLO_Zee_Ht280_500_CFilterBVeto.s2726_r7676_output*.root"
mgZjets="$mgZjets $INPUT_PATH/user.othrif*363158.MGPy8EG_N30NLO_Zee_Ht280_500_BFilter.s2726_r7676_output*.root"
mgZjets="$mgZjets $INPUT_PATH/user.othrif*363159.MGPy8EG_N30NLO_Zee_Ht500_700_CVetoBVeto.s2726_r7676_output*.root"
mgZjets="$mgZjets $INPUT_PATH/user.othrif*363160.MGPy8EG_N30NLO_Zee_Ht500_700_CFilterBVeto.s2726_r7676_output*.root"
mgZjets="$mgZjets $INPUT_PATH/user.othrif*363161.MGPy8EG_N30NLO_Zee_Ht500_700_BFilter.s2726_r7676_output*.root"
mgZjets="$mgZjets $INPUT_PATH/user.othrif*363162.MGPy8EG_N30NLO_Zee_Ht700_1000_CVetoBVeto.s2726_r7676_output*.root"
mgZjets="$mgZjets $INPUT_PATH/user.othrif*363163.MGPy8EG_N30NLO_Zee_Ht700_1000_CFilterBVeto.s2726_r7676_output*.root"
mgZjets="$mgZjets $INPUT_PATH/user.othrif*363164.MGPy8EG_N30NLO_Zee_Ht700_1000_BFilter.s2726_r7676_output*.root"
mgZjets="$mgZjets $INPUT_PATH/user.othrif*363165.MGPy8EG_N30NLO_Zee_Ht1000_2000_CVetoBVeto.s2726_r7676_output*.root"
mgZjets="$mgZjets $INPUT_PATH/user.othrif*363166.MGPy8EG_N30NLO_Zee_Ht1000_2000_CFilterBVeto.s2726_r7676_output*.root"
mgZjets="$mgZjets $INPUT_PATH/user.othrif*363167.MGPy8EG_N30NLO_Zee_Ht1000_2000_BFilter.s2726_r7676_output*.root"
mgZjets="$mgZjets $INPUT_PATH/user.othrif*363168.MGPy8EG_N30NLO_Zee_Ht2000_E_CMS_CVetoBVeto.s2726_r7676_output*.root"
mgZjets="$mgZjets $INPUT_PATH/user.othrif*363169.MGPy8EG_N30NLO_Zee_Ht2000_E_CMS_CFilterBVeto.s2726_r7676_output*.root"
mgZjets="$mgZjets $INPUT_PATH/user.othrif*363170.MGPy8EG_N30NLO_Zee_Ht2000_E_CMS_BFilter.s2726_r7676_output*.root"
mgZjets="$mgZjets $INPUT_PATH/user.othrif*361511.MadGraphPythia8EvtGen_A14NNPDF23LO_Ztautau_Np1*.root"
mgZjets="$mgZjets $INPUT_PATH/user.othrif*361514.MadGraphPythia8EvtGen_A14NNPDF23LO_Ztautau_Np4*.root"
mgZjets="$mgZjets $INPUT_PATH/user.othrif*361512.MadGraphPythia8EvtGen_A14NNPDF23LO_Ztautau_Np2*.root"
mgZjets="$mgZjets $INPUT_PATH/user.othrif*361513.MadGraphPythia8EvtGen_A14NNPDF23LO_Ztautau_Np3*.roo"

mgZjetslowM="$INPUT_PATH/user.othrif*361630.MadGraphPythia8EvtGen_A14NNPDF23LO_Zee_lowMll_Np2*.root 
mgZjetslowM="$mgZjetslowM $INPUT_PATH/user.othrif*361632.MadGraphPythia8EvtGen_A14NNPDF23LO_Zee_lowMll_Np4*.root 
mgZjetslowM="$mgZjetslowM $INPUT_PATH/user.othrif*361628.MadGraphPythia8EvtGen_A14NNPDF23LO_Zee_lowMll_Np0*.root 
mgZjetslowM="$mgZjetslowM $INPUT_PATH/user.othrif*361629.MadGraphPythia8EvtGen_A14NNPDF23LO_Zee_lowMll_Np1*.root 
mgZjetslowM="$mgZjetslowM $INPUT_PATH/user.othrif*361631.MadGraphPythia8EvtGen_A14NNPDF23LO_Zee_lowMll_Np3*.root 
mgZjetslowM="$mgZjetslowM $INPUT_PATH/user.othrif*361633.MadGraphPythia8EvtGen_A14NNPDF23LO_Zmumu_lowMll_Np0*.root 
mgZjetslowM="$mgZjetslowM $INPUT_PATH/user.othrif*361634.MadGraphPythia8EvtGen_A14NNPDF23LO_Zmumu_lowMll_Np1*.root 
mgZjetslowM="$mgZjetslowM $INPUT_PATH/user.othrif*361635.MadGraphPythia8EvtGen_A14NNPDF23LO_Zmumu_lowMll_Np2*.root 
mgZjetslowM="$mgZjetslowM $INPUT_PATH/user.othrif*361636.MadGraphPythia8EvtGen_A14NNPDF23LO_Zmumu_lowMll_Np3*.root 
mgZjetslowM="$mgZjetslowM $INPUT_PATH/user.othrif*361637.MadGraphPythia8EvtGen_A14NNPDF23LO_Zmumu_lowMll_Np4*.root 
mgZjetslowM="$mgZjetslowM $INPUT_PATH/user.othrif*361640.MadGraphPythia8EvtGen_A14NNPDF23LO_Ztautau_lowMll_Np2*.root 
mgZjetslowM="$mgZjetslowM $INPUT_PATH/user.othrif*361638.MadGraphPythia8EvtGen_A14NNPDF23LO_Ztautau_lowMll_Np0*.root 
mgZjetslowM="$mgZjetslowM $INPUT_PATH/user.othrif*361642.MadGraphPythia8EvtGen_A14NNPDF23LO_Ztautau_lowMll_Np4*.root 
mgZjetslowM="$mgZjetslowM $INPUT_PATH/user.othrif*361639.MadGraphPythia8EvtGen_A14NNPDF23LO_Ztautau_lowMll_Np1*.root 
mgZjetslowM="$mgZjetslowM $INPUT_PATH/user.othrif*361641.MadGraphPythia8EvtGen_A14NNPDF23LO_Ztautau_lowMll_Np3*.root 
EOF

<<EOF
nohup analyze $OUTPUT_FOLDER TT_2stepTN2_550_340_260_3body $INPUT_PATH_v48/user.othrif*388230.MGPy8EG_A14N23LO_TT_2stepTN2_550_340_260_3body.a766_r7676_output.root >> nohup_bkg.log &
nohup analyze $OUTPUT_FOLDER TT_2stepTN2_550_340_240_2body_2LSS $INPUT_PATH_v48/user.othrif*388232.MGPy8EG_A14N23LO_TT_2stepTN2_550_340_240_2body_2LSS.a766_r7676_output.root >> nohup_bkg.log &
nohup analyze $OUTPUT_FOLDER TT_2stepTN2_550_342_260_2body $INPUT_PATH_v48/user.othrif*388231.MGPy8EG_A14N23LO_TT_2stepTN2_550_342_260_2body.a766_r7676_output.root >> nohup_bkg.log &
nohup analyze $OUTPUT_FOLDER TT_2stepTN2_550_375_275_2body_2LSS $INPUT_PATH_v48/user.othrif*388233.MGPy8EG_A14N23LO_TT_2stepTN2_550_375_275_2body_2LSS.a766_r7676_output.root >> nohup_bkg.log 

# MadGraph+Pythia
#nohup analyze $OUTPUT_FOLDER mgTTBar $madgraphpythia8TTBar >> nohup_bkg.log 
#analyze $OUTPUT_FOLDER mgZjets $mgZjets $mgZjetslowM
#analyze $OUTPUT_FOLDER mgWjets $mgWjets

cd $OUTPUT_PATH
hadd merged.${OUTPUT_FOLDER}_pythia8.root data.root ttW.root ttZ.root WW.root WZ.root ZZ.root tth.root Vh.root ttWW.root 3t.root 4t.root tZ.root VVV.root tWZ.root otherNP.root mgTTBar.root powhegpythia8Zjets.root powhegpythia8Wjets.root
cd $loc

#cd $OUTPUT_PATH
#hadd merged.${OUTPUT_FOLDER}_mg.root data.root ttW.root ttZ.root WW.root WZ.root ZZ.root tth.root Vh.root ttWW.root 3t.root 4t.root tZ.root VVV.root tWZ.root otherNP.root mgTTBar.root mgZjets.root mgWjets.root
#cd $loc

# alternative
nohup analyze $OUTPUT_FOLDER WZold $WZold  >> nohup_bkg.log &
nohup analyze $OUTPUT_FOLDER ZZold $ZZold >> nohup_bkg.log 



cd $OUTPUT_PATH
hadd merged.${OUTPUT_FOLDER}_sherpa_oldVV.root data.root ttW.root ttZ.root WW.root WZold.root ZZold.root tth.root Vh.root ttWW.root 3t.root 4t.root tZ.root VVV.root tWZ.root otherNP.root sherpaTTBar.root sherpaZjets.root sherpaWjets.root
hadd merged.${OUTPUT_FOLDER}_powheg_oldVV.root data.root ttW.root ttZ.root WW.root WZold.root ZZold.root tth.root Vh.root ttWW.root 3t.root 4t.root tZ.root VVV.root tWZ.root otherNP.root powhegpythia6TTBar.root powhegpythia8Zjets.root powhegpythia8Wjets.root
hadd merged.${OUTPUT_FOLDER}_pythia8_oldVV.root data.root ttW.root ttZ.root WW.root WZold.root ZZold.root tth.root Vh.root ttWW.root 3t.root 4t.root tZ.root VVV.root tWZ.root otherNP.root mgTTBar.root powhegpythia8Zjets.root powhegpythia8Wjets.root
cd $loc


EOF