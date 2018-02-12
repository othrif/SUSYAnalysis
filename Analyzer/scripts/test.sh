
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
export BASE_PATH=/afs/cern.ch/work/o/othrif/workarea/results/v39/
mkdir -p $BASE_PATH
export OUTPUT_PATH=/afs/cern.ch/work/o/othrif/workarea/results/v39/$OUTPUT_FOLDER
mkdir -p $OUTPUT_PATH

# path to input files
export INPUT_PATH=/UserDisk2/othrif/data/MiniNtuple/v39

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
ttW410066="$INPUT_PATH/user.othrif.410066.MadGraphPythia8EvtGen_A14NNPDF23LO_ttW_Np0*.root"
ttW410067="$INPUT_PATH/user.othrif.410067.MadGraphPythia8EvtGen_A14NNPDF23LO_ttW_Np1*.root"
ttW410068="$INPUT_PATH/user.othrif.410068.MadGraphPythia8EvtGen_A14NNPDF23LO_ttW_Np2*.root"

#ttZ
ttZ410111="$INPUT_PATH/user.othrif.410111.MadGraphPythia8EvtGen_A14NNPDF23LO_ttee_Np0*.root"
ttZ410114="$INPUT_PATH/user.othrif.410114.MadGraphPythia8EvtGen_A14NNPDF23LO_ttmumu_Np1*.root"
ttZ410112="$INPUT_PATH/user.othrif.410112.MadGraphPythia8EvtGen_A14NNPDF23LO_ttee_Np1*.root"
ttZ410115="$INPUT_PATH/user.othrif.410115.MadGraphPythia8EvtGen_A14NNPDF23LO_tttautau_Np0*.root"
ttZ410113="$INPUT_PATH/user.othrif.410113.MadGraphPythia8EvtGen_A14NNPDF23LO_ttmumu_Np0*.root"
ttZ410116="$INPUT_PATH/user.othrif.410116.MadGraphPythia8EvtGen_A14NNPDF23LO_tttautau_Np1*.root"

#WW
WW361069="$INPUT_PATH/user.othrif.361069.Sherpa_CT10_llvvjj_ss_EW4*.root"
WW361070="$INPUT_PATH/user.othrif.361070.Sherpa_CT10_llvvjj_ss_EW6*.root"

#WZ
WZ361064="$INPUT_PATH/user.othrif.361064.Sherpa_CT10_lllvSFMinus*.root"
WZ361065="$INPUT_PATH/user.othrif.361065.Sherpa_CT10_lllvOFMinus*.root"
WZ361066="$INPUT_PATH/user.othrif.361066.Sherpa_CT10_lllvSFPlus*.root"
WZ361067="$INPUT_PATH/user.othrif.361067.Sherpa_CT10_lllvOFPlus*.root"
WZ361071="$INPUT_PATH/user.othrif.361071.Sherpa_CT10_lllvjj_EW6*.root"

#ZZ
ZZ361063="$INPUT_PATH/user.othrif.361063.Sherpa_CT10_llll*.root"
ZZ361072="$INPUT_PATH/user.othrif.361072.Sherpa_CT10_lllljj_EW6*.root"
ZZ361073="$INPUT_PATH/user.othrif.361073.Sherpa_CT10_ggllll*.root"

#Higgs
ttH341177="$INPUT_PATH/user.othrif.341177.aMcAtNloHerwigppEvtGen_UEEE5_CTEQ6L1_CT10ME_ttH125_*.root"
ttH341270="$INPUT_PATH/user.othrif.341270.aMcAtNloHerwigppEvtGen_UEEE5_CTEQ6L1_CT10ME_ttH125_*.root"
ttH341271="$INPUT_PATH/user.othrif.341271.aMcAtNloHerwigppEvtGen_UEEE5_CTEQ6L1_CT10ME_ttH125_*.root"
Wh342284="$INPUT_PATH/user.othrif.342284.Pythia8EvtGen_A14NNPDF23LO_WH125_inc*.root"
Zh342285="$INPUT_PATH/user.othrif.342285.Pythia8EvtGen_A14NNPDF23LO_ZH125_inc*.root"

#Rare
tttt410080="$INPUT_PATH/user.othrif.410080.MadGraphPythia8EvtGen_A14NNPDF23_4topSM*.root"
ttt304014="$INPUT_PATH/user.othrif.304014.MadGraphPythia8EvtGen_A14NNPDF23_3top_SM*.root"
tZ410050="$INPUT_PATH/user.othrif.410050.MadGraphPythiaEvtGen_P2012_tZ_4fl_tchan_noAllHad*.root"
ttWW410081="$INPUT_PATH/user.othrif.410081.MadGraphPythia8EvtGen_A14NNPDF23_ttbarWW*.root"
VVV361620="$INPUT_PATH/user.othrif.361620.Sherpa_CT10_WWW_3l3v*.root"
VVV361621="$INPUT_PATH/user.othrif.361621.Sherpa_CT10_WWZ_4l2v*.root"
VVV361622="$INPUT_PATH/user.othrif.361622.Sherpa_CT10_WWZ_2l4v*.root"
VVV361623="$INPUT_PATH/user.othrif.361623.Sherpa_CT10_WZZ_5l1v*.root"
VVV361624="$INPUT_PATH/user.othrif.361624.Sherpa_CT10_WZZ_3l3v*.root"
VVV361625="$INPUT_PATH/user.othrif.361625.Sherpa_CT10_ZZZ_6l0v*.root"
VVV361626="$INPUT_PATH/user.othrif.361626.Sherpa_CT10_ZZZ_4l2v*.root"
VVV361627="$INPUT_PATH/user.othrif.361627.Sherpa_CT10_ZZZ_2l4v*.root"

tWZ410215="$INPUT_PATH/user.othrif.410215.aMcAtNloPythia8EvtGen_A14_NNPDF23LO_260000_tWZDR.s2726_r7676_output.root"

# All the samples below do NOT produce SS/3L #

#powhegpythia6TTBarALL
powhegpythia6TTBarALL410000="$INPUT_PATH/user.othrif.410000.PowhegPythiaEvtGen_P2012_ttbar_hdamp172p5_nonallhad*.root"
powhegpythia6TTBarALL="$powhegpythia6TTBarALL $INPUT_PATH/user.othrif.407009.PowhegPythiaEvtGen_P2012CT10_ttbarHT6c_1k_hdamp172p5_.*.root" 
powhegpythia6TTBarALL="$powhegpythia6TTBarALL $INPUT_PATH/user.othrif.407011.PowhegPythiaEvtGen_P2012CT10_ttbarHT1k5_hdamp172p5_no.*.root"
powhegpythia6TTBarALL="$powhegpythia6TTBarALL $INPUT_PATH/user.othrif.407010.PowhegPythiaEvtGen_P2012CT10_ttbarHT1k_1k5_hdamp172p5.*.root"
powhegpythia6TTBarALL="$powhegpythia6TTBarALL $INPUT_PATH/user.othrif.407012.*.root" 

#powhegpythia6TTBar
powhegpythia6TTBar="$INPUT_PATH/user.othrif.410000.PowhegPythiaEvtGen_P2012_ttbar_hdamp172p5_nonallhad*.root"

#powhegpythia6TTBarHT
powhegpythia6TTBarHT="$INPUT_PATH/user.othrif.410000.PowhegPythiaEvtGen_P2012_ttbar_hdamp172p5_nonallhad*.root"
powhegpythia6TTBarHT="$powhegpythia6TTBarHT $INPUT_PATH/user.othrif.407009.PowhegPythiaEvtGen_P2012CT10_ttbarHT6c_1k_hdamp172p5_.*.root" 
powhegpythia6TTBarHT="$powhegpythia6TTBarHT $INPUT_PATH/user.othrif.407011.PowhegPythiaEvtGen_P2012CT10_ttbarHT1k5_hdamp172p5_no.*.root"
powhegpythia6TTBarHT="$powhegpythia6TTBarHT $INPUT_PATH/user.othrif.407010.PowhegPythiaEvtGen_P2012CT10_ttbarHT1k_1k5_hdamp172p5.*.root"

#powhegpythia6TTBarMET
powhegpythia6TTBarMET="$INPUT_PATH/user.othrif.410000.PowhegPythiaEvtGen_P2012_ttbar_hdamp172p5_nonallhad*.root"
powhegpythia6TTBarMET="$powhegpythia6TTBarMET $INPUT_PATH/user.othrif.407012.*.root" 

#singletop
singletop="$INPUT_PATH/user.othrif.410011.PowhegPythiaEvtGen_P2012_singletop_tchan_lept_top*.root"
singletop="$singletop $INPUT_PATH/user.othrif.410012.PowhegPythiaEvtGen_P2012_singletop_tchan_lept_antitop*.root"

#powhegpythiaWjets
powhegpythia8Wjets361100="$INPUT_PATH/user.othrif.361100.PowhegPythia8EvtGen_AZNLOCTEQ6L1_Wplusenu*.root"
powhegpythia8Wjets361101="$INPUT_PATH/user.othrif.361101.PowhegPythia8EvtGen_AZNLOCTEQ6L1_Wplusmunu*.root"
powhegpythia8Wjets361102="$INPUT_PATH/user.othrif.361102.PowhegPythia8EvtGen_AZNLOCTEQ6L1_Wplustaunu*.root"
powhegpythia8Wjets361103="$INPUT_PATH/user.othrif.361103.PowhegPythia8EvtGen_AZNLOCTEQ6L1_Wminusenu*.root"
powhegpythia8Wjets361104="$INPUT_PATH/user.othrif.361104.PowhegPythia8EvtGen_AZNLOCTEQ6L1_Wminusmunu*.root"
powhegpythia8Wjets361105="$INPUT_PATH/user.othrif.361105.PowhegPythia8EvtGen_AZNLOCTEQ6L1_Wminustaunu*.root"

#WWos
WWos="$INPUT_PATH/user.othrif.361077.Sherpa_CT10_ggllvv*.root"
WWos="$WWos $INPUT_PATH/user.othrif.361068.Sherpa_CT10_llvv*.root"

#Wt
Wt="$INPUT_PATH/user.othrif.410015.PowhegPythiaEvtGen_P2012_Wt_dilepton_top*.root"
Wt="$Wt $INPUT_PATH/user.othrif.410016.PowhegPythiaEvtGen_P2012_Wt_dilepton_antitop*.root"

#powhegpythia8Zjets
powhegpythia8Zjets361106="$INPUT_PATH/user.othrif.361106.PowhegPythia8EvtGen_AZNLOCTEQ6L1_Zee*.root"
powhegpythia8Zjets361107="$INPUT_PATH/user.othrif.361107.PowhegPythia8EvtGen_AZNLOCTEQ6L1_Zmumu*.root"
powhegpythia8Zjets361108="$INPUT_PATH/user.othrif.361108.PowhegPythia8EvtGen_AZNLOCTEQ6L1_Ztautau*.root"

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


#printf "\n\nRunning over data...\n\n"
#analyze $OUTPUT_FOLDER data $DATA
#printf "\nDone running over data...\n\n"


analyze-test $OUTPUT_FOLDER ttW410066 $ttW410066
analyze-test $OUTPUT_FOLDER ttW410067 $ttW410067
analyze-test $OUTPUT_FOLDER ttW410068 $ttW410068
analyze-test $OUTPUT_FOLDER ttZ410111 $ttZ410111
analyze-test $OUTPUT_FOLDER ttZ410114 $ttZ410114
analyze-test $OUTPUT_FOLDER ttZ410112 $ttZ410112
analyze-test $OUTPUT_FOLDER ttZ410115 $ttZ410115
analyze-test $OUTPUT_FOLDER ttZ410113 $ttZ410113
analyze-test $OUTPUT_FOLDER ttZ410116 $ttZ410116
analyze-test $OUTPUT_FOLDER WW361069 $WW361069
analyze-test $OUTPUT_FOLDER WW361070 $WW361070
analyze-test $OUTPUT_FOLDER WZ361064 $WZ361064
analyze-test $OUTPUT_FOLDER WZ361065 $WZ361065
analyze-test $OUTPUT_FOLDER WZ361066 $WZ361066
analyze-test $OUTPUT_FOLDER WZ361067 $WZ361067
analyze-test $OUTPUT_FOLDER WZ361071 $WZ361071
analyze-test $OUTPUT_FOLDER ZZ361063 $ZZ361063
analyze-test $OUTPUT_FOLDER ZZ361072 $ZZ361072
analyze-test $OUTPUT_FOLDER ZZ361073 $ZZ361073
analyze-test $OUTPUT_FOLDER ttH341177 $ttH341177
analyze-test $OUTPUT_FOLDER ttH341270 $ttH341270
analyze-test $OUTPUT_FOLDER ttH341271 $ttH341271
analyze-test $OUTPUT_FOLDER Wh342284 $Wh342284
analyze-test $OUTPUT_FOLDER Zh342285 $Zh342285
analyze-test $OUTPUT_FOLDER tttt410080 $tttt410080
analyze-test $OUTPUT_FOLDER ttt304014 $ttt304014
analyze-test $OUTPUT_FOLDER tZ410050 $tZ410050
analyze-test $OUTPUT_FOLDER ttWW410081 $ttWW410081
analyze-test $OUTPUT_FOLDER VVV361620 $VVV361620
analyze-test $OUTPUT_FOLDER VVV361621 $VVV361621
analyze-test $OUTPUT_FOLDER VVV361622 $VVV361622
analyze-test $OUTPUT_FOLDER VVV361623 $VVV361623
analyze-test $OUTPUT_FOLDER VVV361624 $VVV361624
analyze-test $OUTPUT_FOLDER VVV361625 $VVV361625
analyze-test $OUTPUT_FOLDER VVV361626 $VVV361626
analyze-test $OUTPUT_FOLDER VVV361627 $VVV361627
analyze-test $OUTPUT_FOLDER tWZ410215 $tWZ410215
analyze-test $OUTPUT_FOLDER powhegpythia6TTBarALL410000 $powhegpythia6TTBarALL410000


analyze-test $OUTPUT_FOLDER powhegpythia8Wjets361100 $powhegpythia8Wjets361100
analyze-test $OUTPUT_FOLDER powhegpythia8Wjets361101 $powhegpythia8Wjets361101
analyze-test $OUTPUT_FOLDER powhegpythia8Wjets361102 $powhegpythia8Wjets361102
analyze-test $OUTPUT_FOLDER powhegpythia8Wjets361103 $powhegpythia8Wjets361103
analyze-test $OUTPUT_FOLDER powhegpythia8Wjets361104 $powhegpythia8Wjets361104
analyze-test $OUTPUT_FOLDER powhegpythia8Wjets361105 $powhegpythia8Wjets361105
analyze-test $OUTPUT_FOLDER powhegpythia8Zjets361106 $powhegpythia8Zjets361106
analyze-test $OUTPUT_FOLDER powhegpythia8Zjets361107 $powhegpythia8Zjets361107
analyze-test $OUTPUT_FOLDER powhegpythia8Zjets361108 $powhegpythia8Zjets361108