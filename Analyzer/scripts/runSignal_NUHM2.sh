#for i in $(ls MiniNtuple/v28/); do echo $i | awk -F'.' '{print "analyze-v36 $OUTPUT_FOLDER " $3 "." $4 " $INPUT_PATH/"$i}'; done | grep BB  >> runSignal_BB_onestepC1.sh

#!/bin/bash

# Analyze samples according to desired grouping

if ! type -p "analyze-v36" > /dev/null; then
	printf "Setting up the environment...\n"
	source rcSetup.sh
fi

printf "Compiling...\n"
rc compile_pkg myAnalysis

# path to input files
export INPUT_PATH=$PWD/MiniNtuple/v28

# output folder name
if [ $# -eq 0 ]
  then
    printf "\nERROR: No output folder supplied\n\n"
	return # change to exit when not sourcing
fi

export BASE_PATH=$PWD/Results/v28/
mkdir -p $BASE_PATH
export OUTPUT_FOLDER=$1
export OUTPUT_PATH=$PWD/Results/v28/$OUTPUT_FOLDER
mkdir -p $OUTPUT_PATH

analyze-v36 $OUTPUT_FOLDER m300 $INPUT_PATH/user.othrif.m300_output.Strong.root

#<<EOF
analyze-v36 $OUTPUT_FOLDER m350 $INPUT_PATH/user.othrif.m350_output.Strong.root
analyze-v36 $OUTPUT_FOLDER m400 $INPUT_PATH/user.othrif.m400_output.Strong.root
analyze-v36 $OUTPUT_FOLDER m500 $INPUT_PATH/user.othrif.m500_output.Strong.root
analyze-v36 $OUTPUT_FOLDER m600 $INPUT_PATH/user.othrif.m600_output.Strong.root
analyze-v36 $OUTPUT_FOLDER m700 $INPUT_PATH/user.othrif.m700_output.Strong.root
analyze-v36 $OUTPUT_FOLDER m800 $INPUT_PATH/user.othrif.m800_output.Strong.root
#EOF
