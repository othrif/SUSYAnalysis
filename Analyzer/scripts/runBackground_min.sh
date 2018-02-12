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
export INPUT_PATH=/UserDisk2/othrif/data/MiniNtuple/v52
export INPUT_PATH_v48=/UserDisk2/othrif/data/MiniNtuple/v48_0
export INPUT_PATH_test=/UserDisk2/othrif/data/MiniNtuple/test

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
WW="$WW $INPUT_PATH/user.othrif*361070.Sherpa_CT10_llvvjj_ss_EW6*.root"

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



###########################################################################################################################
# Process samples
###########################################################################################################################

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
