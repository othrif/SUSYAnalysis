
#!/bin/bash

# Analyze samples according to desired grouping

loc=`pwd`

if ! type -p "analyze" > /dev/null; then
	printf "Setting up the environment...\n"
	source rcSetup.sh
fi

printf "Compiling...\n"
rc compile

# path to input files
export INPUT_PATH=/UserDisk2/othrif/data/MiniNtuple/v37

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


bb_650_400_300="$INPUT_PATH/user.othrif.372327.MGPy8EG_A14N_BB_onestepC1_650_400_300_SS2L.a766_r7676_output.root"
bb_700_150_50="$INPUT_PATH/user.othrif.372330.MGPy8EG_A14N_BB_onestepC1_700_150_50_SS2L.a766_r7676_output.root"
ttn1_1300_5000_945="$INPUT_PATH/user.othrif.370128.MGPy8EG_A14N_GG_ttn1_1300_5000_945.s2608_r7676_output.root"
ttn1_1400_5000_1="$INPUT_PATH/user.othrif.370129.MGPy8EG_A14N_GG_ttn1_1400_5000_1.s2608_r7676_output.root"
ttn1_1400_5000_800="$INPUT_PATH/user.othrif.370134.MGPy8EG_A14N_GG_ttn1_1400_5000_800.s2608_r7676_output.root"
TwostepWZ_1000_900_850_80="$INPUT_PATH/user.othrif.371221.MadGraphPythia8EvtGen_A14N_GG_2stepWZ_1000_900_850_80.a766_r7676_output.root"
TwostepWZ_1300_1000_850_7="$INPUT_PATH/user.othrif.371243.MadGraphPythia8EvtGen_A14N_GG_2stepWZ_1300_1000_850_7.a766_r7676_output.root"
TwostepWZ_1500_800_450_10="$INPUT_PATH/user.othrif.371255.MadGraphPythia8EvtGen_A14N_GG_2stepWZ_1500_800_450_10.a766_r7676_output.root"
N2_SLN1_1400_1100="$INPUT_PATH/user.othrif.372471.MGPy8EG_A14N23LO_SM_GG_N2_SLN1_1400_1100_2L.a766_r7676_output.root"
N2_SLN1_800_720="$INPUT_PATH/user.othrif.372508.MGPy8EG_A14N23LO_SM_GG_N2_SLN1_800_720_2L.a766_r7676_output.root"

printf "\n\nRunning over signal...\n\n"
analyze $OUTPUT_FOLDER bb_650_400_300 $bb_650_400_300
analyze $OUTPUT_FOLDER bb_700_150_50 $bb_700_150_50
analyze $OUTPUT_FOLDER ttn1_1300_5000_945 $ttn1_1300_5000_945
analyze $OUTPUT_FOLDER ttn1_1400_5000_1 $ttn1_1400_5000_1
analyze $OUTPUT_FOLDER ttn1_1400_5000_800 $ttn1_1400_5000_800
analyze $OUTPUT_FOLDER TwostepWZ_1000_900_850_80 $TwostepWZ_1000_900_850_80
analyze $OUTPUT_FOLDER TwostepWZ_1300_1000_850_7 $TwostepWZ_1300_1000_850_7
analyze $OUTPUT_FOLDER TwostepWZ_1500_800_450_10 $TwostepWZ_1500_800_450_10
analyze $OUTPUT_FOLDER N2_SLN1_1400_1100 $N2_SLN1_1400_1100
analyze $OUTPUT_FOLDER N2_SLN1_800_720 $N2_SLN1_800_720
printf "\nDone running over signal...\n\n"

