
#!/bin/bash

# Analyze samples according to desired grouping

loc=`pwd`

if ! type -p "analyze-2015" > /dev/null; then
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
export BASE_PATH=/afs/cern.ch/work/o/othrif/workarea/results/v37/
mkdir -p $BASE_PATH
export OUTPUT_PATH=/afs/cern.ch/work/o/othrif/workarea/results/v37/$OUTPUT_FOLDER
mkdir -p $OUTPUT_PATH

# path to input files
export INPUT_PATH=/UserDisk2/othrif/data/MiniNtuple/v37

######################
# DATA
######################

## 2016 ##
#DATA="$INPUT_PATH/user.othrif.*.physics_Main*.root"

## 2015 ##

## 2015+2016 ##
DATA="$INPUT_PATH/user.othrif.*.physics_Main*.root"

##
#DATA="$INPUT_PATH/user.othrif.periodD.physics_Main*.root"
#DATA="$DATA $INPUT_PATH/user.othrif.periodE.physics_Main*.root"
#DATA="$DATA $INPUT_PATH/user.othrif.periodF.physics_Main*.root"
#DATA="$DATA $INPUT_PATH/user.othrif.periodG.physics_Main*.root"
#DATA="$DATA $INPUT_PATH/user.othrif.periodH.physics_Main*.root"
#DATA="$DATA $INPUT_PATH/user.othrif.periodJ.physics_Main*.root"

######################
# MC
######################

# All the samples below do produce SS/3L #

#ttW  
ttW="$INPUT_PATH/user.othrif.410066.MadGraphPythia8EvtGen_A14NNPDF23LO_ttW_Np0*.root"
ttW="$ttW $INPUT_PATH/user.othrif.410067.MadGraphPythia8EvtGen_A14NNPDF23LO_ttW_Np1*.root"
ttW="$ttW $INPUT_PATH/user.othrif.410068.MadGraphPythia8EvtGen_A14NNPDF23LO_ttW_Np2*.root"

#ttZ
ttZ="$INPUT_PATH/user.othrif.410111.MadGraphPythia8EvtGen_A14NNPDF23LO_ttee_Np0*.root"
ttZ="$ttZ $INPUT_PATH/user.othrif.410114.MadGraphPythia8EvtGen_A14NNPDF23LO_ttmumu_Np1*.root"
ttZ="$ttZ $INPUT_PATH/user.othrif.410112.MadGraphPythia8EvtGen_A14NNPDF23LO_ttee_Np1*.root"
ttZ="$ttZ $INPUT_PATH/user.othrif.410115.MadGraphPythia8EvtGen_A14NNPDF23LO_tttautau_Np0*.root"
ttZ="$ttZ $INPUT_PATH/user.othrif.410113.MadGraphPythia8EvtGen_A14NNPDF23LO_ttmumu_Np0*.root"
ttZ="$ttZ $INPUT_PATH/user.othrif.410116.MadGraphPythia8EvtGen_A14NNPDF23LO_tttautau_Np1*.root"

#WW
WWa="$INPUT_PATH/user.othrif.361069.Sherpa_CT10_llvvjj_ss_EW4*.root"
WWb="$INPUT_PATH/user.othrif.361070.Sherpa_CT10_llvvjj_ss_EW6*.root"

#WZ
WZ="$INPUT_PATH/user.othrif.361064.Sherpa_CT10_lllvSFMinus*.root"
WZ="$WZ $INPUT_PATH/user.othrif.361065.Sherpa_CT10_lllvOFMinus*.root"
WZ="$WZ $INPUT_PATH/user.othrif.361066.Sherpa_CT10_lllvSFPlus*.root"
WZ="$WZ $INPUT_PATH/user.othrif.361067.Sherpa_CT10_lllvOFPlus*.root"
WZ="$WZ $INPUT_PATH/user.othrif.361071.Sherpa_CT10_lllvjj_EW6*.root"

#ZZ
ZZa="$INPUT_PATH/user.othrif.361063.Sherpa_CT10_llll*.root"
ZZa="$ZZa $INPUT_PATH/user.othrif.361072.Sherpa_CT10_lllljj_EW6*.root"
ZZb="$INPUT_PATH/user.othrif.361073.Sherpa_CT10_ggllll*.root"

#Higgs
ttH="$INPUT_PATH/user.othrif.341177.aMcAtNloHerwigppEvtGen_UEEE5_CTEQ6L1_CT10ME_ttH125_*.root"
ttH="$ttH $INPUT_PATH/user.othrif.341270.aMcAtNloHerwigppEvtGen_UEEE5_CTEQ6L1_CT10ME_ttH125_*.root"
ttH="$ttH $INPUT_PATH/user.othrif.341271.aMcAtNloHerwigppEvtGen_UEEE5_CTEQ6L1_CT10ME_ttH125_*.root"
Wh="$INPUT_PATH/user.othrif.342284.Pythia8EvtGen_A14NNPDF23LO_WH125_inc*.root"
Zh="$INPUT_PATH/user.othrif.342285.Pythia8EvtGen_A14NNPDF23LO_ZH125_inc*.root"

#Rare
tttt="$INPUT_PATH/user.othrif.410080.MadGraphPythia8EvtGen_A14NNPDF23_4topSM*.root"
ttt="$INPUT_PATH/user.othrif.304014.MadGraphPythia8EvtGen_A14NNPDF23_3top_SM*.root"
tZ="$INPUT_PATH/user.othrif.410050.MadGraphPythiaEvtGen_P2012_tZ_4fl_tchan_noAllHad*.root"
ttWW="$INPUT_PATH/user.othrif.410081.MadGraphPythia8EvtGen_A14NNPDF23_ttbarWW*.root"
VVV="$INPUT_PATH/user.othrif.361620.Sherpa_CT10_WWW_3l3v*.root"
VVV="$VVV $INPUT_PATH/user.othrif.361621.Sherpa_CT10_WWZ_4l2v*.root"
VVV="$VVV $INPUT_PATH/user.othrif.361622.Sherpa_CT10_WWZ_2l4v*.root"
VVV="$VVV $INPUT_PATH/user.othrif.361623.Sherpa_CT10_WZZ_5l1v*.root"
VVV="$VVV $INPUT_PATH/user.othrif.361624.Sherpa_CT10_WZZ_3l3v*.root"
VVV="$VVV $INPUT_PATH/user.othrif.361625.Sherpa_CT10_ZZZ_6l0v*.root"
VVV="$VVV $INPUT_PATH/user.othrif.361626.Sherpa_CT10_ZZZ_4l2v*.root"
VVV="$VVV $INPUT_PATH/user.othrif.361627.Sherpa_CT10_ZZZ_2l4v*.root"

# All the samples below do NOT produce SS/3L #

#powhegpythia6TTBar
powhegpythia6TTBar="$INPUT_PATH/user.othrif.410000.PowhegPythiaEvtGen_P2012_ttbar_hdamp172p5_nonallhad*.root"

#powhegpythia6TTBarHT
powhegpythia6TTBarHT="$INPUT_PATH/user.othrif.410000.PowhegPythiaEvtGen_P2012_ttbar_hdamp172p5_nonallhad*.root"
powhegpythia6TTBarHT="$powhegpythia6TTBarHT $INPUT_PATH/user.othrif.407009.PowhegPythiaEvtGen_P2012CT10_ttbarHT6c_1k_hdamp172p5_.*.root" 
powhegpythia6TTBarHT="$powhegpythia6TTBarHT $INPUT_PATH/user.othrif.407011.PowhegPythiaEvtGen_P2012CT10_ttbarHT1k5_hdamp172p5_no.*.root"
powhegpythia6TTBarHT="$powhegpythia6TTBarHT $INPUT_PATH/user.othrif.407010.PowhegPythiaEvtGen_P2012CT10_ttbarHT1k_1k5_hdamp172p5.*.root"

#singletop
singletop="$INPUT_PATH/user.othrif.410011.PowhegPythiaEvtGen_P2012_singletop_tchan_lept_top*.root"
singletop="$singletop $INPUT_PATH/user.othrif.410012.PowhegPythiaEvtGen_P2012_singletop_tchan_lept_antitop*.root"

#powhegpythiaWjets
powhegpythia8Wjets="$INPUT_PATH/user.othrif.361100.PowhegPythia8EvtGen_AZNLOCTEQ6L1_Wplusenu*.root"
powhegpythia8Wjets="$powhegpythia8Wjets $INPUT_PATH/user.othrif.361101.PowhegPythia8EvtGen_AZNLOCTEQ6L1_Wplusmunu*.root"
powhegpythia8Wjets="$powhegpythia8Wjets $INPUT_PATH/user.othrif.361102.PowhegPythia8EvtGen_AZNLOCTEQ6L1_Wplustaunu*.root"
powhegpythia8Wjets="$powhegpythia8Wjets $INPUT_PATH/user.othrif.361103.PowhegPythia8EvtGen_AZNLOCTEQ6L1_Wminusenu*.root"
powhegpythia8Wjets="$powhegpythia8Wjets $INPUT_PATH/user.othrif.361104.PowhegPythia8EvtGen_AZNLOCTEQ6L1_Wminusmunu*.root"
powhegpythia8Wjets="$powhegpythia8Wjets $INPUT_PATH/user.othrif.361105.PowhegPythia8EvtGen_AZNLOCTEQ6L1_Wminustaunu*.root"

#WWos
WWos="$INPUT_PATH/user.othrif.361077.Sherpa_CT10_ggllvv*.root"
WWos="$WWos $INPUT_PATH/user.othrif.361068.Sherpa_CT10_llvv*.root"

#Wt
Wt="$INPUT_PATH/user.othrif.410015.PowhegPythiaEvtGen_P2012_Wt_dilepton_top*.root"
Wt="$Wt $INPUT_PATH/user.othrif.410016.PowhegPythiaEvtGen_P2012_Wt_dilepton_antitop*.root"

#powhegpythia8Zjets
powhegpythia8Zjets="$INPUT_PATH/user.othrif.361106.PowhegPythia8EvtGen_AZNLOCTEQ6L1_Zee*.root"
powhegpythia8Zjets="$powhegpythia8Zjets $INPUT_PATH/user.othrif.361107.PowhegPythia8EvtGen_AZNLOCTEQ6L1_Zmumu*.root"
powhegpythia8Zjets="$powhegpythia8Zjets $INPUT_PATH/user.othrif.361108.PowhegPythia8EvtGen_AZNLOCTEQ6L1_Ztautau*.root"

###########################################################################################################################
#Spare

#powhegpythia8TTBar
#powhegpythia8TTBar="$INPUT_PATH/user.othrif.410006.PowhegPythia8EvtGen_A14_ttbar_hdamp172p5_nonallhad*.root"

#sherpaTTBar
sherpaTTBar="$INPUT_PATH/user.othrif.410022.Sherpa_CT10_ttbar_SingleLeptonP_MEPS_NLO*.root"
sherpaTTBar="$SherpaTTBar $INPUT_PATH/user.othrif.410023.Sherpa_CT10_ttbar_SingleLeptonM_MEPS_NLO*.root"

#sherpaZjetsHF = BFilter
sherpaZjetsHF="$INPUT_PATH/user.othrif.361383.Sherpa_CT10_Zee_Pt280_500_BFilter.*_output.root"
sherpaZjetsHF="$sherpaZjetsHF $INPUT_PATH/user.othrif.361437.Sherpa_CT10_Ztautau_Pt700_1000_BFilter.*_output.root"
sherpaZjetsHF="$sherpaZjetsHF $INPUT_PATH/user.othrif.361386.Sherpa_CT10_Zee_Pt500_700_BFilter.*_output.root"
sherpaZjetsHF="$sherpaZjetsHF $INPUT_PATH/user.othrif.361440.Sherpa_CT10_Ztautau_Pt1000_2000_BFilter.*_output.root"
sherpaZjetsHF="$sherpaZjetsHF $INPUT_PATH/user.othrif.361389.Sherpa_CT10_Zee_Pt700_1000_BFilter.*_output.root"
sherpaZjetsHF="$sherpaZjetsHF $INPUT_PATH/user.othrif.361443.Sherpa_CT10_Ztautau_Pt2000_E_CMS_BFilter.*_output.root"
sherpaZjetsHF="$sherpaZjetsHF $INPUT_PATH/user.othrif.361392.Sherpa_CT10_Zee_Pt1000_2000_BFilter.*_output.root"
sherpaZjetsHF="$sherpaZjetsHF $INPUT_PATH/user.othrif.361469.Sherpa_CT10_Zee_Mll10to40_Pt0_70_BFilter.*_output.root"
sherpaZjetsHF="$sherpaZjetsHF $INPUT_PATH/user.othrif.361395.Sherpa_CT10_Zee_Pt2000_E_CMS_BFilter.*_output.root"
sherpaZjetsHF="$sherpaZjetsHF $INPUT_PATH/user.othrif.361471.Sherpa_CT10_Zee_Mll10to40_Pt70_140_BFilter.*_output.root"
sherpaZjetsHF="$sherpaZjetsHF $INPUT_PATH/user.othrif.361407.Sherpa_CT10_Zmumu_Pt280_500_BFilter.*_output.root"
sherpaZjetsHF="$sherpaZjetsHF $INPUT_PATH/user.othrif.361473.Sherpa_CT10_Zee_Mll10to40_Pt140_400_BFilter.*_output.root"
sherpaZjetsHF="$sherpaZjetsHF $INPUT_PATH/user.othrif.361410.Sherpa_CT10_Zmumu_Pt500_700_BFilter.*_output.root"
sherpaZjetsHF="$sherpaZjetsHF $INPUT_PATH/user.othrif.361475.Sherpa_CT10_Zee_Mll10to40_Pt400_E_CMS_BFilter.*_output.root"
sherpaZjetsHF="$sherpaZjetsHF $INPUT_PATH/user.othrif.361413.Sherpa_CT10_Zmumu_Pt700_1000_BFilter.*_output.root"
sherpaZjetsHF="$sherpaZjetsHF $INPUT_PATH/user.othrif.361477.Sherpa_CT10_Zmumu_Mll10to40_Pt0_70_BFilter.*_output.root"
sherpaZjetsHF="$sherpaZjetsHF $INPUT_PATH/user.othrif.361416.Sherpa_CT10_Zmumu_Pt1000_2000_BFilter.*_output.root"
sherpaZjetsHF="$sherpaZjetsHF $INPUT_PATH/user.othrif.361479.Sherpa_CT10_Zmumu_Mll10to40_Pt70_140_BFilter.*_output.root"
sherpaZjetsHF="$sherpaZjetsHF $INPUT_PATH/user.othrif.361419.Sherpa_CT10_Zmumu_Pt2000_E_CMS_BFilter.*_output.root"
sherpaZjetsHF="$sherpaZjetsHF $INPUT_PATH/user.othrif.361481.Sherpa_CT10_Zmumu_Mll10to40_Pt140_400_BFilter.*_output.root"
sherpaZjetsHF="$sherpaZjetsHF $INPUT_PATH/user.othrif.361422.Sherpa_CT10_Ztautau_Pt0_70_BFilter.*_output.root"
sherpaZjetsHF="$sherpaZjetsHF $INPUT_PATH/user.othrif.361483.Sherpa_CT10_Zmumu_Mll10to40_Pt400_E_CMS_BFilter.*_output.root"
sherpaZjetsHF="$sherpaZjetsHF $INPUT_PATH/user.othrif.361425.Sherpa_CT10_Ztautau_Pt70_140_BFilter.*_output.root"
sherpaZjetsHF="$sherpaZjetsHF $INPUT_PATH/user.othrif.361485.Sherpa_CT10_Ztautau_Mll10to40_Pt0_70_BFilter.*_output.root"
sherpaZjetsHF="$sherpaZjetsHF $INPUT_PATH/user.othrif.361428.Sherpa_CT10_Ztautau_Pt140_280_BFilter.*_output.root"
sherpaZjetsHF="$sherpaZjetsHF $INPUT_PATH/user.othrif.361487.Sherpa_CT10_Ztautau_Mll10to40_Pt70_140_BFilter.*_output.root"
sherpaZjetsHF="$sherpaZjetsHF $INPUT_PATH/user.othrif.361431.Sherpa_CT10_Ztautau_Pt280_500_BFilter.*_output.root"
sherpaZjetsHF="$sherpaZjetsHF $INPUT_PATH/user.othrif.361489.Sherpa_CT10_Ztautau_Mll10to40_Pt140_400_BFilter.*_output.root"
sherpaZjetsHF="$sherpaZjetsHF $INPUT_PATH/user.othrif.361434.Sherpa_CT10_Ztautau_Pt500_700_BFilter.*_output.root"
sherpaZjetsHF="$sherpaZjetsHF $INPUT_PATH/user.othrif.361491.Sherpa_CT10_Ztautau_Mll10to40_Pt400_E_CMS_BFilter.*_output.root"

#sherpaZjetsLF = CVetoBVeto CFilterBVeto
sherpaZjetsLF="$INPUT_PATH/user.othrif.361382.Sherpa_CT10_Zee_Pt280_500_CFilterBVeto.*_output.root"
sherpaZjetsLF="$sherpaZjetsLF $INPUT_PATH/user.othrif.361418.Sherpa_CT10_Zmumu_Pt2000_E_CMS_CFilterBVeto.*_output.root"
sherpaZjetsLF="$sherpaZjetsLF $INPUT_PATH/user.othrif.361385.Sherpa_CT10_Zee_Pt500_700_CFilterBVeto.*_output.root"
sherpaZjetsLF="$sherpaZjetsLF $INPUT_PATH/user.othrif.361421.Sherpa_CT10_Ztautau_Pt0_70_CFilterBVeto.*_output.root"
sherpaZjetsLF="$sherpaZjetsLF $INPUT_PATH/user.othrif.361388.Sherpa_CT10_Zee_Pt700_1000_CFilterBVeto.*_output.root"
sherpaZjetsLF="$sherpaZjetsLF $INPUT_PATH/user.othrif.361424.Sherpa_CT10_Ztautau_Pt70_140_CFilterBVeto.*_output.root"
sherpaZjetsLF="$sherpaZjetsLF $INPUT_PATH/user.othrif.361391.Sherpa_CT10_Zee_Pt1000_2000_CFilterBVeto.*_output.root"
sherpaZjetsLF="$sherpaZjetsLF $INPUT_PATH/user.othrif.361427.Sherpa_CT10_Ztautau_Pt140_280_CFilterBVeto.*_output.root"
sherpaZjetsLF="$sherpaZjetsLF $INPUT_PATH/user.othrif.361394.Sherpa_CT10_Zee_Pt2000_E_CMS_CFilterBVeto.*_output.root"
sherpaZjetsLF="$sherpaZjetsLF $INPUT_PATH/user.othrif.361430.Sherpa_CT10_Ztautau_Pt280_500_CFilterBVeto.*_output.root"
sherpaZjetsLF="$sherpaZjetsLF $INPUT_PATH/user.othrif.361406.Sherpa_CT10_Zmumu_Pt280_500_CFilterBVeto.*_output.root"
sherpaZjetsLF="$sherpaZjetsLF $INPUT_PATH/user.othrif.361433.Sherpa_CT10_Ztautau_Pt500_700_CFilterBVeto.*_output.root"
sherpaZjetsLF="$sherpaZjetsLF $INPUT_PATH/user.othrif.361409.Sherpa_CT10_Zmumu_Pt500_700_CFilterBVeto.*_output.root"
sherpaZjetsLF="$sherpaZjetsLF $INPUT_PATH/user.othrif.361436.Sherpa_CT10_Ztautau_Pt700_1000_CFilterBVeto.*_output.root"
sherpaZjetsLF="$sherpaZjetsLF $INPUT_PATH/user.othrif.361412.Sherpa_CT10_Zmumu_Pt700_1000_CFilterBVeto.*_output.root"
sherpaZjetsLF="$sherpaZjetsLF $INPUT_PATH/user.othrif.361439.Sherpa_CT10_Ztautau_Pt1000_2000_CFilterBVeto.*_output.root"
sherpaZjetsLF="$sherpaZjetsLF $INPUT_PATH/user.othrif.361415.Sherpa_CT10_Zmumu_Pt1000_2000_CFilterBVeto.*_output.root"
sherpaZjetsLF="$sherpaZjetsLF $INPUT_PATH/user.othrif.361442.Sherpa_CT10_Ztautau_Pt2000_E_CMS_CFilterBVeto.*_output.root"
sherpaZjetsLF="$sherpaZjetsLF $INPUT_PATH/user.othrif.361381.Sherpa_CT10_Zee_Pt280_500_CVetoBVeto.*_output.root"
sherpaZjetsLF="$sherpaZjetsLF $INPUT_PATH/user.othrif.361417.Sherpa_CT10_Zmumu_Pt2000_E_CMS_CVetoBVeto.*_output.root"
sherpaZjetsLF="$sherpaZjetsLF $INPUT_PATH/user.othrif.361384.Sherpa_CT10_Zee_Pt500_700_CVetoBVeto.*_output.root"
sherpaZjetsLF="$sherpaZjetsLF $INPUT_PATH/user.othrif.361423.Sherpa_CT10_Ztautau_Pt70_140_CVetoBVeto.*_output.root"
sherpaZjetsLF="$sherpaZjetsLF $INPUT_PATH/user.othrif.361387.Sherpa_CT10_Zee_Pt700_1000_CVetoBVeto.*_output.root"
sherpaZjetsLF="$sherpaZjetsLF $INPUT_PATH/user.othrif.361426.Sherpa_CT10_Ztautau_Pt140_280_CVetoBVeto.*_output.root"
sherpaZjetsLF="$sherpaZjetsLF $INPUT_PATH/user.othrif.361390.Sherpa_CT10_Zee_Pt1000_2000_CVetoBVeto.*_output.root"
sherpaZjetsLF="$sherpaZjetsLF $INPUT_PATH/user.othrif.361429.Sherpa_CT10_Ztautau_Pt280_500_CVetoBVeto.*_output.root"
sherpaZjetsLF="$sherpaZjetsLF $INPUT_PATH/user.othrif.361393.Sherpa_CT10_Zee_Pt2000_E_CMS_CVetoBVeto.*_output.root"
sherpaZjetsLF="$sherpaZjetsLF $INPUT_PATH/user.othrif.361432.Sherpa_CT10_Ztautau_Pt500_700_CVetoBVeto.*_output.root"
sherpaZjetsLF="$sherpaZjetsLF $INPUT_PATH/user.othrif.361405.Sherpa_CT10_Zmumu_Pt280_500_CVetoBVeto.*_output.root"
sherpaZjetsLF="$sherpaZjetsLF $INPUT_PATH/user.othrif.361435.Sherpa_CT10_Ztautau_Pt700_1000_CVetoBVeto.*_output.root"
sherpaZjetsLF="$sherpaZjetsLF $INPUT_PATH/user.othrif.361408.Sherpa_CT10_Zmumu_Pt500_700_CVetoBVeto.*_output.root"
sherpaZjetsLF="$sherpaZjetsLF $INPUT_PATH/user.othrif.361438.Sherpa_CT10_Ztautau_Pt1000_2000_CVetoBVeto.*_output.root"
sherpaZjetsLF="$sherpaZjetsLF $INPUT_PATH/user.othrif.361411.Sherpa_CT10_Zmumu_Pt700_1000_CVetoBVeto.*_output.root"
sherpaZjetsLF="$sherpaZjetsLF $INPUT_PATH/user.othrif.361441.Sherpa_CT10_Ztautau_Pt2000_E_CMS_CVetoBVeto.*_output.root"
sherpaZjetsLF="$sherpaZjetsLF $INPUT_PATH/user.othrif.361414.Sherpa_CT10_Zmumu_Pt1000_2000_CVetoBVeto.*_output.root"
sherpaZjetsLF="$sherpaZjetsLF $INPUT_PATH/user.othrif.361468.Sherpa_CT10_Zee_Mll10to40_Pt0_70_BVeto.*_output.root       "
sherpaZjetsLF="$sherpaZjetsLF $INPUT_PATH/user.othrif.361480.Sherpa_CT10_Zmumu_Mll10to40_Pt140_400_BVeto.*_output.root"
sherpaZjetsLF="$sherpaZjetsLF $INPUT_PATH/user.othrif.361470.Sherpa_CT10_Zee_Mll10to40_Pt70_140_BVeto.*_output.root     "
sherpaZjetsLF="$sherpaZjetsLF $INPUT_PATH/user.othrif.361482.Sherpa_CT10_Zmumu_Mll10to40_Pt400_E_CMS_BVeto.*_output.root"
sherpaZjetsLF="$sherpaZjetsLF $INPUT_PATH/user.othrif.361472.Sherpa_CT10_Zee_Mll10to40_Pt140_400_BVeto.*_output.root    "
sherpaZjetsLF="$sherpaZjetsLF $INPUT_PATH/user.othrif.361486.Sherpa_CT10_Ztautau_Mll10to40_Pt70_140_BVeto.*_output.root"
sherpaZjetsLF="$sherpaZjetsLF $INPUT_PATH/user.othrif.361474.Sherpa_CT10_Zee_Mll10to40_Pt400_E_CMS_BVeto.*_output.root  "
sherpaZjetsLF="$sherpaZjetsLF $INPUT_PATH/user.othrif.361488.Sherpa_CT10_Ztautau_Mll10to40_Pt140_400_BVeto.*_output.root"
sherpaZjetsLF="$sherpaZjetsLF $INPUT_PATH/user.othrif.361476.Sherpa_CT10_Zmumu_Mll10to40_Pt0_70_BVeto.*_output.root     "
sherpaZjetsLF="$sherpaZjetsLF $INPUT_PATH/user.othrif.361490.Sherpa_CT10_Ztautau_Mll10to40_Pt400_E_CMS_BVeto.*_output.root"


printf "\n\nRunning over data...\n\n"
analyze-2015 $OUTPUT_FOLDER data $DATA
printf "\nDone running over data...\n\n"

printf "Running over MC...\n"
analyze-2015 $OUTPUT_FOLDER background $ttW $ttZ $WZ $ttH $Wh $Zh $ttWW $ttt $tttt $tZ $VVV $powhegpythia6TTBar $singletop $powhegpythia8Zjets $powhegpythia8Wjets $WWos $Wt $WWb $ZZb 

analyze-2015 $OUTPUT_FOLDER mc15a $WWa $ZZa

printf "Done running over MC...\n\n"
